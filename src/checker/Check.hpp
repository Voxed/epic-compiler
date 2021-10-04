#pragma once

#include "parser/Absyn.H"

namespace checker {

/**
 * Type check a program.
 */
parser::Program*
Check(parser::Program* program);

} // namespace checker