#pragma once
#include "LogEvent.hpp"
#include "StrConv.hpp"

namespace Spektral::Log {
template <StrConv T> class Message : public IMessage {
    T val;
    Message(T val) : val(val) {}

  public:
    operator std::string() { return (std::string)val; }
    template <typename... Args> static Message *make(Args... args) {
        return new Message(args...);
    }
};

class Message_int : public IMessage {
    int val;
    Message_int(int val) : val(val) {}

  public:
    operator std::string() { return std::to_string(val); }
    template <typename... Args> static Message_int *make(int val) {
        return new Message_int(val);
    }
};
}
