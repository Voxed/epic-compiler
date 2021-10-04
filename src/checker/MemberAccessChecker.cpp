#include "MemberAccessChecker.hpp"

#include "ast/Clone.hpp"
#include "ast/Print.hpp"
#include "checker/ExpressionChecker.hpp"
#include "common/Exceptions.hpp"

namespace checker {

void
MemberAccessChecker::visitEVar(parser::EVar* p)
{
    if (hideFields) {
        throw common::CheckerException("Fields are marked private");
    }
    annotated = new parser::ETyped(
      ast::Clone(p), ast::Clone(classDescriptor->GetField(p->ident_)), static_cast<parser::Char>(writable));
}
void
MemberAccessChecker::visitEInt(parser::EInt* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitEDouble(parser::EDouble* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitELitTrue(parser::ELitTrue* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitELitFalse(parser::ELitFalse* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitEApp(parser::EApp* p)
{
    if (hideMethods) {
        throw common::CheckerException("Methods are marked private");
    }
    parser::TFun* funType = classDescriptor->GetMethod(p->ident_);

    if (p->listexp_->size() != funType->listtype_->size()) {
        throw common::CheckerException("Wrong amount of arguments in function call, expected " +
                                       std::to_string(funType->listtype_->size()) + " got " +
                                       std::to_string(p->listexp_->size()));
    }
    auto* newListExpr = new parser::ListExp();
    for (size_t i = 0; i < funType->listtype_->size(); i++) {
        parser::ETyped* typed = ExpressionChecker::Visit(state, (*p->listexp_)[i], (*funType->listtype_)[i]);

        newListExpr->push_back(typed);
    }

    annotated = new parser::ETyped(new parser::EApp(p->ident_, newListExpr), ast::Clone(funType->type_), 0);
}
void
MemberAccessChecker::visitEString(parser::EString* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitENeg(parser::ENeg* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitENot(parser::ENot* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitEMul(parser::EMul* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitEAdd(parser::EAdd* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitERel(parser::ERel* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitEAnd(parser::EAnd* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitEOr(parser::EOr* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitETyped(parser::ETyped* p)
{
    wrongExpression(p);
}

void
MemberAccessChecker::visitEAllocate(parser::EAllocate* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitEDot(parser::EDot* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitEIndex(parser::EIndex* p)
{
    wrongExpression(p);
}

void
MemberAccessChecker::visitEDeref(parser::EDeref* p)
{
    wrongExpression(p);
}
void
MemberAccessChecker::visitENull(parser::ENull* p)
{
    wrongExpression(p);
}

MemberAccessChecker::MemberAccessChecker(ClassDescriptor* classDescriptor,
  State* state,
  bool writable,
  bool hideMethods,
  bool hideFields)
  : classDescriptor(classDescriptor)
  , annotated(nullptr)
  , state(state)
  , writable(writable)
  , hideMethods(hideMethods)
  , hideFields(hideFields)
  , ast::BaseVisitor("MemberAccessChecker")
{}

parser::ETyped*
MemberAccessChecker::Visit(ClassDescriptor* classDescriptor,
  State* state,
  parser::Exp* exp,
  bool writable,
  bool hideMethods,
  bool hideFields)
{
    MemberAccessChecker expChecker(classDescriptor, state, writable, hideMethods, hideFields);
    exp->accept(&expChecker);
    return expChecker.annotated;
}

void
MemberAccessChecker::wrongExpression(parser::Exp* p)
{
    throw common::CheckerException("Expected member got " + ast::Print(p));
}

} // namespace checker