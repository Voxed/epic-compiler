#pragma once

#include "State.hpp"
#include "ast/BaseVisitor.hpp"

namespace compiler {

/**
 * Compile a class and add it's members to it's class descriptor.
 * Does not touch the inner method code.
 */
class ClassCompiler : public ast::BaseVisitor
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
    explicit ClassCompiler(State* state);

    State* state;
};

} // namespace compiler