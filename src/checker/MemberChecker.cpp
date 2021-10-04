#include "MemberChecker.hpp"

#include "ast/Clone.hpp"
#include "checker/IdentTypeChecker.hpp"
#include "parser/Absyn.H"

namespace checker {

MemberChecker::MemberChecker(State* state, ClassDescriptor* classDescriptor)
  : state(state)
  , classDescriptor(classDescriptor)
  , annotated(nullptr)
  , ast::BaseVisitor("MemberChecker")
{}

void
MemberChecker::visitMField(parser::MField* p)
{
    auto* concrete = static_cast<parser::FField*>(p->field_);
    parser::Type* type = IdentTypeChecker::Visit(state, concrete->type_);
    classDescriptor->PutField(concrete->ident_, ast::Clone(type));
    annotated = new parser::MField(new parser::FField(type, concrete->ident_));
}
void
MemberChecker::visitMFun(parser::MFun* p)
{
    auto* listType = new parser::ListType;
    auto* newArgs = new parser::ListArg;
    for (parser::Arg* arg : *p->listarg_) {
        auto* concrete = static_cast<parser::ADecl*>(arg);
        parser::Type* type = IdentTypeChecker::Visit(state, concrete->type_);
        listType->push_back(ast::Clone(type));
        newArgs->push_back(new parser::ADecl(type, concrete->ident_));
    }
    parser::Type* type = IdentTypeChecker::Visit(state, p->type_);
    auto* funType = new parser::TFun(ast::Clone(type), listType);
    classDescriptor->PutMethod(p->ident_, funType);
    annotated = new parser::MFun(type, p->ident_, newArgs, ast::Clone(p->liststm_));
}

parser::Member*
MemberChecker::Visit(State* state, ClassDescriptor* classDescriptor, parser::Member* p)
{
    MemberChecker checker(state, classDescriptor);
    p->accept(&checker);
    return checker.annotated;
}

} // namespace checker