#ifndef CLASSES_GF_GFMEMMANAGER_H
#define CLASSES_GF_GFMEMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfAllocatorManager.h"
#include "mtl/AllocHandle.h"

namespace gf { class GfMemManager; }

namespace gf {
// table 0x7100B59868
class GfMemManager : public ::mm::mtl::PtrSingleton< ::gf::GfMemManager> {
public:
    virtual ~GfMemManager();  // slot 0
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
};
}  // namespace gf

#endif
