#pragma once

#include "State.hpp"
#include "ast/BaseVisitor.hpp"
#include "parser/Absyn.H"

namespace compiler {

/**
 * Compile a function.
 */
class FunctionCompiler : public ast::BaseVisitor
{
  public:
    void visitDFun(parser::DFun* p) override;
    void visitDStruct(parser::DStruct* p) override;
    void visitDInlinePointer(parser::DInlinePointer* p) override;
    void visitDPointer(parser::DPointer* p) override;
    void visitSStruct(parser::SStruct* p) override;

    void visitDClass(parser::DClass* p) override;
    void visitDSubclass(parser::DSubclass* p) override;

    /**
     * Accept the visitor into a def.
     */
    static void Visit(State* state, parser::Def* def);

  private:
    explicit FunctionCompiler(State* state);

    State* state;
};

} // namespace compiler