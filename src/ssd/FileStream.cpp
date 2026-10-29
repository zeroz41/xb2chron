#include "nn/os.h"
#include "nn/fs.h"
#include "ssd/Debug.h"
#include "classes/ssd/Allocator.h"
#include "ssd/MemoryBlock.h"
#include "ssd/Hash.h"
#include "ssd/Text.h"
#include "classes/ssd/Object.h"
#include "classes/ssd/TextRef.h"
#include "classes/ssd/IoStreamBase.h"
#include "classes/ssd/FileStream.h"
#include "classes/ssd/MemoryStream.h"
#include "ssd/AudioContents.h"
#include <string.h>

namespace ssd {

Debug::LogState Debug::log_;

void Debug::Init() {
    log_.timeStampType = LogTimeStamp::Type(3);
    log_.errorFlag = 0x10000015;
    log_.warningFlag = 0x10000015;
    log_.debugFlag = 0x10000015;
    log_.messageMethod = LogMethodT;
}

Result Debug::LogMethodT(LogMessage::Type, const char16_t*) {
    return Result(0);
}

void Debug::SetMessageMethod(LogMethod method) {
    log_.messageMethod = method != nullptr ? method : LogMethodT;
}

void Debug::SetTimeStampType(LogTimeStamp::Type type) {
    log_.timeStampType = type;
}

void FileStream::Initialize() {}

void FileStream::Finalize() {}

FileStream::FileStream() : IoStreamBase(ObjectType::Id(0xC)), position_(0), size_(0) {
    handle_.handle = nullptr;
}

Result FileStream::Open(const TextRef& path, OpenMode) {
    position_ = 0;
    MemoryBlock name = {};
    path.GetText(&name, TextEncodeType_Utf8);
    nn::Result result = nn::fs::OpenFile(&handle_, static_cast<const char*>(name.address), nn::fs::OpenMode_Read);
    name.Free();
    if (result.IsFailure()) {
        log_error(Result(-0x41), Debug::LogFlag::Type(0x30), u"ファイルが開けませんでした。: file=\"%s\"", path.tchar_);
        return Result(-0x41);
    }
    long size;
    nn::fs::GetFileSize(&size, handle_);
    size_ = size;
    return Result(0);
}

Result FileStream::GetSize(unsigned long* fileSize) const {
    if (!IsOpen()) {
        return Result(-1);
    }
#line 424 "D:/ssd/ssd51/ssd/sources/io/file_stream.cpp"
    SSD_ASSERT_NOT_NULL(fileSize);
    *fileSize = size_;
    return Result(0);
}

Result FileStream::Read(unsigned long size, void* buffer, unsigned long* readSize) {
    unsigned long read;
    nn::fs::ReadFile(&read, handle_, position_, buffer, size);
    position_ += read;
    if (readSize != nullptr) {
        *readSize = read;
    }
    return Result(0);
}

Result FileStream::Close() {
    if (IsOpen()) {
        nn::fs::CloseFile(handle_);
        handle_.handle = nullptr;
    }
    return Result(0);
}

Result FileStream::Write(unsigned long, const void*, unsigned long*) {
    if (!IsOpen()) {
        return Result(-1);
    }
    return Result(-1);
}

void FileStream::Clear() {
    position_ = 0;
    size_ = 0;
}

bool FileStream::IsOpen() const {
    return handle_.handle != nullptr;
}

Result FileStream::Tell(unsigned long* position) {
    if (!IsOpen()) {
        return Result(-1);
    }
    *position = size_;
    return Result(0);
}

Result FileStream::GetPosition(unsigned long* position) const {
    *position = position_;
    return Result(0);
}

unsigned long FileStream::CheckAccessSize(unsigned long size) {
    if (!IsOpen()) {
        return 0;
    }
    if (size_ != 0 && position_ + size >= size_) {
        return size_ - position_;
    }
    return size;
}

}  // namespace ssd
