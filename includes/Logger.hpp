#pragma once
#include "LogEvent.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>

static_assert(__cplusplus == 202002L, "Spektral::Log requires C++20");

namespace Spektral::Log {

class Logger {
  public:
    Logger(std::string log_directory) {
        system(std::string{"mkdir -p " + log_directory}.c_str());
        files[INFO] = std::ofstream{log_directory + "/INFO.log"};
        files[WARN] = std::ofstream{log_directory + "/WARN.log"};
        files[DEBUG] = std::ofstream{log_directory + "/DEBUG.log"};
        files[ERROR] = std::ofstream{log_directory + "/ERROR.log"};
    }
    void insert(LogLevels level, ISource *src, IMessage *msg) {
        log.push_back({level, src, msg});
        if (log.size() == max_size)
            dump();
    }
    void dump() {
        // NOTE:
        std::sort(log.begin(), log.end());
        for (auto elem : log) {
            files[elem.level] << (std::string)elem;
        }
        log.clear();
    }
    ~Logger() {
        // NOTE:
        dump();
    }

  private:
    std::vector<LogEvent> log;
    std::array<std::ofstream, 4> files;
    const size_t max_size = log.max_size();
};
} // namespace Spektral::Log
