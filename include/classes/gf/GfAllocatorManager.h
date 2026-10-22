#ifndef CLASSES_GF_GFALLOCATORMANAGER_H
#define CLASSES_GF_GFALLOCATORMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfAllocator.h"
#include "mtl/AllocHandle.h"

namespace gf { class GfAllocatorManager; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B597F0
class GfAllocatorManager : public ::mm::mtl::PtrSingleton< ::gf::GfAllocatorManager> {
public:
    GfAllocatorManager();
    virtual ~GfAllocatorManager();  // slot 0
    void initialize(const GfSetupParam& param);
    void finalize();
    // the allocator of a kind, in the instance's array of them (0x50 apart from 0x10)
    static GfAllocator* getAllocator(ALLOCATOR allocator);
    // an allocator of a kind given its memory (GfMemManager::initializeCore), and taken back (finalizeCore)
    void buildAllocator(ALLOCATOR allocator, mtl::ALLOC_HANDLE handle);
    void destroyAllocator(ALLOCATOR allocator, mtl::ALLOC_HANDLE handle);

    // the names are not the original's
    bool m_initialized;  // initialize sets it, finalize clears it
    GfAllocator m_allocators[12];  // by ALLOCATOR (GfMemManager::getMemHandle knows 12 kinds)
};
}  // namespace gf

#endif
