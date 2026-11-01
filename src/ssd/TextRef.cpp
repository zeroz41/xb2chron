#include "ssd/Debug.h"
#include "ssd/Math.h"
#include "classes/ssd/Allocator.h"
#include "ssd/MemoryBlock.h"
#include "ssd/Hash.h"
#include "ssd/Text.h"
#include "classes/ssd/TextRef.h"
#include "classes/ssd/TextFixedBase.h"

namespace ssd {

Vec3* Vec3Transform(const Mat34* m, const Vec3* v, Vec3* out) {
    float x = v->x * m->m[0][0] + v->y * m->m[1][0] + v->z * m->m[2][0] + m->m[3][0];
    float y = v->x * m->m[0][1] + v->y * m->m[1][1] + v->z * m->m[2][1] + m->m[3][1];
    float z = v->x * m->m[0][2] + v->y * m->m[1][2] + v->z * m->m[2][2] + m->m[3][2];
    out->x = x;
    out->y = y;
    out->z = z;
    return out;
}

const char16_t* TextRef::EmptyText = u"";

TextRef::TextRef(const char* text) {
    InitImpl(text);
}

void TextRef::InitImpl(const char16_t* text) {
    tchar_ = text;
    type_ = TextEncodeType_Utf16;
    hash_.Clear();
    hash_.CalcTextHash(text);
}

void TextRef::Set(const TextRef&) {
    log_error(Result(-1), Debug::LogFlag::Type(0x7FFFFFFF), u"TextRef::Set は使用できません。", EmptyText);
}

void TextRef::Set(const char*) {
    log_error(Result(-1), Debug::LogFlag::Type(0x7FFFFFFF), u"TextRef::Set は使用できません。", EmptyText);
}

void TextRef::Set(const char16_t*) {
    log_error(Result(-1), Debug::LogFlag::Type(0x7FFFFFFF), u"TextRef::Set は使用できません。", EmptyText);
}

void TextRef::GetText(MemoryBlock* block, TextEncodeType type) const {
    if (type_ == type) {
        unsigned long length = GetTextLength(utf8_);
        if (type == TextEncodeType_Utf8) {
            char* text = SoundMemory::allocator_->NewBuffer<char>(length + 1);
            CopyText(text, utf8_, length + 1);
            block->address = text;
            block->size = length;
        } else {
            char16_t* text = SoundMemory::allocator_->NewBuffer<char16_t>(length + 1);
            CopyText(text, tchar_, (length + 1) * sizeof(char16_t));
            block->address = text;
            block->size = length;
        }
        return;
    }
    if (type_ == TextEncodeType_Utf8) {
        Utf8ToUTF16(utf8_, block);
    } else {
        Utf16ToUTF8(tchar_, block);
    }
}

void TextFixedBase::Set(const TextRef& text) {
    if (text.type_ == TextEncodeType_Utf8) {
        Utf8ToUTF16(text.utf8_, const_cast<char16_t*>(tchar_), capacity_);
    } else {
        CopyText(const_cast<char16_t*>(tchar_), text.tchar_, capacity_);
    }
    hash_.Clear();
    hash_.CalcTextHash(tchar_);
}

void TextFixedBase::Set(const char* text) {
    Utf8ToUTF16(text, const_cast<char16_t*>(tchar_), capacity_);
    hash_.Clear();
    hash_.CalcTextHash(tchar_);
}

void TextFixedBase::Set(const char16_t* text) {
    CopyText(const_cast<char16_t*>(tchar_), text, capacity_);
    hash_.Clear();
    hash_.CalcTextHash(tchar_);
}

}  // namespace ssd
