#include "TypeCompiler.hpp"

namespace compiler {

TypeCompiler::TypeCompiler(State* state)
  : state(state)
  , type(nullptr)
  , ast::BaseVisitor("TypeCompiler")
{}

void
TypeCompiler::visitTInt(parser::TInt* /*p*/)
{
    type = llvm::Type::getInt32Ty(*state->GetContext());
}

void
TypeCompiler::visitTDouble(parser::TDouble* /*p*/)
{
    type = llvm::Type::getDoubleTy(*state->GetContext());
}

void
TypeCompiler::visitTBool(parser::TBool* /*p*/)
{
    type = llvm::Type::getInt1Ty(*state->GetContext());
}

void
TypeCompiler::visitTArray(parser::TArray* p)
{
    llvm::Type* aType = llvm::ArrayType::get(TypeCompiler::Visit(state, p->type_), 0);

    std::vector<llvm::Type*> sTypes;
    sTypes.push_back(llvm::Type::getInt32Ty(*state->GetContext()));
    sTypes.push_back(aType);

    llvm::Type* sType = llvm::StructType::get(*state->GetContext(), sTypes, false);

    type = sType->getPointerTo();
}

void
TypeCompiler::visitTFun(parser::TFun* /*p*/)
{}

void
TypeCompiler::visitTStr(parser::TStr* /*p*/)
{
    type = llvm::Type::getInt8PtrTy(*state->GetContext());
}

void
TypeCompiler::visitTVoid(parser::TVoid* /*p*/)
{
    type = llvm::Type::getVoidTy(*state->GetContext());
}

void
TypeCompiler::visitTStruct(parser::TStruct* p)
{
    type = state->GetClassDescriptor(p->ident_)->GetType();
}

void
TypeCompiler::visitTPointer(parser::TPointer* p)
{
    type = state->GetClassDescriptor(p->ident_)->GetType()->getPointerTo();
}

void
TypeCompiler::visitTClass(parser::TClass* p)
{
    type = state->GetClassDescriptor(p->ident_)->GetType()->getPointerTo();
}

llvm::Type*
TypeCompiler::Visit(State* state, parser::Type* type)
{
    TypeCompiler compiler(state);
    type->accept(&compiler);
    return compiler.type;
}

} // namespace compiler