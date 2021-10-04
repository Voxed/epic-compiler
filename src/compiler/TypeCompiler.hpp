#pragma once

#include "State.hpp"
#include "ast/BaseVisitor.hpp"
#include <llvm/IR/Type.h>

namespace compiler {

/**
 * Compiles a type getting the llvm type.
 */
class TypeCompiler : public ast::BaseVisitor
{
  public:
    void visitTInt(parser::TInt* p) override;
    void visitTDouble(parser::TDouble* p) override;
    void visitTBool(parser::TBool* p) override;
    void visitTArray(parser::TArray* p) override;
    void visitTFun(parser::TFun* p) override;
    void visitTStr(parser::TStr* p) override;
    void visitTVoid(parser::TVoid* p) override;
    void visitTStruct(parser::TStruct* p) override;
    void visitTPointer(parser::TPointer* p) override;
    void visitTClass(parser::TClass* p) override;

    /**
     * Accept the visitor into a type.
     */
    static llvm::Type* Visit(State* state, parser::Type* type);

  private:
    explicit TypeCompiler(State* state);

    State* state;
    llvm::Type* type;
};

} // namespace compiler