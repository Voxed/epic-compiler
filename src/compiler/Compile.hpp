#pragma once

#include "parser/Absyn.H"
#include <string>

namespace compiler {

/**
 * Compile the program! :D
 */
std::string
Compile(parser::Program* annotated);

} // namespace compiler