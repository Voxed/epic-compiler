#include "ExpressionCompiler.hpp"

#include "common/OperatorDeducer.hpp"
#include "common/TypeDeducer.hpp"
#include "compiler/Allocate.hpp"
#include "compiler/MemberAccessCompiler.hpp"
#include "compiler/TypeCompiler.hpp"
#include "parser/Absyn.H"
#include <llvm/IR/Type.h>
#include <stack>

namespace compiler {

ExpressionCompiler::ExpressionCompiler(State* state)
  : state(state)
  , lvalue(false)
  , value(nullptr)
  , type(nullptr)
  , ast::BaseVisitor("ExpressionCompiler")
{}

void
ExpressionCompiler::visitEVar(parser::EVar* p)
{
    value = state->GetVariable(p->ident_);
}

void
ExpressionCompiler::visitEInt(parser::EInt* p)
{
    value = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), p->integer_);
}

void
ExpressionCompiler::visitEDouble(parser::EDouble* p)
{
    value = llvm::ConstantFP::get(llvm::Type::getDoubleTy(*state->GetContext()), p->double_);
}

void
ExpressionCompiler::visitELitTrue(parser::ELitTrue* /*p*/)
{
    value = llvm::ConstantInt::get(llvm::Type::getInt1Ty(*state->GetContext()), 1);
}

void
ExpressionCompiler::visitELitFalse(parser::ELitFalse* /*p*/)
{
    value = llvm::ConstantInt::get(llvm::Type::getInt1Ty(*state->GetContext()), 0);
}

void
ExpressionCompiler::visitEApp(parser::EApp* p)
{
    std::vector<llvm::Value*> values;
    for (parser::Exp* exp : *p->listexp_) {
        values.push_back(ExpressionCompiler::Visit(state, exp).GetRValue());
    }
    value = state->GetBuilder()->CreateCall(state->GetFunction(p->ident_), values);
}

void
ExpressionCompiler::visitEString(parser ::EString* p)
{
    value = llvm::ConstantExpr::getCast(llvm::Instruction::BitCast,
      state->GetBuilder()->CreateGlobalString(llvm::StringRef(p->string_), "Str"),
      llvm::Type::getInt8PtrTy(*state->GetContext()));
}

void
ExpressionCompiler::visitENeg(parser ::ENeg* p)
{
    if (common::CompareType(type, common::DOUBLE)) {
        value = state->GetBuilder()->CreateFMul(ExpressionCompiler::Visit(state, p->exp_).GetRValue(),
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(*state->GetContext()), -1));
    } else {
        value = state->GetBuilder()->CreateMul(ExpressionCompiler::Visit(state, p->exp_).GetRValue(),
          llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), -1));
    }
}

void
ExpressionCompiler::visitENot(parser ::ENot* p)
{
    value = state->GetBuilder()->CreateXor(ExpressionCompiler::Visit(state, p->exp_).GetRValue(),
      llvm::ConstantInt::get(llvm::Type::getInt1Ty(*state->GetContext()), 1));
}

void
ExpressionCompiler::visitEMul(parser ::EMul* p)
{
    llvm::Value* val1 = ExpressionCompiler::Visit(state, p->exp_1).GetRValue();
    llvm::Value* val2 = ExpressionCompiler::Visit(state, p->exp_2).GetRValue();

    parser::Type* exp1Type = static_cast<parser::ETyped*>(p->exp_1)->type_;
    parser::Type* exp2Type = static_cast<parser::ETyped*>(p->exp_2)->type_;

    common::OpId opId = common::OperatorDeducer::Visit(p->mulop_);
    if (common::CompareType(exp1Type, common::INT)) {
        if (opId == common::DIV) {
            value = state->GetBuilder()->CreateSDiv(val1, val2);
        } else if (opId == common::TIMES) {
            value = state->GetBuilder()->CreateMul(val1, val2);
        } else if (opId == common::MOD) {
            value = state->GetBuilder()->CreateSRem(val1, val2);
        }
    } else {
        if (opId == common::DIV) {
            value = state->GetBuilder()->CreateFDiv(val1, val2);
        } else if (opId == common::TIMES) {
            value = state->GetBuilder()->CreateFMul(val1, val2);
        } else if (opId == common::MOD) {
            value = state->GetBuilder()->CreateFRem(val1, val2);
        }
    }
}

