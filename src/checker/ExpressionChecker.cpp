#include "ExpressionChecker.hpp"

#include "ast/Clone.hpp"
#include "ast/Print.hpp"
#include "checker/IdentTypeChecker.hpp"
#include "checker/MemberAccessChecker.hpp"
#include "common/Exceptions.hpp"
#include "common/OperatorDeducer.hpp"
#include "common/TypeDeducer.hpp"
#include "parser/Absyn.H"

namespace checker {

void
ExpressionChecker::checkBinary(parser::ETyped* typed1, parser::ETyped* typed2, bool boolOperator, bool allowBool)
{
    // Differing type
    if (!common::CompareTypes(typed1->type_, typed2->type_)) {
        throw common::CheckerException("Passed differing types to binary operator, got " + ast::Print(typed1->type_) +
                                       "and " + ast::Print(typed2->type_));
    }

    // Ext type on binary op
    if (!common::CompareType(typed1->type_, common::INT) && !common::CompareType(typed1->type_, common::DOUBLE) &&
        !common::CompareType(typed1->type_, common::BOOL)) {
        throw common::CheckerException("Passed " + ast::Print(typed1->type_) + "to binary operator");
    }

    // Ext type on binary op
    if (!common::CompareType(typed2->type_, common::INT) && !common::CompareType(typed2->type_, common::DOUBLE) &&
        !common::CompareType(typed2->type_, common::BOOL)) {
        throw common::CheckerException("Passed " + ast::Print(typed2->type_) + "to binary operator");
    }

    // Int/double on AND/OR
    if (boolOperator && (!CompareType(typed1->type_, common::BOOL) || (!CompareType(typed2->type_, common::BOOL)))) {
        if (!CompareType(typed1->type_, common::BOOL)) {
            throw common::CheckerException(std::string("Passed ") + ast::Print(typed1->type_) + "to boolean operator");
        }
        throw common::CheckerException(std::string("Passed ") + ast::Print(typed2->type_) + "to boolean operator");
    }

    // Booleans on add/mul
    if (!allowBool && ((CompareType(typed1->type_, common::BOOL) || (CompareType(typed2->type_, common::BOOL))))) {
        throw common::CheckerException(std::string("Passed boolean to binary operator which does not accept booleans"));
    }
}

ExpressionChecker::ExpressionChecker(State* state)
  : state(state)
  , annotated(nullptr)
  , ast::BaseVisitor("ExpressionChecker")
{}

void
ExpressionChecker::visitEVar(parser::EVar* p)
{
    annotated = new parser::ETyped(ast::Clone(p), ast::Clone(state->GetVariable(p->ident_)), 1);
}

void
ExpressionChecker::visitEInt(parser::EInt* p)
{
    annotated = new parser::ETyped(ast::Clone(p), new parser::TInt, 0);
}

void
ExpressionChecker::visitEDouble(parser::EDouble* p)
{
    annotated = new parser::ETyped(ast::Clone(p), new parser::TDouble, 0);
}

void
ExpressionChecker::visitELitTrue(parser::ELitTrue* p)
{
    annotated = new parser::ETyped(ast::Clone(p), new parser::TBool, 0);
}

void
ExpressionChecker::visitELitFalse(parser::ELitFalse* p)
{
    annotated = new parser::ETyped(ast::Clone(p), new parser::TBool, 0);
}

void
ExpressionChecker::visitEApp(parser::EApp* p)
{

    parser::TFun* funType = state->GetFunction(p->ident_);

    if (p->listexp_->size() != funType->listtype_->size()) {
        throw common::CheckerException("Wrong amount of arguments in function call, expected " +
                                       std::to_string(funType->listtype_->size()) + " got " +
                                       std::to_string(p->listexp_->size()));
    }

    auto* newListExpr = new parser::ListExp();
    for (size_t i = 0; i < funType->listtype_->size(); i++) {
        State* state = this->state;
        parser::ETyped* typed = ExpressionChecker::Visit(state, (*p->listexp_)[i], (*funType->listtype_)[i]);

        newListExpr->push_back(typed);
    }

    annotated = new parser::ETyped(new parser::EApp(p->ident_, newListExpr), ast::Clone(funType->type_), 0);
}

void
ExpressionChecker::visitEString(parser::EString* p)
{
    annotated = new parser::ETyped(ast::Clone(p), new parser::TStr, 0);
}

void
ExpressionChecker::visitENeg(parser::ENeg* p)
{
    parser::ETyped* newExp = ExpressionChecker::Visit(state, p->exp_);
    if (!CompareType(newExp->type_, common::DOUBLE) && !CompareType(newExp->type_, common::INT)) {
        throw common::CheckerException(
          std::string("Attempted to negate ") + ast::Print(newExp->type_) + "using - operator");
    }
    annotated = new parser::ETyped(new parser::ENeg(newExp), ast::Clone(newExp->type_), 0);
}

void
ExpressionChecker::visitENot(parser::ENot* p)
{
    parser::ETyped* newExp = ExpressionChecker::Visit(state, p->exp_);
    if (!CompareType(newExp->type_, common::BOOL)) {
        throw common::CheckerException(
          std::string("Attempted to negate ") + ast::Print(newExp->type_) + "using ! operator");
    }
    annotated = new parser::ETyped(new parser::ENot(newExp), ast::Clone(newExp->type_), 0);
}

void
ExpressionChecker::visitEMul(parser::EMul* p)
{
    parser::ETyped* typed1 = ExpressionChecker::Visit(state, p->exp_1);
    parser::ETyped* typed2 = ExpressionChecker::Visit(state, p->exp_2);

    checkBinary(typed1, typed2, false, false);

    annotated =
      new parser::ETyped(new parser::EMul(typed1, ast::Clone(p->mulop_), typed2), ast::Clone(typed1->type_), 0);
}

void
ExpressionChecker::visitEAdd(parser::EAdd* p)
{
    parser::ETyped* typed1 = ExpressionChecker::Visit(state, p->exp_1);
    parser::ETyped* typed2 = ExpressionChecker::Visit(state, p->exp_2);

    checkBinary(typed1, typed2, false, false);

    annotated =
      new parser::ETyped(new parser::EAdd(typed1, ast::Clone(p->addop_), typed2), ast::Clone(typed1->type_), 0);
}

void
ExpressionChecker::visitERel(parser::ERel* p)
{
    parser::ETyped* typed1 = ExpressionChecker::Visit(state, p->exp_1);
    parser::ETyped* typed2 = ExpressionChecker::Visit(state, p->exp_2);

    // Special case for pointers and classes.
    if ((common::CompareType(typed1->type_, common::CLASS) && common::CompareType(typed2->type_, common::CLASS)) ||
        (common::CompareType(typed1->type_, common::POINTER) && common::CompareType(typed2->type_, common::POINTER))) {
        if (!common::CompareTypes(typed1->type_, typed2->type_)) {
            throw common::CheckerException(
              "Comparing different types, got " + ast::Print(typed1->type_) + "and " + ast::Print(typed2->type_));
        }
        common::OpId op = common::OperatorDeducer::Visit(p->relop_);
        if (op != common::NE && op != common::EQ) {
            throw common::CheckerException("Comparing using unsupported operator " + ast::Print(p->relop_));
        }
    } else {
        checkBinary(typed1, typed2, false, true);
    }

    annotated = new parser::ETyped(new parser::ERel(typed1, ast::Clone(p->relop_), typed2), new parser::TBool, 0);
}

void
ExpressionChecker::visitEAnd(parser::EAnd* p)
{
    parser::ETyped* typed1 = ExpressionChecker::Visit(state, p->exp_1);
    parser::ETyped* typed2 = ExpressionChecker::Visit(state, p->exp_2);

    checkBinary(typed1, typed2, true, true);

    annotated = new parser::ETyped(new parser::EAnd(typed1, typed2), ast::Clone(typed1->type_), 0);
}

void
ExpressionChecker::visitEOr(parser::EOr* p)
{
    parser::ETyped* typed1 = ExpressionChecker::Visit(state, p->exp_1);
    parser::ETyped* typed2 = ExpressionChecker::Visit(state, p->exp_2);

    checkBinary(typed1, typed2, true, true);

    annotated = new parser::ETyped(new parser::EOr(typed1, typed2), ast::Clone(typed1->type_), 0);
}

void
ExpressionChecker::visitETyped(parser::ETyped* p)
{}

void
ExpressionChecker::visitEAllocate(parser::EAllocate* p)
{
    parser::Type* pType = IdentTypeChecker::Visit(state, p->type_);
    parser::Type* finalType = ast::Clone(pType);

    if (p->listlength_->empty() && !common::CompareType(finalType, common::CLASS) &&
        !common::CompareType(finalType, common::STRUCT)) {
        throw common::CheckerException("Cannot allocate type " + ast::Print(finalType));
    }

    if (common::CompareType(finalType, common::STRUCT)) {
        if (!p->listlength_->empty()) {
            throw common::CheckerException("Cannot allocate an array of " + ast::Print(finalType));
        }
        std::string structName = static_cast<parser::TStruct*>(finalType)->ident_;
        ast::Destroy(finalType);
        finalType = new parser::TPointer(structName);
    } else if (common::CompareType(finalType, common::CLASS)) {
        if (!p->listlength_->empty()) {
            throw common::CheckerException("Cannot allocate an array of " + ast::Print(finalType));
        }
    } else if (common::CompareType(finalType, common::ARRAY)) {
        throw common::CheckerException("Need to specify length for all array dimensions in allocation");
    }

    auto* newListSize = new parser::ListLength;
    for (int i = 0; i < p->listlength_->size(); i++) {
        auto* concrete = static_cast<parser::LLength*>((*p->listlength_)[i]);
        parser::ETyped* newExp = ExpressionChecker::Visit(state, concrete->exp_);
        if (!common::CompareType(newExp->type_, common::INT)) {
            throw common::CheckerException("Non-int array length");
        }
        newListSize->push_back(new parser::LLength(newExp));

        finalType = new parser::TArray(finalType);
    }

    annotated = new parser::ETyped(new parser::EAllocate(pType, newListSize), finalType, 0);
}

void
ExpressionChecker::visitEDot(parser::EDot* p)
{
    parser::ETyped* typed = ExpressionChecker::Visit(state, p->exp_1);

    if (!common::CompareType(typed->type_, common::ARRAY) && !common::CompareType(typed->type_, common::CLASS)) {
        throw common::CheckerException("Attempted to use dot operator on " + ast::Print(typed->type_));
    }

    ClassDescriptor* classDescriptor;

    bool hideFields = false;
    bool hideMethods = true;
    bool writable = false;

    if (common::CompareType(typed->type_, common::ARRAY)) {
        classDescriptor = new ClassDescriptor(false);
        classDescriptor->PutField("length", new parser::TInt);
    } else if (common::CompareType(typed->type_, common::CLASS)) {
        auto* classType = static_cast<parser::TClass*>(typed->type_);
        classDescriptor = state->GetClassDescriptor(classType->ident_);
        hideFields = true;
        hideMethods = false;
    }

    parser::ETyped* typed2 =
      MemberAccessChecker::Visit(classDescriptor, state, p->exp_2, writable, hideMethods, hideFields);
    annotated = new parser::ETyped(new parser::EDot(typed, typed2), ast::Clone(typed2->type_), typed2->char_);
}

void
ExpressionChecker::visitEIndex(parser::EIndex* p)
{
    parser::ETyped* typed = ExpressionChecker::Visit(state, p->exp_1);

    if (!common::CompareType(typed->type_, common::ARRAY)) {
        throw common::CheckerException("Attempted to index non-array");
    }

    auto* arrayT = static_cast<parser::TArray*>(typed->type_);

    parser::ETyped* typed2 = ExpressionChecker::Visit(state, p->exp_2);

    if (!common::CompareType(typed2->type_, common::INT)) {
        throw common::CheckerException("Non int index");
    }

    annotated = new parser::ETyped(new parser::EIndex(typed, typed2), ast::Clone(arrayT->type_), 1);
}

void
ExpressionChecker::visitEDeref(parser::EDeref* p)
{
    parser::ETyped* typed = ExpressionChecker::Visit(state, p->exp_1);

    if (!common::CompareType(typed->type_, common::POINTER)) {
        throw common::CheckerException("Attempted to dereference a " + ast::Print(typed->type_));
    }

    auto* pointer = static_cast<parser::TPointer*>(typed->type_);

    ClassDescriptor* namespaceDesc = state->GetClassDescriptor(pointer->ident_);

    parser::ETyped* typed2 = MemberAccessChecker::Visit(namespaceDesc, state, p->exp_2, true, true, false);
    annotated = new parser::ETyped(new parser::EDeref(typed, typed2), ast::Clone(typed2->type_), typed2->char_);
}

void
ExpressionChecker::visitENull(parser::ENull* p)
{
    parser::Type* pType = IdentTypeChecker::Visit(state, p->type_);

    if (!common::CompareType(pType, common::POINTER) && !common::CompareType(pType, common::CLASS)) {
        throw common::CheckerException("Attempted to create a null " + ast::Print(pType));
    }

    annotated = new parser::ETyped(new parser::ENull(pType), ast::Clone(pType), 0);
}

parser::ETyped*
ExpressionChecker::Visit(State* state, parser::Exp* exp, parser::Type* type)
{
    ExpressionChecker expChecker(state);
    exp->accept(&expChecker);

    if (type != nullptr) {
        if (!common::CompareTypes(expChecker.annotated->type_, type)) {
            if (common::CompareType(type, common::CLASS) &&
                common::CompareType(expChecker.annotated->type_, common::CLASS)) {
                // Insert cast
                std::string classId1 = static_cast<parser::TClass*>(type)->ident_;
                std::string classId2 = static_cast<parser::TClass*>(expChecker.annotated->type_)->ident_;
                if (state->GetClassDescriptor(classId2)->IsDerivedFrom(state->GetClassDescriptor(classId1))) {
                    return new parser::ETyped(new parser::ECast(expChecker.annotated, ast::Clone(type)),
                      ast::Clone(type),
                      expChecker.annotated->char_);
                }
            }
            throw common::CheckerException(
              "Expected " + ast::Print(type) + "got " + ast::Print(expChecker.annotated->type_));
        }
    }
    return expChecker.annotated;
}

} // namespace checker