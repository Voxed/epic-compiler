/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Skeleton.H"


namespace parser
{
void Skeleton::visitProgram(Program *t) {} //abstract class
void Skeleton::visitDef(Def *t) {} //abstract class
void Skeleton::visitArg(Arg *t) {} //abstract class
void Skeleton::visitStm(Stm *t) {} //abstract class
void Skeleton::visitDec(Dec *t) {} //abstract class
void Skeleton::visitType(Type *t) {} //abstract class
void Skeleton::visitExp(Exp *t) {} //abstract class
void Skeleton::visitAddOp(AddOp *t) {} //abstract class
void Skeleton::visitMulOp(MulOp *t) {} //abstract class
void Skeleton::visitRelOp(RelOp *t) {} //abstract class
void Skeleton::visitLength(Length *t) {} //abstract class
void Skeleton::visitStruct(Struct *t) {} //abstract class
void Skeleton::visitField(Field *t) {} //abstract class
void Skeleton::visitMember(Member *t) {} //abstract class

void Skeleton::visitPDefs(PDefs *p_defs)
{
  /* Code For PDefs Goes Here */

  if (p_defs->listdef_) p_defs->listdef_->accept(this);

}

void Skeleton::visitDFun(DFun *d_fun)
{
  /* Code For DFun Goes Here */

  if (d_fun->type_) d_fun->type_->accept(this);
  visitIdent(d_fun->ident_);
  if (d_fun->listarg_) d_fun->listarg_->accept(this);
  if (d_fun->liststm_) d_fun->liststm_->accept(this);

}

void Skeleton::visitDPointer(DPointer *d_pointer)
{
  /* Code For DPointer Goes Here */

  visitIdent(d_pointer->ident_1);
  visitIdent(d_pointer->ident_2);

}

void Skeleton::visitDStruct(DStruct *d_struct)
{
  /* Code For DStruct Goes Here */

  if (d_struct->struct_) d_struct->struct_->accept(this);

}

void Skeleton::visitDInlinePointer(DInlinePointer *d_inline_pointer)
{
  /* Code For DInlinePointer Goes Here */

  if (d_inline_pointer->struct_) d_inline_pointer->struct_->accept(this);
  visitIdent(d_inline_pointer->ident_);

}

void Skeleton::visitDClass(DClass *d_class)
{
  /* Code For DClass Goes Here */

  visitIdent(d_class->ident_);
  if (d_class->listmember_) d_class->listmember_->accept(this);

}

void Skeleton::visitDSubclass(DSubclass *d_subclass)
{
  /* Code For DSubclass Goes Here */

  visitIdent(d_subclass->ident_1);
  visitIdent(d_subclass->ident_2);
  if (d_subclass->listmember_) d_subclass->listmember_->accept(this);

}

void Skeleton::visitADecl(ADecl *a_decl)
{
  /* Code For ADecl Goes Here */

  if (a_decl->type_) a_decl->type_->accept(this);
  visitIdent(a_decl->ident_);

}

void Skeleton::visitSEmpty(SEmpty *s_empty)
{
  /* Code For SEmpty Goes Here */


}

void Skeleton::visitSBlock(SBlock *s_block)
{
  /* Code For SBlock Goes Here */

  if (s_block->liststm_) s_block->liststm_->accept(this);

}

void Skeleton::visitSDecl(SDecl *s_decl)
{
  /* Code For SDecl Goes Here */

  if (s_decl->type_) s_decl->type_->accept(this);
  if (s_decl->listdec_) s_decl->listdec_->accept(this);

}

void Skeleton::visitSAss(SAss *s_ass)
{
  /* Code For SAss Goes Here */

  if (s_ass->exp_1) s_ass->exp_1->accept(this);
  if (s_ass->exp_2) s_ass->exp_2->accept(this);

}

void Skeleton::visitSIncr(SIncr *s_incr)
{
  /* Code For SIncr Goes Here */

  if (s_incr->exp_) s_incr->exp_->accept(this);

}

void Skeleton::visitSDecr(SDecr *s_decr)
{
  /* Code For SDecr Goes Here */

  if (s_decr->exp_) s_decr->exp_->accept(this);

}

void Skeleton::visitSRet(SRet *s_ret)
{
  /* Code For SRet Goes Here */

  if (s_ret->exp_) s_ret->exp_->accept(this);

}

void Skeleton::visitSVRet(SVRet *sv_ret)
{
  /* Code For SVRet Goes Here */


}

void Skeleton::visitSCond(SCond *s_cond)
{
  /* Code For SCond Goes Here */

  if (s_cond->exp_) s_cond->exp_->accept(this);
  if (s_cond->stm_) s_cond->stm_->accept(this);

}

void Skeleton::visitSCondElse(SCondElse *s_cond_else)
{
  /* Code For SCondElse Goes Here */

  if (s_cond_else->exp_) s_cond_else->exp_->accept(this);
  if (s_cond_else->stm_1) s_cond_else->stm_1->accept(this);
  if (s_cond_else->stm_2) s_cond_else->stm_2->accept(this);

}

void Skeleton::visitSWhile(SWhile *s_while)
{
  /* Code For SWhile Goes Here */

  if (s_while->exp_) s_while->exp_->accept(this);
  if (s_while->stm_) s_while->stm_->accept(this);

}

void Skeleton::visitSExp(SExp *s_exp)
{
  /* Code For SExp Goes Here */

  if (s_exp->exp_) s_exp->exp_->accept(this);

}

void Skeleton::visitSForEach(SForEach *s_for_each)
{
  /* Code For SForEach Goes Here */

  if (s_for_each->type_) s_for_each->type_->accept(this);
  visitIdent(s_for_each->ident_);
  if (s_for_each->exp_) s_for_each->exp_->accept(this);
  if (s_for_each->stm_) s_for_each->stm_->accept(this);

}

void Skeleton::visitDecNoInit(DecNoInit *dec_no_init)
{
  /* Code For DecNoInit Goes Here */

  visitIdent(dec_no_init->ident_);

}

void Skeleton::visitDecInit(DecInit *dec_init)
{
  /* Code For DecInit Goes Here */

  visitIdent(dec_init->ident_);
  if (dec_init->exp_) dec_init->exp_->accept(this);

}

void Skeleton::visitTInt(TInt *t_int)
{
  /* Code For TInt Goes Here */


}

void Skeleton::visitTDouble(TDouble *t_double)
{
  /* Code For TDouble Goes Here */


}

void Skeleton::visitTBool(TBool *t_bool)
{
  /* Code For TBool Goes Here */


}

void Skeleton::visitTVoid(TVoid *t_void)
{
  /* Code For TVoid Goes Here */


}

void Skeleton::visitTStr(TStr *t_str)
{
  /* Code For TStr Goes Here */


}

void Skeleton::visitTFun(TFun *t_fun)
{
  /* Code For TFun Goes Here */

  if (t_fun->type_) t_fun->type_->accept(this);
  if (t_fun->listtype_) t_fun->listtype_->accept(this);

}

void Skeleton::visitTArray(TArray *t_array)
{
  /* Code For TArray Goes Here */

  if (t_array->type_) t_array->type_->accept(this);

}

void Skeleton::visitTIdent(TIdent *t_ident)
{
  /* Code For TIdent Goes Here */

  visitIdent(t_ident->ident_);

}

void Skeleton::visitTPointer(TPointer *t_pointer)
{
  /* Code For TPointer Goes Here */

  visitIdent(t_pointer->ident_);

}

void Skeleton::visitTStruct(TStruct *t_struct)
{
  /* Code For TStruct Goes Here */

  visitIdent(t_struct->ident_);

}

void Skeleton::visitTClass(TClass *t_class)
{
  /* Code For TClass Goes Here */

  visitIdent(t_class->ident_);

}

void Skeleton::visitEVar(EVar *e_var)
{
  /* Code For EVar Goes Here */

  visitIdent(e_var->ident_);

}

void Skeleton::visitEApp(EApp *e_app)
{
  /* Code For EApp Goes Here */

  visitIdent(e_app->ident_);
  if (e_app->listexp_) e_app->listexp_->accept(this);

}

void Skeleton::visitEInt(EInt *e_int)
{
  /* Code For EInt Goes Here */

  visitInteger(e_int->integer_);

}

void Skeleton::visitEDouble(EDouble *e_double)
{
  /* Code For EDouble Goes Here */

  visitDouble(e_double->double_);

}

void Skeleton::visitELitTrue(ELitTrue *e_lit_true)
{
  /* Code For ELitTrue Goes Here */


}

void Skeleton::visitELitFalse(ELitFalse *e_lit_false)
{
  /* Code For ELitFalse Goes Here */


}

void Skeleton::visitEString(EString *e_string)
{
  /* Code For EString Goes Here */

  visitString(e_string->string_);

}

void Skeleton::visitENeg(ENeg *e_neg)
{
  /* Code For ENeg Goes Here */

  if (e_neg->exp_) e_neg->exp_->accept(this);

}

void Skeleton::visitENot(ENot *e_not)
{
  /* Code For ENot Goes Here */

  if (e_not->exp_) e_not->exp_->accept(this);

}

void Skeleton::visitEMul(EMul *e_mul)
{
  /* Code For EMul Goes Here */

  if (e_mul->exp_1) e_mul->exp_1->accept(this);
  if (e_mul->mulop_) e_mul->mulop_->accept(this);
  if (e_mul->exp_2) e_mul->exp_2->accept(this);

}

void Skeleton::visitEAdd(EAdd *e_add)
{
  /* Code For EAdd Goes Here */

  if (e_add->exp_1) e_add->exp_1->accept(this);
  if (e_add->addop_) e_add->addop_->accept(this);
  if (e_add->exp_2) e_add->exp_2->accept(this);

}

void Skeleton::visitERel(ERel *e_rel)
{
  /* Code For ERel Goes Here */

  if (e_rel->exp_1) e_rel->exp_1->accept(this);
  if (e_rel->relop_) e_rel->relop_->accept(this);
  if (e_rel->exp_2) e_rel->exp_2->accept(this);

}

void Skeleton::visitEAnd(EAnd *e_and)
{
  /* Code For EAnd Goes Here */

  if (e_and->exp_1) e_and->exp_1->accept(this);
  if (e_and->exp_2) e_and->exp_2->accept(this);

}

void Skeleton::visitEOr(EOr *e_or)
{
  /* Code For EOr Goes Here */

  if (e_or->exp_1) e_or->exp_1->accept(this);
  if (e_or->exp_2) e_or->exp_2->accept(this);

}

void Skeleton::visitETyped(ETyped *e_typed)
{
  /* Code For ETyped Goes Here */

  if (e_typed->exp_) e_typed->exp_->accept(this);
  if (e_typed->type_) e_typed->type_->accept(this);
  visitChar(e_typed->char_);

}

void Skeleton::visitEIndex(EIndex *e_index)
{
  /* Code For EIndex Goes Here */

  if (e_index->exp_1) e_index->exp_1->accept(this);
  if (e_index->exp_2) e_index->exp_2->accept(this);

}

void Skeleton::visitEAllocate(EAllocate *e_allocate)
{
  /* Code For EAllocate Goes Here */

  if (e_allocate->type_) e_allocate->type_->accept(this);
  if (e_allocate->listlength_) e_allocate->listlength_->accept(this);

}

void Skeleton::visitEDot(EDot *e_dot)
{
  /* Code For EDot Goes Here */

  if (e_dot->exp_1) e_dot->exp_1->accept(this);
  if (e_dot->exp_2) e_dot->exp_2->accept(this);

}

void Skeleton::visitENull(ENull *e_null)
{
  /* Code For ENull Goes Here */

  if (e_null->type_) e_null->type_->accept(this);

}

void Skeleton::visitEDeref(EDeref *e_deref)
{
  /* Code For EDeref Goes Here */

  if (e_deref->exp_1) e_deref->exp_1->accept(this);
  if (e_deref->exp_2) e_deref->exp_2->accept(this);

}

void Skeleton::visitECast(ECast *e_cast)
{
  /* Code For ECast Goes Here */

  if (e_cast->exp_) e_cast->exp_->accept(this);
  if (e_cast->type_) e_cast->type_->accept(this);

}

void Skeleton::visitOPlus(OPlus *o_plus)
{
  /* Code For OPlus Goes Here */


}

void Skeleton::visitOMinus(OMinus *o_minus)
{
  /* Code For OMinus Goes Here */


}

void Skeleton::visitOTimes(OTimes *o_times)
{
  /* Code For OTimes Goes Here */


}

void Skeleton::visitODiv(ODiv *o_div)
{
  /* Code For ODiv Goes Here */


}

void Skeleton::visitOMod(OMod *o_mod)
{
  /* Code For OMod Goes Here */


}

void Skeleton::visitOLt(OLt *o_lt)
{
  /* Code For OLt Goes Here */


}

void Skeleton::visitOLe(OLe *o_le)
{
  /* Code For OLe Goes Here */


}

void Skeleton::visitOGt(OGt *o_gt)
{
  /* Code For OGt Goes Here */


}

void Skeleton::visitOGe(OGe *o_ge)
{
  /* Code For OGe Goes Here */


}

void Skeleton::visitOEq(OEq *o_eq)
{
  /* Code For OEq Goes Here */


}

void Skeleton::visitONe(ONe *o_ne)
{
  /* Code For ONe Goes Here */


}

void Skeleton::visitLLength(LLength *l_length)
{
  /* Code For LLength Goes Here */

  if (l_length->exp_) l_length->exp_->accept(this);

}

void Skeleton::visitSStruct(SStruct *s_struct)
{
  /* Code For SStruct Goes Here */

  visitIdent(s_struct->ident_);
  if (s_struct->listfield_) s_struct->listfield_->accept(this);

}

void Skeleton::visitFField(FField *f_field)
{
  /* Code For FField Goes Here */

  if (f_field->type_) f_field->type_->accept(this);
  visitIdent(f_field->ident_);

}

void Skeleton::visitMField(MField *m_field)
{
  /* Code For MField Goes Here */

  if (m_field->field_) m_field->field_->accept(this);

}

void Skeleton::visitMFun(MFun *m_fun)
{
  /* Code For MFun Goes Here */

  if (m_fun->type_) m_fun->type_->accept(this);
  visitIdent(m_fun->ident_);
  if (m_fun->listarg_) m_fun->listarg_->accept(this);
  if (m_fun->liststm_) m_fun->liststm_->accept(this);

}


void Skeleton::visitListDef(ListDef *list_def)
{
  for (ListDef::iterator i = list_def->begin() ; i != list_def->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListArg(ListArg *list_arg)
{
  for (ListArg::iterator i = list_arg->begin() ; i != list_arg->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListStm(ListStm *list_stm)
{
  for (ListStm::iterator i = list_stm->begin() ; i != list_stm->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListDec(ListDec *list_dec)
{
  for (ListDec::iterator i = list_dec->begin() ; i != list_dec->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListType(ListType *list_type)
{
  for (ListType::iterator i = list_type->begin() ; i != list_type->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListExp(ListExp *list_exp)
{
  for (ListExp::iterator i = list_exp->begin() ; i != list_exp->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListLength(ListLength *list_length)
{
  for (ListLength::iterator i = list_length->begin() ; i != list_length->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListField(ListField *list_field)
{
  for (ListField::iterator i = list_field->begin() ; i != list_field->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListMember(ListMember *list_member)
{
  for (ListMember::iterator i = list_member->begin() ; i != list_member->end() ; ++i)
  {
    (*i)->accept(this);
  }
}


void Skeleton::visitInteger(Integer x)
{
  /* Code for Integer Goes Here */
}

void Skeleton::visitChar(Char x)
{
  /* Code for Char Goes Here */
}

void Skeleton::visitDouble(Double x)
{
  /* Code for Double Goes Here */
}

void Skeleton::visitString(String x)
{
  /* Code for String Goes Here */
}

void Skeleton::visitIdent(Ident x)
{
  /* Code for Ident Goes Here */
}


}
