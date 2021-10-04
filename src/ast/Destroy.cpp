#include "Destroy.hpp"

#include "ast/BaseVisitor.hpp"
#include "parser/Absyn.H"

using namespace parser;

namespace ast {

namespace internal {

Destroyer::Destroyer()
  : BaseVisitor("Destroyer")
{}

void
Destroyer::visitProgram(Program* p)
{}
void
Destroyer::visitDef(Def* p)
{}
void
Destroyer::visitArg(Arg* p)
{}
void
Destroyer::visitStm(Stm* p)
{}
void
Destroyer::visitDec(Dec* p)
{}
void
Destroyer::visitType(Type* p)
{}
void
Destroyer::visitExp(Exp* p)
{}
void
Destroyer::visitAddOp(AddOp* p)
{}
void
Destroyer::visitMulOp(MulOp* p)
{}
void
Destroyer::visitRelOp(RelOp* p)
{}

void
Destroyer::visitPDefs(PDefs* p)
{
    if (p->listdef_ != nullptr) {
        p->listdef_->accept(this);
    }
}

void
Destroyer::visitDFun(DFun* p)
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
Destroyer::visitADecl(ADecl* p)
{
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
    visitIdent(p->ident_);
}

void
Destroyer::visitSEmpty(SEmpty* p)
{}

void
Destroyer::visitSBlock(SBlock* p)
{
    if (p->liststm_ != nullptr) {
        p->liststm_->accept(this);
    }
}

void
Destroyer::visitSDecl(SDecl* p)
{
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
    if (p->listdec_ != nullptr) {
        p->listdec_->accept(this);
    }
}

void
Destroyer::visitSAss(SAss* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}

void
Destroyer::visitSIncr(SIncr* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}
void
Destroyer::visitSDecr(SDecr* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}

void
Destroyer::visitSRet(SRet* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}

void
Destroyer::visitSVRet(SVRet* p)
{}

void
Destroyer::visitSCond(SCond* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
    if (p->stm_ != nullptr) {
        p->stm_->accept(this);
    }
}

void
Destroyer::visitSCondElse(SCondElse* p)
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
Destroyer::visitSWhile(SWhile* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
    if (p->stm_ != nullptr) {
        p->stm_->accept(this);
    }
}

void
Destroyer::visitSExp(SExp* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}

void
Destroyer::visitDecNoInit(DecNoInit* p)
{
    visitIdent(p->ident_);
}

void
Destroyer::visitDecInit(DecInit* p)
{
    visitIdent(p->ident_);
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}

void
Destroyer::visitTInt(TInt* p)
{}
void
Destroyer::visitTDouble(TDouble* p)
{}
void
Destroyer::visitTBool(TBool* p)
{}
void
Destroyer::visitTVoid(TVoid* p)
{}
void
Destroyer::visitTStr(TStr* p)
{}

void
Destroyer::visitTFun(TFun* p)
{
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
    if (p->listtype_ != nullptr) {
        p->listtype_->accept(this);
    }
}

void
Destroyer::visitEVar(EVar* p)
{
    visitIdent(p->ident_);
}
void
Destroyer::visitEInt(EInt* p)
{
    visitInteger(p->integer_);
}

void
Destroyer::visitEDouble(EDouble* p)
{
    visitDouble(p->double_);
}

void
Destroyer::visitELitTrue(ELitTrue* p)
{}
void
Destroyer::visitELitFalse(ELitFalse* p)
{}

void
Destroyer::visitEApp(EApp* p)
{
    visitIdent(p->ident_);
    if (p->listexp_ != nullptr) {
        p->listexp_->accept(this);
    }
}

void
Destroyer::visitEString(EString* p)
{
    visitString(p->string_);
}

void
Destroyer::visitENeg(ENeg* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}

void
Destroyer::visitENot(ENot* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}

void
Destroyer::visitEMul(EMul* p)
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
Destroyer::visitEAdd(EAdd* p)
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
Destroyer::visitERel(ERel* p)
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
Destroyer::visitEAnd(EAnd* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}

void
Destroyer::visitEOr(EOr* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}

void
Destroyer::visitETyped(ETyped* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
}

void
Destroyer::visitOPlus(OPlus* p)
{}
void
Destroyer::visitOMinus(OMinus* p)
{}
void
Destroyer::visitOTimes(OTimes* p)
{}
void
Destroyer::visitODiv(ODiv* p)
{}
void
Destroyer::visitOMod(OMod* p)
{}
void
Destroyer::visitOLt(OLt* p)
{}
void
Destroyer::visitOLe(OLe* p)
{}
void
Destroyer::visitOGt(OGt* p)
{}
void
Destroyer::visitOGe(OGe* p)
{}
void
Destroyer::visitOEq(OEq* p)
{}
void
Destroyer::visitONe(ONe* p)
{}

void
Destroyer::visitListDef(ListDef* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        (*i)->accept(this);
        delete *i;
    }
}

void
Destroyer::visitListArg(ListArg* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        (*i)->accept(this);
        delete *i;
    }
}

