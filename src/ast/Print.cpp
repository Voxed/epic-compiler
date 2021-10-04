#include "Print.hpp"

#include "parser/Absyn.H"

namespace ast {

std::string
Print(parser::Visitable* program)
{
    parser::PrintAbsyn printer;
    char* ctext = printer.print(program);
    std::string text(ctext);
    delete ctext;
    return text;
}

} // namespace ast