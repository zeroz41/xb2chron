#ifndef ML_OPENREADPARAM_H
#define ML_OPENREADPARAM_H

#include "ml/DevFileParamTh.h"
#include "mm/mtl/FixStr.h"
#include "mm/threading/ReadWriteLock.h"
#include "nn/fs.h"

namespace ml { class DevFileAccessor; }
namespace ml { class FileHandleTh; }
namespace ml { class Thread; }

namespace ml {

// one read channel of the Switch file devices (ml::DevFileNxTh and ml::DevFileArchiveNx hold 13 in their Impl,
// 0x1D8 each; rfOpen locks m_lock, builds m_path with DevFileTh::makeMediaFileName, opens m_handle and sets
// m_isOpen, which rfIsUsedChannel returns). Every name here is inferred, none is the original's.
struct OpenReadParam {
    OpenReadParam()
        : m_handle(), m_isOpen(false), m_busy(), pad_10E(), m_reading(), m_closePending(false), m_request(nullptr), m_param(),
          m_archiveOffset(0), m_thread(), m_owner() {}

    nn::fs::FileHandle m_handle;
    mm::mtl::FixStr<256> m_path;
    bool m_isOpen;
    // set by rfRead once it has queued a read (rfIsBusy returns it; tail clears it when the read ends or is
    // canceled, rfClose before closing the file)
    bool m_busy;
    bool pad_10E;
    // set by the channel's thread while it reads (thUpdate); rfClose then leaves the file open and sets
    // m_closePending
    bool m_reading;
    bool m_closePending;  // tail closes the file once the canceled read is over
    FileHandleTh* m_request;  // 0x118: the request the channel's thread reads for (rfRead stores it)
    DevFileParamTh m_param;   // 0x120: rfRead's copy of the read's parameters (the thread reads buffer, offset, size)
    // 0x190: DevFileArchiveNx: the file's offset in the archive (rfOpen sets it, thUpdate adds it)
    unsigned long m_archiveOffset;
    Thread* m_thread;      // 0x198: the channel's loader thread (DevFileNxTh::initialize creates it)
    // 0x1A0: the device whose channel it is (DevFileNxTh::initialize and DevFileArchiveNx::initialize set it; the
    // pointee type is inferred)
    DevFileAccessor* m_owner;
    mm::threading::ReadWriteLock m_lock;
};

}  // namespace ml

#endif
