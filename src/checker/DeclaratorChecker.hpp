#pragma once

#include "ast/BaseVisitor.hpp"
#include "checker/State.hpp"

namespace checker {

/**
 * Checks a declarator and returns the annotated tree.
 */
class DeclaratorChecker : public ast::BaseVisitor
{
  public:
    void visitDecNoInit(parser::DecNoInit* p) override;
    void visitDecInit(parser::DecInit* p) override;

    /**
     * Accepts the visitor into a dec.
     */
    static parser::Dec* Visit(State* state, parser::Type* type, parser::Dec* dec);

  private:
    DeclaratorChecker(State* state, parser::Type* type);

    State* state;
    parser::Dec* annotated;
    parser::Type* type;
};

} // namespace checker