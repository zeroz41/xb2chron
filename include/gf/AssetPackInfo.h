#ifndef GF_ASSETPACKINFO_H
#define GF_ASSETPACKINFO_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GF_SLOT_HANDLE; }
namespace gf { class GfAssetPack; }
namespace gf { class GfExtendResource; }
namespace gf { enum GfFileIdx : int; }
namespace fw { class SoundPack; }
namespace gf { class GfAssetResource; }
namespace mm { namespace mtl { template <typename T, unsigned long N> class FixedVector; } }

#include "mm/mtl/FixStr.h"

namespace gf { class GF_ASSET_HANDLE; }

namespace gf {
// one loaded asset pack: GfAssetManager keeps them 0x98 apart (getAssetPackInfo)
class AssetPackInfo {
public:
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
    // marks the pack destroyed once and hands its handle to GfAssetUtil::addDestroyObject (1.0.0's symbols name it)
    void setDestroy();
    // GfAssetManager::enableGameResource/disableGameResource call it with true/false (1.0.0's symbols name it)
    void setUsingGame(bool usingGame);
    // GfAssetManager::destroyExtResource forwards to it (3.0.1's symbols name it)
    void releaseExtResource();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because GfAssetManager::
    // fn_71001AE8A8 calls it on the handle's AssetPackInfo. What it does: walks the packs' resources and appends to
    // `names` the asset name of each resource whose name contains `name` (strstr); returns !names.empty().
    bool fn_71001B1840(mm::mtl::FixedVector<const char*, 128>& names, const char* name);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because GfAssetManager::
    // fn_71001AE9D0 calls it on the handle's AssetPackInfo. What it does: walks the packs' resources and returns the
    // first whose asset name equals `name` (strcmp), else nullptr.
    GfAssetResource* fn_71001B1B30(const char* name);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because GfAssetManager::
    // fn_71001AF824 calls it on the handle's AssetPackInfo. What it does: walks the packs' resources and returns
    // true when one's asset name contains `name` (strstr).
    bool fn_71001B3624(const char* name);

    unsigned char pad_0[0x8];
    GF_ASSET_HANDLE* m_handle;  // setDestroy hands it to GfAssetUtil::addDestroyObject (the name is not the original's)
    unsigned char pad_10[0x28];
    GF_OBJ_HANDLE* m_objHandle;  // the object GfAssetUtil::addDestroyObject destroys for the pack
    // GfAssetManager::getExtentResource reads them by index, destroyExtResource releases all four (the name is not
    // the original's)
    GfExtendResource* m_extendResources[4];
    unsigned char pad_60[0x4];
    bool m_destroy;  // GfAssetManager::isDestroy reads it (the name is not the original's)
    bool m_usingGame;  // setUsingGame's state: enableGameResource/disableGameResource test it (the name is not the original's)
    bool m_retargetLoad;  // GfAssetUtil::setRetargetLoad sets it, isRetargetLoad reads it
    bool m_reload;  // GfAssetManager::isReload reads it (the name is not the original's)
    unsigned char pad_68[0x4];
    // setModelName and setMotionName's names, GfAssetManager::getModelInfo and getMotionInfo read them (the names
    // are not the original's)
    mm::mtl::FixStr<16> m_modelName;
    mm::mtl::FixStr<16> m_motionName;
    int m_loadState;  // setupLoadStart clears it (the name is not the original's)
};
}  // namespace gf

#endif
