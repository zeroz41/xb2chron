#include "nn/diag.h"
#include "classes/ssd/String.h"
#include "classes/ssd/MemoryStream.h"
#include "classes/ssd/SystemCorePlatform.h"
#include "classes/ssd/AudioFileBase.h"
#include "ssd/AudioContents.h"
#include "classes/ssd/WaveSource.h"
#include "classes/ssd/CommandManager.h"
#include "classes/ssd/Allocator.h"
#include "classes/ssd/SoundCore.h"
#include "ssd/Debug.h"
#include "ssd/Text.h"
#include "nn/os.h"
#include "nn/time.h"
#include <stdarg.h>

namespace ssd {

WaveSource::WaveSource() : Object(ObjectType::Id(1)) {}

WaveSource::~WaveSource() {
    Quit();
}

Result WaveSource::Quit() {
    data_ = nullptr;
    dataSize_ = 0;
    contents_ = nullptr;
    contentsSize_ = 0;
    if (buffer_ != nullptr) {
        static_cast<SystemCorePlatform*>(SoundCore::instance_)->FreeAudioDataBuffer(buffer_);
        buffer_ = nullptr;
    }
    path_.FreeImpl();
    return Result(0);
}

Result WaveSource::Init(void* data, unsigned long size) {
    fromFile_ = false;
    referenceCount_ = 0;
    contents_ = static_cast<AudioContents*>(data);
    contentsSize_ = size;
    MemoryStream stream;
    Result result = stream.Open(data, size, IoStreamBase::OpenMode_Read);
    if (result >= 0) {
        result = PreLoad(&stream, false);
    }
    stream.Close();
    return result;
}

Result WaveSource::InitWithFile(const TextRef& path) {
    fromFile_ = true;
    path_ = path;
    contents_ = nullptr;
    contentsSize_ = 0;
    return Result(0);
}

unsigned long WaveSource::TimeToSample(float time) const {
    if (format_.sample.format == 3) {
        return format_.data.sampleRate * time * 8.0f / 14.0f;
    }
    return format_.data.sampleRate * time;
}

unsigned long WaveSource::SampleToPosition(unsigned int sample) const {
    unsigned long s = sample;
    if (format_.sample.format == 3) {
        return s * 16 / 28;
    }
    return format_.sample.blockAlign * s;
}

Result WaveSource::PreLoad(IoStreamBase* stream, bool headerOnly) {
    MediaFileType type;
    Result result = MediaContentsHeader::CheckFileType(stream, &type);
    if (result < 0) {
        return result;
    }
    unsigned char buffer[0x100];
    AudioFileBase* file = AudioFileBase::CreateFileBase(type, buffer);
    if (file == nullptr) {
        return Result(-1);
    }
    file->Open(stream);
    file->PreLoad();
    formatType_ = file->format_.sample.format;
    format_.data = file->format_.data;
    format_.sample = file->format_.sample;
    format_.loop = file->format_.loop;
    extra_ = file->extra_;
    AudioFileBase::CloseFileBase(&file);
    if (headerOnly) {
        loaded_ = true;
        return Result(0);
    }
    if (format_.data.reserved != 0) {
        return Result(-1);
    }
    bool adpcm = format_.sample.format == 3;
    AudioContents* contents = contents_;
    adpcmHeaders_ = adpcm ? reinterpret_cast<AdpcmHeader*>(contents + 1) : nullptr;
    unsigned long size = format_.data.dataSize;
    unsigned char* data = reinterpret_cast<unsigned char*>(contents) + format_.data.dataOffset;
    if ((reinterpret_cast<unsigned long>(data) & 0x3F) != 0) {
        data = static_cast<unsigned char*>(
            static_cast<SystemCorePlatform*>(SoundCore::instance_)->AllocAudioDataBuffer(size));
        if (data == nullptr) {
            return Result(-1);
        }
        buffer_ = data;
        stream->GetData(format_.data.dataOffset, size, data, nullptr);
    }
    data_ = data;
    dataSize_ = size;
    loaded_ = true;
    return Result(0);
}

const AdpcmHeader* WaveSource::GetAdpcmHeader(int channel) const {
    return adpcmHeaders_ != nullptr ? &adpcmHeaders_[channel] : nullptr;
}

const unsigned char* WaveSource::GetDataAddress(int channel) const {
    unsigned long offset = format_.sample.format == 3 ? contents_->channelDataOffset[channel] : 0;
    return data_ + offset;
}

unsigned int WaveSource::GetDataSize() const {
    return format_.sample.format == 3 ? contents_->dataSize : format_.data.dataSize;
}

void CommandManager::Init(int capacity) {
    capacity_ = capacity;
    for (int i = 0; i < 2; i++) {
        lists_[i].entries = SoundMemory::allocator_->NewInstance<CommandEntry>(capacity);
        lists_[i].count = 0;
    }
    SwitchBuffer();
}

void CommandManager::SwitchBuffer() {
    List* written = write_;
    List* executed = &lists_[written != &lists_[0]];
    write_ = &lists_[written == &lists_[0]];
    execute_ = executed;
    write_->count = 0;
}

void CommandManager::ExecuteCommands() {
    for (int i = 0; i < execute_->count; i++) {
        Command* command = execute_->entries[i].command;
        command->Execute();
        command->~Command();
    }
}

void CommandManager::Quit() {
    CommandEntry* entries = lists_[0].entries;
    SoundMemory::allocator_->DeleteInstance(entries);
    entries = lists_[1].entries;
    SoundMemory::allocator_->DeleteInstance(entries);
}

Result set_result(Result result) {
    SoundCore::instance_->result_ = result;
    return result;
}

void get_log_time_stamp(LogTimeStamp::Type type, char* buffer, unsigned long size) {
    if (SoundCore::instance_ == nullptr) {
        const char* text = "[Invalid sound]";
        while ((*buffer++ = *text++) != 0) {
        }
        return;
    }
    switch (type) {
    case 2: {
        nn::time::PosixTime posix;
        nn::time::CalendarTime calendar;
        nn::time::CalendarAdditionalInfo info;
        nn::time::StandardUserSystemClock::GetCurrentTime(&posix);
        nn::Result result = nn::time::ToCalendarTime(&calendar, &info, posix);
        if (result.IsFailure()) {
            nn::diag::detail::AbortImpl("", "", "", 0, &result, "");
        }
        sprintf(buffer, size, "[%02d.%02d.%02d.%03d] ", calendar.hour, calendar.minute, calendar.second, 0);
        break;
    }
    case 0:
        buffer[0] = 0;
        break;
    case 1:
        sprintf(buffer, size, "[%.3f] ",
                nn::os::ConvertToTimeSpan(nn::os::GetSystemTick()).GetMilliSeconds() / 1000.0);
        break;
    default: {
        nn::time::PosixTime posix;
        nn::time::CalendarTime calendar;
        nn::time::CalendarAdditionalInfo info;
        nn::time::StandardUserSystemClock::GetCurrentTime(&posix);
        nn::Result result = nn::time::ToCalendarTime(&calendar, &info, posix);
        if (result.IsFailure()) {
            nn::diag::detail::AbortImpl("", "", "", 0, &result, "");
        }
        sprintf(buffer, size, "[%02d.%02d.%02d %02d.%02d.%02d.%03d] ", calendar.year, calendar.month, calendar.day,
                calendar.hour, calendar.minute, calendar.second, 0);
        break;
    }
    }
}

void get_log_time_stamp(LogTimeStamp::Type type, char16_t* buffer, unsigned long size) {
    if (SoundCore::instance_ == nullptr) {
        const char16_t* text = u"[Invalid sound]";
        while ((*buffer++ = *text++) != 0) {
        }
        return;
    }
    switch (type) {
    case 2: {
        nn::time::PosixTime posix;
        nn::time::CalendarTime calendar;
        nn::time::CalendarAdditionalInfo info;
        nn::time::StandardUserSystemClock::GetCurrentTime(&posix);
        nn::Result result = nn::time::ToCalendarTime(&calendar, &info, posix);
        if (result.IsFailure()) {
            nn::diag::detail::AbortImpl("", "", "", 0, &result, "");
        }
        sprintf(buffer, size, u"[%02d.%02d.%02d.%03d] ", calendar.hour, calendar.minute, calendar.second, 0);
        break;
    }
    case 0:
        buffer[0] = 0;
        break;
    case 1:
        sprintf(buffer, size, u"[%.3f] ",
                nn::os::ConvertToTimeSpan(nn::os::GetSystemTick()).GetMilliSeconds() / 1000.0);
        break;
    default: {
        nn::time::PosixTime posix;
        nn::time::CalendarTime calendar;
        nn::time::CalendarAdditionalInfo info;
        nn::time::StandardUserSystemClock::GetCurrentTime(&posix);
        nn::Result result = nn::time::ToCalendarTime(&calendar, &info, posix);
        if (result.IsFailure()) {
            nn::diag::detail::AbortImpl("", "", "", 0, &result, "");
        }
        sprintf(buffer, size, u"[%02d.%02d.%02d %02d.%02d.%02d.%03d] ", calendar.year, calendar.month, calendar.day,
                calendar.hour, calendar.minute, calendar.second, 0);
        break;
    }
    }
}

void abort() {
    nn::diag::detail::AbortImpl("", "", "", 0);
}

void log_message(const char* format, ...) {
    va_list args;
    va_start(args, format);
    char line[256];
    // the original formats through a helper taking the arguments by value (their second copy)
    [&](char* buffer, unsigned long size, va_list list) {
        char stamp[32];
        get_log_time_stamp(SoundCore::instance_->GetLogTimeStampType(), stamp, sizeof(stamp));
        char message[256];
        vsprintf(message, sizeof(message), format, list);
        sprintf(buffer, size, "SSD %s: %s\n", stamp, message);
    }(line, sizeof(line), args);
    char16_t text[256];
    Utf8ToUTF16(line, text, sizeof(line));
    Debug::log_.messageMethod(LogMessage::Type(0), text);
    va_end(args);
}

void log_message(const char16_t* format, ...) {
    va_list args;
    va_start(args, format);
    char16_t line[256];
    // the original formats through a helper taking the arguments by value (their second copy)
    [&](char16_t* buffer, unsigned long size, va_list list) {
        char16_t stamp[32];
        get_log_time_stamp(SoundCore::instance_->GetLogTimeStampType(), stamp, sizeof(stamp));
        char16_t message[256];
        vsprintf(message, sizeof(message), format, list);
        sprintf(buffer, size, u"SSD %s: %s\n", stamp, message);
    }(line, sizeof(line), args);
    Debug::log_.messageMethod(LogMessage::Type(0), line);
    va_end(args);
}

void log_error(Result result, Debug::LogFlag::Type flag, const char16_t* format, ...) {
    va_list args;
    va_start(args, format);
    SoundCore* core = SoundCore::instance_;
    if (core != nullptr) {
        core->result_ = result;
    }
    if (Debug::log_.errorFlag & flag) {
        char16_t line[256];
        // the original formats through a helper taking the arguments by value (their second copy)
        [&](char16_t* buffer, unsigned long size, va_list list) {
            char16_t stamp[32];
            get_log_time_stamp(core->GetLogTimeStampType(), stamp, sizeof(stamp));
            char16_t message[256];
            vsprintf(message, sizeof(message), format, list);
            sprintf(buffer, size, u"SSD %s: %s\n", stamp, message);
        }(line, sizeof(line), args);
        Debug::log_.messageMethod(LogMessage::Type(2), line);
    }
    va_end(args);
}

const char16_t* get_logfilename(const char16_t* path) {
    const char16_t* name = path;
    for (const char16_t* p = path; *p != 0; p++) {
        if (*p == u'/') {
            name = p + 1;
        }
    }
    return name;
}

}  // namespace ssd
