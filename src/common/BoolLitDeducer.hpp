#pragma once

#include "ast/BaseVisitor.hpp"
#include "parser/Absyn.H"

namespace common {

class BoolLitDeducerResult
{
  public:
    BoolLitDeducerResult(bool lit, bool value);

    /**
     * Returns the value of the boolean literal.
     */
    [[nodiscard]] bool GetValue() const;

    /**
     * Returns whether the expression is a boolean literal.
     */
    [[nodiscard]] bool IsBoolLit() const;

  private:
    bool boolLit;
    bool value;
};

/**
 * Get the value and if an expression is a boolean literal.
 */
class BoolLitDeducer : public ast::BaseVisitor
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

    /**
     * Accepts the visitor into exp.
     */
    static BoolLitDeducerResult Visit(parser::Exp* exp);

  private:
    BoolLitDeducer();

    bool boolLit;
    bool value;
};

} // namespace common