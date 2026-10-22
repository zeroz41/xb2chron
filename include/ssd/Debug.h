#ifndef SSD_DEBUG_H
#define SSD_DEBUG_H

// the sound library's results and logging: the result code the library's calls return (negative on failure,
// set_result keeps the last one in SoundCore::instance_), the log message and time-stamp kinds, and the logging
// state Debug::Init sets up
namespace ssd {

// a call's result, 64 bits wide (SoundCore::Init tests its sign bit); 0 is success
enum Result : long {};

namespace LogMessage {
// what a message is: log_message passes 0, log_error 2
enum Type {};
}  // namespace LogMessage

namespace LogTimeStamp {
// how a message is time-stamped (get_log_time_stamp); Debug::Init sets 3, SoundCore::InitParam defaults to 1
enum Type {};
}  // namespace LogTimeStamp

typedef Result (*LogMethod)(LogMessage::Type type, const char16_t* text);

namespace Debug {

namespace LogFlag {
// the bits a message is logged under; log_error logs only while one is set in the error flags
enum Type : unsigned int {};
}  // namespace LogFlag

// the logging state (the type's name is not the original's): 1.0.0's SoundCore::GetErrorLogFlag and
// GetWarningLogFlag read the words at 0x4 and 0x8, Debug::OnErrorFlag and OnWarningFlag set bits in them;
// the word at 0xC is the third flag set Debug::Init gives the same bits (the name is not the original's)
struct LogState {
    LogTimeStamp::Type timeStampType;
    unsigned int errorFlag;
    unsigned int warningFlag;
    unsigned int debugFlag;
    LogMethod messageMethod;
};

extern LogState log_;

void Init();
Result LogMethodT(LogMessage::Type type, const char16_t* text);
void SetMessageMethod(LogMethod method);
void SetTimeStampType(LogTimeStamp::Type type);

}  // namespace Debug

void set_result(Result result);
// the logged form of a source path (the assertions pass their file's)
const char16_t* get_logfilename(const char16_t* path);
void abort();
void log_message(const char16_t* format, ...);
void log_error(Result result, Debug::LogFlag::Type flag, const char16_t* format, ...);

}  // namespace ssd

// logs and aborts when pointer is null, citing the argument, the file and the line (the macro's name is not
// the original's; its message is "Assert : "%s" = nullptr, %s:%d")
#define SSD_ASSERT_NOT_NULL(pointer)                                                                         \
    if ((pointer) == nullptr) {                                                                               \
        ::ssd::log_message(u"Assert : \"%s\" = nullptr, %s:%d", u"" #pointer, ::ssd::get_logfilename(u"" __FILE__), \
                           __LINE__);                                                                         \
        ::ssd::abort();                                                                                       \
    }

// logs and aborts when condition fails, citing the condition, the file, the line and a message (the macro's
// name is not the original's; its format is "Assert : "%s", %s:%d, %s": MemoryManager::Quit's
// "memoryManager_.numInstance_ == 0")
#define SSD_ASSERT_MSG(condition, message)                                                                    \
    if (!(condition)) {                                                                                       \
        ::ssd::log_message(u"Assert : \"%s\", %s:%d, %s", u"" #condition, ::ssd::get_logfilename(u"" __FILE__), \
                           __LINE__, message);                                                                \
        ::ssd::abort();                                                                                       \
    }

#endif
