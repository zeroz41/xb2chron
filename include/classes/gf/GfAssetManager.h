#ifndef CLASSES_GF_GFASSETMANAGER_H
#define CLASSES_GF_GFASSETMANAGER_H

#include "classes/ml/IWorkEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/fixed_size_alloc_inside.h"
#include "gf/AssetPackInfo.h"
#include "mm/mtl/FixedList.h"

namespace gf { class GfSetupParam; }
namespace gf { class GfExtendResource; }
namespace fw { class UpdateInfo; }
namespace fw { class SoundPack; }
namespace gf { class GfAssetManager; }
namespace gf { class AssetPackInfo; }
namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GF_SLOT_HANDLE; }
namespace gf { class GfInitParam; }
namespace gf { class GfAssetResource; }
namespace gf { class GfAssetPack; }
namespace gf { class GfAssetFilesInfo; }
namespace gf { class GfSlotMapping; }
// 1.0.0's GfAssetManager::addEvent(gf::IGfAssetEvent*) names it; no table in 3.0.1 (nothing implements it)
namespace gf { class IGfAssetEvent; }
namespace mm { namespace mtl { class IAllocator; } }
namespace mm { namespace mtl { template <int> class FixStr; } }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace gf {
// which of an asset's files (gf::MapColi takes 1, MapNavi 2, MapEff 6, MapGIBL 7, MapLIBL 8); no value has a
// name yet
enum GfFileIdx : int {};
// an asset file's kind (the map parts pass 0); no value has a name yet
enum GfAssetType : int {};
}  // namespace gf

namespace gf {
// table 0x7100B43558
class GfAssetManager : public ::mm::mtl::PtrSingleton< ::gf::GfAssetManager>, public ::ml::IWorkEvent {
public:
    GfAssetManager(const GfSetupParam& param);
    void initialize(const GfSetupParam& param);
    static unsigned int getUsedAssetPackInfo();
    static void build(const GfSetupParam& param);
    static void destroy();
    // releases an asset pack (GfObjFactory::destroyObjHandle passes its object's)
    static void destroy(GF_ASSET_HANDLE* handle);
    void finalize();
    void update(const fw::UpdateInfo& info);
    void updateCheckLoading();
    void updateCheckDestroy();
    void updateCheckCacheReload();
    virtual ~GfAssetManager();  // slot 0
    static void clear();
    static void destroySlotCache(GfAssetType type);
    // GfAssetSetup's destructor hands it the setup's handle
    static void lockEnterRersource(GF_ASSET_HANDLE* handle);
    // whether the asset is being loaded again (GfObjAcc::isReload asks it for the object's)
    static bool isReload(GF_ASSET_HANDLE* handle);
    static bool isDestroy(GF_ASSET_HANDLE* handle);
    bool isLoaded(GF_ASSET_HANDLE* handle, mm::mtl::FixStr<128>* name);
    static GF_OBJ_HANDLE* getObj(GF_ASSET_HANDLE* handle);
    static GF_ASSET_HANDLE* createAssetHandle(const GfInitParam& param);
    static AssetPackInfo* getAssetPackInfo(GF_ASSET_HANDLE* handle);
    static GfAssetPack* getAssetPack(GF_ASSET_HANDLE* handle, GfFileIdx file);
    static bool isExist(GF_ASSET_HANDLE* handle, GfFileIdx file);
    static bool getSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE*, 88>& handles, GF_ASSET_HANDLE* handle);
    static void setModelInfo(GF_ASSET_HANDLE* handle, const char* name);
    static const char* getModelInfo(GF_ASSET_HANDLE* handle);
    static void setMotionInfo(GF_ASSET_HANDLE* handle, const char* name);
    // the pack info describes, made or found (1.0.0's symbols name it)
    static GfAssetPack* createAssetFiles(const GfAssetFilesInfo& info);
    bool isFullResource(GF_ASSET_HANDLE* handle) const;
    fw::SoundPack* getSePackByFileIdx(GF_ASSET_HANDLE* handle, GfFileIdx file);
    static void setupLoadStart(GF_ASSET_HANDLE* handle);
    void setupStreamObject(GF_ASSET_HANDLE* handle);
    static void setExtendResource(GF_ASSET_HANDLE* handle, unsigned int index, GfExtendResource* resource);
    static void loadStart(GfAssetPack* pack, mm::mtl::IAllocator* allocator);
    static void releaseSlotHandle(GF_SLOT_HANDLE* handle);
    // tells the listeners about a pack AssetPackInfo's destructor lets go of (1.0.0's symbols name it)
    static void callEventAssetPack(GfAssetPack* pack);
    static GfSlotMapping* getSlotMapping();
    // an asset's loaded file, none while it is not loaded
    static GfAssetResource* getResource(GF_ASSET_HANDLE* handle, GfFileIdx file, GfAssetType type);
    // the asset's extend resource at an index (GfObjUtil::isExistAsm asks for 0 and casts it to GfExtendPacking)
    // the asset's motion name (GfObjUtil::getAssetMotionName returns it)
    static const char* getMotionInfo(GF_ASSET_HANDLE* handle);
    static GfExtendResource* getExtentResource(GF_ASSET_HANDLE* handle, unsigned int index);
    static void enableGameResource(GF_ASSET_HANDLE* handle);
    static void disableGameResource(GF_ASSET_HANDLE* handle);
    static void destroyExtResource(GF_ASSET_HANDLE* handle);
    // whether another loaded pack with the same key holds the same asset (GfAssetPack::isExistSameAsset)
    static bool isExistSameAsset(GfAssetPack* pack);
    // hands a resource to the loaded packs until one releases its reference to it
    void releaseRefResource(void* resource);
    // 2.0.0's symbols name it. What it does: for a valid handle and a non-null name, collects the names of the asset's
    // resources containing `name` (AssetPackInfo::getFileNameByExt); returns !names.empty(). Callers:
    // GfComEffectCaster::setup, setupEfTail, fn_7100540E78.
    static bool getFileNameByExt(mm::mtl::FixedVector<const char*, 128>& names, GF_ASSET_HANDLE* handle,
                              const char* name);
    // 2.0.0's symbols name it. What it does: the asset's resource whose asset name equals `name`
    // (AssetPackInfo::getResource), nullptr for an unknown handle. Callers: GfComEffectCaster::setup, setupEfTail,
    // fn_7100540E78.
    static GfAssetResource* getResource(GF_ASSET_HANDLE* handle, const char* name);
    // 2.0.0's symbols name it. What it does: whether one of the asset's resource names contains `name`
    // (AssetPackInfo::isExistResourceName), false for an unknown handle. Callers: fn_71002C5208,
    // GfGameScene::gevAcceParam.
    static bool isExistResourceName(GF_ASSET_HANDLE* handle, const char* name);

