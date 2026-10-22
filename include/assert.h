#ifndef ASSERT_H
#define ASSERT_H

// The C library's assertion, as the SDK's <assert.h> defines it: the expression's text, the file, the line and the
// function's name go to __assert_fail, which does not return
#ifdef __cplusplus
extern "C" {
#endif
__attribute__((noreturn)) void __assert_fail(const char* expression, const char* file, int line,
                                             const char* function);
#ifdef __cplusplus
}
#endif

#define assert(expression) ((expression) ? (void)0 : __assert_fail(#expression, __FILE__, __LINE__, __func__))

#endif
