#pragma once

#include "compiler/State.hpp"
#include "parser/Absyn.H"
#include <llvm/IR/Value.h>
#include <stack>

namespace compiler {

namespace internal {

/**
 * Insert instructions for allocating an array.
 */
llvm::Value*
AllocateArray(State* state, parser::Type* type, std::stack<llvm::Value*> sizes);

/**
 * Insert instructions for allocating a struct.
 */
llvm::Value*
AllocateStruct(State* state, llvm::StructType* type);

/**
 * Insert instructions for allocating a class.
 */
llvm::Value*
AllocateClass(State* state, llvm::StructType* type, llvm::Value* vtable);

} // namespace internal

/**
 * Insert instructions for allocation.
 */
llvm::Value*
Allocate(State* state, parser::Type* type, std::stack<llvm::Value*> sizes);

} // namespace compiler