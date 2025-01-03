#pragma once

#include <string>
template <typename T>
concept StrConv = requires(const T &t) {
    { std::string(t) } -> std::convertible_to<std::string>;
};
