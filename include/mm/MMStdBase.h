#ifndef MM_MMSTDBASE_H
#define MM_MMSTDBASE_H

namespace mm {

class MMStdBase {
public:
    static void mmAssert(const char* expression, const char* file, unsigned int line);
};

}  // namespace mm

// the game's assertion: what it reports is the expression as written, the file and the line
#define MM_ASSERT(expression)                                                    \
    do {                                                                         \
        if (!(expression)) ::mm::MMStdBase::mmAssert(#expression, __FILE__, __LINE__); \
    } while (0)

#endif
