#ifndef CLASSES_SSD_TEXTFIXEDBASE_H
#define CLASSES_SSD_TEXTFIXEDBASE_H

#include "classes/ssd/TextRef.h"

namespace ssd {
// table none (its derived classes'): a TextRef over a UTF-16 buffer of its own (TextFixed<N>'s), which Set
// copies into
class TextFixedBase : public ::ssd::TextRef {
public:
    virtual void Set(const TextRef& text);  // slot 0
    virtual void Set(const char* text);  // slot 1
    virtual void Set(const char16_t* text);  // slot 2

    // the buffer's size in characters (the name is not the original's)
    unsigned long capacity_;
};
}  // namespace ssd

#endif
