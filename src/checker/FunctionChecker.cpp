#include "FunctionChecker.hpp"

#include "ast/Clone.hpp"
#include "checker/IdentTypeChecker.hpp"
#include "checker/StatementChecker.hpp"
#include "common/Exceptions.hpp"
#include "common/TypeDeducer.hpp"
#include "parser/Absyn.H"

namespace checker {

FunctionChecker::FunctionChecker(State* state)
  : state(state)
  , annotated(nullptr)
  , ast::BaseVisitor("FunctionChecker")
{}

void
FunctionChecker::visitDFun(parser::DFun* p)
{
    parser::Type* type = IdentTypeChecker::Visit(state, p->type_);

    State newState(state);
    newState.SetReturnType(type);

    // Add argument to variable table
    auto* annotatedArgs = new parser::ListArg;
    for (parser::Arg* arg : *p->listarg_) {
        auto* concrete = static_cast<parser::ADecl*>(arg);
        parser::Type* type = IdentTypeChecker::Visit(state, concrete->type_);
        newState.PutVariable(concrete->ident_, ast::Clone(type));
        auto* annotated = new parser::ADecl(type, concrete->ident_);
        annotatedArgs->push_back(annotated);
    }

    // Check all statements
    auto* stmList = new parser::ListStm;
    for (parser::Stm* stm : *p->liststm_) {
        stmList->push_back(StatementChecker::Visit(&newState, stm));
    }

    if (!common::CompareType(newState.GetReturnType(), common::VOID) && !newState.GetDoesReturn()) {
        throw common::CheckerException("All paths don't return in function");
    }

    annotated = new parser::DFun(ast::Clone(newState.GetReturnType()), p->ident_, annotatedArgs, stmList);
}

void
FunctionChecker::visitDPointer(parser::DPointer* p)
{
    annotated = ast::Clone(p);
}

void
FunctionChecker::visitDStruct(parser::DStruct* p)
{
    annotated = ast::Clone(p);
}

void
FunctionChecker::visitDInlinePointer(parser::DInlinePointer* p)
{
    annotated = ast::Clone(p);
}

void
FunctionChecker::visitDClass(parser::DClass* p)
{
    annotated = ast::Clone(p);
}

void
FunctionChecker::visitDSubclass(parser::DSubclass* p)
{
    annotated = ast::Clone(p);
}

parser::Def*
FunctionChecker::Visit(State* state, parser::Def* def)
{
    FunctionChecker checker(state);
    def->accept(&checker);
    return checker.annotated;
}

} // namespace checker