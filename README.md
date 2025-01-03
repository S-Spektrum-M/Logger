# BinLog

- Very extensible and simple binary tree backed thread-safe logger

## Usage

### Log Insert
```cpp
Logger a("/path/to/log/dir");
a.insert(LogLevel, SourceType::make(args), MessageType::make(args));
```

### Defining a SourceType
```cpp
#include "BinLog/Logger.hpp"
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
#include "BinLog/Logger.hpp"
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
