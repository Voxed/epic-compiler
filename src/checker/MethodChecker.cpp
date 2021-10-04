#include "MethodChecker.hpp"

#include "ast/Clone.hpp"
#include "checker/StatementChecker.hpp"
#include "common/Exceptions.hpp"
#include "common/TypeDeducer.hpp"

namespace checker {

MethodChecker::MethodChecker(State* state)
  : state(state)
  , annotated(nullptr)
  , ast::BaseVisitor("MethodChecker")
{}

void
MethodChecker::visitMField(parser::MField* p)
{
    annotated = ast::Clone(p);
}
void
MethodChecker::visitMFun(parser::MFun* p)
{
    State newState(state);
    newState.SetReturnType(ast::Clone(p->type_));

    // Add argument to variable table
    for (parser::Arg* arg : *p->listarg_) {
        auto* concrete = static_cast<parser::ADecl*>(arg);
        newState.PutVariable(concrete->ident_, ast::Clone(concrete->type_));
    }

    // Check all statements
    auto* stmList = new parser::ListStm;
    for (parser::Stm* stm : *p->liststm_) {
        stmList->push_back(StatementChecker::Visit(&newState, stm));
    }

    if (!common::CompareType(newState.GetReturnType(), common::VOID) && !newState.GetDoesReturn()) {
        throw common::CheckerException("All paths don't return in function");
    }

    annotated = new parser::MFun(ast::Clone(p->type_), p->ident_, ast::Clone(p->listarg_), stmList);
}

parser::Member*
MethodChecker::Visit(State* state, parser::Member* p)
{
    MethodChecker checker(state);
    p->accept(&checker);
    return checker.annotated;
}

} // namespace checker