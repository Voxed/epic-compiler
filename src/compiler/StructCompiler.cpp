#include "StructCompiler.hpp"

#include "compiler/TypeCompiler.hpp"
#include "parser/Absyn.H"

namespace compiler {

StructCompiler::StructCompiler(State* state)
  : state(state)
  , ast::BaseVisitor("StructCompiler")
{}

void
StructCompiler::visitDFun(parser::DFun* p)
{}
void
StructCompiler::visitDStruct(parser::DStruct* p)
{
    compileStruct(p->struct_);
}
void
StructCompiler::visitDInlinePointer(parser::DInlinePointer* p)
{
    compileStruct(p->struct_);
}
void
StructCompiler::visitDPointer(parser::DPointer* p)
{}
void
StructCompiler::visitDClass(parser::DClass* p)
{}
void
StructCompiler::visitDSubclass(parser::DSubclass* p)
{}

void
StructCompiler::compileStruct(parser::Struct* s)
{
    auto* p = static_cast<parser::SStruct*>(s);

    ClassDescriptor* classDescriptor = state->GetClassDescriptor(p->ident_);

    // Add field types
    for (int i = 0; i < p->listfield_->size(); i++) {
        auto* concrete = static_cast<parser::FField*>(p->listfield_->at(i));
        classDescriptor->PutField(concrete->ident_, TypeCompiler::Visit(state, concrete->type_));
    }
}

void
StructCompiler::Visit(State* state, parser::Def* def)
{
    StructCompiler compiler(state);
    def->accept(&compiler);
}

} // namespace compiler