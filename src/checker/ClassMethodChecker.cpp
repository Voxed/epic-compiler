#include "ClassMethodChecker.hpp"

#include "ast/Clone.hpp"
#include "checker/MethodChecker.hpp"

namespace checker {

ClassMethodChecker::ClassMethodChecker(State* state)
  : state(state)
  , annotated(nullptr)
  , ast::BaseVisitor("ClassMethodChecker")
{}

void
ClassMethodChecker::visitDFun(parser::DFun* p)
{
    annotated = ast::Clone(p);
}
void
ClassMethodChecker::visitDPointer(parser::DPointer* p)
{
    annotated = ast::Clone(p);
}
void
ClassMethodChecker::visitDInlinePointer(parser::DInlinePointer* p)
{
    annotated = ast::Clone(p);
}
void
ClassMethodChecker::visitDStruct(parser::DStruct* p)
{
    annotated = ast::Clone(p);
}

void
ClassMethodChecker::visitDClass(parser::DClass* p)
{
    parser::ListMember* annotatedMembers = checkClassMethods(p->listmember_, new parser::TClass(p->ident_));
    annotated = new parser::DClass(p->ident_, annotatedMembers);
}

void
ClassMethodChecker::visitDSubclass(parser::DSubclass* p)
{
    parser::ListMember* annotatedMembers = checkClassMethods(p->listmember_, new parser::TClass(p->ident_1));
    annotated = new parser::DSubclass(p->ident_1, p->ident_2, annotatedMembers);
}

parser::ListMember*
ClassMethodChecker::checkClassMethods(parser::ListMember* list, parser::TClass* selfType)
{
    ClassDescriptor* cd = state->GetClassDescriptor(selfType->ident_);
    State newState(state, cd);
    newState.PutVariable("self", selfType);
    auto* newList = new parser::ListMember;
    for (parser::Member* member : *list) {
        newList->push_back(MethodChecker::Visit(&newState, member));
    }
    return newList;
}

parser::Def*
ClassMethodChecker::Visit(State* state, parser::Def* def)
{
    ClassMethodChecker checker(state);
    def->accept(&checker);
    return checker.annotated;
}

} // namespace checker