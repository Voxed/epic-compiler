#include "Exceptions.hpp"

namespace common {

UnimplementedException::UnimplementedException(const std::string& reason)
  : reason(reason)
  , std::runtime_error(reason){};

char const*
UnimplementedException::what() const noexcept
{
    return reason.c_str();
}

CheckerException::CheckerException(const std::string& reason)
  : reason(reason)
  , std::runtime_error(reason){};

char const*
CheckerException::what() const noexcept
{
    return reason.c_str();
}

} // namespace common