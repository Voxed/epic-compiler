#pragma once

#include <stdexcept>
#include <string>

namespace common {

/**
 * Thrown when a syntax that is unimplemented on a visitor is used.
 */
class UnimplementedException : public std::runtime_error
{
  public:
    explicit UnimplementedException(const std::string& reason);

    [[nodiscard]] char const* what() const noexcept override;

  private:
    std::string reason;
};

/**
 * Thrown when an error occurs in the checker.
 */
class CheckerException : public std::runtime_error
{
  public:
    explicit CheckerException(const std::string& reason);

    [[nodiscard]] char const* what() const noexcept override;

  private:
    std::string reason;
};

} // namespace common