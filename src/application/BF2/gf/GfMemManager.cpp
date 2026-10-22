#include "classes/gf/GfAllocatorManager.h"
#include "classes/gf/GfMemManager.h"

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

}  // namespace gf
