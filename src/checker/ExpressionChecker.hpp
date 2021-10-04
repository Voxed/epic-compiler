#pragma once

#include "ast/BaseVisitor.hpp"
#include "checker/State.hpp"

namespace checker {

/**
 * Checks an expression and returns the annotated tree.
 */
class ExpressionChecker : public ast::BaseVisitor
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
     * Makes an expression accept the visitor with an expected return type.
     */
    static parser::ETyped* Visit(State* state, parser::Exp* exp, parser::Type* type = nullptr);

  private:
    explicit ExpressionChecker(State* state);

    static void checkBinary(parser::ETyped* typed1, parser::ETyped* typed2, bool boolOperator, bool allowBool);

    State* state;
    parser::ETyped* annotated;
};

} // namespace checker