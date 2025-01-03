#include "Logger.hpp"

// TODO: bool, char, char *, std::string

class MessageString : public IMessage {
    std::string val;

  public:
    MessageString(std::string val) : val(val) {}
    operator std::string() { return val; }
    template <typename... Args> static MessageString *make(Args... args) {
        MessageString *ret;
        ret = new MessageString(args...);
        return ret;
    }
};

class MessageInt : public IMessage {
    int val;

  public:
    MessageInt(int val) : val(val) {}
    operator std::string() { return std::to_string(val); }
    template <typename... Args> static MessageInt *make(Args... args) {
        MessageInt *ret;
        ret = new MessageInt(args...);
        return ret;
    }
};
