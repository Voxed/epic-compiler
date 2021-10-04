#pragma once

#include "State.hpp"
#include "ast/BaseVisitor.hpp"
#include "compiler/ClassDescriptor.hpp"
#include <llvm/IR/Value.h>

namespace compiler {

/*
 * Compile a member access operator.
 */
class MemberAccessCompiler : public ast::BaseVisitor
{
  public:
    void visitEVar(parser::EVar* p) override;
    void visitEApp(parser::EApp* p) override;
    void visitETyped(parser::ETyped* p) override;

    /*
     * Accepts the visitor into an expression. Class descriptor is the descriptor to get indices from, object is the
     * llvm value which contains them.
     */
    static llvm::Value* Visit(llvm::Value* object, ClassDescriptor* classDescriptor, State* state, parser::Exp* exp);

  private:
    MemberAccessCompiler(llvm::Value* object, ClassDescriptor* classDescriptor, State* state);

    llvm::Value* object;
    llvm::Value* value;
    State* state;
    ClassDescriptor* classDescriptor;
};

} // namespace compiler