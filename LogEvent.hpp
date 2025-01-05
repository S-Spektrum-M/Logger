#pragma once
#include <chrono>
#include <string>

namespace Spektral::Log {
enum LogLevels : char {
    INFO,
    WARN,
    DEBUG,
    ERROR,
};

class ISource {
  public:
    virtual operator std::string() = 0;
};

class IMessage {
  public:
    virtual operator std::string() = 0;
};
class LogEvent {
  public:
    LogLevels level;
    ISource *source;
    IMessage *message;
    std::chrono::high_resolution_clock::time_point time;

    LogEvent(LogLevels level, ISource *source, IMessage *message) {
        if (!source) {
            throw std::runtime_error(
                "Source object was not properly initialized");
        }
        if (!message) {
            throw std::runtime_error(
                "Message object was not properly initialized");
        }
        this->time = std::chrono::high_resolution_clock::now();
        this->source = source;
        this->message = message;
        this->level = level;
    }

    bool operator<(const LogEvent &cmp) const { return time < cmp.time; };

    operator std::string() {
        return std::format("{}: {} from {}\n", time,
                           message->operator std::string(),
                           source->operator std::string());
    }
};
} // namespace Spektral::Log
