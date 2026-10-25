#ifndef CLASSES_EVENT_MEMORYMANAGER_H
#define CLASSES_EVENT_MEMORYMANAGER_H

#include "mtl/AllocHandle.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::MemoryManager no evidence names yet
class TUnk_B3BE68 {
public:
    virtual ~TUnk_B3BE68();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::MemoryManager no evidence names yet
class TUnk_B3BE90 {
public:
    virtual ~TUnk_B3BE90();
};
// table 0x7100B3BE68; base at 0x0 unknown (TUnk_B3BE68), base at 0x8 unknown (TUnk_B3BE90)
class MemoryManager : public TUnk_B3BE68, public TUnk_B3BE90 {
public:
    // out of line (mm::mtl::Singleton<event::MemoryManager>::getPtr's static calls it)
    MemoryManager();
    virtual ~MemoryManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2

    unsigned char pad_10[0x10];
    // the allocator the script commands come from (every event::Script*::exec passes it to operator new); the name
    // is not the original's
    mtl::ALLOC_HANDLE m_handle;  // 0x20
};
}  // namespace event

#endif
