#pragma once

#include "ast/BaseVisitor.hpp"
#include "checker/State.hpp"

namespace checker {

/**
 * Checks a function and returns the annotated tree.
 */
class FunctionChecker : public ast::BaseVisitor
{
  public:
    void visitDFun(parser::DFun* p) override;
    void visitDPointer(parser::DPointer* p) override;
    void visitDStruct(parser::DStruct* p) override;
    void visitDInlinePointer(parser::DInlinePointer* p) override;

    void visitDClass(parser::DClass* p) override;
    void visitDSubclass(parser::DSubclass* p) override;

    /**
     * Accepts the visitor into a def.
     */
    static parser::Def* Visit(State* state, parser::Def* def);

  private:
    explicit FunctionChecker(State* state);

    State* state;
    parser::Def* annotated;
};

} // namespace checker