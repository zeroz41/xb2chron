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

void AudioFileAiff::SetPositionBySample(unsigned long) {}

}  // namespace ssd
