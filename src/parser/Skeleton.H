#ifndef PARSER_SKELETON_HEADER
#define PARSER_SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.H"

namespace parser
{
class Skeleton : public Visitor
{
public:
  void visitProgram(Program *p);
  void visitDef(Def *p);
  void visitArg(Arg *p);
  void visitStm(Stm *p);
  void visitDec(Dec *p);
  void visitType(Type *p);
  void visitExp(Exp *p);
  void visitAddOp(AddOp *p);
  void visitMulOp(MulOp *p);
  void visitRelOp(RelOp *p);
  void visitLength(Length *p);
  void visitStruct(Struct *p);
  void visitField(Field *p);
  void visitMember(Member *p);
  void visitPDefs(PDefs *p);
  void visitDFun(DFun *p);
  void visitADecl(ADecl *p);
  void visitSEmpty(SEmpty *p);
  void visitSBlock(SBlock *p);
  void visitSDecl(SDecl *p);
  void visitSAss(SAss *p);
  void visitSIncr(SIncr *p);
  void visitSDecr(SDecr *p);
  void visitSRet(SRet *p);
  void visitSVRet(SVRet *p);
  void visitSCond(SCond *p);
  void visitSCondElse(SCondElse *p);
  void visitSWhile(SWhile *p);
  void visitSExp(SExp *p);
  void visitDecNoInit(DecNoInit *p);
  void visitDecInit(DecInit *p);
  void visitTInt(TInt *p);
  void visitTDouble(TDouble *p);
  void visitTBool(TBool *p);
  void visitTVoid(TVoid *p);
  void visitTStr(TStr *p);
  void visitTFun(TFun *p);
  void visitEVar(EVar *p);
  void visitEApp(EApp *p);
  void visitEInt(EInt *p);
  void visitEDouble(EDouble *p);
  void visitELitTrue(ELitTrue *p);
  void visitELitFalse(ELitFalse *p);
  void visitEString(EString *p);
  void visitENeg(ENeg *p);
  void visitENot(ENot *p);
  void visitEMul(EMul *p);
  void visitEAdd(EAdd *p);
  void visitERel(ERel *p);
  void visitEAnd(EAnd *p);
  void visitEOr(EOr *p);
  void visitETyped(ETyped *p);
  void visitOPlus(OPlus *p);
  void visitOMinus(OMinus *p);
  void visitOTimes(OTimes *p);
  void visitODiv(ODiv *p);
  void visitOMod(OMod *p);
  void visitOLt(OLt *p);
  void visitOLe(OLe *p);
  void visitOGt(OGt *p);
  void visitOGe(OGe *p);
  void visitOEq(OEq *p);
  void visitONe(ONe *p);
  void visitSForEach(SForEach *p);
  void visitTArray(TArray *p);
  void visitEIndex(EIndex *p);
  void visitEAllocate(EAllocate *p);
  void visitEDot(EDot *p);
  void visitLLength(LLength *p);
  void visitTIdent(TIdent *p);
  void visitTPointer(TPointer *p);
  void visitTStruct(TStruct *p);
  void visitDPointer(DPointer *p);
  void visitDStruct(DStruct *p);
  void visitDInlinePointer(DInlinePointer *p);
  void visitSStruct(SStruct *p);
  void visitFField(FField *p);
  void visitENull(ENull *p);
  void visitEDeref(EDeref *p);
  void visitTClass(TClass *p);
  void visitDClass(DClass *p);
  void visitDSubclass(DSubclass *p);
  void visitMField(MField *p);
  void visitMFun(MFun *p);
  void visitECast(ECast *p);
  void visitListDef(ListDef *p);
  void visitListArg(ListArg *p);
  void visitListStm(ListStm *p);
  void visitListDec(ListDec *p);
  void visitListType(ListType *p);
  void visitListExp(ListExp *p);
  void visitListLength(ListLength *p);
  void visitListField(ListField *p);
  void visitListMember(ListMember *p);

  void visitInteger(Integer x);
  void visitChar(Char x);
  void visitDouble(Double x);
  void visitString(String x);
  void visitIdent(Ident x);

};
}

#endif
