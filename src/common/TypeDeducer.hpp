#pragma once

#include "ast/BaseVisitor.hpp"
#include "parser/Absyn.H"

namespace common {

/**
 * Type ID's
 */
enum TypeId
{
    INT,
    DOUBLE,
    BOOL,
    VOID,
    ARRAY,
    STR,
    FUN,
    POINTER,
    STRUCT,
    CLASS
};

/**
 * Deduces a type ID.
 */
class TypeDeducer : public ast::BaseVisitor
{
  public:
    void visitTInt(parser ::TInt* p) override;
    void visitTDouble(parser ::TDouble* p) override;
    void visitTBool(parser ::TBool* p) override;
    void visitTVoid(parser ::TVoid* p) override;
    void visitTStr(parser ::TStr* p) override;
    void visitTFun(parser ::TFun* p) override;
    void visitTArray(parser ::TArray* p) override;
    void visitTPointer(parser ::TPointer* p) override;
    void visitTStruct(parser ::TStruct* p) override;
    void visitTClass(parser ::TClass* p) override;

    /**
     * Accepts the visitor into a type.
     */
    static TypeId Visit(parser::Type* type);

  private:
    TypeDeducer();

    TypeId typeId;
};

/**
 * Compares two different types.
 */
bool
CompareTypes(parser::Type* t1, parser::Type* t2);

/**
 * Compares a type with a type id.
 */
bool
CompareType(parser::Type* t, TypeId tId);

} // namespace common