#pragma once
#include "Logger.hpp"
#include "StrConv.hpp"

template <StrConv T> class Source : public ISource {
    T val;

  public:
    Source(T val) : val(val) {}
    operator std::string() { return (std::string)val; }
    template <typename... Args> static Source *make(Args... args) {
        Source *ret;
        ret = new Source(args...);
        return ret;
    }
};
