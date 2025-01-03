#pragma once
#include "Logger.hpp"
#include "StrConv.hpp"


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
