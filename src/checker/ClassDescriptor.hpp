#pragma once

#include "ast/Destroy.hpp"
#include "parser/Absyn.H"

#include <map>
#include <memory>
#include <string>

namespace checker {

/**
 * The class descriptor represents all members of a class, struct or array.
 */
class ClassDescriptor
{
  public:
    explicit ClassDescriptor(bool writable);

    /**
     * Get a field from the descriptor
     */
    parser::Type* GetField(const std::string&);

    /**
     * Add a field to the descriptor.
     */
    void PutField(const std::string& variable, parser::Type* type);

    /**
     * Check if the descriptor has a field.
     */
    bool HasField(const std::string& variable);

    /**
     * Get a method from the descriptor.
     */
    parser::TFun* GetMethod(const std::string& name);

    /**
     * Add a method to the descriptor
     */
    void PutMethod(const std::string& name, parser::TFun* type);

    /**
     * Check if the descriptor has a method.
     */
    bool HasMethod(const std::string& name);

    /**
     * Set a derived from super descriptor
     */
    void SetSuperDescriptor(ClassDescriptor* superDescriptor);

    /**
     * Check if the descriptor derives from another descriptor.
     */
    bool IsDerivedFrom(ClassDescriptor* cd);

    /**
     * Verify that the class does not override any base fields.
     */
    void Verify();

  private:
    std::map<std::string, std::unique_ptr<parser::TFun, ast::Deleter>> functionTable;
    std::map<std::string, std::unique_ptr<parser::Type, ast::Deleter>> variableTable;
    bool writable;
    ClassDescriptor* superDescriptor;
};

} // namespace checker