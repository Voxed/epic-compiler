#include "TopDecChecker.hpp"

#include "ast/Clone.hpp"
#include "checker/IdentTypeChecker.hpp"
#include "parser/Absyn.H"

namespace checker {

TopDecChecker::TopDecChecker(State* state)
  : state(state)
  , ast::BaseVisitor("TopDecChecker")
{}

void
TopDecChecker::visitDFun(parser::DFun* p)
{
    auto* argTypes = new parser::ListType;

    for (parser::Arg* arg : *p->listarg_) {
        auto* concrete = static_cast<parser::ADecl*>(arg);
        parser::Type* type = IdentTypeChecker::Visit(state, concrete->type_);

        argTypes->push_back(type);
    }

    parser::Type* type = IdentTypeChecker::Visit(state, p->type_);

    auto* func = new parser::TFun(type, argTypes);

    state->PutFunction(p->ident_, func);
}

void
TopDecChecker::visitDPointer(parser::DPointer* p)
{
    state->PutType(p->ident_2, new parser::TPointer(p->ident_1));
}

void
TopDecChecker::visitDInlinePointer(parser::DInlinePointer* p)
{
    auto* concrete = static_cast<parser::SStruct*>(p->struct_);
    state->PutType(concrete->ident_, new parser::TStruct(concrete->ident_));
    state->PutType(p->ident_, new parser::TPointer(concrete->ident_));
}

void
TopDecChecker::visitDStruct(parser::DStruct* p)
{
    auto* concrete = static_cast<parser::SStruct*>(p->struct_);
    state->PutType(concrete->ident_, new parser::TStruct(concrete->ident_));
}

void
TopDecChecker::visitDClass(parser::DClass* p)
{
    state->PutType(p->ident_, new parser::TClass(p->ident_));
}

void
TopDecChecker::visitDSubclass(parser::DSubclass* p)
{
    state->PutType(p->ident_1, new parser::TClass(p->ident_1));
}

void
TopDecChecker::Visit(State* state, parser::Def* def)
{
    TopDecChecker topDecChecker(state);
    def->accept(&topDecChecker);
}

} // namespace checker