#pragma once

#include "ast/BaseVisitor.hpp"
#include "checker/ClassDescriptor.hpp"
#include "checker/State.hpp"

namespace checker {

/**
 * Check and store a member and return the annotated tree.
 */
class MemberChecker : public ast::BaseVisitor
{
  public:
    void visitMField(parser::MField* p) override;
    void visitMFun(parser::MFun* p) override;

    /**
     * Accepts the visitor into a member.
     */
    static parser::Member* Visit(State* state, ClassDescriptor* classDescriptor, parser::Member* p);

  private:
    MemberChecker(State* state, ClassDescriptor* classDescriptor);

    State* state;
    parser::Member* annotated;
    ClassDescriptor* classDescriptor;
};

} // namespace checker