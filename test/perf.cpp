#include "../BasicMessages.hpp"
#include "../BasicSources.hpp"
#include "../Logger.hpp"
#include <benchmark/benchmark.h>
#include <ctime>
#include <unistd.h>
#include <string>
#include <random>

auto generateRandomInt() -> int {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(0, 1000000000);
    return dist(rng);
}

std::string generateRandomString(std::size_t size) {
    const std::string characters =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;        // Obtain a random number from hardware
    std::mt19937 generator(rd()); // Seed the generator
    std::uniform_int_distribution<std::size_t> distribution(
        0, characters.size() - 1);

    std::string randomString;
    randomString.reserve(size); // Reserve memory to avoid reallocations

    for (std::size_t i = 0; i < size; ++i) {
        randomString += characters[distribution(generator)];
    }

    return randomString;
}


static void BM_LogTestInt(benchmark::State &state) {
    using namespace Spektral::Log;
    std::vector<int> rands;
    for (int ii = 0; ii < 1000000; ++ii) {
        rands.push_back(generateRandomInt());
    }
    Logger l("/tmp/Spektral-Log/1/");
    int ii = 0;
    for (auto _ : state) {
        l.insert(INFO, Source<std::string>::make("main"),
                 Message_int::make(rands[ii++]));
    }
}

static void BM_LogTestStr400(benchmark::State &state) {
    using namespace Spektral::Log;
    std::vector<std::string> rands;
    for (int ii = 0; ii < 1000000; ++ii) {
        rands.push_back(generateRandomString(400));
    }
    Logger l("/tmp/Spektral-Log/1/");
    int ii = 0;
    for (auto _ : state) {
        l.insert(INFO, Source<std::string>::make("main"),
                 Message<std::string>::make(rands[ii++]));
    }
}

BENCHMARK(BM_LogTestInt)->Iterations(1000000);
BENCHMARK(BM_LogTestStr400)->Iterations(1000000);
// Run the benchmark
BENCHMARK_MAIN();
