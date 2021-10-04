#pragma once

#include "State.hpp"
#include "ast/BaseVisitor.hpp"
#include "compiler/ClassDescriptor.hpp"
#include "parser/Absyn.H"

namespace compiler {

/**
 * Compile and add all members of a class to a class descriptor.
 * Does not touch method inner code.
 */
class MemberCompiler : public ast::BaseVisitor
{
  public:
    void visitMField(parser::MField* p) override;
    void visitMFun(parser::MFun* p) override;

    /**
     * Accepts the visitor into a member.
     */
    static void Visit(State* state, ClassDescriptor* classDescriptor, parser::Member* member);

  private:
    MemberCompiler(State* state, ClassDescriptor* classDescriptor);

    State* state;
    ClassDescriptor* classDescriptor;
};

} // namespace compiler