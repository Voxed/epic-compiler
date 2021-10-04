#include "Clone.hpp"

#include "ast/BaseVisitor.hpp"
#include "parser/Absyn.H"
#include <vector>

using namespace parser;

namespace ast::internal {

Cloner::Cloner()
  : ast::BaseVisitor("Cloner")
{}

void
Cloner::visitPDefs(PDefs* p)
{
    if (p->listdef_ != nullptr) {
        p->listdef_->accept(this);
    }
}

void
Cloner::visitDFun(DFun* p)
{
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
    visitIdent(p->ident_);
    if (p->listarg_ != nullptr) {
        p->listarg_->accept(this);
    }
    if (p->liststm_ != nullptr) {
        p->liststm_->accept(this);
    }
}

void
Cloner::visitADecl(ADecl* p)
{
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
    visitIdent(p->ident_);
}

void
Cloner::visitSEmpty(SEmpty* p)
{}

void
Cloner::visitSBlock(SBlock* p)
{
    if (p->liststm_ != nullptr) {
        p->liststm_->accept(this);
    }
}

void
Cloner::visitSDecl(SDecl* p)
{
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
    if (p->listdec_ != nullptr) {
        p->listdec_->accept(this);
    }
}

void
Cloner::visitSAss(SAss* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}

void
Cloner::visitSIncr(SIncr* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}
void
Cloner::visitSDecr(SDecr* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}

void
Cloner::visitSRet(SRet* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}

void
Cloner::visitSVRet(SVRet* p)
{}

void
Cloner::visitSCond(SCond* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
    if (p->stm_ != nullptr) {
        p->stm_->accept(this);
    }
}

void
Cloner::visitSCondElse(SCondElse* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
    if (p->stm_1 != nullptr) {
        p->stm_1->accept(this);
    }
    if (p->stm_2 != nullptr) {
        p->stm_2->accept(this);
    }
}

void
Cloner::visitSWhile(SWhile* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
    if (p->stm_ != nullptr) {
        p->stm_->accept(this);
    }
}

void
Cloner::visitSExp(SExp* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}

void
Cloner::visitDecNoInit(DecNoInit* p)
{
    visitIdent(p->ident_);
}

void
Cloner::visitDecInit(DecInit* p)
{
    visitIdent(p->ident_);
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}

void
Cloner::visitTInt(TInt* p)
{}
void
Cloner::visitTDouble(TDouble* p)
{}
void
Cloner::visitTBool(TBool* p)
{}
void
Cloner::visitTVoid(TVoid* p)
{}
void
Cloner::visitTStr(TStr* p)
{}

void
Cloner::visitTFun(TFun* p)
{
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
    if (p->listtype_ != nullptr) {
        p->listtype_->accept(this);
    }
}

void
Cloner::visitEVar(EVar* p)
{
    visitIdent(p->ident_);
}
void
Cloner::visitEInt(EInt* p)
{
    visitInteger(p->integer_);
}

void
Cloner::visitEDouble(EDouble* p)
{
    visitDouble(p->double_);
}

void
Cloner::visitELitTrue(ELitTrue* p)
{}
void
Cloner::visitELitFalse(ELitFalse* p)
{}

void
Cloner::visitEApp(EApp* p)
{
    visitIdent(p->ident_);
    if (p->listexp_ != nullptr) {
        p->listexp_->accept(this);
    }
}

void
Cloner::visitEString(EString* p)
{
    visitString(p->string_);
}

void
Cloner::visitENeg(ENeg* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}

void
Cloner::visitENot(ENot* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}

void
Cloner::visitEMul(EMul* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->mulop_ != nullptr) {
        p->mulop_->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}

void
Cloner::visitEAdd(EAdd* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->addop_ != nullptr) {
        p->addop_->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}

void
Cloner::visitERel(ERel* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->relop_ != nullptr) {
        p->relop_->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}

void
Cloner::visitEAnd(EAnd* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}

void
Cloner::visitEOr(EOr* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}

void
Cloner::visitETyped(ETyped* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
}

void
Cloner::visitOPlus(OPlus* p)
{}
void
Cloner::visitOMinus(OMinus* p)
{}
void
Cloner::visitOTimes(OTimes* p)
{}
void
Cloner::visitODiv(ODiv* p)
{}
void
Cloner::visitOMod(OMod* p)
{}
void
Cloner::visitOLt(OLt* p)
{}
void
Cloner::visitOLe(OLe* p)
{}
void
Cloner::visitOGt(OGt* p)
{}
void
Cloner::visitOGe(OGe* p)
{}
void
Cloner::visitOEq(OEq* p)
{}
void
Cloner::visitONe(ONe* p)
{}

void
Cloner::visitListDef(ListDef* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        *i = (*i)->clone();
        (*i)->accept(this);
    }
}

