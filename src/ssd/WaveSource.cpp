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

Result WaveSource::InitWithFile(const TextRef& path) {
    fromFile_ = true;
    path_ = path;
    contents_ = nullptr;
    contentsSize_ = 0;
    return Result(0);
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

void CommandManager::fn_71008A22D0() {
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

Result set_result(Result result) {
    SoundCore::instance_->result_ = result;
    return result;
}

void abort() {
    nn::diag::detail::AbortImpl("", "", "", 0);
}

}  // namespace ssd
