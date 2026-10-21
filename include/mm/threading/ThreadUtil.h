#ifndef MM_THREADING_THREADUTIL_H
#define MM_THREADING_THREADUTIL_H

#include "nn/os.h"

namespace mm { namespace threading {

// a thread as the platform knows it: on NX the SDK's thread (ThreadUtil passes it to nn::os as one)
struct MMTHREAD : nn::os::ThreadType {};

// the core a thread runs on: 0 lets the system choose, n is core n - 1
enum CPUID : int;

namespace ThreadUtil {
void resumeThread(MMTHREAD* thread);
}  // namespace ThreadUtil

}}  // namespace mm::threading

#endif
