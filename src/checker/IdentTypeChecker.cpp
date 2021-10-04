#include "IdentTypeChecker.hpp"

#include "ast/Clone.hpp"
#include "checker/State.hpp"

namespace checker {

IdentTypeChecker::IdentTypeChecker(State* state)
  : state(state)
  , type(nullptr)
  , ast::BaseVisitor("IdentTypeChecker")
{}

void
IdentTypeChecker::visitTIdent(parser::TIdent* p)
{
    type = ast::Clone(state->GetType(p->ident_));
}
void
IdentTypeChecker::visitTInt(parser ::TInt* /*p*/)
{
    type = new parser::TInt;
}
void
IdentTypeChecker::visitTDouble(parser ::TDouble* /*p*/)
{
    type = new parser::TDouble;
}
void
IdentTypeChecker::visitTBool(parser ::TBool* /*p*/)
{
    type = new parser::TBool;
}
void
IdentTypeChecker::visitTVoid(parser ::TVoid* /*p*/)
{
    type = new parser::TVoid;
}
void
IdentTypeChecker::visitTArray(parser ::TArray* p)
{
    type = new parser::TArray(IdentTypeChecker::Visit(state, p->type_));
}

parser::Type*
IdentTypeChecker::Visit(State* state, parser::Type* type)
{
    IdentTypeChecker checker(state);
    type->accept(&checker);
    return checker.type;
}

} // namespace checker