#pragma once
#include "LogEvent.hpp"
#include "StrConv.hpp"

namespace Spektral::Log {
template <StrConv T> class Message : public IMessage {
    T val;

  public:
    Message(T val) : val(val) {}
    operator std::string() { return (std::string)val; }
    template <typename... Args> static Message *make(Args... args) {
        Message *ret;
        ret = new Message(args...);
        return ret;
    }
};

class Message_int : public IMessage {
    int val;

  public:
    Message_int(int val) : val(val) {}
    operator std::string() { return std::to_string(val); }
    template <typename... Args> static Message_int *make(Args... args) {
        Message_int *ret;
        ret = new Message_int(args...);
        return ret;
    }
};
}
