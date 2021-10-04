#include "State.hpp"

namespace compiler {

State::State()
  : parent(nullptr)
  , currentFunction(nullptr)
  , object(nullptr)
  , classDescriptor(nullptr)
{
    context = std::make_unique<llvm::LLVMContext>();
    module = std::make_unique<llvm::Module>("JLC Program", *context);
    dataLayout = std::make_unique<llvm::DataLayout>(module.get());
    builder = std::make_unique<llvm::IRBuilder<>>(*context);
}

State::State(State* parent, llvm::Function* currentFunction)
  : parent(parent)
  , context(nullptr)
  , module(nullptr)
  , dataLayout(nullptr)
  , builder(nullptr)
  , currentFunction(currentFunction)
  , object(nullptr)
  , classDescriptor(nullptr)
{}

State::State(State* parent, ClassDescriptor* classDescriptor, llvm::Value* object)
  : parent(parent)
  , context(nullptr)
  , module(nullptr)
  , dataLayout(nullptr)
  , builder(nullptr)
  , currentFunction(nullptr)
  , object(object)
  , classDescriptor(classDescriptor)
{}

llvm::Value*
State::GetVariable(const std::string& ident)
{
    if (object != nullptr) {
        if (classDescriptor->HasField(ident)) {
            std::vector<llvm::Value*> gepIndices;
            gepIndices.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*GetContext()), 0));
            gepIndices.push_back(
              llvm::ConstantInt::get(llvm::Type::getInt32Ty(*GetContext()), classDescriptor->GetFieldIndex(ident)));
            return GetBuilder()->CreateGEP(object, gepIndices);
        }
    }
    if (variables.contains(ident)) {
        return variables[ident];
    }
    return parent->GetVariable(ident);
}

void
State::PutVariable(const std::string& ident, llvm::Value* value)
{
    variables[ident] = value;
}

llvm::Function*
State::GetCurrentFunction()
{
    if (currentFunction != nullptr) {
        return currentFunction;
    }
    return parent->GetCurrentFunction();
}

ClassDescriptor*
State::GetClassDescriptor(const std::string& ident)
{
    if (classTable.contains(ident)) {
        return classTable[ident].get();
    }
    if (parent != nullptr) {
        return parent->GetClassDescriptor(ident);
    }
    classTable[ident] = std::make_unique<ClassDescriptor>(this, ident);
    return classTable[ident].get();
}

llvm::FunctionCallee
State::GetFunction(const std::string& ident)
{
    if (functions.contains(ident)) {
        return llvm::FunctionCallee(functions[ident]);
    }
    return llvm::FunctionCallee(parent->GetFunction(ident));
}

void
State::PutFunction(const std::string& ident, llvm::Function* value)
{
    functions[ident] = value;
}

void
State::FinalizeDescriptors()
{
    for (auto& cd : classTable) {
        cd.second->Finalize();
    }
}

llvm::LLVMContext*
State::GetContext()
{
    if (context) {
        return context.get();
    }
    return parent->GetContext();
}

llvm::Module*
State::GetModule()
{
    if (module) {
        return module.get();
    }
    return parent->GetModule();
}

llvm::IRBuilder<>*
State::GetBuilder()
{
    if (builder) {
        return builder.get();
    }
    return parent->GetBuilder();
}

llvm::DataLayout*
State::GetDataLayout()
{
    if (dataLayout) {
        return dataLayout.get();
    }
    return parent->GetDataLayout();
}

} // namespace compiler