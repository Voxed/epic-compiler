#include "TypeDeducer.hpp"

namespace common {

TypeDeducer::TypeDeducer()
  : typeId(INT)
  , ast::BaseVisitor("TypeDeducer")
{}

void
TypeDeducer::visitTInt(parser ::TInt* /*p*/)
{
    typeId = INT;
}

void
TypeDeducer::visitTDouble(parser ::TDouble* /*p*/)
{
    typeId = DOUBLE;
}

void
TypeDeducer::visitTBool(parser ::TBool* /*p*/)
{
    typeId = BOOL;
}

void
TypeDeducer::visitTVoid(parser ::TVoid* /*p*/)
{
    typeId = VOID;
}

void
TypeDeducer::visitTStr(parser ::TStr* /*p*/)
{
    typeId = STR;
}

void
TypeDeducer::visitTFun(parser ::TFun* /*p*/)
{
    typeId = FUN;
}

void
TypeDeducer::visitTArray(parser ::TArray* /*p*/)
{
    typeId = ARRAY;
}

void
TypeDeducer::visitTPointer(parser::TPointer* /*p*/)
{
    typeId = POINTER;
}

void
TypeDeducer::visitTStruct(parser::TStruct* /*p*/)
{
    typeId = STRUCT;
}

void
TypeDeducer::visitTClass(parser ::TClass* /*p*/)
{
    typeId = CLASS;
}

TypeId
TypeDeducer::Visit(parser::Type* type)
{
    TypeDeducer deducer;
    type->accept(&deducer);
    return deducer.typeId;
}

bool
CompareTypes(parser::Type* t1, parser::Type* t2)
{
    common::TypeId t1Id = TypeDeducer::Visit(t1);
    common::TypeId t2Id = TypeDeducer::Visit(t2);

    // Code for comparing arrays.
    if (t2Id == ARRAY && t1Id == ARRAY) {
        auto* t1arr = static_cast<parser::TArray*>(t1);
        auto* t2arr = static_cast<parser::TArray*>(t2);

        return CompareTypes(t1arr->type_, t2arr->type_);
    }

    if (t1Id == POINTER && t2Id == POINTER) {
        auto* t1arr = static_cast<parser::TPointer*>(t1);
        auto* t2arr = static_cast<parser::TPointer*>(t2);

        return t1arr->ident_ == t2arr->ident_;
    }

    if (t1Id == STRUCT && t2Id == STRUCT) {
        auto* t1arr = static_cast<parser::TStruct*>(t1);
        auto* t2arr = static_cast<parser::TStruct*>(t2);

        return t1arr->ident_ == t2arr->ident_;
    }

    if (t1Id == CLASS && t2Id == CLASS) {
        auto* t1arr = static_cast<parser::TClass*>(t1);
        auto* t2arr = static_cast<parser::TClass*>(t2);

        return t1arr->ident_ == t2arr->ident_;
    }

    if (t1Id == FUN && t2Id == FUN) {
        auto* t1fun = static_cast<parser::TFun*>(t1);
        auto* t2fun = static_cast<parser::TFun*>(t2);

        if (!CompareTypes(t1fun->type_, t2fun->type_)) {
            return false;
        }
        if (t1fun->listtype_->size() != t2fun->listtype_->size()) {
            return false;
        }
        for (int i = 0; i < t1fun->listtype_->size(); i++) {
            if (!CompareTypes((*t1fun->listtype_)[i], (*t2fun->listtype_)[i])) {
                return false;
            }
        }
        return true;
    }

    return t1Id == t2Id;
}

bool
CompareType(parser::Type* t, TypeId tId)
{
    return TypeDeducer::Visit(t) == tId;
}

} // namespace common