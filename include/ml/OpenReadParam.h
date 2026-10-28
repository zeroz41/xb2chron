#ifndef ML_OPENREADPARAM_H
#define ML_OPENREADPARAM_H

#include "mm/mtl/FixStr.h"
#include "mm/threading/ReadWriteLock.h"
#include "nn/fs.h"

namespace ml {

// one read channel of the Switch file devices (ml::DevFileNxTh and ml::DevFileArchiveNx hold 13 in their Impl,
// 0x1D8 each; rfOpen locks m_lock, builds m_path with DevFileTh::makeMediaFileName, opens m_handle and sets
// m_isOpen, which rfIsUsedChannel returns). Every name here is inferred, none is the original's.
struct OpenReadParam {
    // the member at 0x158: its destructor only clears the pointer it holds
    struct Ref {
        Ref() : m_ptr(nullptr) {}
        ~Ref() {
            if (m_ptr != nullptr) {
                m_ptr = nullptr;
            }
        }
        void* m_ptr;
    };

    // the block at 0x158: built by its own constructor (the original's zeroing order needs it); the name is not the
    // original's
    struct Block158 {
        Block158() : m_ref(), pad_8(0), pad_14(0), pad_18(0) {}

        Ref m_ref;
        unsigned long pad_8;
        int pad_10;
        int pad_14;
        unsigned long pad_18;
    };

    OpenReadParam()
        : m_handle(), m_isOpen(false), pad_10D(), pad_110(0), pad_118(0), pad_120(0), pad_128(0), pad_130(0),
          pad_158(), pad_178(1), pad_17C(0), pad_180(0), pad_188(10), pad_18C(true), pad_18D() {}

    nn::fs::FileHandle m_handle;
    mm::mtl::FixStr<256> m_path;
    bool m_isOpen;
    unsigned char pad_10D[3];
    bool pad_110;
    unsigned long pad_118;
    unsigned long pad_120;
    int pad_128;
    unsigned long pad_130;
    unsigned char pad_138[0x20];
    Block158 pad_158;
    int pad_178;
    int pad_17C;
    unsigned long pad_180;
    int pad_188;
    bool pad_18C;
    unsigned char pad_18D[0x1B];
    mm::threading::ReadWriteLock m_lock;
};

}  // namespace ml

#endif
