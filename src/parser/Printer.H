#ifndef PARSER_PRINTER_HEADER
#define PARSER_PRINTER_HEADER

#include "Absyn.H"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace parser
{
/* Certain applications may improve performance by changing the buffer size */
#define PARSER_BUFFER_INITIAL 2000
/* You may wish to change _L_PAREN or _R_PAREN */
#define PARSER__L_PAREN '('
#define PARSER__R_PAREN ')'

class PrintAbsyn : public Visitor
{
 protected:
  int _n_, _i_;
  /* The following are simple heuristics for rendering terminals */
  /* You may wish to change them */
  void render(Char c);
  void render(String s);
  void render(const char *s);
  void indent(void);
  void backup(void);
 public:
  PrintAbsyn(void);
  ~PrintAbsyn(void);
  char *print(Visitable *v);

  void visitProgram(Program *p); /* abstract class */
  void visitPDefs(PDefs *p);
  void visitDef(Def *p); /* abstract class */
  void visitDFun(DFun *p);
  void visitDPointer(DPointer *p);
  void visitDStruct(DStruct *p);
  void visitDInlinePointer(DInlinePointer *p);
  void visitDClass(DClass *p);
  void visitDSubclass(DSubclass *p);
  void visitListDef(ListDef *p);
  void visitArg(Arg *p); /* abstract class */
  void visitADecl(ADecl *p);
  void visitListArg(ListArg *p);
  void visitListStm(ListStm *p);
  void visitStm(Stm *p); /* abstract class */
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
  void visitSForEach(SForEach *p);
  void visitDec(Dec *p); /* abstract class */
  void visitDecNoInit(DecNoInit *p);
  void visitDecInit(DecInit *p);
  void visitListDec(ListDec *p);
  void visitType(Type *p); /* abstract class */
  void visitTInt(TInt *p);
  void visitTDouble(TDouble *p);
  void visitTBool(TBool *p);
  void visitTVoid(TVoid *p);
  void visitTStr(TStr *p);
  void visitTFun(TFun *p);
  void visitTArray(TArray *p);
  void visitTIdent(TIdent *p);
  void visitTPointer(TPointer *p);
  void visitTStruct(TStruct *p);
  void visitTClass(TClass *p);
  void visitListType(ListType *p);
  void visitExp(Exp *p); /* abstract class */
  void visitEVar(EVar *p);
  void visitEApp(EApp *p);
  void visitEInt(EInt *p);
  void visitEDouble(EDouble *p);
  void visitELitTrue(ELitTrue *p);
  void visitELitFalse(ELitFalse *p);
  void visitEString(EString *p);
  void visitEIndex(EIndex *p);
  void visitENull(ENull *p);
  void visitENeg(ENeg *p);
  void visitENot(ENot *p);
  void visitEMul(EMul *p);
  void visitEAdd(EAdd *p);
  void visitERel(ERel *p);
  void visitEAnd(EAnd *p);
  void visitEOr(EOr *p);
  void visitETyped(ETyped *p);
  void visitECast(ECast *p);
  void visitEAllocate(EAllocate *p);
  void visitEDot(EDot *p);
  void visitEDeref(EDeref *p);
  void visitListExp(ListExp *p);
  void visitAddOp(AddOp *p); /* abstract class */
  void visitOPlus(OPlus *p);
  void visitOMinus(OMinus *p);
  void visitMulOp(MulOp *p); /* abstract class */
  void visitOTimes(OTimes *p);
  void visitODiv(ODiv *p);
  void visitOMod(OMod *p);
  void visitRelOp(RelOp *p); /* abstract class */
  void visitOLt(OLt *p);
  void visitOLe(OLe *p);
  void visitOGt(OGt *p);
  void visitOGe(OGe *p);
  void visitOEq(OEq *p);
  void visitONe(ONe *p);
  void visitLength(Length *p); /* abstract class */
  void visitLLength(LLength *p);
  void visitListLength(ListLength *p);
  void visitStruct(Struct *p); /* abstract class */
  void visitSStruct(SStruct *p);
  void visitField(Field *p); /* abstract class */
  void visitFField(FField *p);
  void visitListField(ListField *p);
  void visitMember(Member *p); /* abstract class */
  void visitMField(MField *p);
  void visitMFun(MFun *p);
  void visitListMember(ListMember *p);

  void visitInteger(Integer i);
  void visitDouble(Double d);
  void visitChar(Char c);
  void visitString(String s);
  void visitIdent(String s);
 protected:
  char *buf_;
  int cur_, buf_size;

  void inline bufAppend(const char *s)
  {
    int end = cur_ + strlen(s);
    if (end >= buf_size) {
      do buf_size *= 2; /* Double the buffer size */
      while (end >= buf_size);
      resizeBuffer();
    }
    strcpy(&buf_[cur_], s);
    cur_ = end;
  }

  void inline bufAppend(const char c)
  {
    if (cur_ + 1 >= buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    buf_[cur_] = c;
    buf_[++cur_] = 0;
  }

  void inline bufAppend(String str)
  {
    const char *s = str.c_str();
    bufAppend(s);
  }
  void inline bufReset(void)
  {
    if (buf_) free(buf_);
    buf_size = PARSER_BUFFER_INITIAL;
    buf_ = (char *) malloc(buf_size);
    if (!buf_) {
      fprintf(stderr, "Error: Out of memory while allocating buffer!\n");
      exit(1);
    }
    memset(buf_, 0, buf_size);
    cur_ = 0;
  }

  void inline resizeBuffer(void)
  {
    char *temp = (char *) malloc(buf_size);
    if (!temp)
    {
      fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
      exit(1);
    }
    if (buf_)
    {
      strcpy(temp, buf_);
      free(buf_);
    }
    buf_ = temp;
  }
};



class ShowAbsyn : public Visitor
{
 public:
  ShowAbsyn(void);
  ~ShowAbsyn(void);
  char *show(Visitable *v);

  void visitProgram(Program *p); /* abstract class */
  void visitPDefs(PDefs *p);
  void visitDef(Def *p); /* abstract class */
  void visitDFun(DFun *p);
  void visitDPointer(DPointer *p);
  void visitDStruct(DStruct *p);
  void visitDInlinePointer(DInlinePointer *p);
  void visitDClass(DClass *p);
  void visitDSubclass(DSubclass *p);
  void visitListDef(ListDef *p);
  void visitArg(Arg *p); /* abstract class */
  void visitADecl(ADecl *p);
  void visitListArg(ListArg *p);
  void visitListStm(ListStm *p);
  void visitStm(Stm *p); /* abstract class */
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
  void visitSForEach(SForEach *p);
  void visitDec(Dec *p); /* abstract class */
  void visitDecNoInit(DecNoInit *p);
  void visitDecInit(DecInit *p);
  void visitListDec(ListDec *p);
  void visitType(Type *p); /* abstract class */
  void visitTInt(TInt *p);
  void visitTDouble(TDouble *p);
  void visitTBool(TBool *p);
  void visitTVoid(TVoid *p);
  void visitTStr(TStr *p);
  void visitTFun(TFun *p);
  void visitTArray(TArray *p);
  void visitTIdent(TIdent *p);
  void visitTPointer(TPointer *p);
  void visitTStruct(TStruct *p);
  void visitTClass(TClass *p);
  void visitListType(ListType *p);
  void visitExp(Exp *p); /* abstract class */
  void visitEVar(EVar *p);
  void visitEApp(EApp *p);
  void visitEInt(EInt *p);
  void visitEDouble(EDouble *p);
  void visitELitTrue(ELitTrue *p);
  void visitELitFalse(ELitFalse *p);
  void visitEString(EString *p);
  void visitEIndex(EIndex *p);
  void visitENull(ENull *p);
  void visitENeg(ENeg *p);
  void visitENot(ENot *p);
  void visitEMul(EMul *p);
  void visitEAdd(EAdd *p);
  void visitERel(ERel *p);
  void visitEAnd(EAnd *p);
  void visitEOr(EOr *p);
  void visitETyped(ETyped *p);
  void visitECast(ECast *p);
  void visitEAllocate(EAllocate *p);
  void visitEDot(EDot *p);
  void visitEDeref(EDeref *p);
  void visitListExp(ListExp *p);
  void visitAddOp(AddOp *p); /* abstract class */
  void visitOPlus(OPlus *p);
  void visitOMinus(OMinus *p);
  void visitMulOp(MulOp *p); /* abstract class */
  void visitOTimes(OTimes *p);
  void visitODiv(ODiv *p);
  void visitOMod(OMod *p);
  void visitRelOp(RelOp *p); /* abstract class */
  void visitOLt(OLt *p);
  void visitOLe(OLe *p);
  void visitOGt(OGt *p);
  void visitOGe(OGe *p);
  void visitOEq(OEq *p);
  void visitONe(ONe *p);
  void visitLength(Length *p); /* abstract class */
  void visitLLength(LLength *p);
  void visitListLength(ListLength *p);
  void visitStruct(Struct *p); /* abstract class */
  void visitSStruct(SStruct *p);
  void visitField(Field *p); /* abstract class */
  void visitFField(FField *p);
  void visitListField(ListField *p);
  void visitMember(Member *p); /* abstract class */
  void visitMField(MField *p);
  void visitMFun(MFun *p);
  void visitListMember(ListMember *p);

  void visitInteger(Integer i);
  void visitDouble(Double d);
  void visitChar(Char c);
  void visitString(String s);
  void visitIdent(String s);
 protected:
  char *buf_;
  int cur_, buf_size;

  void inline bufAppend(const char *s)
  {
    int end = cur_ + strlen(s);
    if (end >= buf_size) {
      do buf_size *= 2; /* Double the buffer size */
      while (end >= buf_size);
      resizeBuffer();
    }
    strcpy(&buf_[cur_], s);
    cur_ = end;
  }

  void inline bufAppend(const char c)
  {
    if (cur_ + 1 >= buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    buf_[cur_] = c;
    buf_[++cur_] = 0;
  }

  void inline bufAppend(String str)
  {
    const char *s = str.c_str();
    bufAppend(s);
  }
  void inline bufReset(void)
  {
    if (buf_) free(buf_);
    buf_size = PARSER_BUFFER_INITIAL;
    buf_ = (char *) malloc(buf_size);
    if (!buf_) {
      fprintf(stderr, "Error: Out of memory while allocating buffer!\n");
      exit(1);
    }
    memset(buf_, 0, buf_size);
    cur_ = 0;
  }

  void inline resizeBuffer(void)
  {
    char *temp = (char *) malloc(buf_size);
    if (!temp)
    {
      fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
      exit(1);
    }
    if (buf_)
    {
      strcpy(temp, buf_);
      free(buf_);
    }
    buf_ = temp;
  }
};


}

#endif

