#include "nn/diag.h"
#include "stdlib.h"
#include "cxxabi.h"
#include "ml/ml_misc.h"

// the parameter's and locals' names are not the original's
void mlStackTrace(unsigned long* pTrace) {
    if (pTrace != nullptr) {
        // walked with a pointer of its own: the original reads each entry twice, which an index on the parameter
        // would not
        unsigned long* p = pTrace;
        for (unsigned long i = 0; i < 30; i++, p++) {
            if (*p == 0) {
                return;
            }
            // the original passes "SYS" as the format, the intended one after it
#line 777
            NN_LOG("SYS", "%2d %s\n", i + 1, *p);
        }
    } else {
        unsigned long trace[31];
        int count = nn::diag::GetBacktrace(trace, 30);
        // the first address is this function's caller
        for (unsigned long i = 1; i < count; i++) {
            if (trace[i] == 0) {
                return;
            }
            char name[0x200];
            unsigned long symbol = nn::diag::GetSymbolName(name, sizeof(name), trace[i]);
            char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, nullptr);
            if (demangled != nullptr) {
#line 796
                NN_LOG("%2d %p %s\n", i, trace[i], symbol != 0 ? demangled : "unknown symbol");
                free(demangled);
            } else {
#line 802
                NN_LOG("%2d %p %s\n", i, trace[i], symbol != 0 ? name : "unknown symbol");
            }
        }
    }
}
