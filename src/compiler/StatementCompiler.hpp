#pragma once

#include "State.hpp"
#include "ast/BaseVisitor.hpp"

namespace compiler {

/**
 * Compile a statement.
 */
class StatementCompiler : public ast::BaseVisitor
{
  public:
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

    void visitSForEach(parser::SForEach* p) override;

    /**
     * Accept the visitor into a stm.
     */
    static void Visit(State* state, parser::Stm* stm);

  private:
    explicit StatementCompiler(State* state);

    State* state;
};

} // namespace compiler