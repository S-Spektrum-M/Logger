#pragma once
#include "Logger.hpp"
#include "StrConv.hpp"

namespace Spektral::Log {
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

class Source_int : public ISource {
    int val;

public:
    Source_int(int val) : val(val) {}
    operator std::string() {return std::to_string(val);}
    template <typename... Args> static Source_int *make(Args... args) {
        Source_int *ret;
        ret = new Source_int(args...);
        return ret;
    }
};
}
