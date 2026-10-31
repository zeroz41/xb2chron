#include "classes/ssd/AudioMarker.h"
#include "classes/ssd/AudioMarkerList.h"
#include "classes/ssd/AudioFileBase.h"
#include "classes/ssd/Allocator.h"
#include "classes/ssd/IoStreamBase.h"
#include "classes/ssd/AudioMarker.h"
#include "classes/ssd/AudioMarkerList.h"
#include "classes/ssd/AudioFileBase.h"
#include "classes/ssd/AudioFileSadf.h"
#include "classes/ssd/AudioFileWave.h"

namespace ssd {

AudioFileBase::~AudioFileBase() {
    DeleteReadBuffer();
}

void AudioFileBase::DeleteReadBuffer() {
    if (readBuffer_ != nullptr && ownsReadBuffer_) {
        SoundMemory::allocator_->DeleteBuffer(readBuffer_);
        readBuffer_ = nullptr;
        ownsReadBuffer_ = false;
    }
}

Result AudioFileBase::Open(IoStreamBase*) {
    stream_ = nullptr;
    return Result(-1);
}

Result AudioFileBase::Close() {
    DeleteReadBuffer();
    return Result(-1);
}

void AudioFileBase::NewReadBuffer(unsigned long size) {
    if (readBuffer_ == nullptr) {
        ownsReadBuffer_ = true;
        readBuffer_ = SoundMemory::allocator_->NewBuffer<unsigned char>(size);
    }
}

Result AudioFileBase::PreLoad() {
    return Result(-1);
}

Result AudioFileBase::PreSave() {
    return Result(-1);
}

Result AudioFileBase::SaveAudioData(const short*, int) {
    return Result(-1);
}

void AudioFileBase::SetPositionBySample(unsigned long) {}

int AudioFileBase::WriteBySamples(const short* data, int count) {
    unsigned long size = format_.sample.blockAlign * static_cast<long>(count);
    stream_->Write(size, data, nullptr);
    return 0;
}

}  // namespace ssd

// AudioFileSadf (0x71008A3CBC..0x71008A3EF0): its own translation unit in the original (session 19 audiofile/SPLITS.md);
// it shares this file until the split is fixed.
namespace ssd {

Result AudioFileSadf::Open(IoStreamBase* stream) {
    stream_ = stream;
    return Result(0);
}

Result AudioFileSadf::Close() {
    stream_ = nullptr;
    return Result(0);
}

void AudioFileSadf::SetPositionBySample(unsigned long) {}

Result AudioFileWave::Open(IoStreamBase* stream) {
    stream_ = stream;
    return Result(0);
}

void AudioFileWave::SetPositionBySample(unsigned long sample) {
    unsigned long position = format_.data.dataOffset + sample;
    stream_->Seek(IoStreamBase::SeekMode_Begin, position, nullptr);
}

}  // namespace ssd
