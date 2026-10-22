#ifndef CLASSES_GF_GFMEMMANAGER_H
#define CLASSES_GF_GFMEMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfAllocatorManager.h"
#include "mtl/AllocHandle.h"
#include "ml/MlMem.h"

namespace gf { class GfMemManager; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B59868
class GfMemManager : public ::mm::mtl::PtrSingleton< ::gf::GfMemManager> {
public:
    // inline: this build has no copy of it nor of initialize, initializeGame and finalize (1.0.0 has all four)
    GfMemManager(const GfSetupParam& param) : m_initialized(false) {
        initialize(param);
    }
    virtual ~GfMemManager();  // slot 0
    void initialize(const GfSetupParam& param) {
        initializeGame(ml::MlMem::getProductMem());
        m_initialized = true;
    }
    void finalize() {
        m_initialized = false;
    }
    void initializeGame(mtl::ALLOC_HANDLE handle) {}

    // the game's allocators, each in a memory of its own made in the setup parameters' memory, and taken back
    static void buildCoreMemory(const GfSetupParam& param);
    static void initializeCore(const GfSetupParam& param);
    static void destroyCoreMemory();
    static void finalizeCore();
    // the instance, made and destroyed
    static void build(const GfSetupParam& param);
    static void destroy();
    // the memory of an allocator kind (10: monolib's debug memory), none past them
    mtl::ALLOC_HANDLE getMemHandle(ALLOCATOR allocator);

    static GfAllocatorManager s_allocator;
    static mtl::ALLOC_HANDLE s_hMemProg;
    static mtl::ALLOC_HANDLE s_hMemInitial;
    static mtl::ALLOC_HANDLE s_hMemScript;
    static mtl::ALLOC_HANDLE s_hMemAsset;
    static mtl::ALLOC_HANDLE s_hMemBdat;
    static mtl::ALLOC_HANDLE s_hMemFontRsc;
    static mtl::ALLOC_HANDLE s_hMemMenu;
    static mtl::ALLOC_HANDLE s_hMemAnimation;
    static mtl::ALLOC_HANDLE s_hMemGimmick;
    static mtl::ALLOC_HANDLE s_hMemGmkBdat;
    static mtl::ALLOC_HANDLE s_hMemProgLarge;

    bool m_initialized;  // 1.0.0's isInitialized reads it
};
}  // namespace gf

#endif
