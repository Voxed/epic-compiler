#include "StatementChecker.hpp"

#include "ast/Clone.hpp"
#include "ast/Print.hpp"
#include "checker/DeclaratorChecker.hpp"
#include "checker/ExpressionChecker.hpp"
#include "checker/IdentTypeChecker.hpp"
#include "checker/State.hpp"
#include "common/BoolLitDeducer.hpp"
#include "common/Exceptions.hpp"
#include "common/TypeDeducer.hpp"
#include "parser/Absyn.H"

namespace checker {

StatementChecker::StatementChecker(State* state)
  : state(state)
  , annotated(nullptr)
  , ast::BaseVisitor("StatementChecker")
{}

void
StatementChecker::visitSEmpty(parser::SEmpty* /*p*/)
{
    annotated = new parser::SEmpty;
}

void
StatementChecker::visitSBlock(parser::SBlock* p)
{
    State newState(state);

    auto* stmList = new parser::ListStm;
    for (parser::Stm* stm : *p->liststm_) {
        stmList->push_back(StatementChecker::Visit(&newState, stm));
    }

    if (newState.GetDoesReturn()) {
        state->SetDoesReturn();
    }

    annotated = new parser::SBlock(stmList);
}

void
StatementChecker::visitSDecl(parser::SDecl* p)
{
    parser::Type* type = IdentTypeChecker::Visit(state, p->type_);

    if (common::CompareType(type, common::STRUCT)) {
        throw common::CheckerException("Cannot declare " + ast::Print(type));
    }

    auto* decList = new parser::ListDec;
    for (parser::Dec* dec : *p->listdec_) {
        decList->push_back(DeclaratorChecker::Visit(state, type, dec));
    }

    annotated = new parser::SDecl(type, decList);
}

void
StatementChecker::visitSAss(parser::SAss* p)
{
    parser::ETyped* typed = ExpressionChecker::Visit(state, p->exp_1);

    if (typed->char_ == 0) {
        throw common::CheckerException("Attempted to assign to rvalue");
    }

    parser::ETyped* typed2 = ExpressionChecker::Visit(state, p->exp_2, typed->type_);

    annotated = new parser::SAss(typed, typed2);
}

void
StatementChecker::visitSIncr(parser::SIncr* p)
{
    parser::ETyped* typed = ExpressionChecker::Visit(state, p->exp_);

    if (typed->char_ == 0) {
        throw common::CheckerException("Attempted to increment to rvalue");
    }

    if (!common::CompareType(typed->type_, common::DOUBLE) && !common::CompareType(typed->type_, common::INT)) {
        throw common::CheckerException("Attempted to increment " + ast::Print(typed->type_));
    }

    annotated = new parser::SIncr(typed);
}

void
StatementChecker::visitSDecr(parser::SDecr* p)
{
    parser::ETyped* typed = ExpressionChecker::Visit(state, p->exp_);

    if (typed->char_ == 0) {
        throw common::CheckerException("Attempted to decrement to rvalue");
    }

    if (!common::CompareType(typed->type_, common::DOUBLE) && !common::CompareType(typed->type_, common::INT)) {
        throw common::CheckerException("Attempted to decrement " + ast::Print(typed->type_));
    }

    annotated = new parser::SDecr(typed);
}

void
StatementChecker::visitSRet(parser::SRet* p)
{
    state->SetDoesReturn();
    parser::ETyped* annotatedExp = ExpressionChecker::Visit(state, p->exp_, state->GetReturnType());
    annotated = new parser::SRet(ExpressionChecker::Visit(state, p->exp_, state->GetReturnType()));
}

void
StatementChecker::visitSVRet(parser::SVRet* /*p*/)
{
    state->SetDoesReturn();

    if (!common::CompareType(state->GetReturnType(), common::VOID)) {
        throw common::CheckerException(
          "Type mismatch in return, expected " + ast::Print(state->GetReturnType()) + "got void");
    }

    annotated = new parser::SVRet();
}

void
StatementChecker::visitSCond(parser::SCond* p)
{
    State newState(state);
    parser::Stm* annotatedStm = StatementChecker::Visit(&newState, p->stm_);

    common::BoolLitDeducerResult result = common::BoolLitDeducer::Visit(p->exp_);
    if (result.IsBoolLit() && result.GetValue() && newState.GetDoesReturn()) {
        state->SetDoesReturn();
    }

    auto* boolT = new parser::TBool;
    parser::ETyped* annotatedExp = ExpressionChecker::Visit(state, p->exp_, boolT);
    ast::Destroy(boolT);

    annotated = new parser::SCond(annotatedExp, annotatedStm);
}

void
StatementChecker::visitSCondElse(parser::SCondElse* p)
{
    State trueState(state);
    State falseState(state);
    StatementChecker trueStatementChecker(&trueState);
    StatementChecker falseStatementChecker(&falseState);

    parser::Stm* trueAnnotatedStm = StatementChecker::Visit(&trueState, p->stm_1);
    parser::Stm* falseAnnotatedStm = StatementChecker::Visit(&falseState, p->stm_2);

    common::BoolLitDeducerResult result = common::BoolLitDeducer::Visit(p->exp_);
    if (result.IsBoolLit()) {
        if ((result.GetValue() && trueState.GetDoesReturn()) || (!result.GetValue() && falseState.GetDoesReturn())) {
            state->SetDoesReturn();
        }
    } else if (falseState.GetDoesReturn() && trueState.GetDoesReturn()) {
        state->SetDoesReturn();
    }

    auto* boolT = new parser::TBool;
    parser::ETyped* annotatedExp = ExpressionChecker::Visit(state, p->exp_, boolT);
    ast::Destroy(boolT);

    annotated = new parser::SCondElse(annotatedExp, trueAnnotatedStm, falseAnnotatedStm);
}

void
StatementChecker::visitSWhile(parser::SWhile* p)
{
    State newState(state);

    parser::Stm* annotatedStm = StatementChecker::Visit(&newState, p->stm_);

    common::BoolLitDeducerResult result = common::BoolLitDeducer::Visit(p->exp_);
    if (result.IsBoolLit() && result.GetValue()) {
        state->SetDoesReturn();
    }

    auto* boolT = new parser::TBool;
    parser::ETyped* annotatedExp = ExpressionChecker::Visit(state, p->exp_, boolT);
    ast::Destroy(boolT);

    annotated = new parser::SWhile(annotatedExp, annotatedStm);
}

void
StatementChecker::visitSExp(parser::SExp* p)
{
    parser::ETyped* annotatedExp = ExpressionChecker::Visit(state, p->exp_);

    if (!common::CompareType(annotatedExp->type_, common::VOID)) {
        throw common::CheckerException("Unused expression return");
    }

    annotated = new parser::SExp(annotatedExp);
}

void
StatementChecker::visitSForEach(parser::SForEach* p)
{
    parser::Type* type = IdentTypeChecker::Visit(state, p->type_);

    State newState(state);
    newState.PutVariable(p->ident_, ast::Clone(type));

    auto* arrayT = new parser::TArray(ast::Clone(type));
    parser::ETyped* typed = ExpressionChecker::Visit(state, p->exp_, arrayT);
    ast::Destroy(arrayT);

    parser::Stm* annotatedStm = StatementChecker::Visit(&newState, p->stm_);

    annotated = new parser::SForEach(type, p->ident_, typed, annotatedStm);
}

parser::Stm*
StatementChecker::Visit(State* state, parser::Stm* stm)
{
    StatementChecker checker(state);
    stm->accept(&checker);
    return checker.annotated;
}

} // namespace checker