#include "StructChecker.hpp"

#include "ast/Clone.hpp"
#include "ast/Print.hpp"
#include "checker/IdentTypeChecker.hpp"
#include "common/Exceptions.hpp"
#include "common/TypeDeducer.hpp"

namespace checker {

StructChecker::StructChecker(State* state)
  : state(state)
  , annotated(nullptr)
  , ast::BaseVisitor("StructChecker")
{}

void
StructChecker::visitDFun(parser::DFun* p)
{
    annotated = ast::Clone(p);
}
void
StructChecker::visitDPointer(parser::DPointer* p)
{
    annotated = ast::Clone(p);
}
void
StructChecker::visitDInlinePointer(parser::DInlinePointer* p)
{
    annotated = new parser::DInlinePointer(checkStruct(p->struct_), p->ident_);
}
void
StructChecker::visitDStruct(parser::DStruct* p)
{
    annotated = new parser::DStruct(checkStruct(p->struct_));
}

void
StructChecker::visitDClass(parser::DClass* p)
{
    annotated = ast::Clone(p);
}

void
StructChecker::visitDSubclass(parser::DSubclass* p)
{
    annotated = ast::Clone(p);
}

parser::Struct*
StructChecker::checkStruct(parser::Struct* s)
{
    auto* p = static_cast<parser::SStruct*>(s);

    ClassDescriptor* classDescriptor = state->GetClassDescriptor(p->ident_);
    auto* newFields = new parser::ListField;
    for (parser::Field* field : *p->listfield_) {
        auto* concrete = static_cast<parser::FField*>(field);
        parser::Type* type = IdentTypeChecker::Visit(state, concrete->type_);

        if (common::CompareType(type, common::STRUCT)) {
            throw common::CheckerException("Cannot declare field of type " + ast::Print(type));
        }

        classDescriptor->PutField(concrete->ident_, ast::Clone(type));
        auto* aField = new parser::FField(type, concrete->ident_);
        newFields->push_back(aField);
    }
    return new parser::SStruct(p->ident_, newFields);
}

parser::Def*
StructChecker::Visit(State* state, parser::Def* def)
{
    StructChecker checker(state);
    def->accept(&checker);
    return checker.annotated;
}

} // namespace checker