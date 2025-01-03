#include "Logger.hpp"

class SourceString : public ISource {
    std::string source;

  public:
    SourceString(std::string src) : source(src) {}
    operator std::string() { return source; }
    template <typename... Args> static SourceString *make(Args... args) {
        SourceString *ret;
        ret = new SourceString(args...);
        return ret;
    }
};
