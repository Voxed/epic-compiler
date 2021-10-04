#pragma once

#include "ast/BaseVisitor.hpp"
#include "checker/State.hpp"

namespace checker {

/**
 * Check and add all the fields of a struct and return the annotated tree.
 */
class StructChecker : public ast::BaseVisitor
{
  public:
    explicit StructChecker(State* state);

    void visitDFun(parser::DFun* p) override;
    void visitDPointer(parser::DPointer* p) override;
    void visitDInlinePointer(parser::DInlinePointer* p) override;
    void visitDStruct(parser::DStruct* p) override;

    void visitDClass(parser::DClass* p) override;
    void visitDSubclass(parser::DSubclass* p) override;

    /**
     * Accepts the visitor into a def.
     */
    static parser::Def* Visit(State* state, parser::Def* def);

  private:
    parser::Struct* checkStruct(parser::Struct* s);

    parser::Def* annotated;
    State* state;
};

} // namespace checker