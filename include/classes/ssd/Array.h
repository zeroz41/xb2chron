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

    // grows the storage to hold size elements (one more is allocated), keeping the elements; never shrinks
    // (SoundBank::AddSoundGroup grows by 16)
    void SetArraySize(int size);

    T0* begin() { return data_; }
    T0* end() { return data_ + size_; }

    int size_;
    int capacity_;
    T0* data_;
};

template <typename T0>
void Array<T0>::SetArraySize(int size) {
    if (capacity_ <= size) {
        T0* old = data_;
        data_ = SoundMemory::allocator_->NewInstance<T0>(size + 1);
        if (old == nullptr) {
            capacity_ = size;
            return;
        }
        // the empty-array exit (codegen merges it with the loop guard) keeps the function out of line as the
        // original calls it: clang 4.0.1 inlines the form without it (inline cost 245 against the 250 threshold)
        if (capacity_ <= 0) {
            SoundMemory::allocator_->DeleteInstance(old);
            capacity_ = size;
            return;
        }
        for (int i = 0; i < capacity_; i++) {
            data_[i] = old[i];
        }
        SoundMemory::allocator_->DeleteInstance(old);
        capacity_ = size;
    }
}
}  // namespace ssd

#endif
