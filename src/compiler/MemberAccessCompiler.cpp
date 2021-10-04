#include "MemberAccessCompiler.hpp"
#include "compiler/ExpressionCompiler.hpp"

namespace compiler {

MemberAccessCompiler::MemberAccessCompiler(llvm::Value* object, ClassDescriptor* classDescriptor, State* state)
  : ast::BaseVisitor("MemberAccessCompiler")
  , classDescriptor(classDescriptor)
  , state(state)
  , object(object)
  , value(nullptr)
{}

void
MemberAccessCompiler::visitEVar(parser::EVar* p)
{
    std::vector<llvm::Value*> gepIndices;
    gepIndices.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 0));
    gepIndices.push_back(
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), classDescriptor->GetFieldIndex(p->ident_)));
    value = state->GetBuilder()->CreateGEP(object, gepIndices);
}

void
MemberAccessCompiler::visitEApp(parser::EApp* p)
{
    std::vector<llvm::Value*> values;

    for (parser::Exp* exp : *p->listexp_) {
        values.push_back(ExpressionCompiler::Visit(state, exp).GetRValue());
    }

    std::vector<llvm::Value*> gepIndices;
    gepIndices.push_back(llvm::ConstantInt::get(llvm::Type::getInt64Ty(*state->GetContext()), 0));
    gepIndices.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 0));
    llvm::Value* vtable = state->GetBuilder()->CreateGEP(object, gepIndices);

    llvm::Value* vtableValue = state->GetBuilder()->CreateLoad(vtable);

    gepIndices.clear();
    gepIndices.push_back(llvm::ConstantInt::get(llvm::Type::getInt64Ty(*state->GetContext()), 0));
    gepIndices.push_back(
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), classDescriptor->GetMethodIndex(p->ident_)));
    llvm::Value* funPtr = state->GetBuilder()->CreateLoad(state->GetBuilder()->CreateGEP(vtableValue, gepIndices));

    llvm::FunctionCallee f =
      llvm::FunctionCallee(static_cast<llvm::FunctionType*>(funPtr->getType()->getPointerElementType()), funPtr);

    values.insert(
      values.begin(), state->GetBuilder()->CreateBitOrPointerCast(object, f.getFunctionType()->getParamType(0)));

    value = state->GetBuilder()->CreateCall(f, values);
}

void
MemberAccessCompiler::visitETyped(parser::ETyped* p)
{
    value = MemberAccessCompiler::Visit(object, classDescriptor, state, p->exp_);
}

llvm::Value*
MemberAccessCompiler::Visit(llvm::Value* object, ClassDescriptor* classDescriptor, State* state, parser::Exp* exp)
{
    MemberAccessCompiler memberAccessCompiler(object, classDescriptor, state);

    exp->accept(&memberAccessCompiler);

    return memberAccessCompiler.value;
}

} // namespace compiler