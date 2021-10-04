#include "Compile.hpp"

#include "compiler/ClassCompiler.hpp"
#include "compiler/ClassMethodCompiler.hpp"
#include "compiler/FunctionCompiler.hpp"
#include "compiler/State.hpp"
#include "compiler/StructCompiler.hpp"
#include "compiler/TopDecCompiler.hpp"
#include "llvm/IR/Value.h"

namespace compiler {

std::string
Compile(parser::Program* annotated)
{
    State state;

    // printInt
    std::vector<llvm::Type*> printIntArgTypes;
    printIntArgTypes.push_back(llvm::Type::getInt32Ty(*state.GetContext()));
    llvm::FunctionType* printIntType =
      llvm::FunctionType::get(llvm::Type::getVoidTy(*state.GetContext()), printIntArgTypes, false);
    state.PutFunction("printInt",
      llvm::Function::Create(printIntType, llvm::Function::ExternalLinkage, "printInt", *state.GetModule()));

    // printDouble
    std::vector<llvm::Type*> printDoubleArgTypes;
    printDoubleArgTypes.push_back(llvm::Type::getDoubleTy(*state.GetContext()));
    llvm::FunctionType* printDoubleType =
      llvm::FunctionType::get(llvm::Type::getVoidTy(*state.GetContext()), printDoubleArgTypes, false);
    state.PutFunction("printDouble",
      llvm::Function::Create(printDoubleType, llvm::Function::ExternalLinkage, "printDouble", *state.GetModule()));

    // printString
    std::vector<llvm::Type*> printStringArgTypes;
    printStringArgTypes.push_back(llvm::Type::getInt8PtrTy(*state.GetContext()));
    llvm::FunctionType* printStringType =
      llvm::FunctionType::get(llvm::Type::getVoidTy(*state.GetContext()), printStringArgTypes, false);
    state.PutFunction("printString",
      llvm::Function::Create(printStringType, llvm::Function::ExternalLinkage, "printString", *state.GetModule()));

    // readInt
    llvm::FunctionType* readIntType = llvm::FunctionType::get(llvm::Type::getInt32Ty(*state.GetContext()), false);
    state.PutFunction(
      "readInt", llvm::Function::Create(readIntType, llvm::Function::ExternalLinkage, "readInt", *state.GetModule()));

    // readDouble
    llvm::FunctionType* readDoubleType = llvm::FunctionType::get(llvm::Type::getDoubleTy(*state.GetContext()), false);
    state.PutFunction("readDouble",
      llvm::Function::Create(readDoubleType, llvm::Function::ExternalLinkage, "readDouble", *state.GetModule()));

    // calloc
    std::vector<llvm::Type*> callocArgTypes(2, llvm::Type::getInt64Ty(*state.GetContext()));
    llvm::FunctionType* callocType =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*state.GetContext()), callocArgTypes, false);
    state.PutFunction(
      "calloc", llvm::Function::Create(callocType, llvm::Function::ExternalLinkage, "calloc", state.GetModule()));

    auto* p = static_cast<parser::PDefs*>(annotated);

    // Definitions
    for (parser::Def* def : *p->listdef_) {
        TopDecCompiler::Visit(&state, def);
    }

    // Structs
    for (parser::Def* def : *p->listdef_) {
        StructCompiler::Visit(&state, def);
    }

    // Classes
    for (parser::Def* def : *p->listdef_) {
        ClassCompiler::Visit(&state, def);
    }

    state.FinalizeDescriptors();

    // Methods
    for (parser::Def* def : *p->listdef_) {
        ClassMethodCompiler::Visit(&state, def);
    }

    // Functions
    for (parser::Def* def : *p->listdef_) {
        FunctionCompiler::Visit(&state, def);
    }

    std::string Str;
    llvm::raw_string_ostream OS(Str);
    OS << *state.GetModule();
    OS.flush();

    return Str;
}

} // namespace compiler