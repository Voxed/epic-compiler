#pragma once

#include "ast/BaseVisitor.hpp"
#include "checker/State.hpp"

namespace checker {

/**
 * Check a statement and return the annotated tree.
 */
class StatementChecker : public ast::BaseVisitor
{
  public:
    explicit StatementChecker(State* state);

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
     * Accepts the visitor into a statement.
     */
    static parser::Stm* Visit(State* state, parser::Stm* stm);

  private:
    State* state;
    parser::Stm* annotated;
};

} // namespace checker