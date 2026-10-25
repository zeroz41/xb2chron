#ifndef GRLIB_CGLIBMEMHANDLE_H
#define GRLIB_CGLIBMEMHANDLE_H

#include "mtl/AllocHandle.h"

namespace grlib {
// a block of GPU-visible memory: CGLibMemHandle allocates and frees it. The field names are not the original's.
struct CGLibMemType {
    CGLibMemType() {
        m_type = 5;
        m_pMem = nullptr;
    }

    void* m_pMem;  // 0x0
    int m_type;  // 0x8, 5 until a CGLibMemHandle call fills the block
};

// the allocator of CGLibMemType blocks (static members: the callers pass only the block)
class CGLibMemHandle {
public:
    // the sizes setup creates its allocators with (CGLibManager::deviceInit fills it). The field names are not the
    // original's: each is named from the allocator setup creates with it ("GLIBPXL", "GLIBVTX", ...)
    struct ArgMemInfo {
        unsigned int m_topSize;      // 0x00 the top allocator's, with the five etc buffers added
        unsigned int m_pxlSize;      // 0x04 "GLIBPXL"
        unsigned int m_vtxSize;      // 0x08 "GLIBVTX"
        unsigned int m_uniSize;      // 0x0C "GLIBUNI"
        unsigned int m_memSize;      // 0x10 "GLIBMEM"
        unsigned int m_fetSize;      // 0x14 "GLIBFET"
        unsigned int m_shdSize;      // 0x18 "GLIBSHD"
        unsigned int m_cntSize;      // 0x1C "GLIBCNT"
        unsigned int m_etc128Size;   // 0x20 CGLibSystemContext::ETCBUFFER_128_SIZE
        unsigned int m_etc256Size;   // 0x24
        unsigned int m_etc512Size;   // 0x28
        unsigned int m_etc768Size;   // 0x2C
        unsigned int m_etc1024Size;  // 0x30
    };

    // creates the allocators (releasing any first)
    static void setup(const ArgMemInfo& info);
    static void release();
    static void free(CGLibMemType& mem);
    static void allocVertex(CGLibMemType& mem, unsigned int size);
    static void allocUniform(CGLibMemType& mem, unsigned int size);
    // the block takes memory owned elsewhere (a CGLibVtlMemPool's)
    static void setMemBuff(CGLibMemType& mem, void* buffer);

    // the allocators setup creates (defined in this order). The names are 1.0.0's.
    static mtl::ALLOC_HANDLE s_hDefHandle;
    // the allocator pixel memory comes from (CGLibState::setPixelResidentArea)
    static mtl::ALLOC_HANDLE s_hPxlHandle;
    static mtl::ALLOC_HANDLE s_hVtxHandle;
    static mtl::ALLOC_HANDLE s_hUniHandle;
    // the "GLIBMEM" allocator (CGLibManager::deviceInit allocates the system context from it)
    static mtl::ALLOC_HANDLE s_hMemHandle;
    static mtl::ALLOC_HANDLE s_hFchHandle;
    static mtl::ALLOC_HANDLE s_hShdHandle;
    static mtl::ALLOC_HANDLE s_hCntHandle;
};
}  // namespace grlib

#endif
