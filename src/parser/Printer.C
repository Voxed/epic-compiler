/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include "Printer.H"
#define INDENT_WIDTH 2

namespace parser
{
//You may wish to change render
void PrintAbsyn::render(Char c)
{
  if (c == '{')
  {
     bufAppend('\n');
     indent();
     bufAppend(c);
     _n_ = _n_ + INDENT_WIDTH;
     bufAppend('\n');
     indent();
  }
  else if (c == '(' || c == '[')
     bufAppend(c);
  else if (c == ')' || c == ']')
  {
     backup();
     bufAppend(c);
     bufAppend(' ');
  }
  else if (c == '}')
  {
     int t;
     _n_ = _n_ - INDENT_WIDTH;
     for (t=0; t<INDENT_WIDTH; t++) {
       backup();
     }
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == ',')
  {
     backup();
     bufAppend(c);
     bufAppend(' ');
  }
  else if (c == ';')
  {
     backup();
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == ' ') bufAppend(c);
  else if (c == 0) return;
  else
  {
     bufAppend(c);
     bufAppend(' ');
  }
}

void PrintAbsyn::render(String s)
{
  render(s.c_str());
}

bool allIsSpace(const char *s)
{
  char c;
  while ((c = *s++))
    if (! isspace(c)) return false;
  return true;
}

void PrintAbsyn::render(const char *s)
{
  if (*s) /* C string not empty */
  {
    if (allIsSpace(s)) {
      backup();
      bufAppend(s);
    } else {
      bufAppend(s);
      bufAppend(' ');
    }
  }
}

void PrintAbsyn::indent()
{
  int n = _n_;
  while (--n >= 0)
    bufAppend(' ');
}

void PrintAbsyn::backup()
{
  if (buf_[cur_ - 1] == ' ')
    buf_[--cur_] = 0;
}

PrintAbsyn::PrintAbsyn(void)
{
  _i_ = 0; _n_ = 0;
  buf_ = 0;
  bufReset();
}

PrintAbsyn::~PrintAbsyn(void)
{
}

char *PrintAbsyn::print(Visitable *v)
{
  _i_ = 0; _n_ = 0;
  bufReset();
  v->accept(this);
  return buf_;
}

void PrintAbsyn::visitProgram(Program *p) {} //abstract class

void PrintAbsyn::visitPDefs(PDefs *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  if(p->listdef_) {_i_ = 0; p->listdef_->accept(this);}

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDef(Def *p) {} //abstract class

void PrintAbsyn::visitDFun(DFun *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);
  render('(');
  if(p->listarg_) {_i_ = 0; p->listarg_->accept(this);}
  render(')');
  render('{');
  if(p->liststm_) {_i_ = 0; p->liststm_->accept(this);}
  render('}');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDPointer(DPointer *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("typedef");
  render("struct");
  visitIdent(p->ident_1);
  render('*');
  visitIdent(p->ident_2);
  render(';');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDStruct(DStruct *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  _i_ = 0; p->struct_->accept(this);
  render(';');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDInlinePointer(DInlinePointer *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("typedef");
  _i_ = 0; p->struct_->accept(this);
  render('*');
  visitIdent(p->ident_);
  render(';');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDClass(DClass *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("class");
  visitIdent(p->ident_);
  render('{');
  if(p->listmember_) {_i_ = 0; p->listmember_->accept(this);}
  render('}');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDSubclass(DSubclass *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("class");
  visitIdent(p->ident_1);
  render("extends");
  visitIdent(p->ident_2);
  render('{');
  if(p->listmember_) {_i_ = 0; p->listmember_->accept(this);}
  render('}');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListDef(ListDef *listdef)
{
  for (ListDef::const_iterator i = listdef->begin() ; i != listdef->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listdef->end() - 1) render("");
  }
}void PrintAbsyn::visitArg(Arg *p) {} //abstract class

void PrintAbsyn::visitADecl(ADecl *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListArg(ListArg *listarg)
{
  for (ListArg::const_iterator i = listarg->begin() ; i != listarg->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listarg->end() - 1) render(',');
  }
}void PrintAbsyn::visitListStm(ListStm *liststm)
{
  for (ListStm::const_iterator i = liststm->begin() ; i != liststm->end() ; ++i)
  {
    (*i)->accept(this);
    render("");
  }
}void PrintAbsyn::visitStm(Stm *p) {} //abstract class

void PrintAbsyn::visitSEmpty(SEmpty *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render(';');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSBlock(SBlock *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render('{');
  if(p->liststm_) {_i_ = 0; p->liststm_->accept(this);}
  render('}');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSDecl(SDecl *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  _i_ = 0; p->type_->accept(this);
  if(p->listdec_) {_i_ = 0; p->listdec_->accept(this);}
  render(';');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSAss(SAss *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  _i_ = 0; p->exp_1->accept(this);
  render('=');
  _i_ = 0; p->exp_2->accept(this);
  render(';');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSIncr(SIncr *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  _i_ = 0; p->exp_->accept(this);
  render("++");
  render(';');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSDecr(SDecr *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  _i_ = 0; p->exp_->accept(this);
  render("--");
  render(';');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSRet(SRet *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("return");
  _i_ = 0; p->exp_->accept(this);
  render(';');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSVRet(SVRet *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("return");
  render(';');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSCond(SCond *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("if");
  render('(');
  _i_ = 0; p->exp_->accept(this);
  render(')');
  _i_ = 0; p->stm_->accept(this);

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSCondElse(SCondElse *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("if");
  render('(');
  _i_ = 0; p->exp_->accept(this);
  render(')');
  _i_ = 0; p->stm_1->accept(this);
  render("else");
  _i_ = 0; p->stm_2->accept(this);

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSWhile(SWhile *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("while");
  render('(');
  _i_ = 0; p->exp_->accept(this);
  render(')');
  _i_ = 0; p->stm_->accept(this);

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSExp(SExp *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  _i_ = 0; p->exp_->accept(this);
  render(';');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSForEach(SForEach *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("for");
  render('(');
  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);
  render(':');
  _i_ = 0; p->exp_->accept(this);
  render(')');
  _i_ = 0; p->stm_->accept(this);

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDec(Dec *p) {} //abstract class

void PrintAbsyn::visitDecNoInit(DecNoInit *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  visitIdent(p->ident_);

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDecInit(DecInit *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  visitIdent(p->ident_);
  render('=');
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListDec(ListDec *listdec)
{
  for (ListDec::const_iterator i = listdec->begin() ; i != listdec->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listdec->end() - 1) render(',');
  }
}void PrintAbsyn::visitType(Type *p) {} //abstract class

void PrintAbsyn::visitTInt(TInt *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("int");

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitTDouble(TDouble *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("double");

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitTBool(TBool *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("boolean");

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitTVoid(TVoid *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("void");

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitTStr(TStr *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("string");

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitTFun(TFun *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  _i_ = 0; p->type_->accept(this);
  render('(');
  if(p->listtype_) {_i_ = 0; p->listtype_->accept(this);}
  render(')');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitTArray(TArray *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  _i_ = 0; p->type_->accept(this);
  render("[]");

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitTIdent(TIdent *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  visitIdent(p->ident_);

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitTPointer(TPointer *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  visitIdent(p->ident_);
  render('*');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitTStruct(TStruct *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("struct");
  visitIdent(p->ident_);

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitTClass(TClass *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("class");
  visitIdent(p->ident_);

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListType(ListType *listtype)
{
  for (ListType::const_iterator i = listtype->begin() ; i != listtype->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listtype->end() - 1) render(',');
  }
}void PrintAbsyn::visitExp(Exp *p) {} //abstract class

void PrintAbsyn::visitEVar(EVar *p)
{
  int oldi = _i_;
  if (oldi > 7) render(PARSER__L_PAREN);

  visitIdent(p->ident_);

  if (oldi > 7) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEApp(EApp *p)
{
  int oldi = _i_;
  if (oldi > 7) render(PARSER__L_PAREN);

  visitIdent(p->ident_);
  render('(');
  if(p->listexp_) {_i_ = 0; p->listexp_->accept(this);}
  render(')');

  if (oldi > 7) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEInt(EInt *p)
{
  int oldi = _i_;
  if (oldi > 7) render(PARSER__L_PAREN);

  visitInteger(p->integer_);

  if (oldi > 7) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEDouble(EDouble *p)
{
  int oldi = _i_;
  if (oldi > 7) render(PARSER__L_PAREN);

  visitDouble(p->double_);

  if (oldi > 7) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitELitTrue(ELitTrue *p)
{
  int oldi = _i_;
  if (oldi > 7) render(PARSER__L_PAREN);

  render("true");

  if (oldi > 7) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitELitFalse(ELitFalse *p)
{
  int oldi = _i_;
  if (oldi > 7) render(PARSER__L_PAREN);

  render("false");

  if (oldi > 7) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEString(EString *p)
{
  int oldi = _i_;
  if (oldi > 7) render(PARSER__L_PAREN);

  visitString(p->string_);

  if (oldi > 7) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEIndex(EIndex *p)
{
  int oldi = _i_;
  if (oldi > 7) render(PARSER__L_PAREN);

  _i_ = 7; p->exp_1->accept(this);
  render('[');
  _i_ = 0; p->exp_2->accept(this);
  render(']');

  if (oldi > 7) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitENull(ENull *p)
{
  int oldi = _i_;
  if (oldi > 7) render(PARSER__L_PAREN);

  render('(');
  _i_ = 0; p->type_->accept(this);
  render(")null");

  if (oldi > 7) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitENeg(ENeg *p)
{
  int oldi = _i_;
  if (oldi > 5) render(PARSER__L_PAREN);

  render('-');
  _i_ = 6; p->exp_->accept(this);

  if (oldi > 5) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitENot(ENot *p)
{
  int oldi = _i_;
  if (oldi > 5) render(PARSER__L_PAREN);

  render('!');
  _i_ = 6; p->exp_->accept(this);

  if (oldi > 5) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEMul(EMul *p)
{
  int oldi = _i_;
  if (oldi > 4) render(PARSER__L_PAREN);

  _i_ = 4; p->exp_1->accept(this);
  _i_ = 0; p->mulop_->accept(this);
  _i_ = 5; p->exp_2->accept(this);

  if (oldi > 4) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEAdd(EAdd *p)
{
  int oldi = _i_;
  if (oldi > 3) render(PARSER__L_PAREN);

  _i_ = 3; p->exp_1->accept(this);
  _i_ = 0; p->addop_->accept(this);
  _i_ = 4; p->exp_2->accept(this);

  if (oldi > 3) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitERel(ERel *p)
{
  int oldi = _i_;
  if (oldi > 2) render(PARSER__L_PAREN);

  _i_ = 2; p->exp_1->accept(this);
  _i_ = 0; p->relop_->accept(this);
  _i_ = 3; p->exp_2->accept(this);

  if (oldi > 2) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEAnd(EAnd *p)
{
  int oldi = _i_;
  if (oldi > 1) render(PARSER__L_PAREN);

  _i_ = 2; p->exp_1->accept(this);
  render("&&");
  _i_ = 1; p->exp_2->accept(this);

  if (oldi > 1) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEOr(EOr *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  _i_ = 1; p->exp_1->accept(this);
  render("||");
  _i_ = 0; p->exp_2->accept(this);

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitETyped(ETyped *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render('[');
  _i_ = 0; p->exp_->accept(this);
  render(':');
  _i_ = 0; p->type_->accept(this);
  render(':');
  visitChar(p->char_);
  render(']');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitECast(ECast *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render('<');
  _i_ = 0; p->exp_->accept(this);
  render(':');
  _i_ = 0; p->type_->accept(this);
  render('>');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEAllocate(EAllocate *p)
{
  int oldi = _i_;
  if (oldi > 6) render(PARSER__L_PAREN);

  render("new");
  _i_ = 0; p->type_->accept(this);
  if(p->listlength_) {_i_ = 0; p->listlength_->accept(this);}

  if (oldi > 6) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEDot(EDot *p)
{
  int oldi = _i_;
  if (oldi > 6) render(PARSER__L_PAREN);

  _i_ = 6; p->exp_1->accept(this);
  render('.');
  _i_ = 7; p->exp_2->accept(this);

  if (oldi > 6) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEDeref(EDeref *p)
{
  int oldi = _i_;
  if (oldi > 6) render(PARSER__L_PAREN);

  _i_ = 6; p->exp_1->accept(this);
  render("->");
  _i_ = 7; p->exp_2->accept(this);

  if (oldi > 6) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListExp(ListExp *listexp)
{
  for (ListExp::const_iterator i = listexp->begin() ; i != listexp->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listexp->end() - 1) render(',');
  }
}void PrintAbsyn::visitAddOp(AddOp *p) {} //abstract class

void PrintAbsyn::visitOPlus(OPlus *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render('+');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitOMinus(OMinus *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render('-');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitMulOp(MulOp *p) {} //abstract class

void PrintAbsyn::visitOTimes(OTimes *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render('*');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitODiv(ODiv *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render('/');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitOMod(OMod *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render('%');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitRelOp(RelOp *p) {} //abstract class

void PrintAbsyn::visitOLt(OLt *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render('<');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitOLe(OLe *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("<=");

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitOGt(OGt *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render('>');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitOGe(OGe *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render(">=");

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitOEq(OEq *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("==");

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitONe(ONe *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("!=");

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitLength(Length *p) {} //abstract class

void PrintAbsyn::visitLLength(LLength *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render('[');
  _i_ = 0; p->exp_->accept(this);
  render(']');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListLength(ListLength *listlength)
{
  for (ListLength::const_iterator i = listlength->begin() ; i != listlength->end() ; ++i)
  {
    (*i)->accept(this);
    render("");
  }
}void PrintAbsyn::visitStruct(Struct *p) {} //abstract class

void PrintAbsyn::visitSStruct(SStruct *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  render("struct");
  visitIdent(p->ident_);
  render('{');
  if(p->listfield_) {_i_ = 0; p->listfield_->accept(this);}
  render('}');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitField(Field *p) {} //abstract class

void PrintAbsyn::visitFField(FField *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);
  render(';');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListField(ListField *listfield)
{
  for (ListField::const_iterator i = listfield->begin() ; i != listfield->end() ; ++i)
  {
    (*i)->accept(this);
    render("");
  }
}void PrintAbsyn::visitMember(Member *p) {} //abstract class

void PrintAbsyn::visitMField(MField *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  _i_ = 0; p->field_->accept(this);

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitMFun(MFun *p)
{
  int oldi = _i_;
  if (oldi > 0) render(PARSER__L_PAREN);

  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);
  render('(');
  if(p->listarg_) {_i_ = 0; p->listarg_->accept(this);}
  render(')');
  render('{');
  if(p->liststm_) {_i_ = 0; p->liststm_->accept(this);}
  render('}');

  if (oldi > 0) render(PARSER__R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListMember(ListMember *listmember)
{
  for (ListMember::const_iterator i = listmember->begin() ; i != listmember->end() ; ++i)
  {
    (*i)->accept(this);
    render("");
  }
}void PrintAbsyn::visitInteger(Integer i)
{
  char tmp[20];
  sprintf(tmp, "%d", i);
  render(tmp);
}

void PrintAbsyn::visitDouble(Double d)
{
  char tmp[24];
  sprintf(tmp, "%.15g", d);
  render(tmp);
}

void PrintAbsyn::visitChar(Char c)
{
  char tmp[4];
  sprintf(tmp, "'%c'", c);
  render(tmp);
}

void PrintAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
  bufAppend(' ');
}

void PrintAbsyn::visitIdent(String s)
{
  render(s);
}

ShowAbsyn::ShowAbsyn(void)
{
  buf_ = 0;
  bufReset();
}

ShowAbsyn::~ShowAbsyn(void)
{
}

char *ShowAbsyn::show(Visitable *v)
{
  bufReset();
  v->accept(this);
  return buf_;
}

void ShowAbsyn::visitProgram(Program *p) {} //abstract class

void ShowAbsyn::visitPDefs(PDefs *p)
{
  bufAppend('(');
  bufAppend("PDefs");
  bufAppend(' ');
  bufAppend('[');
  if (p->listdef_)  p->listdef_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitDef(Def *p) {} //abstract class

void ShowAbsyn::visitDFun(DFun *p)
{
  bufAppend('(');
  bufAppend("DFun");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listarg_)  p->listarg_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->liststm_)  p->liststm_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitDPointer(DPointer *p)
{
  bufAppend('(');
  bufAppend("DPointer");
  bufAppend(' ');
  visitIdent(p->ident_1);
  bufAppend(' ');
  visitIdent(p->ident_2);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitDStruct(DStruct *p)
{
  bufAppend('(');
  bufAppend("DStruct");
  bufAppend(' ');
  bufAppend('[');
  if (p->struct_)  p->struct_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitDInlinePointer(DInlinePointer *p)
{
  bufAppend('(');
  bufAppend("DInlinePointer");
  bufAppend(' ');
  bufAppend('[');
  if (p->struct_)  p->struct_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitDClass(DClass *p)
{
  bufAppend('(');
  bufAppend("DClass");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listmember_)  p->listmember_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitDSubclass(DSubclass *p)
{
  bufAppend('(');
  bufAppend("DSubclass");
  bufAppend(' ');
  visitIdent(p->ident_1);
  bufAppend(' ');
  visitIdent(p->ident_2);
  bufAppend(' ');
  bufAppend('[');
  if (p->listmember_)  p->listmember_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitListDef(ListDef *listdef)
{
  for (ListDef::const_iterator i = listdef->begin() ; i != listdef->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listdef->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitArg(Arg *p) {} //abstract class

void ShowAbsyn::visitADecl(ADecl *p)
{
  bufAppend('(');
  bufAppend("ADecl");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitListArg(ListArg *listarg)
{
  for (ListArg::const_iterator i = listarg->begin() ; i != listarg->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listarg->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitListStm(ListStm *liststm)
{
  for (ListStm::const_iterator i = liststm->begin() ; i != liststm->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != liststm->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitStm(Stm *p) {} //abstract class

void ShowAbsyn::visitSEmpty(SEmpty *p)
{
  bufAppend("SEmpty");
}
void ShowAbsyn::visitSBlock(SBlock *p)
{
  bufAppend('(');
  bufAppend("SBlock");
  bufAppend(' ');
  bufAppend('[');
  if (p->liststm_)  p->liststm_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitSDecl(SDecl *p)
{
  bufAppend('(');
  bufAppend("SDecl");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->listdec_)  p->listdec_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitSAss(SAss *p)
{
  bufAppend('(');
  bufAppend("SAss");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitSIncr(SIncr *p)
{
  bufAppend('(');
  bufAppend("SIncr");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitSDecr(SDecr *p)
{
  bufAppend('(');
  bufAppend("SDecr");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitSRet(SRet *p)
{
  bufAppend('(');
  bufAppend("SRet");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitSVRet(SVRet *p)
{
  bufAppend("SVRet");
}
void ShowAbsyn::visitSCond(SCond *p)
{
  bufAppend('(');
  bufAppend("SCond");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->stm_)  p->stm_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitSCondElse(SCondElse *p)
{
  bufAppend('(');
  bufAppend("SCondElse");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  p->stm_1->accept(this);
  bufAppend(' ');
  p->stm_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitSWhile(SWhile *p)
{
  bufAppend('(');
  bufAppend("SWhile");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->stm_)  p->stm_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitSExp(SExp *p)
{
  bufAppend('(');
  bufAppend("SExp");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitSForEach(SForEach *p)
{
  bufAppend('(');
  bufAppend("SForEach");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->stm_)  p->stm_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitDec(Dec *p) {} //abstract class

void ShowAbsyn::visitDecNoInit(DecNoInit *p)
{
  bufAppend('(');
  bufAppend("DecNoInit");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitDecInit(DecInit *p)
{
  bufAppend('(');
  bufAppend("DecInit");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitListDec(ListDec *listdec)
{
  for (ListDec::const_iterator i = listdec->begin() ; i != listdec->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listdec->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitType(Type *p) {} //abstract class

void ShowAbsyn::visitTInt(TInt *p)
{
  bufAppend("TInt");
}
void ShowAbsyn::visitTDouble(TDouble *p)
{
  bufAppend("TDouble");
}
void ShowAbsyn::visitTBool(TBool *p)
{
  bufAppend("TBool");
}
void ShowAbsyn::visitTVoid(TVoid *p)
{
  bufAppend("TVoid");
}
void ShowAbsyn::visitTStr(TStr *p)
{
  bufAppend("TStr");
}
void ShowAbsyn::visitTFun(TFun *p)
{
  bufAppend('(');
  bufAppend("TFun");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->listtype_)  p->listtype_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitTArray(TArray *p)
{
  bufAppend('(');
  bufAppend("TArray");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitTIdent(TIdent *p)
{
  bufAppend('(');
  bufAppend("TIdent");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitTPointer(TPointer *p)
{
  bufAppend('(');
  bufAppend("TPointer");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitTStruct(TStruct *p)
{
  bufAppend('(');
  bufAppend("TStruct");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitTClass(TClass *p)
{
  bufAppend('(');
  bufAppend("TClass");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitListType(ListType *listtype)
{
  for (ListType::const_iterator i = listtype->begin() ; i != listtype->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listtype->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitExp(Exp *p) {} //abstract class

void ShowAbsyn::visitEVar(EVar *p)
{
  bufAppend('(');
  bufAppend("EVar");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitEApp(EApp *p)
{
  bufAppend('(');
  bufAppend("EApp");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listexp_)  p->listexp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitEInt(EInt *p)
{
  bufAppend('(');
  bufAppend("EInt");
  bufAppend(' ');
  visitInteger(p->integer_);
  bufAppend(')');
}
void ShowAbsyn::visitEDouble(EDouble *p)
{
  bufAppend('(');
  bufAppend("EDouble");
  bufAppend(' ');
  visitDouble(p->double_);
  bufAppend(')');
}
void ShowAbsyn::visitELitTrue(ELitTrue *p)
{
  bufAppend("ELitTrue");
}
void ShowAbsyn::visitELitFalse(ELitFalse *p)
{
  bufAppend("ELitFalse");
}
void ShowAbsyn::visitEString(EString *p)
{
  bufAppend('(');
  bufAppend("EString");
  bufAppend(' ');
  visitString(p->string_);
  bufAppend(')');
}
void ShowAbsyn::visitEIndex(EIndex *p)
{
  bufAppend('(');
  bufAppend("EIndex");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitENull(ENull *p)
{
  bufAppend('(');
  bufAppend("ENull");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitENeg(ENeg *p)
{
  bufAppend('(');
  bufAppend("ENeg");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitENot(ENot *p)
{
  bufAppend('(');
  bufAppend("ENot");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEMul(EMul *p)
{
  bufAppend('(');
  bufAppend("EMul");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  bufAppend('[');
  if (p->mulop_)  p->mulop_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEAdd(EAdd *p)
{
  bufAppend('(');
  bufAppend("EAdd");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  bufAppend('[');
  if (p->addop_)  p->addop_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitERel(ERel *p)
{
  bufAppend('(');
  bufAppend("ERel");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  bufAppend('[');
  if (p->relop_)  p->relop_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEAnd(EAnd *p)
{
  bufAppend('(');
  bufAppend("EAnd");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEOr(EOr *p)
{
  bufAppend('(');
  bufAppend("EOr");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitETyped(ETyped *p)
{
  bufAppend('(');
  bufAppend("ETyped");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitChar(p->char_);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitECast(ECast *p)
{
  bufAppend('(');
  bufAppend("ECast");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitEAllocate(EAllocate *p)
{
  bufAppend('(');
  bufAppend("EAllocate");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->listlength_)  p->listlength_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitEDot(EDot *p)
{
  bufAppend('(');
  bufAppend("EDot");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEDeref(EDeref *p)
{
  bufAppend('(');
  bufAppend("EDeref");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitListExp(ListExp *listexp)
{
  for (ListExp::const_iterator i = listexp->begin() ; i != listexp->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listexp->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitAddOp(AddOp *p) {} //abstract class

void ShowAbsyn::visitOPlus(OPlus *p)
{
  bufAppend("OPlus");
}
void ShowAbsyn::visitOMinus(OMinus *p)
{
  bufAppend("OMinus");
}
void ShowAbsyn::visitMulOp(MulOp *p) {} //abstract class

void ShowAbsyn::visitOTimes(OTimes *p)
{
  bufAppend("OTimes");
}
void ShowAbsyn::visitODiv(ODiv *p)
{
  bufAppend("ODiv");
}
void ShowAbsyn::visitOMod(OMod *p)
{
  bufAppend("OMod");
}
void ShowAbsyn::visitRelOp(RelOp *p) {} //abstract class

void ShowAbsyn::visitOLt(OLt *p)
{
  bufAppend("OLt");
}
void ShowAbsyn::visitOLe(OLe *p)
{
  bufAppend("OLe");
}
void ShowAbsyn::visitOGt(OGt *p)
{
  bufAppend("OGt");
}
void ShowAbsyn::visitOGe(OGe *p)
{
  bufAppend("OGe");
}
void ShowAbsyn::visitOEq(OEq *p)
{
  bufAppend("OEq");
}
void ShowAbsyn::visitONe(ONe *p)
{
  bufAppend("ONe");
}
void ShowAbsyn::visitLength(Length *p) {} //abstract class

void ShowAbsyn::visitLLength(LLength *p)
{
  bufAppend('(');
  bufAppend("LLength");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitListLength(ListLength *listlength)
{
  for (ListLength::const_iterator i = listlength->begin() ; i != listlength->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listlength->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitStruct(Struct *p) {} //abstract class

void ShowAbsyn::visitSStruct(SStruct *p)
{
  bufAppend('(');
  bufAppend("SStruct");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listfield_)  p->listfield_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitField(Field *p) {} //abstract class

void ShowAbsyn::visitFField(FField *p)
{
  bufAppend('(');
  bufAppend("FField");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitListField(ListField *listfield)
{
  for (ListField::const_iterator i = listfield->begin() ; i != listfield->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listfield->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitMember(Member *p) {} //abstract class

void ShowAbsyn::visitMField(MField *p)
{
  bufAppend('(');
  bufAppend("MField");
  bufAppend(' ');
  bufAppend('[');
  if (p->field_)  p->field_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitMFun(MFun *p)
{
  bufAppend('(');
  bufAppend("MFun");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listarg_)  p->listarg_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->liststm_)  p->liststm_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitListMember(ListMember *listmember)
{
  for (ListMember::const_iterator i = listmember->begin() ; i != listmember->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listmember->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitInteger(Integer i)
{
  char tmp[20];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
void ShowAbsyn::visitDouble(Double d)
{
  char tmp[24];
  sprintf(tmp, "%.15g", d);
  bufAppend(tmp);
}
void ShowAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
void ShowAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
void ShowAbsyn::visitIdent(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}

}
