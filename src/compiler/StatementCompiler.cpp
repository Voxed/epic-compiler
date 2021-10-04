#include "StatementCompiler.hpp"

#include "common/TypeDeducer.hpp"
#include "compiler/DeclaratorCompiler.hpp"
#include "compiler/ExpressionCompiler.hpp"
#include "compiler/State.hpp"

namespace compiler {

StatementCompiler::StatementCompiler(State* state)
  : state(state)
  , ast::BaseVisitor("StatementCompiler")
{}

void
StatementCompiler::visitSEmpty(parser::SEmpty* p)
{}

void
StatementCompiler::visitSBlock(parser::SBlock* p)
{
    State newState(state);

    for (parser::Stm* stm : *p->liststm_) {
        Visit(&newState, stm);

        // Break if returns
        if (state->GetBuilder()->GetInsertBlock()->getTerminator() != nullptr) {
            break;
        }
    }
}

void
StatementCompiler::visitSAss(parser::SAss* p)
{
    llvm::Value* var = ExpressionCompiler::Visit(state, p->exp_1).GetValue();
    llvm::Value* value = ExpressionCompiler::Visit(state, p->exp_2).GetRValue();

    state->GetBuilder()->CreateStore(value, var);
}

void
StatementCompiler::visitSDecl(parser::SDecl* p)
{
    for (parser::Dec* dec : *p->listdec_) {
        DeclaratorCompiler::Visit(state, p->type_, dec);
    }
}

void
StatementCompiler::visitSIncr(parser::SIncr* p)
{
    ExpressionCompilerResult result = ExpressionCompiler::Visit(state, p->exp_);

    llvm::Value* var = result.GetValue();
    llvm::Value* val = state->GetBuilder()->CreateLoad(var);
    llvm::Value* inc;
    if (common::CompareType(result.GetType(), common::DOUBLE)) {
        inc = state->GetBuilder()->CreateFAdd(
          val, llvm::ConstantFP::get(llvm::Type::getDoubleTy(*state->GetContext()), 1.0));
    } else {
        inc = state->GetBuilder()->CreateAdd(
          val, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 1.0));
    }
    state->GetBuilder()->CreateStore(inc, var);
}

void
StatementCompiler::visitSDecr(parser::SDecr* p)
{
    ExpressionCompilerResult result = ExpressionCompiler::Visit(state, p->exp_);

    llvm::Value* var = result.GetValue();
    llvm::Value* val = state->GetBuilder()->CreateLoad(var);
    llvm::Value* inc;
    if (common::CompareType(result.GetType(), common::DOUBLE)) {
        inc = state->GetBuilder()->CreateFSub(
          val, llvm::ConstantFP::get(llvm::Type::getDoubleTy(*state->GetContext()), 1.0));
    } else {
        inc = state->GetBuilder()->CreateSub(
          val, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 1.0));
    }
    state->GetBuilder()->CreateStore(inc, var);
}

void
StatementCompiler::visitSCond(parser::SCond* p)
{
    State trueState(state);

    llvm::BasicBlock* exitBlock = llvm::BasicBlock::Create(*state->GetContext(), "exit", state->GetCurrentFunction());
    llvm::BasicBlock* trueBlock = llvm::BasicBlock::Create(*state->GetContext(), "true", state->GetCurrentFunction());

    state->GetBuilder()->CreateCondBr(ExpressionCompiler::Visit(state, p->exp_).GetRValue(), trueBlock, exitBlock);

    state->GetBuilder()->SetInsertPoint(trueBlock);
    Visit(&trueState, p->stm_);

    // If not returns
    if (state->GetBuilder()->GetInsertBlock()->getTerminator() == nullptr) {
        state->GetBuilder()->CreateBr(exitBlock);
    }

    state->GetBuilder()->SetInsertPoint(exitBlock);
}

void
StatementCompiler::visitSCondElse(parser::SCondElse* p)
{
    State trueState(state);
    State falseState(state);

    llvm::BasicBlock* exitBlock = llvm::BasicBlock::Create(*state->GetContext(), "exit", state->GetCurrentFunction());
    llvm::BasicBlock* trueBlock = llvm::BasicBlock::Create(*state->GetContext(), "true", state->GetCurrentFunction());
    llvm::BasicBlock* falseBlock = llvm::BasicBlock::Create(*state->GetContext(), "false", state->GetCurrentFunction());

    state->GetBuilder()->CreateCondBr(ExpressionCompiler::Visit(state, p->exp_).GetRValue(), trueBlock, falseBlock);

    state->GetBuilder()->SetInsertPoint(trueBlock);
    Visit(&trueState, p->stm_1);

    // If not returns
    if (state->GetBuilder()->GetInsertBlock()->getTerminator() == nullptr) {
        state->GetBuilder()->CreateBr(exitBlock);
    }

    state->GetBuilder()->SetInsertPoint(falseBlock);
    Visit(&falseState, p->stm_2);

    // If not returns
    if (state->GetBuilder()->GetInsertBlock()->getTerminator() == nullptr) {
        state->GetBuilder()->CreateBr(exitBlock);
    }

    state->GetBuilder()->SetInsertPoint(exitBlock);
}

