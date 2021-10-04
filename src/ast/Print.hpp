#pragma once

#include <string>

#include "parser/Absyn.H"
#include "parser/Printer.H"

namespace ast {

/**
 * Returns a string representing the passed syntax tree.
 */
std::string
Print(parser::Visitable* program);

} // namespace ast