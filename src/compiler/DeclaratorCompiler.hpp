#pragma once

#include "State.hpp"
#include "ast/BaseVisitor.hpp"

namespace compiler {

/**
 * Compile a declarator.
 */
class DeclaratorCompiler : public ast::BaseVisitor
{
  public:
    void visitDecInit(parser::DecInit* p) override;
    void visitDecNoInit(parser::DecNoInit* p) override;

    /**
     * Accept the visitor into a dec.
     */
    static void Visit(State* state, parser::Type* type, parser::Dec* dec);

  private:
    DeclaratorCompiler(State* state, parser::Type* type);

    State* state;
    parser::Type* type;
};

} // namespace compiler