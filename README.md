# Spektral Logger

A simple/extensible(see usage) fast(see benchmarks) looger

## Usage

> [!TIP]
> Compile with -O3 as this project relies HEAVILY on Named RVO.

### Log Insert

> [!NOTE]
> Everything assumes namespace Spektral::Log

```cpp
Logger a("/path/to/log/dir");
a.insert(LogLevel, SourceType::make(args), MessageType::make(args));
```

### Defining a SourceType
```cpp
class SourceType : public ISource {
private:
    // YOUR VALUE
public:
    operator std::string() {}
    template <typename... Args> static SourceType *make(Args... args) {
        SourceType *ret;
        ret = new SourceType(args...);
        return ret;
    }
}
```

### Defining a MessageType
```cpp
class MessageType : public IMessage {
private:
    // YOUR VALUE
public:
    operator std::string() {}
    template <typename... Args> static MessageType *make(Args... args) {
        MessageType *ret;
        ret = new MessageType(args...);
        return ret;
    }
}
```

## Benchmark Results

see: test/perf.cpp. Compiled with -O3 as suggested above.

System Specs:
```
CPU: Intel Core i9 14900HX
Memory:               32GB
OS:             Ubuntu WSL
```

```
-------------------------------------------------------------------------------------
Benchmark                                           Time             CPU   Iterations
-------------------------------------------------------------------------------------
BM_LogTestInt/iterations:1000000_mean            51.4 ns         57.1 ns            5
BM_LogTestInt/iterations:1000000_median          51.5 ns         57.2 ns            5
BM_LogTestInt/iterations:1000000_stddev          3.41 ns         3.79 ns            5
BM_LogTestInt/iterations:1000000_cv              6.63 %          6.64 %             5
BM_LogTestStr400/iterations:1000000_mean          185 ns          205 ns            5
BM_LogTestStr400/iterations:1000000_median        182 ns          202 ns            5
BM_LogTestStr400/iterations:1000000_stddev       10.6 ns         11.7 ns            5
BM_LogTestStr400/iterations:1000000_cv           5.73 %          5.71 %             5
```
