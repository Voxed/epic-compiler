#include "BoolLitDeducer.hpp"

#include "ast/BaseVisitor.hpp"

namespace common {

BoolLitDeducer::BoolLitDeducer()
  : boolLit(false)
  , value(false)
  , ast::BaseVisitor("BoolLitDeducer")
{}

void
BoolLitDeducer::visitEVar(parser::EVar* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitEInt(parser::EInt* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitEDouble(parser::EDouble* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitELitTrue(parser::ELitTrue* /*p*/)
{
    boolLit = true;
    value = true;
}

void
BoolLitDeducer::visitELitFalse(parser::ELitFalse* /*p*/)
{
    boolLit = true;
    value = false;
}

void
BoolLitDeducer::visitEApp(parser::EApp* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitEString(parser::EString* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitENeg(parser::ENeg* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitENot(parser::ENot* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitEMul(parser::EMul* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitEAdd(parser::EAdd* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitERel(parser::ERel* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitEAnd(parser::EAnd* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitEOr(parser::EOr* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitETyped(parser::ETyped* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitEAllocate(parser::EAllocate* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitEDot(parser::EDot* /*p*/)
{
    boolLit = false;
}

void
BoolLitDeducer::visitEIndex(parser::EIndex* /*p*/)
{
    boolLit = false;
}

BoolLitDeducerResult
BoolLitDeducer::Visit(parser::Exp* exp)
{
    BoolLitDeducer deducer;
    exp->accept(&deducer);
    return BoolLitDeducerResult(deducer.boolLit, deducer.value);
}

BoolLitDeducerResult::BoolLitDeducerResult(bool lit, bool value)
  : boolLit(lit)
  , value(value)
{}

/**
 * Returns the value of the boolean literal.
 */
bool
BoolLitDeducerResult::GetValue() const
{
    return value;
}

/**
 * Returns whether the expression is a boolean literal.
 */
bool
BoolLitDeducerResult::IsBoolLit() const
{
    return boolLit;
}

} // namespace common