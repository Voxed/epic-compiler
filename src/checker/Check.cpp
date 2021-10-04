#include "Check.hpp"

#include "checker/ClassChecker.hpp"
#include "checker/ClassMethodChecker.hpp"
#include "checker/FunctionChecker.hpp"
#include "checker/State.hpp"
#include "checker/StructChecker.hpp"
#include "checker/TopDecChecker.hpp"
#include "common/Exceptions.hpp"

namespace checker {

parser::Program*
Check(parser::Program* program)
{
    State state;

    auto* argTypes = new parser::ListType;
    argTypes->push_back(new parser::TInt);
    state.PutFunction("printInt", new parser::TFun(new parser::TVoid, argTypes));

    argTypes = new parser::ListType;
    argTypes->push_back(new parser::TDouble);
    state.PutFunction("printDouble", new parser::TFun(new parser::TVoid, argTypes));

    argTypes = new parser::ListType;
    argTypes->push_back(new parser::TStr);
    state.PutFunction("printString", new parser::TFun(new parser::TVoid, argTypes));

    argTypes = new parser::ListType;
    state.PutFunction("readInt", new parser::TFun(new parser::TInt, argTypes));

    argTypes = new parser::ListType;
    state.PutFunction("readDouble", new parser::TFun(new parser::TDouble, argTypes));

    auto* p = static_cast<parser::PDefs*>(program);

    // Check and collect top definitions
    for (parser::Def* def : *p->listdef_) {
        TopDecChecker::Visit(&state, def);
    }

    // Type check the program
    parser::TFun* t = state.GetFunction("main");
    if (!t->listtype_->empty()) {
        throw common::CheckerException("Main function takes too many arguments");
    }

    // Check and annotate the program.
    auto* structAnnotated = new parser::ListDef;
    for (parser::Def* def : *p->listdef_) {
        structAnnotated->push_back(StructChecker::Visit(&state, def));
    }

    // Check and annotate classes.
    auto* classAnnotated = new parser::ListDef;
    for (parser::Def* def : *structAnnotated) {
        classAnnotated->push_back(ClassChecker::Visit(&state, def));
    }
    ast::Destroy(structAnnotated);

    state.Verify();

    // Check and annotate class methods.
    auto* classMethodsAnnotated = new parser::ListDef;
    for (parser::Def* def : *classAnnotated) {
        classMethodsAnnotated->push_back(ClassMethodChecker::Visit(&state, def));
    }
    ast::Destroy(classAnnotated);

    auto* functionAnnotated = new parser::ListDef;
    for (parser::Def* def : *classMethodsAnnotated) {
        functionAnnotated->push_back(FunctionChecker::Visit(&state, def));
    }
    ast::Destroy(classMethodsAnnotated);

    return new parser::PDefs(functionAnnotated);
}

} // namespace checker