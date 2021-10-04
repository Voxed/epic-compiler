#pragma once

#include "ast/BaseVisitor.hpp"
#include "parser/Absyn.H"

namespace common {

/**
 * Operator ID's
 */
enum OpId
{
    PLUS,
    MINUS,
    TIMES,
    DIV,
    MOD,
    LT,
    LE,
    GT,
    GE,
    EQ,
    NE
};

/**
 * Deduces an operator ID.
 */
class OperatorDeducer : public ast::BaseVisitor
{
  public:
    void visitOPlus(parser::OPlus* p) override;
    void visitOMinus(parser::OMinus* p) override;
    void visitOTimes(parser::OTimes* p) override;
    void visitODiv(parser::ODiv* p) override;
    void visitOMod(parser::OMod* p) override;
    void visitOLt(parser::OLt* p) override;
    void visitOLe(parser::OLe* p) override;
    void visitOGt(parser::OGt* p) override;
    void visitOGe(parser::OGe* p) override;
    void visitOEq(parser::OEq* p) override;
    void visitONe(parser::ONe* p) override;

    /**
     * Accepts the visitor into an operator.
     */
    static OpId Visit(parser::Visitable* op);

  private:
    OperatorDeducer();

    OpId opId;
};

} // namespace common