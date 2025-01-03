#pragma once
#include <chrono>
#include <filesystem>
#include <fstream>
#include <set>
#include <string>

static_assert(__cplusplus == 202002L, "Spektral::Log requires C++20");

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
        this->source = source;
        this->message = message;
        this->level = level;
        this->time = std::chrono::high_resolution_clock::now();
    }

    bool operator<(const LogEvent &cmp) const { return time < cmp.time; };

    operator std::string() {
        return std::format("{}: {} from {}\n", time,
                           message->operator std::string(),
                           source->operator std::string());
    }
};

class Logger {
  public:
    Logger(std::string log_directory) {
        system(std::string{"mkdir -p " + log_directory}.c_str());
        files_[INFO] = std::ofstream{log_directory + "/INFO.log"};
        files_[WARN] = std::ofstream{log_directory + "/WARN.log"};
        files_[DEBUG] = std::ofstream{log_directory + "/DEBUG.log"};
        files_[ERROR] = std::ofstream{log_directory + "/ERROR.log"};
    }
    void insert(LogLevels level, ISource *src, IMessage *msg) {
        log_.insert({level, src, msg});
        if (log_.size() == 1024)
            dump();
    }
    void dump() {
        for (auto event : log_) {
            files_[event.level] << (std::string)event;
        }
    }
    ~Logger() {
        dump(); // make sure everything gets written eventually
    }

  private:
    std::set<LogEvent> log_;
    std::array<std::ofstream, 4> files_;
};
} // namespace Spektral::Log
