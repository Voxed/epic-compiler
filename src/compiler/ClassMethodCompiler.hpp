#pragma once

#include "State.hpp"
#include "ast/BaseVisitor.hpp"

namespace compiler {

/**
 * Compile all methods in a class.
 */
class ClassMethodCompiler : public ast::BaseVisitor
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
    explicit ClassMethodCompiler(State* state);

    State* state;
};

} // namespace compiler