void
ExpressionCompiler::visitEAdd(parser ::EAdd* p)
{
    llvm::Value* val1 = ExpressionCompiler::Visit(state, p->exp_1).GetRValue();
    llvm::Value* val2 = ExpressionCompiler::Visit(state, p->exp_2).GetRValue();

    parser::Type* exp1Type = static_cast<parser::ETyped*>(p->exp_1)->type_;
    parser::Type* exp2Type = static_cast<parser::ETyped*>(p->exp_2)->type_;

    common::OpId opId = common::OperatorDeducer::Visit(p->addop_);
    if (common::CompareType(exp1Type, common::INT)) {
        if (opId == common::PLUS) {
            value = state->GetBuilder()->CreateAdd(val1, val2);
        } else if (opId == common::MINUS) {
            value = state->GetBuilder()->CreateSub(val1, val2);
        }
    } else {
        if (opId == common::PLUS) {
            value = state->GetBuilder()->CreateFAdd(val1, val2);
        } else if (opId == common::MINUS) {
            value = state->GetBuilder()->CreateFSub(val1, val2);
        }
    }
}

void
ExpressionCompiler::visitERel(parser ::ERel* p)
{
    llvm::Value* val1 = ExpressionCompiler::Visit(state, p->exp_1).GetRValue();
    llvm::Value* val2 = ExpressionCompiler::Visit(state, p->exp_2).GetRValue();

    parser::Type* exp1Type = static_cast<parser::ETyped*>(p->exp_1)->type_;
    parser::Type* exp2Type = static_cast<parser::ETyped*>(p->exp_2)->type_;

    common::OpId opId = common::OperatorDeducer::Visit(p->relop_);
    if (common::CompareType(exp1Type, common::POINTER) || common::CompareType(exp1Type, common::CLASS)) {
        llvm::Value* diff = state->GetBuilder()->CreatePtrDiff(val1, val2);
        if (opId == common::EQ) {
            value = state->GetBuilder()->CreateICmpEQ(
              diff, llvm::ConstantInt::get(llvm::Type::getInt64Ty(*state->GetContext()), 0));
        } else if (opId == common::NE) {
            value = state->GetBuilder()->CreateICmpNE(
              diff, llvm::ConstantInt::get(llvm::Type::getInt64Ty(*state->GetContext()), 0));
        }
    } else if (common::CompareType(exp1Type, common::INT) || common::CompareType(exp1Type, common::BOOL)) {
        if (opId == common::LT) {
            value = state->GetBuilder()->CreateICmpSLT(val1, val2);
        } else if (opId == common::LE) {
            value = state->GetBuilder()->CreateICmpSLE(val1, val2);
        } else if (opId == common::GT) {
            value = state->GetBuilder()->CreateICmpSGT(val1, val2);
        } else if (opId == common::GE) {
            value = state->GetBuilder()->CreateICmpSGE(val1, val2);
        } else if (opId == common::EQ) {
            value = state->GetBuilder()->CreateICmpEQ(val1, val2);
        } else if (opId == common::NE) {
            value = state->GetBuilder()->CreateICmpNE(val1, val2);
        }
    } else {
        if (opId == common::LT) {
            value = state->GetBuilder()->CreateFCmpOLT(val1, val2);
        } else if (opId == common::LE) {
            value = state->GetBuilder()->CreateFCmpOLE(val1, val2);
        } else if (opId == common::GT) {
            value = state->GetBuilder()->CreateFCmpOGT(val1, val2);
        } else if (opId == common::GE) {
            value = state->GetBuilder()->CreateFCmpOGE(val1, val2);
        } else if (opId == common::EQ) {
            value = state->GetBuilder()->CreateFCmpOEQ(val1, val2);
        } else if (opId == common::NE) {
            value = state->GetBuilder()->CreateFCmpONE(val1, val2);
        }
    }
}

