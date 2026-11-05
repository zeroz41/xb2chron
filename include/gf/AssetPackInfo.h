#ifndef GF_ASSETPACKINFO_H
#define GF_ASSETPACKINFO_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GF_SLOT_HANDLE; }
namespace gf { class GfAssetPack; }
namespace gf { class GfExtendResource; }
namespace gf { enum GfFileIdx : int; }
namespace gf { enum GfAssetType : int; }
namespace fw { class SoundPack; }
namespace gf { class GfAssetResource; }
namespace mm { namespace mtl { template <typename T, unsigned long N> class FixedVector; } }

#include "mm/mtl/FixStr.h"
#include "mm/mtl/Vector.h"

namespace gf { class GF_ASSET_HANDLE; }

namespace gf {
// one loaded asset pack: GfAssetManager keeps them 0x98 apart (getAssetPackInfo)
class AssetPackInfo {
public:
    // drops the info's use of each pack and its reference to it (table 0x7100B43628, 1.0.0's symbols name it)
    // GfAssetManager::createAssetHandle builds one in the slot it allocates, passing the init param's pad_c
    AssetPackInfo(unsigned int kind);
    virtual ~AssetPackInfo();
    // the pack of one of the asset's files (1.0.0's symbols name it; GfAssetManager::getAssetPack forwards to it)
    GfAssetPack* getAssetPack(GfFileIdx file) const;
    bool isExist(GfFileIdx file) const;
    // one of the asset's files (1.0.0's symbols name it; GfAssetManager::getResource forwards to it)
    GfAssetResource* getResource(GfFileIdx file);
    bool isLoaded(mm::mtl::FixStr<128>* name);
    bool getSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE*, 88>& handles) const;
    void setModelName(const char* name);
    void setMotionName(const char* name);
    // 1.0.0's symbols name it (GfAssetManager::isFullResource forwards to it)
    bool isFullResource() const;
    fw::SoundPack* getSePackByFileIdx(GfFileIdx file);
    void setupLoadStart();
    // 1.0.0's symbols name it (GfAssetManager::lockEnterRersource forwards to it)
    void lockEnterRersource();
    void setExtendResource(unsigned int index, GfExtendResource* resource);
    void setupStreamObject();
    void releaseEmptySlot();
    // marks the pack destroyed once and hands its handle to GfAssetUtil::addDestroyObject (1.0.0's symbols name it)
    void setDestroy();
    // GfAssetManager::enableGameResource/disableGameResource call it with true/false (1.0.0's symbols name it)
    void setUsingGame(bool usingGame);
    // GfAssetManager::destroyExtResource forwards to it (3.0.1's symbols name it)
    void releaseExtResource();
    // 2.0.0's symbols name it. What it does: walks the packs' resources and appends to `names` the asset name of each
    // resource whose name contains `name` (strstr); returns !names.empty().
    bool getFileNameByExt(mm::mtl::FixedVector<const char*, 128>& names, const char* name);
    // 2.0.0's symbols name it. What it does: walks the packs' resources and returns the first whose asset name equals
    // `name` (strcmp), else nullptr.
    GfAssetResource* getResource(const char* name);
    // 2.0.0's symbols name it. What it does: walks the packs' resources and returns true when one's asset name contains
    // `name` (strstr).
    bool isExistResourceName(const char* name) const;
    // 1.0.0's symbols name it (GfAssetManager::updateCheckLoading calls it there and here); clears m_reload, then
    // walks m_packs with an empty body (begin()/end() asserts only)
    void setLoadComplete();
    // 1.0.0's symbols name it (GfAssetManager::updateCheckCacheReload calls it there and here): for each pack counts
    // the updates it goes with no reference besides its users' (m_RefCount - m_useCount == 1), up to 99, else clears
    void updateReloadCount();
    // whether m_packs holds `pack` (false for nullptr) (1.0.0's symbols name it; GfAssetManager::updateCheckDestroy
    // calls it there and here)
    bool isExistAssetPack(const GfAssetPack* pack) const;
    // true unless a pack has a file whose preloaded size is still unknown (-2) or has no files (1.0.0's symbols name
    // it; GfAssetManager::updateCheckLoading calls it there and here)
    bool isPreSizeSizeValid() const;
    // whether every pack is cached (m_reload: each pack's m_refCacheCount over 9) (1.0.0's symbols name it;
    // GfAssetManager::updateCheckCacheReload calls it there and here)
    bool isCached() const;
    // adds the pack once, referenced and counted in its m_useCount; the first type sets m_assetType (1.0.0's symbols
    // name it; GfAssetManager::createAssetFiles calls it there and here)
    void setAssetPack(GfAssetType type, GfAssetPack* pack);
    // whether both infos hold packs of the same values in the same order (1.0.0's symbols name it;
    // GfAssetManager::updateCheckDestroy calls it there and here)
    bool isSameResource(const AssetPackInfo* other) const;
    // drops the packs' resources and file sizes and requests their slots again (1.0.0's symbols name it;
    // GfAssetManager::updateCheckCacheReload calls it there and here)
    void execReload();

    GF_ASSET_HANDLE* m_handle;  // setDestroy hands it to GfAssetUtil::addDestroyObject (the name is not the original's)
    // the asset's packs, each counted in its m_useCount and referenced (the destructor drops both) (the name is not
    // the original's)
    mm::mtl::Vector<GfAssetPack*> m_packs;
    GF_OBJ_HANDLE* m_objHandle;  // the object GfAssetUtil::addDestroyObject destroys for the pack
    // GfAssetManager::getExtentResource reads them by index, destroyExtResource releases all four (the name is not
    // the original's)
    GfExtendResource* m_extendResources[4];
    unsigned int pad_60;  // the constructor sets 10
    bool m_destroy;  // GfAssetManager::isDestroy reads it (the name is not the original's)
    bool m_usingGame;  // setUsingGame's state: enableGameResource/disableGameResource test it (the name is not the original's)
    bool m_retargetLoad;  // GfAssetUtil::setRetargetLoad sets it, isRetargetLoad reads it
    bool m_reload;  // GfAssetManager::isReload reads it (the name is not the original's)
    GfAssetType m_assetType;  // setAssetPack's first pack's type (the name is not the original's)
    // setModelName and setMotionName's names, GfAssetManager::getModelInfo and getMotionInfo read them (the names
    // are not the original's)
    mm::mtl::FixStr<16> m_modelName;
    mm::mtl::FixStr<16> m_motionName;
    int m_loadState;  // setupLoadStart clears it (the name is not the original's)
};
}  // namespace gf

#endif
