#include "ClassDescriptor.hpp"
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Type.h>

#include "State.hpp"

namespace compiler {

ClassDescriptor::ClassDescriptor(State* state, const std::string& name)
  : state(state)
  , superDescriptor(nullptr)
  , vtable(nullptr)
  , type(nullptr)
  , hasvtable(false)
  , finalized(false)
  , name(name)
{
    type = llvm::StructType::create(*state->GetContext(), name);
}

void
ClassDescriptor::PutField(const std::string& ident, llvm::Type* type)
{
    fields[ident] = type;
}

void
ClassDescriptor::PutMethod(const std::string& ident, llvm::Function* fun)
{
    methods[ident] = fun;
}

int
ClassDescriptor::GetFieldIndex(const std::string& ident)
{
    return static_cast<int>((hasvtable ? 1L : 0L) +
                            std::distance(fieldIndex.begin(), std::find(fieldIndex.begin(), fieldIndex.end(), ident)));
}

int
ClassDescriptor::GetMethodIndex(const std::string& ident)
{
    return std::distance(methodIndex.begin(), std::find(methodIndex.begin(), methodIndex.end(), ident));
}

bool
ClassDescriptor::HasField(const std::string& ident)
{
    return std::find(fieldIndex.begin(), fieldIndex.end(), ident) != fieldIndex.end();
}

bool
ClassDescriptor::HasMethod(const std::string& ident)
{
    return std::find(methodIndex.begin(), methodIndex.end(), ident) != methodIndex.end();
}

void
ClassDescriptor::SetSuperDescriptor(ClassDescriptor* cd)
{
    superDescriptor = cd;
}

void
ClassDescriptor::Finalize()
{
    if (!finalized) {
        if (superDescriptor != nullptr) {
            superDescriptor->Finalize();

            fieldIndex = superDescriptor->fieldIndex;
            methodIndex = superDescriptor->methodIndex;

            fieldTypes = superDescriptor->fieldTypes;
            methodValues = superDescriptor->methodValues;
        }
        for (auto& mp : methods) {
            if (HasMethod(mp.first)) {
                methodValues[GetMethodIndex(mp.first)] = mp.second;
            } else {
                methodValues.push_back(mp.second);
                methodIndex.push_back(mp.first);
            }
        }

        for (auto& fp : fields) {
            if (HasField(fp.first)) {
                fieldTypes[GetFieldIndex(fp.first)] = fp.second;
            } else {
                fieldTypes.push_back(fp.second);
                fieldIndex.push_back(fp.first);
            }
        }

        if (!methodValues.empty()) {
            hasvtable = true;
        }

        finalized = true;

        std::vector<llvm::Type*> structTypes;

        if (hasvtable) {
            llvm::StructType* vtableType = llvm::StructType::create(*state->GetContext(), name + "Vtable");
            for (llvm::Constant* f : methodValues) {
                structTypes.push_back(f->getType());
            }
            vtableType->setBody(structTypes);
            vtable = new llvm::GlobalVariable(*state->GetModule(),
              vtableType,
              false,
              llvm::GlobalValue::ExternalLinkage,
              llvm::ConstantStruct::get(vtableType, methodValues),
              name + ".vtable");
        }

        structTypes = fieldTypes;
        if (hasvtable) {
            structTypes.insert(structTypes.begin(), GetVtable()->getType());
        }
        type->setBody(structTypes);
    }
}

llvm::Function*
ClassDescriptor::GetMethod(const std::string& ident)
{
    return methods[ident];
}

llvm::StructType*
ClassDescriptor::GetType()
{
    return type;
}

llvm::Value*
ClassDescriptor::GetVtable()
{
    return vtable;
}

} // namespace compiler