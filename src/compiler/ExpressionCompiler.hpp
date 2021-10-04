#pragma once

#include "ast/BaseVisitor.hpp"
#include "compiler/State.hpp"
#include <llvm/IR/Value.h>

namespace compiler {

/**
 * Result of the expression compiler.
 */
class ExpressionCompilerResult
{
  public:
    ExpressionCompilerResult(bool lvalue, llvm::Value* value, parser::Type* type, State* state);

    /**
     * Get the r-value of the expression. If it's an l-value it will
     * automatically insert a load.
     */
    llvm::Value* GetRValue();

    /**
     * Get the value of the expression, could be either an r-value or an
     * l-value.
     */
    llvm::Value* GetValue();

    /**
     * Get the parser type of the expression.
     */
    parser::Type* GetType();

  private:
    bool lvalue;
    llvm::Value* value;
    parser::Type* type;
    State* state;
};

/**
 * Compiles an expression.
 */
class ExpressionCompiler : public ast::BaseVisitor
{
  public:
    void visitEVar(parser::EVar* p) override;
    void visitEInt(parser::EInt* p) override;
    void visitEDouble(parser::EDouble* p) override;
    void visitELitFalse(parser::ELitFalse* p) override;
    void visitELitTrue(parser::ELitTrue* p) override;
    void visitEApp(parser::EApp* p) override;
    void visitEString(parser ::EString* p) override;
    void visitENeg(parser ::ENeg* p) override;
    void visitENot(parser ::ENot* p) override;
    void visitEMul(parser ::EMul* p) override;
    void visitEAdd(parser ::EAdd* p) override;
    void visitERel(parser ::ERel* p) override;
    void visitEAnd(parser ::EAnd* p) override;
    void visitEOr(parser ::EOr* p) override;

    void visitETyped(parser::ETyped* p) override;

    void visitEAllocate(parser::EAllocate* p) override;
    void visitEDot(parser::EDot* p) override;
    void visitEIndex(parser::EIndex* p) override;

    void visitENull(parser::ENull* p) override;
    void visitEDeref(parser::EDeref* p) override;

    void visitECast(parser::ECast* p) override;

    /**
     * Accept the visitor into an expression.
     */
    static ExpressionCompilerResult Visit(State* state, parser::Exp* exp);

  private:
    static ExpressionCompilerResult Visit(State* state, parser::Exp* exp, bool isLvalue, parser::Type* expectedType);
    explicit ExpressionCompiler(State* state);
    bool lvalue;
    State* state;
    llvm::Value* value;
    parser::Type* type;
};

} // namespace compiler