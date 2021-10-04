#pragma once

#include "ast/BaseVisitor.hpp"
#include "parser/Absyn.H"

namespace ast {

namespace internal {

/**
 * Destroyer will delete all list pointers in a syntax tree.
 */
class Destroyer : public BaseVisitor
{
  public:
    Destroyer();

    void visitProgram(parser::Program* p) override;
    void visitDef(parser::Def* p) override;
    void visitArg(parser::Arg* p) override;
    void visitStm(parser::Stm* p) override;
    void visitDec(parser::Dec* p) override;
    void visitType(parser::Type* p) override;
    void visitExp(parser::Exp* p) override;
    void visitAddOp(parser::AddOp* p) override;
    void visitMulOp(parser::MulOp* p) override;
    void visitRelOp(parser::RelOp* p) override;
    void visitPDefs(parser::PDefs* p) override;
    void visitDFun(parser::DFun* p) override;
    void visitADecl(parser::ADecl* p) override;
    void visitSEmpty(parser::SEmpty* p) override;
    void visitSBlock(parser::SBlock* p) override;
    void visitSDecl(parser::SDecl* p) override;
    void visitSAss(parser::SAss* p) override;
    void visitSIncr(parser::SIncr* p) override;
    void visitSDecr(parser::SDecr* p) override;
    void visitSRet(parser::SRet* p) override;
    void visitSVRet(parser::SVRet* p) override;
    void visitSCond(parser::SCond* p) override;
    void visitSCondElse(parser::SCondElse* p) override;
    void visitSWhile(parser::SWhile* p) override;
    void visitSExp(parser::SExp* p) override;
    void visitDecNoInit(parser::DecNoInit* p) override;
    void visitDecInit(parser::DecInit* p) override;
    void visitTInt(parser::TInt* p) override;
    void visitTDouble(parser::TDouble* p) override;
    void visitTBool(parser::TBool* p) override;
    void visitTVoid(parser::TVoid* p) override;
    void visitTStr(parser::TStr* p) override;
    void visitTFun(parser::TFun* p) override;
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
    void visitListDef(parser::ListDef* p) override;
    void visitListArg(parser::ListArg* p) override;
    void visitListStm(parser::ListStm* p) override;
    void visitListDec(parser::ListDec* p) override;
    void visitListType(parser::ListType* p) override;
    void visitListExp(parser::ListExp* p) override;
    void visitInteger(parser::Integer x) override;
    void visitChar(parser::Char x) override;
    void visitDouble(parser::Double x) override;
    void visitString(parser::String x) override;
    void visitIdent(parser::Ident x) override;

    void visitEIndex(parser::EIndex* p) override;
    void visitSForEach(parser::SForEach* p) override;
    void visitTArray(parser::TArray* p) override;
    void visitEAllocate(parser::EAllocate* p) override;
    void visitEDot(parser::EDot* p) override;
    void visitLength(parser::Length* p) override;
    void visitLLength(parser::LLength* p) override;
    void visitListLength(parser::ListLength* p) override;

    void visitTIdent(parser::TIdent* p) override;
    void visitTPointer(parser::TPointer* p) override;
    void visitTStruct(parser::TStruct* p) override;
    void visitDPointer(parser::DPointer* p) override;
    void visitSStruct(parser::SStruct* p) override;
    void visitDStruct(parser::DStruct* p) override;
    void visitDInlinePointer(parser::DInlinePointer* p) override;
    void visitField(parser::Field* p) override;
    void visitFField(parser::FField* p) override;
    void visitListField(parser::ListField* p) override;
    void visitEDeref(parser::EDeref* p) override;
    void visitENull(parser::ENull* p) override;

    void visitTClass(parser::TClass* p) override;
    void visitDSubclass(parser::DSubclass* p) override;
    void visitDClass(parser::DClass* p) override;
    void visitListMember(parser::ListMember* p) override;
    void visitMember(parser::Member* p) override;
    void visitMField(parser::MField* p) override;
    void visitMFun(parser::MFun* p) override;
    void visitECast(parser::ECast* p) override;
};

} // namespace internal

/**
 * Delete a syntax tree.
 */
void
Destroy(parser::Visitable* target);

/**
 * Deleter for use by unique_ptr.
 */
struct Deleter
{
    void operator()(parser::Visitable* target) { Destroy(target); }
};

} // namespace ast