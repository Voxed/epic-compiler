#pragma once

#include <llvm/IR/Function.h>
#include <map>
#include <string>

namespace compiler {

class State;

/**
 * The class descriptor represents all members of a class, struct or array.
 * Also deduces struct type and vtable.
 */
class ClassDescriptor
{
  public:
    /**
     * Create a class descriptor with a name. Name is only used for code
     * readability.
     */
    ClassDescriptor(State* state, const std::string& name);

    /**
     * Add a field to the descriptor.
     */
    void PutField(const std::string& ident, llvm::Type* type);

    /**
     * Add a method to the descriptor.
     */
    void PutMethod(const std::string& ident, llvm::Function* fun);

    /**
     * Get a field index in the struct, offset of vtable is added.
     */
    int GetFieldIndex(const std::string& ident);

    /**
     * Get a method index in a vtable.
     */
    int GetMethodIndex(const std::string& ident);

    /**
     * Get whether the descriptor has a field.
     */
    bool HasField(const std::string& ident);

    /**
     * Get whether the descriptor has a method.
     */
    bool HasMethod(const std::string& ident);

    /**
     * Get the deduced struct type.
     * Only complete after finalization, but can be used before then.
     */
    llvm::StructType* GetType();

    /**
     * Get the global vtable variable for the descriptor.
     * Only available after finilization.
     */
    llvm::Value* GetVtable();

    /**
     * Set a derived from super descriptor.
     */
    void SetSuperDescriptor(ClassDescriptor* cd);

    /**
     * Get a method from the descriptor.
     */
    llvm::Function* GetMethod(const std::string& ident);

    /**
     * Finalize the class descriptor, adding all fields and methods from base
     * class. Constructs the vtable.
     */
    void Finalize();

  private:
    State* state;
    std::map<std::string, llvm::Function*> methods;
    std::map<std::string, llvm::Type*> fields;

    std::vector<std::string> fieldIndex;
    std::vector<llvm::Type*> fieldTypes;
    std::vector<std::string> methodIndex;
    std::vector<llvm::Constant*> methodValues;
    llvm::StructType* type;
    llvm::GlobalVariable* vtable;
    ClassDescriptor* superDescriptor;
    bool hasvtable;
    bool finalized;
    std::string name;
};

} // namespace compiler