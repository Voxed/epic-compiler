#include "ast/Destroy.hpp"
#include "checker/Check.hpp"
#include "common/Exceptions.hpp"
#include "compiler/Compile.hpp"
#include "parser/Absyn.H"
#include "parser/Parser.H"
#include "parser/ParserError.H"
#include <iostream>

/**
 * Start of everything.
 */
int
main()
{
    try {
        // Parse
        parser::Program* program = parser::pProgram(stdin);

        // Type check
        parser::Program* annotated = checker::Check(program);
        ast::Destroy(program);

        // Compile
        std::string code = compiler::Compile(annotated);
        ast::Destroy(annotated);

        // Output
        std::cout << code << std::endl;
        std::cerr << "OK" << std::endl;
    } catch (parser::parse_error& e) {
        std::cerr << "ERROR" << std::endl;
        std::cerr << "ParseException: Parse error on line " << e.getLine() << "\n";
        return 1;
    } catch (const common::CheckerException& e) {
        std::cerr << "ERROR" << std::endl;
        std::cerr << "CheckerException: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}