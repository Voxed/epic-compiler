#pragma once

#include "compiler/ClassDescriptor.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>

namespace compiler {

/**
 * The main state of the compiler.
 */
class State
{
  public:
    /**
     * Construct the initial state.
     */
    State();

    /**
     * Construct a state with a new current function.
     */
    State(State* parent, llvm::Function* currentFunction);

    /**
     * Construct a new state inheriting from a class descriptor, which will make variables first get pulled from object.
     */
    explicit State(State* parent, ClassDescriptor* classDescriptor = nullptr, llvm::Value* object = nullptr);

    /**
     * Get the llvm context.
     */
    llvm::LLVMContext* GetContext();

    /**
     * Get the llvm module.
     */
    llvm::Module* GetModule();

    /**
     * Get the llvm IR builder.
     */
    llvm::IRBuilder<>* GetBuilder();

    /**
     * Get the llvm data layout.
     */
    llvm::DataLayout* GetDataLayout();

    /**
     * Get a variable from the state.
     */
    llvm::Value* GetVariable(const std::string& ident);

    /**
     * Add a variable to the state.
     */
    void PutVariable(const std::string& ident, llvm::Value* value);

    /**
     * Get a function from the state.
     */
    llvm::FunctionCallee GetFunction(const std::string& ident);

    /**
     * Add a function to the state.
     */
    void PutFunction(const std::string& ident, llvm::Function* value);

    /**
     * Get the current function from the state.
     */
    llvm::Function* GetCurrentFunction();

    /**
     * Get a class descriptor from the state. Creating it if it doesn't exist.
     */
    ClassDescriptor* GetClassDescriptor(const std::string& ident);

    /**
     * Finalize all the descriptors, pulling in their base class members and
     * creating their vtables.
     */
    void FinalizeDescriptors();

  private:
    State* parent;
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    std::unique_ptr<llvm::DataLayout> dataLayout;
    std::map<std::string, llvm::Value*> variables;
    std::map<std::string, llvm::Function*> functions;
    llvm::Function* currentFunction;

    std::map<std::string, std::unique_ptr<ClassDescriptor>> classTable;
    std::map<std::string, llvm::StructType*> typeTable;

    llvm::Value* object;
    ClassDescriptor* classDescriptor;
};

} // namespace compiler