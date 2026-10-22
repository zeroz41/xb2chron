#ifndef NN_DIAG_H
#define NN_DIAG_H

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

namespace detail {
void LogImpl(const LogMetaData& metaData, const char* format, ...);
}  // namespace detail

}}  // namespace nn::diag

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

#endif
