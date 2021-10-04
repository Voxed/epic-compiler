#include "ClassCompiler.hpp"

#include "compiler/MemberCompiler.hpp"

namespace compiler {

ClassCompiler::ClassCompiler(State* state)
  : state(state)
  , ast::BaseVisitor("ClassCompiler")
{}

void
ClassCompiler::visitDFun(parser::DFun* p)
{}
void
ClassCompiler::visitDStruct(parser::DStruct* p)
{}
void
ClassCompiler::visitDInlinePointer(parser::DInlinePointer* p)
{}
void
ClassCompiler::visitDPointer(parser::DPointer* p)
{}
void
ClassCompiler::visitSStruct(parser::SStruct* p)
{}

void
ClassCompiler::visitDClass(parser::DClass* p)
{
    ClassDescriptor* cd = state->GetClassDescriptor(p->ident_);
    for (parser::Member* m : *p->listmember_) {
        MemberCompiler::Visit(state, cd, m);
    }
}
void
ClassCompiler::visitDSubclass(parser::DSubclass* p)
{
    ClassDescriptor* cd = state->GetClassDescriptor(p->ident_1);
    cd->SetSuperDescriptor(state->GetClassDescriptor(p->ident_2));
    for (parser::Member* m : *p->listmember_) {
        MemberCompiler::Visit(state, cd, m);
    }
}

void
ClassCompiler::Visit(State* state, parser::Def* def)
{
    ClassCompiler compiler(state);
    def->accept(&compiler);
}

} // namespace compiler