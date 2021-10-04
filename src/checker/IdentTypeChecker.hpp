#pragma once

#include "State.hpp"
#include "ast/BaseVisitor.hpp"
#include "parser/Absyn.H"

namespace checker {

/**
 * Checks and returns a type, if it's of type TIdent, returns the assigned type
 * from state.
 */
class IdentTypeChecker : public ast::BaseVisitor
{
  public:
    void visitTIdent(parser::TIdent* p) override;
    void visitTInt(parser ::TInt* p) override;
    void visitTDouble(parser ::TDouble* p) override;
    void visitTBool(parser ::TBool* p) override;
    void visitTVoid(parser ::TVoid* p) override;
    void visitTArray(parser ::TArray* p) override;

    /**
     * Accepts the visitor into a type.
     */
    static parser::Type* Visit(State* state, parser::Type* type);

  private:
    explicit IdentTypeChecker(State* state);

    State* state;
    parser::Type* type;
};

} // namespace checker