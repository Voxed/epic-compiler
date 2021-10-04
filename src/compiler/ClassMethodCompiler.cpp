#include "compiler/ClassMethodCompiler.hpp"

#include "compiler/MethodCompiler.hpp"

namespace compiler {

ClassMethodCompiler::ClassMethodCompiler(State* state)
  : state(state)
  , ast::BaseVisitor("ClassMethodCompiler")
{}

void
ClassMethodCompiler::visitDFun(parser::DFun* p)
{}
void
ClassMethodCompiler::visitDStruct(parser::DStruct* p)
{}
void
ClassMethodCompiler::visitDInlinePointer(parser::DInlinePointer* p)
{}
void
ClassMethodCompiler::visitDPointer(parser::DPointer* p)
{}
void
ClassMethodCompiler::visitSStruct(parser::SStruct* p)
{}

void
ClassMethodCompiler::visitDClass(parser::DClass* p)
{
    ClassDescriptor* cd = state->GetClassDescriptor(p->ident_);
    for (parser::Member* m : *p->listmember_) {
        MethodCompiler::Visit(state, cd, m);
    }
}
void
ClassMethodCompiler::visitDSubclass(parser::DSubclass* p)
{
    ClassDescriptor* cd = state->GetClassDescriptor(p->ident_1);
    cd->SetSuperDescriptor(state->GetClassDescriptor(p->ident_2));
    for (parser::Member* m : *p->listmember_) {
        MethodCompiler::Visit(state, cd, m);
    }
}

void
ClassMethodCompiler::Visit(State* state, parser::Def* def)
{
    ClassMethodCompiler compiler(state);
    def->accept(&compiler);
}

} // namespace compiler