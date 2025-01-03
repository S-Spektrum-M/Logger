#pragma once
#include <string>

namespace Spektral::Log {
template <typename T>
concept StrConv = requires(const T &t) {
    { std::string(t) } -> std::convertible_to<std::string>;
};
} // namespace Spektral::Log
