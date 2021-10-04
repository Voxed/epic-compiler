#include "BaseVisitor.hpp"

#include "common/Exceptions.hpp"
#include "parser/Absyn.H"

using namespace parser;

namespace ast {

BaseVisitor::BaseVisitor(const char* visitorName)
  : visitorName(visitorName)
{}

void
BaseVisitor::unimplemented(const char* syntaxName)
{
    throw common::UnimplementedException(
      std::string("Attempted to visit unimplemented syntax ") + syntaxName + " on visitor " + visitorName);
}

void
BaseVisitor::visitProgram(Program* /*p*/)
{
    unimplemented("Program");
}
void
BaseVisitor::visitDef(Def* /*p*/)
{
    unimplemented("Def");
}
void
BaseVisitor::visitArg(Arg* /*p*/)
{
    unimplemented("Arg");
}
void
BaseVisitor::visitStm(Stm* /*p*/)
{
    unimplemented("Stm");
}
void
BaseVisitor::visitDec(Dec* /*p*/)
{
    unimplemented("Dec");
}
void
BaseVisitor::visitType(Type* /*p*/)
{
    unimplemented("Type");
}
void
BaseVisitor::visitExp(Exp* /*p*/)
{
    unimplemented("Exp");
}
void
BaseVisitor::visitAddOp(AddOp* /*p*/)
{
    unimplemented("AddOp");
}
void
BaseVisitor::visitMulOp(MulOp* /*p*/)
{
    unimplemented("MulOp");
}
void
BaseVisitor::visitRelOp(RelOp* /*p*/)
{
    unimplemented("RelOp");
}
void
BaseVisitor::visitPDefs(PDefs* /*p*/)
{
    unimplemented("PDefs");
}
void
BaseVisitor::visitDFun(DFun* /*p*/)
{
    unimplemented("DFun");
}
void
BaseVisitor::visitADecl(ADecl* /*p*/)
{
    unimplemented("ADecl");
}
void
BaseVisitor::visitSEmpty(SEmpty* /*p*/)
{
    unimplemented("SEmpty");
}
void
BaseVisitor::visitSBlock(SBlock* /*p*/)
{
    unimplemented("SBlock");
}
void
BaseVisitor::visitSDecl(SDecl* /*p*/)
{
    unimplemented("SDecl");
}
void
BaseVisitor::visitSAss(SAss* /*p*/)
{
    unimplemented("SAss");
}
void
BaseVisitor::visitSIncr(SIncr* /*p*/)
{
    unimplemented("SIncr");
}
void
BaseVisitor::visitSDecr(SDecr* /*p*/)
{
    unimplemented("SDecr");
}
void
BaseVisitor::visitSRet(SRet* /*p*/)
{
    unimplemented("SRet");
}
void
BaseVisitor::visitSVRet(SVRet* /*p*/)
{
    unimplemented("SVRet");
}
void
BaseVisitor::visitSCond(SCond* /*p*/)
{
    unimplemented("SCond");
}
void
BaseVisitor::visitSCondElse(SCondElse* /*p*/)
{
    unimplemented("SCondElse");
}
void
BaseVisitor::visitSWhile(SWhile* /*p*/)
{
    unimplemented("SWhile");
}
void
BaseVisitor::visitSExp(SExp* /*p*/)
{
    unimplemented("SExp");
}
void
BaseVisitor::visitDecNoInit(DecNoInit* /*p*/)
{
    unimplemented("DecNoInit");
}
void
BaseVisitor::visitDecInit(DecInit* /*p*/)
{
    unimplemented("DecInit");
}
void
BaseVisitor::visitTInt(TInt* /*p*/)
{
    unimplemented("TInt");
}
void
BaseVisitor::visitTDouble(TDouble* /*p*/)
{
    unimplemented("TDouble");
}
void
BaseVisitor::visitTBool(TBool* /*p*/)
{
    unimplemented("TBool");
}
void
BaseVisitor::visitTVoid(TVoid* /*p*/)
{
    unimplemented("TVoid");
}
void
BaseVisitor::visitTStr(TStr* /*p*/)
{
    unimplemented("TStr");
}
void
BaseVisitor::visitTFun(TFun* /*p*/)
{
    unimplemented("TFun");
}
void
BaseVisitor::visitEVar(EVar* /*p*/)
{
    unimplemented("EVar");
}
void
BaseVisitor::visitEInt(EInt* /*p*/)
{
    unimplemented("EInt");
}
void
BaseVisitor::visitEDouble(EDouble* /*p*/)
{
    unimplemented("EDouble");
}
void
BaseVisitor::visitELitFalse(ELitFalse* /*p*/)
{
    unimplemented("ELitFalse");
}
void
BaseVisitor::visitELitTrue(ELitTrue* /*p*/)
{
    unimplemented("ELitTrue");
}
void
BaseVisitor::visitEApp(EApp* /*p*/)
{
    unimplemented("EApp");
}
void
BaseVisitor::visitEString(EString* /*p*/)
{
    unimplemented("EString");
}
void
BaseVisitor::visitENeg(ENeg* /*p*/)
{
    unimplemented("ENeg");
}
void
BaseVisitor::visitENot(ENot* /*p*/)
{
    unimplemented("ENot");
}
void
BaseVisitor::visitEMul(EMul* /*p*/)
{
    unimplemented("EMul");
}
void
BaseVisitor::visitEAdd(EAdd* /*p*/)
{
    unimplemented("EAdd");
}
void
BaseVisitor::visitERel(ERel* /*p*/)
{
    unimplemented("ERel");
}
void
BaseVisitor::visitEAnd(EAnd* /*p*/)
{
    unimplemented("EAnd");
}
void
BaseVisitor::visitEOr(EOr* /*p*/)
{
    unimplemented("EOr");
}
void
BaseVisitor::visitETyped(ETyped* /*p*/)
{
    unimplemented("ETyped");
}
void
BaseVisitor::visitOPlus(OPlus* /*p*/)
{
    unimplemented("OPlus");
}
void
BaseVisitor::visitOMinus(OMinus* /*p*/)
{
    unimplemented("OMinus");
}
void
BaseVisitor::visitOTimes(OTimes* /*p*/)
{
    unimplemented("OTimes");
}
void
BaseVisitor::visitODiv(ODiv* /*p*/)
{
    unimplemented("ODiv");
}
void
BaseVisitor::visitOMod(OMod* /*p*/)
{
    unimplemented("OMod");
}
void
BaseVisitor::visitOLt(OLt* /*p*/)
{
    unimplemented("OLt");
}
void
BaseVisitor::visitOLe(OLe* /*p*/)
{
    unimplemented("OLe");
}
void
BaseVisitor::visitOGt(OGt* /*p*/)
{
    unimplemented("OGt");
}
void
BaseVisitor::visitOGe(OGe* /*p*/)
{
    unimplemented("OGe");
}
void
BaseVisitor::visitOEq(OEq* /*p*/)
{
    unimplemented("OEq");
}
void
BaseVisitor::visitONe(ONe* /*p*/)
{
    unimplemented("ONe");
}
void
BaseVisitor::visitListDef(ListDef* /*p*/)
{
    unimplemented("ListDef");
}
void
BaseVisitor::visitListArg(ListArg* /*p*/)
{
    unimplemented("ListArg");
}
void
BaseVisitor::visitListStm(ListStm* /*p*/)
{
    unimplemented("ListStm");
}
void
BaseVisitor::visitListDec(ListDec* /*p*/)
{
    unimplemented("ListDec");
}
void
BaseVisitor::visitListType(ListType* /*p*/)
{
    unimplemented("ListType");
}
void
BaseVisitor::visitListExp(ListExp* /*p*/)
{
    unimplemented("ListExp");
}
void BaseVisitor::visitInteger(Integer /*x*/)
{
    unimplemented("Integer");
}
void BaseVisitor::visitChar(Char /*x*/)
{
    unimplemented("Char");
}
void BaseVisitor::visitDouble(Double /*x*/)
{
    unimplemented("Double");
}
void BaseVisitor::visitString(String /*x*/)
{
    unimplemented("String");
}
void BaseVisitor::visitIdent(Ident /*x*/)
{
    unimplemented("Ident");
}

void
BaseVisitor::visitEIndex(parser::EIndex* /*p*/)
{
    unimplemented("EIndex");
}
void
BaseVisitor::visitSForEach(parser::SForEach* /*p*/)
{
    unimplemented("SForEach");
}
void
BaseVisitor::visitTArray(parser::TArray* /*p*/)
{
    unimplemented("TArray");
}
void
BaseVisitor::visitEAllocate(parser::EAllocate* /*p*/)
{
    unimplemented("EAllocate");
}
void
BaseVisitor::visitEDot(parser::EDot* /*p*/)
{
    unimplemented("EDot");
}
void
BaseVisitor::visitLLength(parser::LLength* /*p*/)
{
    unimplemented("LLength");
}
void
BaseVisitor::visitLength(parser::Length* /*p*/)
{
    unimplemented("Length");
}
void
BaseVisitor::visitListLength(parser::ListLength* /*p*/)
{
    unimplemented("ListLength");
}

void
BaseVisitor::visitTIdent(parser::TIdent* /*p*/)
{
    unimplemented("TIdent");
}
void
BaseVisitor::visitTPointer(parser::TPointer* /*p*/)
{
    unimplemented("TPointer");
}
void
BaseVisitor::visitTStruct(parser::TStruct* /*p*/)
{
    unimplemented("TStruct");
}
void
BaseVisitor::visitDPointer(parser::DPointer* /*p*/)
{
    unimplemented("DPointer");
}
void
BaseVisitor::visitStruct(parser::Struct* /*p*/)
{
    unimplemented("Struct");
}
void
BaseVisitor::visitSStruct(parser::SStruct* /*p*/)
{
    unimplemented("SStruct");
}
void
BaseVisitor::visitDStruct(parser::DStruct* /*p*/)
{
    unimplemented("DStruct");
}
void
BaseVisitor::visitDInlinePointer(parser::DInlinePointer* /*p*/)
{
    unimplemented("DInlinePointer");
}
void
BaseVisitor::visitField(parser::Field* /*p*/)
{
    unimplemented("Field");
}
void
BaseVisitor::visitFField(parser::FField* /*p*/)
{
    unimplemented("FField");
}
void
BaseVisitor::visitListField(parser::ListField* /*p*/)
{
    unimplemented("ListField");
}
void
BaseVisitor::visitEDeref(parser::EDeref* /*p*/)
{
    unimplemented("EDeref");
}
void
BaseVisitor::visitENull(parser::ENull* /*p*/)
{
    unimplemented("ENull");
}

void
BaseVisitor::visitTClass(parser::TClass* /*p*/)
{
    unimplemented("TClass");
}
void
BaseVisitor::visitDSubclass(parser::DSubclass* /*p*/)
{
    unimplemented("DSubclass");
}
void
BaseVisitor::visitDClass(parser::DClass* /*p*/)
{
    unimplemented("DClass");
}
void
BaseVisitor::visitListMember(parser::ListMember* /*p*/)
{
    unimplemented("ListMember");
}
void
BaseVisitor::visitMember(parser::Member* /*p*/)
{
    unimplemented("Member");
}
void
BaseVisitor::visitMField(parser::MField* /*p*/)
{
    unimplemented("MField");
}
void
BaseVisitor::visitMFun(parser::MFun* /*p*/)
{
    unimplemented("MFun");
}
void
BaseVisitor::visitECast(parser::ECast* /*p*/)
{
    unimplemented("ECast");
}

} // namespace ast