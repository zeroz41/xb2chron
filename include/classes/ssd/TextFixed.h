#ifndef CLASSES_SSD_TEXTFIXED_H
#define CLASSES_SSD_TEXTFIXED_H

#include "classes/ssd/TextFixedBase.h"

namespace ssd {
// a template: 2 instances in the module. A text of up to T0 UTF-16 characters (SoundBank's name is a
// TextFixed<64>); the constructor points the reference at the (empty) buffer
template <int T0>
class TextFixed : public ::ssd::TextFixedBase {
public:
    TextFixed() : TextFixedBase(T0) {
        InitImpl(buffer_);
        buffer_[0] = 0;
    }

    TextFixed& operator=(const TextRef& text) {
        Set(text);
        return *this;
    }

    char16_t buffer_[T0];
};
}  // namespace ssd

#endif
