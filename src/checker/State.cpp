#include "State.hpp"
#include "common/Exceptions.hpp"
#include "common/TypeDeducer.hpp"

namespace checker {

State::State(State* parent, ClassDescriptor* classDescriptor)
  : parent(parent)
  , doesReturn(false)
  , classDescriptor(classDescriptor)
{}

void
State::PutVariable(const std::string& variable, parser::Type* type)
{
    if (variableTable.contains(variable)) {
        throw common::CheckerException("Variable already declared, " + variable);
    }
    variableTable[variable] = std::unique_ptr<parser::Type, ast::Deleter>(type);
}

parser::Type*
State::GetVariable(const std::string& variable)
{
    if (classDescriptor != nullptr) {
        if (classDescriptor->HasField(variable)) {
            return classDescriptor->GetField(variable);
        }
    }
    if (variableTable.contains(variable)) {
        return variableTable[variable].get();
    }
    if (parent != nullptr) {
        return parent->GetVariable(variable);
    }
    throw common::CheckerException("Variable not declared, " + variable);
}

void
State::PutFunction(const std::string& name, parser::TFun* type)
{
    if (functionTable.contains(name)) {
        throw common::CheckerException("Function already declared, " + name);
    }
    functionTable[name] = std::unique_ptr<parser::TFun, ast::Deleter>(type);
}

parser::TFun*
State::GetFunction(const std::string& name)
{
    if (functionTable.contains(name)) {
        return functionTable[name].get();
    }
    if (parent != nullptr) {
        return parent->GetFunction(name);
    }
    throw common::CheckerException("Function not declared, " + name);
}

void
State::PutType(const std::string& typeName, parser::Type* type)
{
    if (typeDeclarations.contains(typeName)) {
        throw common::CheckerException("Type " + typeName + " already declared");
    }
    typeDeclarations[typeName] = std::unique_ptr<parser::Type, ast::Deleter>(type);
}

parser::Type*
State::GetType(const std::string& typeName)
{
    if (typeDeclarations.contains(typeName)) {
        return typeDeclarations[typeName].get();
    }
    if (parent != nullptr) {
        return parent->GetType(typeName);
    }
    throw common::CheckerException("Type " + typeName + " is not declared");
}

bool
State::HasType(const std::string& typeName)
{
    return typeDeclarations.contains(typeName);
}

ClassDescriptor*
State::GetClassDescriptor(const std::string& id)
{
    if (classDescriptorTable.contains(id)) {
        return classDescriptorTable[id].get();
    }
    if (parent != nullptr) {
        return parent->GetClassDescriptor(id);
    }
    classDescriptorTable[id] = std::make_unique<ClassDescriptor>(true);
    return classDescriptorTable[id].get();
}

bool
State::GetDoesReturn() const
{
    return doesReturn;
}

void
State::SetDoesReturn()
{
    doesReturn = true;
}

void
State::SetReturnType(parser::Type* type)
{
    returnType = std::unique_ptr<parser::Type, ast::Deleter>(type);
}

parser::Type*
State::GetReturnType()
{
    if (!returnType) {
        return parent->GetReturnType();
    }
    return returnType.get();
}

void
State::Verify()
{
    for (auto& t : typeDeclarations) {
        parser::Type* type = t.second.get();
        if (common::CompareType(type, common::POINTER)) {
            auto* pType = static_cast<parser::TPointer*>(type);
            if (!HasType(pType->ident_)) {
                throw common::CheckerException("Type referenced by " + t.first + " is not defined, " + pType->ident_);
            }
            parser::Type* type = GetType(pType->ident_);
            if (!common::CompareType(type, common::STRUCT)) {
                throw common::CheckerException("Type referenced by " + t.first + " is not a struct, " + pType->ident_);
            }
        }
    }
    for (auto& cd : classDescriptorTable) {
        cd.second->Verify();
    }
}

} // namespace checker