    // the asset packs' records, one per handle: a handle's low ten bits index them (the name is not the original's)
    ml::fixed_size_alloc_inside<AssetPackInfo, 1024> m_packInfos;
    // handles updateCheckLoading walks (it moves them to m_loadedHandles; updateCheckCacheReload moves them back)
    // (the name is not the original's)
    mm::mtl::FixedList<GF_ASSET_HANDLE*, 1024> m_loadingHandles;
    // handles destroy(handle) queues once their info is set to destroy (finalize waits until it is empty) (the name
    // is not the original's)
    mm::mtl::FixedList<GF_ASSET_HANDLE*, 1024> m_destroyHandles;
    // handles updateCheckLoading has finished loading (updateCheckCacheReload walks them) (the name is not the
    // original's)
    mm::mtl::FixedList<GF_ASSET_HANDLE*, 1024> m_loadedHandles;
    // createAssetHandle's serial: a handle is the info's slot | serial << 10 (the name is not the original's)
    unsigned int m_serial;
    unsigned char pad_3391C[0x4];
    // the loaded asset packs (releaseRefResource and isExistSameAsset walk them; updateCheckDestroy and
    // updateCheckCacheReload erase from them: the erase's offsets prove 2048 nodes) (the name is not the original's)
    mm::mtl::FixedList<GfAssetPack*, 2048> m_assetPacks;
    // the asset types destroySlotCache was asked for, each once (updateCheckDestroy walks and clears them) (the name
    // is not the original's)
    mm::mtl::FixedList<GfAssetType, 32> m_list3C940;
    // made by the constructor (the name is not the original's)
    GfSlotMapping* m_slotMapping;
    // the listeners callEventAssetPack calls (1.0.0's addEvent/removeEvent fill it; 3.0.1 dropped both) (the name is
    // not the original's)
    mm::mtl::FixedList<IGfAssetEvent*, 32> m_events;
    bool m_initialized;  // initialize sets it last (1.0.0 has isInitialized()) (the name is not the original's)
    // the constructor clears it, finalize sets it first; updateCheckCacheReload reads it
    bool pad_3CCC1;
    unsigned char pad_3CCC2[0x6];
};
}  // namespace gf

#endif
