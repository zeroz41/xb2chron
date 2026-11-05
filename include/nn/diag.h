#ifndef NN_DIAG_H
#define NN_DIAG_H

#include "nn/result.h"

// NintendoSDK 3.5.0's nn::diag logging, as far as the module uses it.
namespace nn { namespace diag {

enum LogSeverity {
    LogSeverity_Trace,
    LogSeverity_Info,
    LogSeverity_Warn,
    LogSeverity_Error,
    LogSeverity_Fatal,
};

struct SourceInfo {
    int lineNumber;
    const char* fileName;
    const char* functionName;
};

struct LogMetaData {
    SourceInfo sourceInfo;
    const char* moduleName;
    LogSeverity severity;
    int verbosity;
    bool useDefaultLocaleCharset;
    void* pAdditionalData;
    unsigned long additionalDataBytes;
};

// fills `pOutArray` with up to `arrayCountMax` return addresses of the calling thread, innermost first;
// the count written
int GetBacktrace(unsigned long* pOutArray, int arrayCountMax);
// the name of the symbol holding `address`, written to `pOutName`; the symbol's start, 0 when none is found
unsigned long GetSymbolName(char* pOutName, unsigned long nameSize, unsigned long address);

enum AssertionType {
    AssertionType_SdkAssert,
    AssertionType_SdkRequires,
    AssertionType_UserAssert,
};

namespace detail {
void OnAssertionFailure(AssertionType type, const char* condition, const char* functionName, const char* fileName,
                        int lineNumber);
void LogImpl(const LogMetaData& metaData, const char* format, ...);
// what NN_ABORT_UNLESS calls (the release build passes empty texts and line 0)
[[noreturn]] void AbortImpl(const char* condition, const char* functionName, const char* fileName, int lineNumber);
// the same for a failed result (ml::DevFileNxTh::initializeSave's save mount)
[[noreturn]] void AbortImpl(const char* condition, const char* functionName, const char* fileName, int lineNumber,
                            const ::nn::Result* result, const char* format, ...);
// whether pointer (as an integer) is not null: NN_ABORT_UNLESS_NOT_NULL's test
bool NotNullImpl(unsigned long pointer);
}  // namespace detail

}}  // namespace nn::diag

namespace nn { namespace detail {
// what NN_UNEXPECTED_DEFAULT calls (the release build passes empty texts and line 0)
[[noreturn]] void UnexpectedDefaultImpl(const char* functionName, const char* fileName, int lineNumber);
}}  // namespace nn::detail

// the SDK's log macro: the call site's line, file and function travel with the text
#define NN_LOG(...)                                                       \
    do {                                                                  \
        ::nn::diag::LogMetaData logMetaData;                              \
        logMetaData.sourceInfo.lineNumber = __LINE__;                     \
        logMetaData.sourceInfo.fileName = __FILE__;                       \
        logMetaData.sourceInfo.functionName = __FUNCTION__;               \
        logMetaData.moduleName = "";                                      \
        logMetaData.severity = ::nn::diag::LogSeverity_Info;              \
        logMetaData.verbosity = 0;                                        \
        logMetaData.useDefaultLocaleCharset = false;                      \
        logMetaData.pAdditionalData = nullptr;                            \
        logMetaData.additionalDataBytes = 0;                              \
        ::nn::diag::detail::LogImpl(logMetaData, __VA_ARGS__);            \
    } while (0)

// the release build's abort checks: empty texts, line 0
#define NN_ABORT_UNLESS(condition)                         \
    if (!(condition)) {                                    \
        ::nn::diag::detail::AbortImpl("", "", "", 0);      \
    }
#define NN_ABORT_UNLESS_NOT_NULL(pointer)                                                              \
    if (!::nn::diag::detail::NotNullImpl(reinterpret_cast<unsigned long>(pointer))) {                \
        ::nn::diag::detail::AbortImpl("", "", "", 0);                                                \
    }
#define NN_ABORT_UNLESS_RESULT_SUCCESS(result) NN_ABORT_UNLESS((result).IsSuccess())
// the user assertion the release build keeps: empty texts, line 0
#define NN_ASSERT(condition)                                                                           \
    if (!(condition)) {                                                                                \
        ::nn::diag::detail::OnAssertionFailure(::nn::diag::AssertionType_UserAssert, "", "", "", 0);   \
    }

#endif
