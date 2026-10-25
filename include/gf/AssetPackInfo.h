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
namespace mm { namespace mtl { template <int> class FixStr; } }

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

    unsigned char pad_0[0x38];
    GF_OBJ_HANDLE* m_objHandle;  // the object GfAssetUtil::addDestroyObject destroys for the pack
    // GfAssetManager::getExtentResource reads them by index, destroyExtResource releases all four (the name is not
    // the original's)
    GfExtendResource* m_extendResources[4];
    unsigned char pad_60[0x4];
    bool m_destroy;  // GfAssetManager::isDestroy reads it (the name is not the original's)
    unsigned char pad_65[0x1];
    bool m_retargetLoad;  // GfAssetUtil::setRetargetLoad sets it, isRetargetLoad reads it
    bool m_reload;  // GfAssetManager::isReload reads it (the name is not the original's)
    unsigned char pad_68[0x4];
    // setModelName and setMotionName's names, GfAssetManager::getModelInfo and getMotionInfo read them (the names
    // are not the original's)
    char m_modelName[0x14];
    char m_motionName[0x18];
};
}  // namespace gf

#endif
