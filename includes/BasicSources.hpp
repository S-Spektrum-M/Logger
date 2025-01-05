#pragma once
#include "LogEvent.hpp"
#include "StrConv.hpp"

namespace Spektral::Log {
template <StrConv T> class Source : public ISource {
    T val;
    Source(T val) : val(val) {}

  public:
    operator std::string() { return (std::string)val; }
    static Source *make(T &val) {
        return new Source(val);
    }
    static Source *make(T &&val) {
        return new Source(val);
    }
};

class Source_int : public ISource {
    int val;
    Source_int(int val) : val(val) {}

public:
    operator std::string() {return std::to_string(val);}
    static Source_int *make(int &args) {
        return new Source_int(args);
    }
    static Source_int *make(int &&args) {
        return new Source_int(args);
    }
};
}
