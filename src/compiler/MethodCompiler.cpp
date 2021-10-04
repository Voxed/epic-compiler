#include "MethodCompiler.hpp"

#include "common/TypeDeducer.hpp"
#include "compiler/StatementCompiler.hpp"
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>

namespace compiler {

MethodCompiler::MethodCompiler(State* state, ClassDescriptor* classDescriptor)
  : state(state)
  , classDescriptor(classDescriptor)
  , ast::BaseVisitor("MethodCompiler")
{}

void
MethodCompiler::visitMField(parser::MField* p)
{}

void
MethodCompiler::visitMFun(parser::MFun* p)
{
    llvm::Function* function = classDescriptor->GetMethod(p->ident_);
    llvm::BasicBlock* BB = llvm::BasicBlock::Create(*state->GetContext(), "entry", function);
    state->GetBuilder()->SetInsertPoint(BB);

    State classState(state, classDescriptor, function->getArg(0));
    State newState(&classState, function);

    llvm::Value* self = state->GetBuilder()->CreateAlloca(classDescriptor->GetType()->getPointerTo());
    state->GetBuilder()->CreateStore(function->getArg(0), self);
    newState.PutVariable("self", self);

    for (int i = 0; i < p->listarg_->size(); i++) {
        auto* concreteArg = static_cast<parser::ADecl*>(p->listarg_->at(i));

        llvm::Argument* llvmArg = function->getArg(i + 1);
        llvm::Value* var = newState.GetBuilder()->CreateAlloca(llvmArg->getType(), nullptr, concreteArg->ident_);
        newState.GetBuilder()->CreateStore(llvmArg, var);
        newState.PutVariable(concreteArg->ident_, var);
    }

    for (parser::Stm* stm : *p->liststm_) {
        StatementCompiler::Visit(&newState, stm);
    }

    // If final block is not well formed, insert unreachable or return void.
    if (newState.GetBuilder()->GetInsertBlock()->getTerminator() == nullptr) {
        if (common::CompareType(p->type_, common::VOID)) {
            newState.GetBuilder()->CreateRetVoid();
        } else {
            newState.GetBuilder()->CreateUnreachable();
        }
    }

    // Verify function
    llvm::verifyFunction(*function);
}

void
MethodCompiler::Visit(State* state, ClassDescriptor* classDescriptor, parser::Member* member)
{
    MethodCompiler compiler(state, classDescriptor);
    member->accept(&compiler);
}

} // namespace compiler