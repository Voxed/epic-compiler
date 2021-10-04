#include "FunctionCompiler.hpp"

#include "common/TypeDeducer.hpp"
#include "compiler/StatementCompiler.hpp"
#include "parser/Absyn.H"
#include <llvm/IR/Verifier.h>

namespace compiler {

FunctionCompiler::FunctionCompiler(State* state)
  : state(state)
  , ast::BaseVisitor("FunctionCompiler")
{}

void
FunctionCompiler::visitDFun(parser::DFun* p)
{
    llvm::Function* function = state->GetModule()->getFunction(p->ident_);
    llvm::BasicBlock* BB = llvm::BasicBlock::Create(*state->GetContext(), "entry", function);
    state->GetBuilder()->SetInsertPoint(BB);

    State newState(state, function);

    for (int i = 0; i < p->listarg_->size(); i++) {
        auto* concreteArg = static_cast<parser::ADecl*>(p->listarg_->at(i));
        llvm::Argument* llvmArg = function->getArg(i);
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
FunctionCompiler::visitDStruct(parser::DStruct* p)
{}
void
FunctionCompiler::visitDInlinePointer(parser::DInlinePointer* p)
{}
void
FunctionCompiler::visitDPointer(parser::DPointer* p)
{}
void
FunctionCompiler::visitSStruct(parser::SStruct* p)
{}
void
FunctionCompiler::visitDClass(parser::DClass* p)
{}
void
FunctionCompiler::visitDSubclass(parser::DSubclass* p)
{}

void
FunctionCompiler::Visit(State* state, parser::Def* def)
{
    FunctionCompiler compiler(state);
    def->accept(&compiler);
}

} // namespace compiler