void
StatementCompiler::visitSWhile(parser::SWhile* p)
{
    State whileState(state);

    llvm::BasicBlock* exitBlock = llvm::BasicBlock::Create(*state->GetContext(), "exit", state->GetCurrentFunction());
    llvm::BasicBlock* condBlock = llvm::BasicBlock::Create(*state->GetContext(), "cond", state->GetCurrentFunction());
    llvm::BasicBlock* whileBlock = llvm::BasicBlock::Create(*state->GetContext(), "while", state->GetCurrentFunction());

    state->GetBuilder()->CreateBr(condBlock);

    state->GetBuilder()->SetInsertPoint(condBlock);
    state->GetBuilder()->CreateCondBr(ExpressionCompiler::Visit(state, p->exp_).GetRValue(), whileBlock, exitBlock);

    state->GetBuilder()->SetInsertPoint(whileBlock);
    Visit(&whileState, p->stm_);

    // If not returns
    if (state->GetBuilder()->GetInsertBlock()->getTerminator() == nullptr) {
        state->GetBuilder()->CreateBr(condBlock);
    }

    state->GetBuilder()->SetInsertPoint(exitBlock);
}

void
StatementCompiler::visitSRet(parser::SRet* p)
{
    state->GetBuilder()->CreateRet(ExpressionCompiler::Visit(state, p->exp_).GetRValue());
}

void
StatementCompiler::visitSVRet(parser::SVRet* /*p*/)
{
    state->GetBuilder()->CreateRetVoid();
}

void
StatementCompiler::visitSForEach(parser::SForEach* p)
{
    llvm::Value* array = ExpressionCompiler::Visit(state, p->exp_).GetRValue();

    llvm::BasicBlock* exitBlock = llvm::BasicBlock::Create(*state->GetContext(), "exit", state->GetCurrentFunction());
    llvm::BasicBlock* condBlock = llvm::BasicBlock::Create(*state->GetContext(), "cond", state->GetCurrentFunction());
    llvm::BasicBlock* forBlock = llvm::BasicBlock::Create(*state->GetContext(), "for", state->GetCurrentFunction());

    llvm::Value* counter = state->GetBuilder()->CreateAlloca(llvm::Type::getInt32Ty(*state->GetContext()));
    state->GetBuilder()->CreateStore(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 0), counter);

    std::vector<llvm::Value*> lengthIndices;
    lengthIndices.push_back(llvm::ConstantInt::get(llvm::Type::getInt64Ty(*state->GetContext()), 0));
    lengthIndices.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 0));
    llvm::Value* lengthPointer = state->GetBuilder()->CreateGEP(array, lengthIndices);
    llvm::Value* length = state->GetBuilder()->CreateLoad(lengthPointer);

    state->GetBuilder()->CreateBr(condBlock);

    state->GetBuilder()->SetInsertPoint(condBlock);
    llvm::Value* counterVal = state->GetBuilder()->CreateLoad(counter);
    llvm::Value* cond = state->GetBuilder()->CreateICmpSLT(counterVal, length);
    llvm::Value* newCounterVal = state->GetBuilder()->CreateAdd(
      counterVal, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 1));
    state->GetBuilder()->CreateStore(newCounterVal, counter);
    state->GetBuilder()->CreateCondBr(cond, forBlock, exitBlock);

    state->GetBuilder()->SetInsertPoint(forBlock);

    std::vector<llvm::Value*> indices;
    indices.push_back(llvm::ConstantInt::get(llvm::Type::getInt64Ty(*state->GetContext()), 0));
    indices.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 1));
    indices.push_back(counterVal);

    llvm::Value* element = state->GetBuilder()->CreateGEP(array, indices);

    State forEachState(state);
    forEachState.PutVariable(p->ident_, element);
    Visit(&forEachState, p->stm_);

    // If not returns
    if (state->GetBuilder()->GetInsertBlock()->getTerminator() == nullptr) {
        state->GetBuilder()->CreateBr(condBlock);
    }

    state->GetBuilder()->SetInsertPoint(exitBlock);
}

void
StatementCompiler::visitSExp(parser::SExp* p)
{
    ExpressionCompiler::Visit(state, p->exp_);
}

void
StatementCompiler::Visit(State* state, parser::Stm* stm)
{
    StatementCompiler compiler(state);
    stm->accept(&compiler);
}

} // namespace compiler