#pragma once

#include "ast/BaseVisitor.hpp"
#include "checker/State.hpp"

namespace checker {

/**
 * Checks and adds all top declarations to the state.
 */
class TopDecChecker : public ast::BaseVisitor
{
  public:
    void visitDFun(parser::DFun* p) override;
    void visitDPointer(parser::DPointer* p) override;
    void visitDInlinePointer(parser::DInlinePointer* p) override;
    void visitDStruct(parser::DStruct* p) override;

    void visitDClass(parser::DClass* p) override;
    void visitDSubclass(parser::DSubclass* p) override;

    /**
     * Accepts the visitor into a def.
     */
    static void Visit(State* state, parser::Def* def);

  private:
    explicit TopDecChecker(State* state);

    State* state;
};

} // namespace checker