void
ExpressionCompiler::visitEAnd(parser ::EAnd* p)
{
    llvm::BasicBlock* trueBlock = llvm::BasicBlock::Create(*state->GetContext(), "true", state->GetCurrentFunction());
    llvm::BasicBlock* exitBlock = llvm::BasicBlock::Create(*state->GetContext(), "exit", state->GetCurrentFunction());
    llvm::Value* result = state->GetBuilder()->CreateAlloca(llvm::Type::getInt1Ty(*state->GetContext()));

    ExpressionCompilerResult exp1Result = ExpressionCompiler::Visit(state, p->exp_1);
    state->GetBuilder()->CreateStore(exp1Result.GetRValue(), result);
    state->GetBuilder()->CreateCondBr(exp1Result.GetRValue(), trueBlock, exitBlock);

    state->GetBuilder()->SetInsertPoint(trueBlock);
    ExpressionCompilerResult exp2Result = ExpressionCompiler::Visit(state, p->exp_2);
    state->GetBuilder()->CreateStore(exp2Result.GetRValue(), result);
    state->GetBuilder()->CreateBr(exitBlock);

    state->GetBuilder()->SetInsertPoint(exitBlock);
    value = state->GetBuilder()->CreateLoad(result);
}

void
ExpressionCompiler::visitEOr(parser ::EOr* p)
{
    llvm::BasicBlock* falseBlock = llvm::BasicBlock::Create(*state->GetContext(), "false", state->GetCurrentFunction());
    llvm::BasicBlock* exitBlock = llvm::BasicBlock::Create(*state->GetContext(), "exit", state->GetCurrentFunction());

    llvm::Value* result = state->GetBuilder()->CreateAlloca(llvm::Type::getInt1Ty(*state->GetContext()));

    ExpressionCompilerResult exp1Result = ExpressionCompiler::Visit(state, p->exp_1);
    state->GetBuilder()->CreateStore(exp1Result.GetRValue(), result);
    state->GetBuilder()->CreateCondBr(exp1Result.GetRValue(), exitBlock, falseBlock);

    state->GetBuilder()->SetInsertPoint(falseBlock);
    ExpressionCompilerResult exp2Result = ExpressionCompiler::Visit(state, p->exp_2);
    state->GetBuilder()->CreateStore(exp2Result.GetRValue(), result);
    state->GetBuilder()->CreateBr(exitBlock);

    state->GetBuilder()->SetInsertPoint(exitBlock);
    value = state->GetBuilder()->CreateLoad(result);
}

void
ExpressionCompiler::visitETyped(parser::ETyped* p)
{
    type = p->type_;
    lvalue = (p->char_ != 0);
    value = ExpressionCompiler::Visit(state, p->exp_, lvalue, type).GetValue();
}

void
ExpressionCompiler::visitEAllocate(parser::EAllocate* p)
{
    std::stack<llvm::Value*> sizeValues;
    for (auto size = p->listlength_->rbegin(); size != p->listlength_->rend(); ++size) {
        auto* ssize = static_cast<parser::LLength*>(*size);
        sizeValues.push(ExpressionCompiler::Visit(state, ssize->exp_).GetRValue());
    }
    value = Allocate(state, type, sizeValues);
}

