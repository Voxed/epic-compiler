#pragma once

#include "ClassDescriptor.hpp"

namespace checker {

/**
 * Main checker state.
 */
class State
{
  public:
    /**
     * Create a state, optionally inheriting from another state or a class
     * descriptor.
     */
    explicit State(State* parent = nullptr, ClassDescriptor* classDescriptor = nullptr);

    /**
     * Add a variable to the state.
     */
    void PutVariable(const std::string& variable, parser::Type* type);

    /**
     * Get a variable from the state.
     */
    parser::Type* GetVariable(const std::string& variable);

    /**
     * Add a function to the state.
     */
    void PutFunction(const std::string& name, parser::TFun* type);

    /**
     * Get a function from the state.
     */
    parser::TFun* GetFunction(const std::string& name);

    /**
     * Get whether the state returns in all paths.
     */
    [[nodiscard]] bool GetDoesReturn() const;

    /**
     * Set whether the the state returns.
     */
    void SetDoesReturn();

    /**
     * Set what type the state should return.
     */
    void SetReturnType(parser::Type* type);

    /**
     * GEt what type the state should return.
     */
    parser::Type* GetReturnType();

    /**
     * Get a class descriptor defined in the state. Might be a struct or class.
     * Creates it if it doesnt exist.
     */
    ClassDescriptor* GetClassDescriptor(const std::string& id);

    /**
     * Add a custom type to the state.
     */
    void PutType(const std::string& typeName, parser::Type* type);

    /**
     * Get a custom type from the state.
     */
    parser::Type* GetType(const std::string& typeName);

    /**
     * Get whether the state has a type.
     */
    bool HasType(const std::string& typeName);

    /**
     * Verify the state, class descriptors and types.
     */
    void Verify();

  private:
    State* parent;
    std::map<std::string, std::unique_ptr<parser::Type, ast::Deleter>> variableTable;
    std::map<std::string, std::unique_ptr<parser::TFun, ast::Deleter>> functionTable;
    std::map<std::string, std::unique_ptr<ClassDescriptor>> classDescriptorTable;
    std::map<std::string, std::unique_ptr<parser::Type, ast::Deleter>> typeDeclarations;
    ClassDescriptor* classDescriptor;
    bool doesReturn;
    std::unique_ptr<parser::Type, ast::Deleter> returnType;
};

} // namespace checker