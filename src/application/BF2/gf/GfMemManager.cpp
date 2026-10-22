#include "gf/GfSetupParam.h"
#include "gf/GfSlotMapping.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfAllocatorManager.h"
#include "classes/gf/GfMemManager.h"
#include "classes/ml/DevGraph.h"
#include "ml/MlMem.h"
#include "mtl/MemManager.h"

namespace gf {

GfMemManager::~GfMemManager() {}

GfAllocatorManager GfMemManager::s_allocator;
mtl::ALLOC_HANDLE GfMemManager::s_hMemProg;
mtl::ALLOC_HANDLE GfMemManager::s_hMemInitial;
mtl::ALLOC_HANDLE GfMemManager::s_hMemScript;
mtl::ALLOC_HANDLE GfMemManager::s_hMemAsset;
mtl::ALLOC_HANDLE GfMemManager::s_hMemBdat;
mtl::ALLOC_HANDLE GfMemManager::s_hMemFontRsc;
mtl::ALLOC_HANDLE GfMemManager::s_hMemMenu;
mtl::ALLOC_HANDLE GfMemManager::s_hMemAnimation;
mtl::ALLOC_HANDLE GfMemManager::s_hMemGimmick;
mtl::ALLOC_HANDLE GfMemManager::s_hMemGmkBdat;
mtl::ALLOC_HANDLE GfMemManager::s_hMemProgLarge;

void GfMemManager::buildCoreMemory(const GfSetupParam& param) {
    s_allocator.initialize(param);
    initializeCore(param);
}

void GfMemManager::initializeCore(const GfSetupParam& param) {
    mtl::ALLOC_HANDLE parent = param.m_hMem;
    s_hMemProg = mtl::MemManager::create(parent, 0x2400000, "GfProg", false, mtl::AllocatorType(1), 0x10, "no name", 0);
    s_allocator.buildAllocator(ALLOCATOR(0), s_hMemProg);
    s_hMemInitial =
        mtl::MemManager::create(parent, 0xE00000, "GfInitial", false, mtl::AllocatorType(1), 0x10, "no name", 0);
    s_allocator.buildAllocator(ALLOCATOR(1), s_hMemInitial);
    s_hMemScript =
        mtl::MemManager::create(parent, 0x200000, "GfScript", false, mtl::AllocatorType(2), 0x1000, "no name", 0);
    s_allocator.buildAllocator(ALLOCATOR(2), s_hMemScript);
    s_hMemBdat = mtl::MemManager::create(parent, 0x100000, "GfBdat", false, mtl::AllocatorType(2), 0x1000, "no name", 0);
    s_allocator.buildAllocator(ALLOCATOR(4), s_hMemBdat);
    s_hMemFontRsc =
        mtl::MemManager::create(parent, 0x1400000, "GfFontRsc", false, mtl::AllocatorType(2), 0x1000, "no name", 0);
    s_allocator.buildAllocator(ALLOCATOR(5), s_hMemFontRsc);
    s_hMemMenu = mtl::MemManager::create(parent, 0x5A00000, "GfMenu", false, mtl::AllocatorType(2), 0x1000, "no name", 0);
    s_allocator.buildAllocator(ALLOCATOR(6), s_hMemMenu);
    s_hMemAnimation =
        mtl::MemManager::create(parent, 0xE00000, "GfAnim", false, mtl::AllocatorType(1), 0x10, "no name", 0);
    s_allocator.buildAllocator(ALLOCATOR(7), s_hMemAnimation);
    s_hMemGimmick = mtl::MemManager::create(parent, 0x400000, "GfGmk", false, mtl::AllocatorType(1), 0x10, "no name", 0);
    s_allocator.buildAllocator(ALLOCATOR(8), s_hMemGimmick);
    s_hMemGmkBdat =
        mtl::MemManager::create(parent, 0x200000, "GfGmkBdat", false, mtl::AllocatorType(1), 0x10, "no name", 0);
    s_allocator.buildAllocator(ALLOCATOR(9), s_hMemGmkBdat);
    s_allocator.buildAllocator(ALLOCATOR(10), ml::MlMem::getDebugMem());
    s_hMemAsset = mtl::MemManager::create(parent, GfSlotMapping::getAllSize(), "AssetMain", false, mtl::AllocatorType(2),
                                          0x1000, "no name", 0);
    s_allocator.buildAllocator(ALLOCATOR(3), s_hMemAsset);
    ml::DevGraph::setMemPoolMemHandle(s_hMemAsset);
    s_hMemProgLarge =
        mtl::MemManager::create(parent, 0x4000, "ProgLarge", false, mtl::AllocatorType(2), 0x1000, "no name", 0);
    s_allocator.buildAllocator(ALLOCATOR(11), s_hMemProgLarge);
}

void GfMemManager::destroyCoreMemory() {
    finalizeCore();
    s_allocator.finalize();
}

void GfMemManager::finalizeCore() {
    s_allocator.destroyAllocator(ALLOCATOR(9), s_hMemGmkBdat);
    s_allocator.destroyAllocator(ALLOCATOR(8), s_hMemGimmick);
    s_allocator.destroyAllocator(ALLOCATOR(7), s_hMemAnimation);
    s_allocator.destroyAllocator(ALLOCATOR(6), s_hMemMenu);
    s_allocator.destroyAllocator(ALLOCATOR(5), s_hMemFontRsc);
    s_allocator.destroyAllocator(ALLOCATOR(4), s_hMemBdat);
    s_allocator.destroyAllocator(ALLOCATOR(3), s_hMemAsset);
    s_allocator.destroyAllocator(ALLOCATOR(2), s_hMemScript);
    s_allocator.destroyAllocator(ALLOCATOR(10), ml::MlMem::getDebugMem());
    s_allocator.destroyAllocator(ALLOCATOR(1), s_hMemInitial);
    s_allocator.destroyAllocator(ALLOCATOR(0), s_hMemProg);
    s_allocator.destroyAllocator(ALLOCATOR(11), s_hMemProgLarge);
    if (s_hMemAsset.m_handle != 0) {
        ml::DevGraph::releaseMemPoolMemHandle(s_hMemAsset);
    }
    if (s_hMemProgLarge.m_handle != 0) {
        mtl::MemManager::erase(s_hMemProgLarge);
        s_hMemProgLarge = mtl::ALLOC_HANDLE();
    }
    if (s_hMemGmkBdat.m_handle != 0) {
        mtl::MemManager::erase(s_hMemGmkBdat);
        s_hMemGmkBdat = mtl::ALLOC_HANDLE();
    }
    if (s_hMemGimmick.m_handle != 0) {
        mtl::MemManager::erase(s_hMemGimmick);
        s_hMemGimmick = mtl::ALLOC_HANDLE();
    }
    if (s_hMemAnimation.m_handle != 0) {
        mtl::MemManager::erase(s_hMemAnimation);
        s_hMemAnimation = mtl::ALLOC_HANDLE();
    }
    if (s_hMemMenu.m_handle != 0) {
        mtl::MemManager::erase(s_hMemMenu);
        s_hMemMenu = mtl::ALLOC_HANDLE();
    }
    if (s_hMemFontRsc.m_handle != 0) {
        mtl::MemManager::erase(s_hMemFontRsc);
        s_hMemFontRsc = mtl::ALLOC_HANDLE();
    }
    if (s_hMemBdat.m_handle != 0) {
        mtl::MemManager::erase(s_hMemBdat);
        s_hMemBdat = mtl::ALLOC_HANDLE();
    }
    if (s_hMemAsset.m_handle != 0) {
        mtl::MemManager::erase(s_hMemAsset);
        s_hMemAsset = mtl::ALLOC_HANDLE();
    }
    if (s_hMemScript.m_handle != 0) {
        mtl::MemManager::erase(s_hMemScript);
        s_hMemScript = mtl::ALLOC_HANDLE();
    }
    if (s_hMemInitial.m_handle != 0) {
        mtl::MemManager::erase(s_hMemInitial);
        s_hMemInitial = mtl::ALLOC_HANDLE();
    }
    if (s_hMemProg.m_handle != 0) {
        mtl::MemManager::erase(s_hMemProg);
        s_hMemProg = mtl::ALLOC_HANDLE();
    }
}

void GfMemManager::build(const GfSetupParam& param) {
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMemManager(param);
}

GfAllocator* getAllocator(ALLOCATOR allocator) {
    return GfAllocatorManager::getAllocator(allocator);
}

}  // namespace gf

