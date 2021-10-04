#include "ClassDescriptor.hpp"

#include "common/Exceptions.hpp"
#include "common/TypeDeducer.hpp"

namespace checker {

ClassDescriptor::ClassDescriptor(bool writable)
  : writable(writable)
  , superDescriptor(nullptr)
{}

parser::Type*
ClassDescriptor::GetField(const std::string& variable)
{
    if (!variableTable.contains(variable)) {
        if (superDescriptor != nullptr) {
            return superDescriptor->GetField(variable);
        }
        throw common::CheckerException("Field not declared, " + variable);
    }
    return variableTable[variable].get();
}

void
ClassDescriptor::PutField(const std::string& variable, parser::Type* type)
{
    if (variableTable.contains(variable)) {
        throw common::CheckerException("Field already declared, " + variable);
    }
    variableTable[variable] = std::unique_ptr<parser::Type, ast::Deleter>(type);
}

bool
ClassDescriptor::HasField(const std::string& variable)
{
    if (variableTable.contains(variable)) {
        return true;
    }
    if (superDescriptor != nullptr) {
        return superDescriptor->HasField(variable);
    }
    return false;
}

void
ClassDescriptor::PutMethod(const std::string& name, parser::TFun* type)
{
    if (functionTable.contains(name)) {
        throw common::CheckerException("Method already declared, " + name);
    }
    functionTable[name] = std::unique_ptr<parser::TFun, ast::Deleter>(type);
}

parser::TFun*
ClassDescriptor::GetMethod(const std::string& name)
{
    if (!functionTable.contains(name)) {
        if (superDescriptor != nullptr) {
            return superDescriptor->GetMethod(name);
        }
        throw common::CheckerException("Method not declared, " + name);
    }
    return functionTable[name].get();
}

bool
ClassDescriptor::HasMethod(const std::string& name)
{
    if (functionTable.contains(name)) {
        return true;
    }
    if (superDescriptor != nullptr) {
        return superDescriptor->HasMethod(name);
    }
    return false;
}

void
ClassDescriptor::SetSuperDescriptor(ClassDescriptor* superDescriptor)
{
    if (superDescriptor->IsDerivedFrom(this)) {
        throw common::CheckerException("Cyclic inheritance");
    }
    this->superDescriptor = superDescriptor;
}

bool
ClassDescriptor::IsDerivedFrom(ClassDescriptor* cd)
{
    if (this == cd) {
        return true; // Base of itself.
    }
    if (superDescriptor != nullptr) {
        return superDescriptor->IsDerivedFrom(cd);
    }
    return false;
}

void
ClassDescriptor::Verify()
{
    if (superDescriptor != nullptr) {
        for (auto& f : functionTable) {
            if (superDescriptor->HasMethod(f.first)) {
                parser::Type* fType = superDescriptor->GetMethod(f.first);
                if (!common::CompareTypes(f.second.get(), fType)) {
                    throw common::CheckerException("Virtual function has the wrong signature");
                }
            }
        }
        for (auto& v : variableTable) {
            if (superDescriptor->HasField(v.first)) {
                throw common::CheckerException("Field " + v.first + " already declared in base class");
            }
        }
    }
}

} // namespace checker