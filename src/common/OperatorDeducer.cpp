#include "OperatorDeducer.hpp"

#include "ast/BaseVisitor.hpp"

namespace common {

OperatorDeducer::OperatorDeducer()
  : opId(PLUS)
  , ast::BaseVisitor("OperatorDeducer")
{}

void
OperatorDeducer::visitOPlus(parser::OPlus* /*p*/)
{
    opId = PLUS;
}

void
OperatorDeducer::visitOMinus(parser::OMinus* /*p*/)
{
    opId = MINUS;
}

void
OperatorDeducer::visitOTimes(parser::OTimes* /*p*/)
{
    opId = TIMES;
}

void
OperatorDeducer::visitODiv(parser::ODiv* /*p*/)
{
    opId = DIV;
}

void
OperatorDeducer::visitOMod(parser::OMod* /*p*/)
{
    opId = MOD;
}

void
OperatorDeducer::visitOLt(parser::OLt* /*p*/)
{
    opId = LT;
}

void
OperatorDeducer::visitOLe(parser::OLe* /*p*/)
{
    opId = LE;
}

void
OperatorDeducer::visitOGt(parser::OGt* /*p*/)
{
    opId = GT;
}

void
OperatorDeducer::visitOGe(parser::OGe* /*p*/)
{
    opId = GE;
}

void
OperatorDeducer::visitOEq(parser::OEq* /*p*/)
{
    opId = EQ;
}

void
OperatorDeducer::visitONe(parser::ONe* /*p*/)
{
    opId = NE;
}

OpId
OperatorDeducer::Visit(parser::Visitable* op)
{
    OperatorDeducer deducer;
    op->accept(&deducer);
    return deducer.opId;
}

} // namespace common