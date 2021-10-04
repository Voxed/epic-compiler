#include "ClassChecker.hpp"

#include "ast/Clone.hpp"
#include "checker/MemberChecker.hpp"

namespace checker {

ClassChecker::ClassChecker(State* state)
  : state(state)
  , annotated(nullptr)
  , ast::BaseVisitor("ClassChecker")
{}

void
ClassChecker::visitDFun(parser::DFun* p)
{
    annotated = ast::Clone(p);
}
void
ClassChecker::visitDPointer(parser::DPointer* p)
{
    annotated = ast::Clone(p);
}
void
ClassChecker::visitDInlinePointer(parser::DInlinePointer* p)
{
    annotated = ast::Clone(p);
}
void
ClassChecker::visitDStruct(parser::DStruct* p)
{
    annotated = ast::Clone(p);
}

void
ClassChecker::visitDClass(parser::DClass* p)
{
    ClassDescriptor* cd = state->GetClassDescriptor(p->ident_);
    parser::ListMember* annotatedMembers = CheckClass(p->listmember_, cd);
    annotated = new parser::DClass(p->ident_, annotatedMembers);
}

void
ClassChecker::visitDSubclass(parser::DSubclass* p)
{
    ClassDescriptor* cd = state->GetClassDescriptor(p->ident_1);
    cd->SetSuperDescriptor(state->GetClassDescriptor(p->ident_2));
    parser::ListMember* annotatedMembers = CheckClass(p->listmember_, cd);
    annotated = new parser::DSubclass(p->ident_1, p->ident_2, annotatedMembers);
}

parser::ListMember*
ClassChecker::CheckClass(parser::ListMember* list, ClassDescriptor* cd)
{
    auto* newList = new parser::ListMember;
    for (parser::Member* member : *list) {
        newList->push_back(MemberChecker::Visit(state, cd, member));
    }
    return newList;
}

parser::Def*
ClassChecker::Visit(State* state, parser::Def* def)
{
    ClassChecker checker(state);
    def->accept(&checker);
    return checker.annotated;
}

} // namespace checker