void
ExpressionCompiler::visitEDot(parser::EDot* p)
{
    ExpressionCompilerResult result = ExpressionCompiler::Visit(state, p->exp_1);

    if (common::CompareType(result.GetType(), common::ARRAY)) {
        ClassDescriptor classDescriptor(state, "array");
        classDescriptor.PutField("length", llvm::Type::getInt32Ty(*state->GetContext()));
        classDescriptor.Finalize();
        value = state->GetBuilder()->CreateLoad(
          MemberAccessCompiler::Visit(result.GetRValue(), &classDescriptor, state, p->exp_2));
    } else if (common::CompareType(result.GetType(), common::CLASS)) {
        auto* cType = static_cast<parser::TClass*>(result.GetType());
        value =
          MemberAccessCompiler::Visit(result.GetRValue(), state->GetClassDescriptor(cType->ident_), state, p->exp_2);
    }
}

void
ExpressionCompiler::visitEIndex(parser::EIndex* p)
{
    ExpressionCompilerResult result = ExpressionCompiler::Visit(state, p->exp_1);
    llvm::Value* loaded = result.GetRValue();

    std::vector<llvm::Value*> indices;
    indices.push_back(llvm::ConstantInt::get(llvm::Type::getInt64Ty(*state->GetContext()), 0));
    indices.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 1));
    indices.push_back(ExpressionCompiler::Visit(state, p->exp_2).GetRValue());

    value = state->GetBuilder()->CreateGEP(loaded, indices);
}

void
ExpressionCompiler::visitENull(parser::ENull* p)
{
    auto* pType = static_cast<parser::TPointer*>(p->type_);
    value = llvm::ConstantPointerNull::get(state->GetClassDescriptor(pType->ident_)->GetType()->getPointerTo());
}

void
ExpressionCompiler::visitEDeref(parser::EDeref* p)
{
    ExpressionCompilerResult result = ExpressionCompiler::Visit(state, p->exp_1);
    auto* ptrType = static_cast<parser::TPointer*>(result.GetType());
    ClassDescriptor* classDescriptor = state->GetClassDescriptor(ptrType->ident_);
    value = MemberAccessCompiler::Visit(result.GetRValue(), classDescriptor, state, p->exp_2);
}

void
ExpressionCompiler::visitECast(parser::ECast* p)
{
    ExpressionCompilerResult result = ExpressionCompiler::Visit(state, p->exp_);
    llvm::Type* type = TypeCompiler::Visit(state, p->type_);
    if (lvalue) {
        // Cast to the pointer of the type
        value = state->GetBuilder()->CreateBitOrPointerCast(result.GetValue(), type->getPointerTo());
    } else {
        // Cast to the type (might still be a pointer)
        value = state->GetBuilder()->CreateBitOrPointerCast(result.GetValue(), type);
    }
}

ExpressionCompilerResult
ExpressionCompiler::Visit(State* state, parser::Exp* exp)
{
    ExpressionCompiler compiler(state);
    exp->accept(&compiler);
    return ExpressionCompilerResult(compiler.lvalue, compiler.value, compiler.type, state);
}

ExpressionCompilerResult
ExpressionCompiler::Visit(State* state, parser::Exp* exp, bool isLvalue, parser::Type* expectedType)
{
    ExpressionCompiler compiler(state);
    compiler.type = expectedType;
    compiler.lvalue = isLvalue;
    exp->accept(&compiler);
    return ExpressionCompilerResult(compiler.lvalue, compiler.value, compiler.type, state);
}

ExpressionCompilerResult::ExpressionCompilerResult(bool lvalue, llvm::Value* value, parser::Type* type, State* state)
  : lvalue(lvalue)
  , value(value)
  , type(type)
  , state(state)
{}

llvm::Value*
ExpressionCompilerResult::GetRValue()
{
    if (lvalue) {
        return state->GetBuilder()->CreateLoad(value);
    }
    return value;
}

llvm::Value*
ExpressionCompilerResult::GetValue()
{
    return value;
}

parser::Type*
ExpressionCompilerResult::GetType()
{
    return type;
}

} // namespace compiler