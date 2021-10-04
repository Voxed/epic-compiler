#include "DeclaratorChecker.hpp"

#include "ast/Clone.hpp"
#include "checker/ExpressionChecker.hpp"
#include "parser/Absyn.H"

namespace checker {

DeclaratorChecker::DeclaratorChecker(State* state, parser::Type* type)
  : state(state)
  , type(type)
  , annotated(nullptr)
  , ast::BaseVisitor("DeclaratorChecker")
{}

void
DeclaratorChecker::visitDecNoInit(parser::DecNoInit* p)
{
    state->PutVariable(p->ident_, ast::Clone(type));
    annotated = new parser::DecNoInit(p->ident_);
}

void
DeclaratorChecker::visitDecInit(parser::DecInit* p)
{
    parser::ETyped* typed = ExpressionChecker::Visit(state, p->exp_, type);

    state->PutVariable(p->ident_, ast::Clone(type));
    annotated = new parser::DecInit(p->ident_, typed);
}

parser::Dec*
DeclaratorChecker::Visit(State* state, parser::Type* type, parser::Dec* dec)
{
    DeclaratorChecker checker(state, type);
    dec->accept(&checker);
    return checker.annotated;
}

} // namespace checker