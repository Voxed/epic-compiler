#include "DeclaratorCompiler.hpp"

#include "common/TypeDeducer.hpp"
#include "compiler/ExpressionCompiler.hpp"
#include "compiler/TypeCompiler.hpp"

namespace compiler {

DeclaratorCompiler::DeclaratorCompiler(State* state, parser::Type* type)
  : state(state)
  , type(type)
  , ast::BaseVisitor("DeclaratorCompiler")
{}

void
DeclaratorCompiler::visitDecInit(parser::DecInit* p)
{
    llvm::Value* value = state->GetBuilder()->CreateAlloca(TypeCompiler::Visit(state, type), nullptr, p->ident_);
    state->GetBuilder()->CreateStore(ExpressionCompiler::Visit(state, p->exp_).GetRValue(), value);
    state->PutVariable(p->ident_, value);
}

void
DeclaratorCompiler::visitDecNoInit(parser::DecNoInit* p)
{
    llvm::Value* value = state->GetBuilder()->CreateAlloca(TypeCompiler::Visit(state, type));
    if (common::CompareType(type, common::DOUBLE)) {
        state->GetBuilder()->CreateStore(
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(*state->GetContext()), 0), value);
    } else if (common::CompareType(type, common::INT)) {
        state->GetBuilder()->CreateStore(
          llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 0), value);
    } else if (common::CompareType(type, common::BOOL)) {
        state->GetBuilder()->CreateStore(llvm::ConstantInt::get(llvm::Type::getInt1Ty(*state->GetContext()), 0), value);
    }
    state->PutVariable(p->ident_, value);
}

void
DeclaratorCompiler::Visit(State* state, parser::Type* type, parser::Dec* dec)
{
    DeclaratorCompiler compiler(state, type);
    dec->accept(&compiler);
}

} // namespace compiler