#include "classes/ssd/SystemCorePlatform.h"
#include "classes/ssd/String.h"
#include "classes/ssd/FileStream.h"
#include "classes/ssd/MemoryBuffer.h"
#include "classes/ssd/StreamBuffer.h"
#include "nn/codec.h"
#include "classes/ssd/StreamController.h"
#include "classes/ssd/StreamController.h"
#include "classes/ssd/Allocator.h"
#include "classes/ssd/SoundCore.h"
#include "classes/ssd/SystemCore.h"
#include "classes/ssd/SystemCorePlatform.h"

namespace ssd {

// the constructor (not matched yet) takes the next number
unsigned int StreamController::idCounter_;

StreamController::~StreamController() {}

void StreamController::Execution() {
    switch (state_) {
    case 3:
        ExecCloseStream();
        break;
    case 6:
        if (seekRequested_) {
            buffer_.Clear();
            if (decodeState_ == 4) {
                decodeState_ = 1;
            }
            bufferReady_ = false;
            readEnd_ = false;
            pad_f4 = false;
            unsigned long size = source_.format_.data.dataSize;
            unsigned long position;
            switch (source_.format_.sample.format) {
            case 4: {
                int sample = 0;
                if (source_.format_.sample.blockAlign != 0) {
                    sample = seekPosition_ / source_.format_.sample.blockAlign;
                }
                int frame = sample / static_cast<int>(source_.extra_.pad_0[2]);
                if (frame >= static_cast<int>(source_.extra_.pad_0[5])) {
                    frame = source_.extra_.pad_0[5];
                }
                frameIndex_ = frame;
                position = opusFrameOffsets_[frame];
                break;
            }
            case 3:
                position = (seekPosition_ & ~0xFUL) * source_.format_.sample.channelCount;
                if (position >= size) {
                    position = size;
                }
                break;
            default:
                position = seekPosition_;
                if (position >= size) {
                    position = size;
                }
                break;
            }
            if (seekPosition_ == size) {
                bufferReady_ = true;
                readEnd_ = true;
                pad_f4 = true;
            }
            readPosition_ = position;
            seekPosition_ = 0;
            seekRequested_ = false;
            seekPending_ = false;
        }
        if (inData_) {
            ExecReadStream(inData_);
        }
        break;
    case 4:
        ExecOpenStream();
        break;
    }
    if (decode_) {
        (this->*decode_)();
    }
    if (closeRequested_) {
        state_ = 3;
        closeRequested_ = false;
    }
}

void StreamController::ExecCloseStream() {
    decode_ = nullptr;
    inData_ = nullptr;
    file_.Close();
    Allocator* allocator = SoundMemory::allocator_;
    if (opusWorkBuffer_ != nullptr) {
        allocator->DeleteBuffer(opusWorkBuffer_);
        opusWorkBuffer_ = nullptr;
    }
    if (opusFrameOffsets_ != nullptr) {
        allocator->DeleteBuffer(opusFrameOffsets_);
        opusFrameOffsets_ = nullptr;
    }
    decodeState_ = 0;
    if (extraBuffer_ != nullptr) {
        allocator->DeleteBuffer(extraBuffer_);
        extraBuffer_ = nullptr;
    }
    state_ = 1;
    active_ = false;
}

Result StreamController::InitStream(WaveSource* source, unsigned long bufferSize, unsigned long startPosition) {
    if (!SoundCore::instance_->pad_11) {
        if (!initialized_) {
            file_.Clear();
            buffer_.Alloc(bufferSize, SoundMemory::allocator_);
            readBuffer_.Alloc(0x20000, 0x10, nullptr);
            source_.fromFile_ = true;
            source_.path_ = static_cast<const TextRef&>(source->path_);
            state_ = 4;
            active_ = true;
            static_cast<SystemCore*>(SoundCore::instance_)->AddStreamController(this);
        }
        extraBuffer_ = nullptr;
        startPosition_ = startPosition;
        opusWorkBuffer_ = nullptr;
        opusFrameOffsets_ = nullptr;
        decodeState_ = 1;
        initialized_ = true;
        decodeTime_ = 0.0;
        decodedFrames_ = 0;
        frameIndex_ = 0;
    } else {
        state_ = 1;
    }
    return Result(0);
}

Result StreamController::QuitStream() {
    initialized_ = false;
    state_ = 0;
    static_cast<SystemCore*>(SoundCore::instance_)->RemoveStreamController(this);
    readBuffer_.Free();
    buffer_.Free();
    file_.Close();
    source_.Quit();
    return Result(0);
}

Result StreamController::ResetStream() {
    state_ = 4;
    return Result(0);
}

Result StreamController::CloseStream() {
    if (streaming_) {
        return Result(0);
    }
    bufferReady_ = false;
    closeRequested_ = true;
    state_ = 3;
    return Result(1);
}

void StreamController::ExecAdpcmDecode() {}

unsigned long StreamBuffer::GetDataSize() const {
    return dataSize_;
}

unsigned long StreamBuffer::GetFreeSize() const {
    return bufferSize_ - dataSize_;
}

void StreamController::SetReadPosition(unsigned long position) {
    if (fileOpen_) {
        seekPending_ = true;
        bufferReady_ = false;
        seekPosition_ = position;
        seekRequested_ = true;
    }
}

unsigned long StreamBuffer::GetBufferSize() const {
    return bufferSize_;
}

}  // namespace ssd
