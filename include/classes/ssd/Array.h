#ifndef CLASSES_SSD_ARRAY_H
#define CLASSES_SSD_ARRAY_H

#include "classes/ssd/Allocator.h"

namespace ssd {
// a template: 6 instances in the module. A growable array of T in one SoundMemory::allocator_ instance block
// (Array<SoundHandle*>: SoundActor::SetCategoryId's local, filled by SystemCore::GetPlaySoundHandleFromActor).
// The member names are not the original's.
template <typename T0>
class Array {
public:
    Array() : size_(0), capacity_(0), data_(nullptr) {}
    virtual ~Array() {  // slot 0
        if (data_ != nullptr) {
            SoundMemory::allocator_->DeleteInstance(data_);
        }
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    }

    T0* begin() { return data_; }
    T0* end() { return data_ + size_; }

    int size_;
    int capacity_;
    T0* data_;
};
}  // namespace ssd

#endif
