#pragma once

#include "State.hpp"
#include "ast/BaseVisitor.hpp"
#include "compiler/ClassDescriptor.hpp"

namespace compiler {

/**
 * Compiles a method and it's inner code with the state inheriting from the
 * class descriptor.
 */
class MethodCompiler : public ast::BaseVisitor
{
  public:
    void visitMField(parser::MField* p) override;
    void visitMFun(parser::MFun* p) override;

    /**
     * Accept the visitor into a member.
     */
    static void Visit(State* state, ClassDescriptor* classDescriptor, parser::Member* member);

  private:
    MethodCompiler(State* state, ClassDescriptor* classDescriptor);

    State* state;
    ClassDescriptor* classDescriptor;
};

} // namespace compiler