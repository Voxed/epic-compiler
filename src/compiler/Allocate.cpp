#include "Allocate.hpp"

#include "common/TypeDeducer.hpp"
#include "compiler/TypeCompiler.hpp"

namespace compiler {

namespace internal {

llvm::Value*
AllocateArray(State* state, parser::Type* type, std::stack<llvm::Value*> sizes)
{

    auto* astArrayType = static_cast<parser::TArray*>(type);
    parser::Type* astElementType = astArrayType->type_;

    llvm::Value* length = sizes.top();
    sizes.pop();

    // Calculate size of the elements
    llvm::Value* elementSize = llvm::ConstantExpr::getCast(llvm::Instruction::BitCast,
      llvm::ConstantExpr::getSizeOf(TypeCompiler::Visit(state, astElementType)),
      llvm::Type::getInt32Ty(*state->GetContext()));

    // Calculate size of the empty list
    llvm::Value* emptyListSize = llvm::ConstantExpr::getCast(llvm::Instruction::BitCast,
      llvm::ConstantExpr::getSizeOf(TypeCompiler::Visit(state, astArrayType)->getPointerElementType()),
      llvm::Type::getInt32Ty(*state->GetContext()));

    // Calculate size of the full list
    llvm::Value* arraySize = state->GetBuilder()->CreateMul(elementSize, length);
    llvm::Value* listSize = state->GetBuilder()->CreateIntCast(
      state->GetBuilder()->CreateAdd(arraySize, emptyListSize), llvm::Type::getInt64Ty(*state->GetContext()), true);

    // Call calloc
    std::vector<llvm::Value*> callocArgs;
    callocArgs.push_back(llvm::ConstantInt::get(llvm::Type::getInt64Ty(*state->GetContext()), 1));
    callocArgs.push_back(listSize);
    llvm::Value* memory = state->GetBuilder()->CreateCall(state->GetModule()->getFunction("calloc"), callocArgs);

    // Cast to array type
    llvm::Value* array = state->GetBuilder()->CreateBitOrPointerCast(memory, TypeCompiler::Visit(state, astArrayType));

    // Set length
    std::vector<llvm::Value*> lengthIndices;
    lengthIndices.push_back(llvm::ConstantInt::get(llvm::Type::getInt64Ty(*state->GetContext()), 0));
    lengthIndices.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 0));
    llvm::Value* lengthPtr = state->GetBuilder()->CreateGEP(array, lengthIndices);
    state->GetBuilder()->CreateStore(length, lengthPtr);

    // If there are sub arrays
    // Possible pointers should automatically be allocated to 0. Hopefully llvm null is 0.
    if (common::CompareType(astElementType, common::ARRAY)) {
        // Blocks
        llvm::BasicBlock* condBlock =
          llvm::BasicBlock::Create(*state->GetContext(), "cond", state->GetCurrentFunction());
        llvm::BasicBlock* allocBlock =
          llvm::BasicBlock::Create(*state->GetContext(), "alloc", state->GetCurrentFunction());
        llvm::BasicBlock* exitBlock =
          llvm::BasicBlock::Create(*state->GetContext(), "exit", state->GetCurrentFunction());

        // Counter
        llvm::Value* counter =
          state->GetBuilder()->CreateAlloca(llvm::Type::getInt32Ty(*state->GetContext()), nullptr, "counter");
        state->GetBuilder()->CreateStore(
          llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 0), counter);

        state->GetBuilder()->CreateBr(condBlock);

        // CONDITION BLOCK
        state->GetBuilder()->SetInsertPoint(condBlock);
        {
            llvm::Value* counterVal = state->GetBuilder()->CreateLoad(counter);
            llvm::Value* cond = state->GetBuilder()->CreateICmpSLT(counterVal, length);
            state->GetBuilder()->CreateCondBr(cond, allocBlock, exitBlock);
        }

        // ALLOCATION BLOCK
        state->GetBuilder()->SetInsertPoint(allocBlock);
        {
            llvm::Value* counterVal = state->GetBuilder()->CreateLoad(counter);
            std::vector<llvm::Value*> indexIndices;
            indexIndices.push_back(llvm::ConstantInt::get(llvm::Type::getInt64Ty(*state->GetContext()), 0));
            indexIndices.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 1));
            indexIndices.push_back(counterVal);
            llvm::Value* indexPointer = state->GetBuilder()->CreateGEP(array, indexIndices);

            state->GetBuilder()->CreateStore(AllocateArray(state, astElementType, sizes), indexPointer);

            llvm::Value* incrementedCounterValue = state->GetBuilder()->CreateAdd(
              counterVal, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 1));

            state->GetBuilder()->CreateStore(incrementedCounterValue, counter);
            state->GetBuilder()->CreateBr(condBlock);
        }
        // EXIT BLOCK
        state->GetBuilder()->SetInsertPoint(exitBlock);
    }

    return array;
}

llvm::Value*
AllocateStruct(State* state, llvm::StructType* type)
{
    std::vector<llvm::Value*> callocArgs;
    callocArgs.push_back(llvm::ConstantInt::get(llvm::Type::getInt64Ty(*state->GetContext()), 1));
    callocArgs.push_back(llvm::ConstantExpr::getSizeOf(type));
    llvm::Value* v = state->GetBuilder()->CreateCall(state->GetModule()->getFunction("calloc"), callocArgs);
    llvm::Value* structData = state->GetBuilder()->CreateBitOrPointerCast(v, type->getPointerTo());
    return structData;
}

llvm::Value*
AllocateClass(State* state, llvm::StructType* type, llvm::Value* vtable)
{
    std::vector<llvm::Value*> callocArgs;
    callocArgs.push_back(llvm::ConstantInt::get(llvm::Type::getInt64Ty(*state->GetContext()), 1));
    callocArgs.push_back(llvm::ConstantExpr::getSizeOf(type));
    llvm::Value* v = state->GetBuilder()->CreateCall(state->GetModule()->getFunction("calloc"), callocArgs);
    llvm::Value* structData = state->GetBuilder()->CreateBitOrPointerCast(v, type->getPointerTo());
    llvm::Value* vtablePtr = state->GetBuilder()->CreateGEP(structData,
      std::vector<llvm::Value*>{
        llvm::ConstantInt::get(llvm::Type::getInt64Ty(*state->GetContext()), 0),
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*state->GetContext()), 0),
      });
    state->GetBuilder()->CreateStore(vtable, vtablePtr);
    return structData;
}

} // namespace internal

llvm::Value*
Allocate(State* state, parser::Type* type, std::stack<llvm::Value*> sizes)
{
    if (common::CompareType(type, common::ARRAY)) {
        return internal::AllocateArray(state, type, std::move(sizes));
    }

    if (common::CompareType(type, common::POINTER)) {
        auto* pType = static_cast<parser::TPointer*>(type);
        return internal::AllocateStruct(state, state->GetClassDescriptor(pType->ident_)->GetType());
    }

    if (common::CompareType(type, common::CLASS)) {
        auto* cType = static_cast<parser::TClass*>(type);
        return internal::AllocateClass(state,
          state->GetClassDescriptor(cType->ident_)->GetType(),
          state->GetClassDescriptor(cType->ident_)->GetVtable());
    }

    return nullptr; // unreachable
}

} // namespace compiler