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
    // Manager's destructor calls it on the singleton (0x71000B3918, 3.0.1 symbol)
    void destroy();
    void create();
    void login();
    void render();
    // a copy of str in m_txtbufs (null for null, "" for an empty string)
    const char* createTxtbuf(const char* str);

    // bit 0: render draws the "SYS" and "RES" meters without ml::ProcDesktop::isDispInfo; the name is not the
    // original's
    unsigned int m_flags;  // 0x10
    // zeroed by OnEventProc; what it holds is not known yet
    unsigned int pad_14;
    // login's choice of sizes (0, or 1 to 3 for scenes of the Ira game type); the name is not the original's
    unsigned int m_sizeType;  // 0x18
    // create's "EvStatic" memory; the name is not the original's
    mtl::ALLOC_HANDLE m_static;  // 0x1c
    // the allocator the script commands come from (every event::Script*::exec passes it to operator new); create's
    // "EvSys" memory; the name is not the original's
    mtl::ALLOC_HANDLE m_handle;  // 0x20
    // create's and login's "EvRes" memory (the GPU cache's memory pool): StmPackHeader::create (0x71000C1790)
    // requests its resource from it
    mtl::ALLOC_HANDLE pad_24;
    // create's and login's "EvMotstm" memory; the name is not the original's
    mtl::ALLOC_HANDLE m_motstm;  // 0x28
    // the sizes of the EvStatic, EvSys, EvRes and EvMotstm memories (create sets them, login resets the last two);
    // the name is not the original's
    unsigned int m_sizes[4];  // 0x2c
    unsigned char pad_3c[0x4];
    // the buffers createTxtbuf allocates (login delete[]s each one and erases it; the destructor only clears the
    // count); the name is not the original's
    mm::mtl::FixedVector<char*, 512> m_txtbufs;  // 0x40 (count at 0x1040)
    long pad_1048;
    long pad_1050;
    // render's frame counter (0 to 31; bit 4 blinks the full meters); the name is not the original's
    int m_frame;  // 0x1058
    unsigned char pad_105c[0x4];
};
}  // namespace event

#endif