void
Cloner::visitListArg(ListArg* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        *i = (*i)->clone();
        (*i)->accept(this);
    }
}

void
Cloner::visitListStm(ListStm* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        *i = (*i)->clone();
        (*i)->accept(this);
    }
}

void
Cloner::visitListDec(ListDec* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        *i = (*i)->clone();
        (*i)->accept(this);
    }
}

void
Cloner::visitListType(ListType* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        *i = (*i)->clone();
        (*i)->accept(this);
    }
}

void
Cloner::visitListExp(ListExp* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        *i = (*i)->clone();
        (*i)->accept(this);
    }
}

void
Cloner::visitInteger(Integer x)
{}
void
Cloner::visitChar(Char x)
{}
void
Cloner::visitDouble(Double x)
{}
void
Cloner::visitString(String x)
{}
void
Cloner::visitIdent(Ident x)
{}

void
Cloner::visitEIndex(parser::EIndex* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}
void
Cloner::visitSForEach(parser::SForEach* p)
{
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
    visitIdent(p->ident_);
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
    if (p->stm_ != nullptr) {
        p->stm_->accept(this);
    }
}
void
Cloner::visitTArray(parser::TArray* p)
{
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
}
void
Cloner::visitEAllocate(parser::EAllocate* p)
{
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
    if (p->listlength_ != nullptr) {
        p->listlength_->accept(this);
    }
}
void
Cloner::visitEDot(parser::EDot* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}
void
Cloner::visitLLength(parser::LLength* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}
void
Cloner::visitListLength(parser::ListLength* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        *i = (*i)->clone();
        (*i)->accept(this);
    }
}

void
Cloner::visitTIdent(parser::TIdent* p)
{
    visitIdent(p->ident_);
}
void
Cloner::visitTPointer(parser::TPointer* p)
{
    visitIdent(p->ident_);
}
void
Cloner::visitTStruct(parser::TStruct* p)
{
    visitIdent(p->ident_);
}
void
Cloner::visitDPointer(parser::DPointer* p)
{
    visitIdent(p->ident_1);
    visitIdent(p->ident_2);
}
void
Cloner::visitSStruct(parser::SStruct* p)
{
    visitIdent(p->ident_);
    if (p->listfield_ != nullptr) {
        p->listfield_->accept(this);
    }
}
void
Cloner::visitDStruct(parser::DStruct* p)
{
    if (p->struct_ != nullptr) {
        p->struct_->accept(this);
    }
}
void
Cloner::visitDInlinePointer(parser::DInlinePointer* p)
{
    visitIdent(p->ident_);
    if (p->struct_ != nullptr) {
        p->struct_->accept(this);
    }
}
void
Cloner::visitField(parser::Field* p)
{}
void
Cloner::visitFField(parser::FField* p)
{
    visitIdent(p->ident_);
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
}
void
Cloner::visitListField(parser::ListField* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        *i = (*i)->clone();
        (*i)->accept(this);
    }
}
void
Cloner::visitEDeref(parser::EDeref* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}
void
Cloner::visitENull(parser::ENull* p)
{
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
}

void
Cloner::visitTClass(parser::TClass* p)
{
    visitIdent(p->ident_);
}
void
Cloner::visitDSubclass(parser::DSubclass* p)
{
    visitIdent(p->ident_1);
    visitIdent(p->ident_2);
    if (p->listmember_ != nullptr) {
        p->listmember_->accept(this);
    }
}
void
Cloner::visitDClass(parser::DClass* p)
{
    visitIdent(p->ident_);
    if (p->listmember_ != nullptr) {
        p->listmember_->accept(this);
    }
}
void
Cloner::visitListMember(parser::ListMember* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        *i = (*i)->clone();
        (*i)->accept(this);
    }
}
void
Cloner::visitMember(parser::Member* p)
{}
void
Cloner::visitMField(parser::MField* p)
{
    if (p->field_ != nullptr) {
        p->field_->accept(this);
    }
}
void
Cloner::visitMFun(parser::MFun* p)
{
    visitIdent(p->ident_);
    if (p->listarg_ != nullptr) {
        p->listarg_->accept(this);
    }
    if (p->liststm_ != nullptr) {
        p->liststm_->accept(this);
    }
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
}
void
Cloner::visitECast(parser::ECast* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
}

} // namespace ast::internal