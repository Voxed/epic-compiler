#pragma once

#include "ast/BaseVisitor.hpp"
#include "checker/State.hpp"

namespace checker {

/**
 * Checks all methods of a class and returns the annotated tree.
 */
class ClassMethodChecker : public ast::BaseVisitor
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
    static parser::Def* Visit(State* state, parser::Def* def);

  private:
    explicit ClassMethodChecker(State* state);

    parser::ListMember* checkClassMethods(parser::ListMember* list, parser::TClass* selfType);

    parser::Def* annotated;
    State* state;
};

} // namespace checker
