#pragma once

#include "ast/BaseVisitor.hpp"
#include "checker/ClassDescriptor.hpp"
#include "checker/State.hpp"

namespace checker {

/**
 * Check a member access operand and returns the annotated tree.
 */
class MemberAccessChecker : public ast::BaseVisitor
{
  public:
    void visitEVar(parser::EVar* p) override;
    void visitEInt(parser::EInt* p) override;
    void visitEDouble(parser::EDouble* p) override;
    void visitELitTrue(parser::ELitTrue* p) override;
    void visitELitFalse(parser::ELitFalse* p) override;
    void visitEApp(parser::EApp* p) override;
    void visitEString(parser::EString* p) override;
    void visitENeg(parser::ENeg* p) override;
    void visitENot(parser::ENot* p) override;
    void visitEMul(parser::EMul* p) override;
    void visitEAdd(parser::EAdd* p) override;
    void visitERel(parser::ERel* p) override;
    void visitEAnd(parser::EAnd* p) override;
    void visitEOr(parser::EOr* p) override;
    void visitETyped(parser::ETyped* p) override;

    void visitEAllocate(parser::EAllocate* p) override;
    void visitEDot(parser::EDot* p) override;
    void visitEIndex(parser::EIndex* p) override;

    void visitEDeref(parser::EDeref* p) override;
    void visitENull(parser::ENull* p) override;

    /**
     * Makes an expression accept the visitor with a class descriptor as field/
     * method pool.
     */
    static parser::ETyped* Visit(ClassDescriptor* classDescriptor,
      State* state,
      parser::Exp* exp,
      bool writable,
      bool hideMethods,
      bool hideFields);

  private:
    MemberAccessChecker(ClassDescriptor* classDescriptor,
      State* state,
      bool writable,
      bool hideMethods,
      bool hideFields);
    static void wrongExpression(parser::Exp* p);

    State* state;
    ClassDescriptor* classDescriptor;
    parser::ETyped* annotated;
    bool writable;
    bool hideMethods;
    bool hideFields;
};

} // namespace checker