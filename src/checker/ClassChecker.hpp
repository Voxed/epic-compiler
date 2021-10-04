#pragma once

#include "ast/BaseVisitor.hpp"
#include "checker/ClassDescriptor.hpp"
#include "checker/State.hpp"

namespace checker {

/**
 * Class checker will check and store class members and return an annotated
 * tree with deduced types.
 */
class ClassChecker : public ast::BaseVisitor
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
    explicit ClassChecker(State* state);

    parser::ListMember* CheckClass(parser::ListMember* list, ClassDescriptor* cd);

    parser::Def* annotated;
    State* state;
};

} // namespace checker