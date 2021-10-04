#include "TopDecCompiler.hpp"

#include "compiler/TypeCompiler.hpp"
#include "parser/Absyn.H"

namespace compiler {

TopDecCompiler::TopDecCompiler(State* state)
  : state(state)
  , ast::BaseVisitor("TopDecCompiler")
{}

void
TopDecCompiler::visitDFun(parser::DFun* p)
{
    llvm::Type* funType = TypeCompiler::Visit(state, p->type_);

    std::vector<llvm::Type*> argTypes;

    for (parser::Arg* arg : *p->listarg_) {
        auto* concreteArg = static_cast<parser::ADecl*>(arg);
        argTypes.push_back(TypeCompiler::Visit(state, concreteArg->type_));
    }

    llvm::FunctionType* functionType = llvm::FunctionType::get(funType, argTypes, false);
    state->PutFunction(
      p->ident_, llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, p->ident_, *state->GetModule()));
}

void
TopDecCompiler::visitDStruct(parser::DStruct* p)
{}
void
TopDecCompiler::visitDInlinePointer(parser::DInlinePointer* p)
{}
void
TopDecCompiler::visitDPointer(parser::DPointer* p)
{}
void
TopDecCompiler::visitSStruct(parser::SStruct* p)
{}
void
TopDecCompiler::visitDClass(parser::DClass* p)
{}
void
TopDecCompiler::visitDSubclass(parser::DSubclass* p)
{}

void
TopDecCompiler::Visit(State* state, parser::Def* def)
{
    TopDecCompiler compiler(state);
    def->accept(&compiler);
}

} // namespace compiler