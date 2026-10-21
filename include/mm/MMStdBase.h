#ifndef MM_MMSTDBASE_H
#define MM_MMSTDBASE_H

namespace mm {

// where mm_lib's text output and failed assertions go: s_pCurrentStd's overrides
class MMStdBase {
public:
    virtual ~MMStdBase() {}  // slot 0
    virtual void customOutput(const char* text) = 0;  // slot 2
    virtual void customAssert(const char* expression, const char* file, unsigned int line) = 0;  // slot 3
    virtual void customAssertMsg(const char* expression, const char* file, unsigned int line,
                                 const char* message) = 0;  // slot 4
    static void mmPrint(const char* format, ...);
    static void mmAssert(const char* expression, const char* file, unsigned int line);

    static MMStdBase* s_pCurrentStd;
};

}  // namespace mm

// the game's assertion: what it reports is the expression as written, the file and the line
#define MM_ASSERT(expression)                                                    \
    do {                                                                         \
        if (!(expression)) ::mm::MMStdBase::mmAssert(#expression, __FILE__, __LINE__); \
    } while (0)

#endif
