#include "ssd/Debug.h"
#include "ssd/Text.h"
#include "ssd/MemoryBlock.h"
#include "classes/ssd/TextRef.h"
#include "classes/ssd/String.h"
#include "classes/ssd/StreamBuffer.h"
#include "classes/ssd/AudioFileAiff.h"
#include "classes/ssd/Allocator.h"

namespace ssd {

String::String() : TextRef(TextEncodeType_Utf16), data_() {}

String::~String() {
    FreeImpl();
}

void String::FreeImpl() {
    if (data_.GetAdrs() != ssd_null) {
        data_.Free();
    }
}

void String::Set(const TextRef& text) {
    if (text.type_ == TextEncodeType_Utf8) {
        Set(text.utf8_);
    } else {
        Set(text.tchar_);
    }
}

void String::Set(const char* text) {
    Utf8ToUTF16(text, &data_);
#line 65 "D:/ssd/ssd51/ssd/sources/util/string.cpp"
    SSD_ASSERT_MSG(data_.GetAdrs() != ssd_null, u"メモリが確保できませんでした。: textBuf == nullptr");
    tchar_ = data_.GetAdrs<ssd_tchar>();
    hash_.Clear();
    hash_.CalcTextHash(tchar_);
}

void String::Set(const char16_t* text) {
    unsigned long count = GetTextLength(text) + 1;
    unsigned long size = (count + 1) * sizeof(ssd_tchar);
    if (data_.GetAdrs() != ssd_null && data_.size < size) {
        data_.Free();
    }
    if (data_.GetAdrs() == ssd_null) {
        ssd_tchar* textBuf = SoundMemory::allocator_->NewBuffer<ssd_tchar>(count);
#line 85
        SSD_ASSERT_MSG(textBuf != ssd_null, u"メモリが確保できませんでした。: textBuf == nullptr");
        data_.address = textBuf;
        data_.size = size;
        tchar_ = textBuf;
    } else {
#line 92
        SSD_ASSERT_MSG(tchar_ == data_.GetAdrs<ssd_tchar>(), u"Stringのメンバ情報に異常があります。: tchar_ != data_.GetAdrs<ssd_tchar>()");
        tchar_ = data_.GetAdrs<ssd_tchar>();
    }
    ssd_tchar* out = data_.GetAdrs<ssd_tchar>();
    while ((*out = *text) != 0) {
        out++;
        text++;
    }
    hash_.Clear();
    hash_.CalcTextHash(tchar_);
}

int StreamBuffer::Alloc(unsigned long size, Allocator* allocator) {
    allocator_ = allocator;
#line 29 "D:/ssd/ssd51/ssd/sources/stream_buffer.cpp"
    SSD_ASSERT(buffer_ == NULL);
    Allocator::Block* block = allocator->NewStreamImpl(size, 0x10);
    buffer_ = block != nullptr ? static_cast<unsigned char*>(block->data) : nullptr;
    if (buffer_ == nullptr) {
        return -8;
    }
    allocator_ = allocator;
    writePosition_ = 0;
    readPosition_ = 0;
    bufferSize_ = size;
    dataSize_ = 0;
    return 0;
}

void StreamBuffer::Clear() {
    readPosition_ = 0;
    dataSize_ = 0;
    writePosition_ = 0;
}

int StreamBuffer::Free() {
    if (buffer_ != nullptr) {
        allocator_->DeleteStreamImpl(allocator_->GetMemoryBlock(buffer_));
        allocator_ = nullptr;
        buffer_ = nullptr;
    }
    return 0;
}

Result StreamBuffer::InData8(const void* data, unsigned long size, bool loop) {
    unsigned int count = size;
    if (count > GetFreeSize()) {
        return Result(-9);
    }
    unsigned int position = writePosition_;
    if (loop) {
        loopPosition_ = position;
    }
    unsigned char* destination = buffer_ + position;
    dataSize_ += count;
    if (count <= bufferSize_ - position) {
        CopyMemory8(data, destination, count);
        writePosition_ += count;
        if (writePosition_ < bufferSize_) {
            return Result(0);
        }
        writePosition_ = 0;
    } else {
        unsigned int rest = bufferSize_ - position;
        CopyMemory8(data, destination, rest);
        CopyMemory8(static_cast<const unsigned char*>(data) + rest, buffer_, count - rest);
        writePosition_ = count - rest;
    }
    return Result(0);
}

Result StreamBuffer::InData16(const void* data, unsigned long size, bool loop) {
    unsigned int count = size;
    if (count > GetFreeSize()) {
        return Result(-9);
    }
    unsigned int position = writePosition_;
    if (loop) {
        loopPosition_ = position;
    }
    unsigned char* destination = buffer_ + position;
    dataSize_ += count;
    if (count <= bufferSize_ - position) {
        CopyMemory16(data, destination, count);
        writePosition_ += count;
        if (writePosition_ < bufferSize_) {
            return Result(0);
        }
        writePosition_ = 0;
    } else {
        unsigned int rest = bufferSize_ - position;
        CopyMemory16(data, destination, rest);
        CopyMemory16(static_cast<const unsigned char*>(data) + rest, buffer_, count - rest);
        writePosition_ = count - rest;
    }
    return Result(0);
}

Result StreamBuffer::InData32(const void* data, unsigned long size, bool loop) {
    unsigned int count = size;
    if (count > GetFreeSize()) {
        return Result(-9);
    }
    unsigned int position = writePosition_;
    if (loop) {
        loopPosition_ = position;
    }
    unsigned char* destination = buffer_ + position;
    dataSize_ += count;
    if (count <= bufferSize_ - position) {
        CopyMemory32(data, destination, count);
        writePosition_ += count;
        if (writePosition_ < bufferSize_) {
            return Result(0);
        }
        writePosition_ = 0;
    } else {
        unsigned int rest = bufferSize_ - position;
        CopyMemory32(data, destination, rest);
        CopyMemory32(static_cast<const unsigned char*>(data) + rest, buffer_, count - rest);
        writePosition_ = count - rest;
    }
    return Result(0);
}

Result StreamBuffer::InData64(const void* data, unsigned long size, bool loop) {
    unsigned int count = size;
    if (count > GetFreeSize()) {
        return Result(-9);
    }
    unsigned int position = writePosition_;
    if (loop) {
        loopPosition_ = position;
    }
    unsigned char* destination = buffer_ + position;
    dataSize_ += count;
    if (count <= bufferSize_ - position) {
        CopyMemory64(data, destination, count);
        writePosition_ += count;
        if (writePosition_ < bufferSize_) {
            return Result(0);
        }
        writePosition_ = 0;
    } else {
        unsigned int rest = bufferSize_ - position;
        CopyMemory64(data, destination, rest);
        CopyMemory64(static_cast<const unsigned char*>(data) + rest, buffer_, count - rest);
        writePosition_ = count - rest;
    }
    return Result(0);
}

Result StreamBuffer::OutData8(void* data, unsigned long size, unsigned long* outSize, bool* end) {
    unsigned int count = size;
    if (count > dataSize_) {
        count = dataSize_;
    }
    if (outSize != nullptr) {
        *outSize = count;
    }
    dataSize_ -= count;
    const unsigned char* source = buffer_ + readPosition_;
    unsigned int rest = bufferSize_ - readPosition_;
    if (count <= rest) {
        CopyMemory8(source, data, count);
        readPosition_ += count;
        if (readPosition_ < bufferSize_) {
            return Result(0);
        }
        readPosition_ = 0;
    } else {
        CopyMemory8(source, data, rest);
        CopyMemory8(buffer_, static_cast<unsigned char*>(data) + rest, count - rest);
        readPosition_ = count - rest;
    }
    return Result(0);
}

Result StreamBuffer::OutData16(void* data, unsigned long size, unsigned long* outSize, bool* end) {
    if (dataSize_ == 0) {
        *outSize = 0;
        return Result(0);
    }
    unsigned int count = size;
    if (count > dataSize_) {
        count = dataSize_;
    }
    if (outSize != nullptr) {
        *outSize = count;
    }
    dataSize_ -= count;
    const unsigned char* source = buffer_ + readPosition_;
    unsigned int rest = bufferSize_ - readPosition_;
    if (count <= rest) {
        CopyMemory16(source, data, count);
        readPosition_ += count;
        if (readPosition_ < bufferSize_) {
            return Result(0);
        }
        readPosition_ = 0;
    } else {
        CopyMemory16(source, data, rest);
        CopyMemory16(buffer_, static_cast<unsigned char*>(data) + rest, count - rest);
        readPosition_ = count - rest;
    }
    return Result(0);
}

Result StreamBuffer::OutData64(void* data, unsigned long size, unsigned long* outSize, bool* end) {
    if (dataSize_ == 0) {
        *outSize = 0;
        return Result(0);
    }
    unsigned int count = size;
    if (count > dataSize_) {
        count = dataSize_;
    }
    *end = false;
    if (loopLimit_) {
        if (loopPosition_ != 0) {
            if (count > loopPosition_) {
                count = loopPosition_;
            }
            loopPosition_ -= count;
        } else {
            *end = true;
        }
    }
    if (outSize != nullptr) {
        *outSize = count;
    }
    dataSize_ -= count;
    const unsigned char* source = buffer_ + readPosition_;
    unsigned int rest = bufferSize_ - readPosition_;
    if (count <= rest) {
        CopyMemory64(source, data, count);
        readPosition_ += count;
        if (readPosition_ < bufferSize_) {
            return Result(0);
        }
        readPosition_ = 0;
    } else {
        CopyMemory64(source, data, rest);
        CopyMemory64(buffer_, static_cast<unsigned char*>(data) + rest, count - rest);
        readPosition_ = count - rest;
    }
    return Result(0);
}

Result AudioFileAiff::Open(IoStreamBase* stream) {
    stream_ = stream;
    return Result(0);
}

Result AudioFileAiff::Close() {
    stream_ = nullptr;
    return Result(0);
}

void AudioFileAiff::SetPositionBySample(unsigned long) {}

}  // namespace ssd
