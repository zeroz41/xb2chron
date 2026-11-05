#ifndef ML_OPENREADPARAM_H
#define ML_OPENREADPARAM_H

#include "mm/mtl/FixStr.h"
#include "mm/threading/ReadWriteLock.h"
#include "nn/fs.h"

namespace ml { class DevFileNxTh; }
namespace ml { class FileHandleTh; }
namespace ml { class Thread; }

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
        Block158() : m_ref(), pad_8(nullptr), pad_14(0), pad_18(0), pad_1C(0) {}

        Ref m_ref;
        void* pad_8;  // the buffer the channel's thread reads into
        int pad_10;
        unsigned int pad_14;  // the file offset the channel's thread reads from
        unsigned int pad_18;  // the byte count the channel's thread reads
        int pad_1C;
    };

    OpenReadParam()
        : m_handle(), m_isOpen(false), pad_10D(), pad_10E(), pad_10F(), pad_110(0), pad_118(nullptr), pad_120(0), pad_128(0), pad_130(0),
          pad_158(), pad_178(1), pad_17C(0), pad_180(0), pad_188(10), pad_18C(true), pad_18D(), m_thread(), m_owner() {}

    nn::fs::FileHandle m_handle;
    mm::mtl::FixStr<256> m_path;
    bool m_isOpen;
    bool pad_10D;  // cleared before the channel's file is closed
    bool pad_10E;
    bool pad_10F;  // when set, rfClose leaves the file open and sets pad_110
    bool pad_110;
    FileHandleTh* pad_118;  // the request the channel's thread reads for
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
    unsigned char pad_18D[0xB];
    Thread* m_thread;      // 0x198: the channel's loader thread (DevFileNxTh::initialize creates it)
    DevFileNxTh* m_owner;  // 0x1A0: the device whose channel it is (DevFileNxTh::initialize sets it)
    mm::threading::ReadWriteLock m_lock;
};

}  // namespace ml

#endif