void* operator new(unsigned long size, gf::GfAllocator* allocator, const char* file, unsigned long line, int alignment) {
    return allocator->allocate(size, alignment);
}

namespace gf {

void GfMemManager::destroy() {
    GfMemManager* manager = get();
    manager->finalize();
    delete manager;
}

mtl::ALLOC_HANDLE GfMemManager::getMemHandle(ALLOCATOR allocator) {
    switch (static_cast<int>(allocator)) {
    case 0:
        return s_hMemProg;
    case 1:
        return s_hMemInitial;
    case 2:
        return s_hMemScript;
    case 3:
        return s_hMemAsset;
    case 4:
        return s_hMemBdat;
    case 5:
        return s_hMemFontRsc;
    case 6:
        return s_hMemMenu;
    case 7:
        return s_hMemAnimation;
    case 8:
        return s_hMemGimmick;
    case 9:
        return s_hMemGmkBdat;
    case 10:
        return ml::MlMem::getDebugMem();
    case 11:
        return s_hMemProgLarge;
    default:
        return mtl::ALLOC_HANDLE();
    }
}

}  // namespace gf

void* operator new[](unsigned long size, gf::GfAllocator* allocator, const char* file, unsigned long line,
                     int alignment) {
    return allocator->allocate(size, alignment);
}
