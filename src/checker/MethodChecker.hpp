#pragma once

#include "ast/BaseVisitor.hpp"
#include "checker/ClassDescriptor.hpp"
#include "checker/State.hpp"
#include "parser/Absyn.H"

namespace checker {

/**
 * Check a method and return the annotated tree.
 */
class MethodChecker : public ast::BaseVisitor
{
  public:
    void visitMField(parser::MField* p) override;
    void visitMFun(parser::MFun* p) override;

    /**
     * Accepts the visitor into a member.
     */
    static parser::Member* Visit(State* state, parser::Member* p);

  private:
    explicit MethodChecker(State* state);

    State* state;
    parser::Member* annotated;
};

} // namespace checker