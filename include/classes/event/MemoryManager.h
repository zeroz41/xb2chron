#ifndef CLASSES_EVENT_MEMORYMANAGER_H
#define CLASSES_EVENT_MEMORYMANAGER_H

#include "mtl/AllocHandle.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixedVector.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3BE68; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::MemoryManager>
class MemoryManager : public IManager, public mm::mtl::Singleton<MemoryManager> {
public:
    // out of line (mm::mtl::Singleton<event::MemoryManager>::getPtr's static calls it)
    MemoryManager();
    virtual ~MemoryManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2

    long pad_10;
    long pad_18;
    // the allocator the script commands come from (every event::Script*::exec passes it to operator new); the name
    // is not the original's
    mtl::ALLOC_HANDLE m_handle;  // 0x20
    // a second handle: StmPackHeader::create (0x71000C1790) requests its resource from it; zeroed by the constructor
    mtl::ALLOC_HANDLE pad_24;
    // fields the constructor initializes; what they hold is not known yet
    long pad_28;
    long pad_30;
    unsigned int pad_38;
    unsigned char pad_3c[0x4];
    // the buffers createTxtbuf allocates (login delete[]s each one and erases it; the destructor only clears the
    // count); the name is not the original's
    mm::mtl::FixedVector<char*, 512> m_txtbufs;  // 0x40 (count at 0x1040)
    long pad_1048;
    long pad_1050;
    unsigned int pad_1058;
    unsigned char pad_105c[0x4];
};
}  // namespace event

#endif