void
Destroyer::visitListStm(ListStm* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        (*i)->accept(this);
        delete *i;
    }
}

void
Destroyer::visitListDec(ListDec* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        (*i)->accept(this);
        delete *i;
    }
}

void
Destroyer::visitListType(ListType* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        (*i)->accept(this);
        delete *i;
    }
}

void
Destroyer::visitListExp(ListExp* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        (*i)->accept(this);
        delete *i;
    }
}

void
Destroyer::visitInteger(Integer x)
{}
void
Destroyer::visitChar(Char x)
{}
void
Destroyer::visitDouble(Double x)
{}
void
Destroyer::visitString(String x)
{}
void
Destroyer::visitIdent(Ident x)
{}

void
Destroyer::visitEIndex(parser::EIndex* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}
void
Destroyer::visitSForEach(parser::SForEach* p)
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
Destroyer::visitTArray(parser::TArray* p)
{
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
}
void
Destroyer::visitEAllocate(parser::EAllocate* p)
{
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
    if (p->listlength_ != nullptr) {
        p->listlength_->accept(this);
    }
}
void
Destroyer::visitEDot(parser::EDot* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}
void
Destroyer::visitLength(parser::Length* p)
{}
void
Destroyer::visitLLength(parser::LLength* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
}
void
Destroyer::visitListLength(parser::ListLength* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        (*i)->accept(this);
        delete *i;
    }
}

void
Destroyer::visitTPointer(parser::TPointer* p)
{
    visitIdent(p->ident_);
}
void
Destroyer::visitTIdent(parser::TIdent* p)
{
    visitIdent(p->ident_);
}
void
Destroyer::visitTStruct(parser::TStruct* p)
{
    visitIdent(p->ident_);
}
void
Destroyer::visitDPointer(parser::DPointer* p)
{
    visitIdent(p->ident_1);
    visitIdent(p->ident_2);
}
void
Destroyer::visitSStruct(parser::SStruct* p)
{
    visitIdent(p->ident_);
    if (p->listfield_ != nullptr) {
        p->listfield_->accept(this);
    }
}
void
Destroyer::visitDStruct(parser::DStruct* p)
{
    if (p->struct_ != nullptr) {
        p->struct_->accept(this);
    }
}
void
Destroyer::visitDInlinePointer(parser::DInlinePointer* p)
{
    visitIdent(p->ident_);
    if (p->struct_ != nullptr) {
        p->struct_->accept(this);
    }
}
void
Destroyer::visitField(parser::Field* p)
{}
void
Destroyer::visitFField(parser::FField* p)
{
    visitIdent(p->ident_);
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
}
void
Destroyer::visitListField(parser::ListField* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        (*i)->accept(this);
        delete *i;
    }
}
void
Destroyer::visitEDeref(parser::EDeref* p)
{
    if (p->exp_1 != nullptr) {
        p->exp_1->accept(this);
    }
    if (p->exp_2 != nullptr) {
        p->exp_2->accept(this);
    }
}
void
Destroyer::visitENull(parser::ENull* p)
{
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
}

void
Destroyer::visitTClass(parser::TClass* p)
{
    visitIdent(p->ident_);
}
void
Destroyer::visitDSubclass(parser::DSubclass* p)
{
    visitIdent(p->ident_1);
    visitIdent(p->ident_2);
    if (p->listmember_ != nullptr) {
        p->listmember_->accept(this);
    }
}
void
Destroyer::visitDClass(parser::DClass* p)
{
    visitIdent(p->ident_);
    if (p->listmember_ != nullptr) {
        p->listmember_->accept(this);
    }
}
void
Destroyer::visitListMember(parser::ListMember* p)
{
    for (auto i = p->begin(); i != p->end(); ++i) {
        (*i)->accept(this);
        delete *i;
    }
}
void
Destroyer::visitMember(parser::Member* p)
{}
void
Destroyer::visitMField(parser::MField* p)
{
    if (p->field_ != nullptr) {
        p->field_->accept(this);
    }
}
void
Destroyer::visitMFun(parser::MFun* p)
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
Destroyer::visitECast(parser::ECast* p)
{
    if (p->exp_ != nullptr) {
        p->exp_->accept(this);
    }
    if (p->type_ != nullptr) {
        p->type_->accept(this);
    }
}

} // namespace internal

void
Destroy(parser::Visitable* target)
{
    internal::Destroyer destroyer;
    target->accept(&destroyer);
    delete target;
}

} // namespace ast