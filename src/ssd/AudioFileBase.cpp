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
#include "classes/ssd/AudioFileAiff.h"
#include "ssd/MemoryBlock.h"

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

AudioFileBase* AudioFileBase::CreateFileBase(MediaFileType type, unsigned char* buffer) {
    AudioFileBase* file = nullptr;
    bool heap;
    if (buffer != nullptr) {
        switch (type) {
        case 1:
            file = new (buffer) AudioFileAiff;
            break;
        case 2:
            file = new (buffer) AudioFileWave;
            break;
        case 3:
            file = new (buffer) AudioFileSadf;
            break;
        }
        heap = false;
    } else {
        switch (type) {
        case 1:
            file = new AudioFileAiff;
            break;
        case 2:
            file = new AudioFileWave;
            break;
        case 3:
            file = new AudioFileSadf;
            break;
        }
        heap = true;
    }
    if (file != nullptr) {
        file->heap_ = heap;
    }
    return file;
}

Result AudioFileBase::CloseFileBase(AudioFileBase** file) {
    if (file != nullptr && *file != nullptr) {
        AudioFileBase* reader = *file;
        reader->Close();
        if (reader->ownsStream_ && reader->stream_ != nullptr) {
            reader->stream_->Close();
            reader->stream_ = nullptr;
        }
        if (!reader->heap_) {
            reader->~AudioFileBase();
        } else {
            delete reader;
        }
        *file = nullptr;
    }
    return Result(0);
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

// AudioFileSadf (0x71008A3CBC..0x71008A3EF0): its own translation unit in the original;
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


Result AudioFileWave::PreSave() {
    // the RIFF chunk's header: "RIFF", the size (Close writes it), "WAVE"
    unsigned int header[4];
    header[0] = 0x46464952;
    header[1] = 0;
    header[2] = 0x45564157;
    stream_->Write(0xC, header, nullptr);

    // the "fmt " chunk (the local type and field names are not the original's)
    struct {
        unsigned int id;
        unsigned int size;
        unsigned short format;
        unsigned short channelCount;
        unsigned int sampleRate;
        unsigned int bytesPerSecond;
        unsigned short blockAlign;
        unsigned short bitsPerSample;
    } fmt;
    fmt.id = 0x20746D66;
    fmt.size = 0x10;
    fmt.format = 1;
    fmt.channelCount = format_.sample.channelCount;
    fmt.sampleRate = format_.data.sampleRate;
    fmt.bytesPerSecond = format_.sample.blockAlign * fmt.sampleRate;
    fmt.blockAlign = format_.sample.blockAlign;
    fmt.bitsPerSample = format_.sample.bitsPerSample;
    stream_->Write(sizeof(fmt), &fmt, nullptr);

    if (format_.loop.loop) {
        // the "smpl" chunk with one loop (the local type and field names are not the original's)
        struct {
            unsigned int id;
            unsigned int size;
            unsigned int pad_8[7];
            unsigned int loopCount;
            unsigned int pad_28[3];
            unsigned int loopStart;
            unsigned int loopEnd;
            unsigned int pad_3c[0x79];
        } smpl;
        ClearMemory8(&smpl, 0x44);
        smpl.id = 0x6C706D73;
        smpl.size = 0x3C;
        smpl.loopCount = 1;
        smpl.loopStart = format_.loop.loopStart;
        smpl.loopEnd = format_.loop.loopEnd;
        stream_->Write(0x44, &smpl, nullptr);
    }
    return Result(0);
}

}  // namespace ssd
