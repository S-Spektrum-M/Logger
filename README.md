# Spektral BTLog

- Very extensible and simple binary tree backed thread-safe logger

## Usage

### Log Insert

> [!NOTE]
> Everything assumes namespace Spektral::Log

> [!TIP]
> Compile with -O3 as this project relies HEAVILY on Named RVO.

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
