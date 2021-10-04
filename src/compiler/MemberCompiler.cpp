#include "MemberCompiler.hpp"

#include "ast/BaseVisitor.hpp"
#include "compiler/TypeCompiler.hpp"
#include "parser/Absyn.H"

namespace compiler {

MemberCompiler::MemberCompiler(State* state, ClassDescriptor* classDescriptor)
  : state(state)
  , classDescriptor(classDescriptor)
  , ast::BaseVisitor("MemberCompiler")
{}

void
MemberCompiler::visitMField(parser::MField* p)
{
    auto* concrete = static_cast<parser::FField*>(p->field_);
    classDescriptor->PutField(concrete->ident_, TypeCompiler::Visit(state, concrete->type_));
}

void
MemberCompiler::visitMFun(parser::MFun* p)
{
    llvm::Type* funType = TypeCompiler::Visit(state, p->type_);

    std::vector<llvm::Type*> argTypes;

    argTypes.push_back(classDescriptor->GetType()->getPointerTo());

    for (parser::Arg* arg : *p->listarg_) {
        auto* concreteArg = static_cast<parser::ADecl*>(arg);
        argTypes.push_back(TypeCompiler::Visit(state, concreteArg->type_));
    }

    llvm::FunctionType* functionType = llvm::FunctionType::get(funType, argTypes, false);
    classDescriptor->PutMethod(
      p->ident_, llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, p->ident_, *state->GetModule()));
};

void
MemberCompiler::Visit(State* state, ClassDescriptor* classDescriptor, parser::Member* member)
{
    MemberCompiler compiler(state, classDescriptor);
    member->accept(&compiler);
}

} // namespace compiler
