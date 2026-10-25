#ifndef CLASSES_GF_GFASSETMANAGER_H
#define CLASSES_GF_GFASSETMANAGER_H

#include "classes/ml/IWorkEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/fixed_size_alloc_inside.h"
#include "gf/AssetPackInfo.h"

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
namespace gf { class GfSlotMapping; }
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
    bool isFullResource(GF_ASSET_HANDLE* handle) const;
    fw::SoundPack* getSePackByFileIdx(GF_ASSET_HANDLE* handle, GfFileIdx file);
    static void setupLoadStart(GF_ASSET_HANDLE* handle);
    void setupStreamObject(GF_ASSET_HANDLE* handle);
    static void setExtendResource(GF_ASSET_HANDLE* handle, unsigned int index, GfExtendResource* resource);
    static void loadStart(GfAssetPack* pack, mm::mtl::IAllocator* allocator);
    static void releaseSlotHandle(GF_SLOT_HANDLE* handle);
    static GfSlotMapping* getSlotMapping();
    // an asset's loaded file, none while it is not loaded
    static GfAssetResource* getResource(GF_ASSET_HANDLE* handle, GfFileIdx file, GfAssetType type);
    // the asset's extend resource at an index (GfObjUtil::isExistAsm asks for 0 and casts it to GfExtendPacking)
    // the asset's motion name (GfObjUtil::getAssetMotionName returns it)
    static const char* getMotionInfo(GF_ASSET_HANDLE* handle);
    static GfExtendResource* getExtentResource(GF_ASSET_HANDLE* handle, unsigned int index);

    // the asset packs' records, one per handle: a handle's low ten bits index them (the name is not the original's)
    ml::fixed_size_alloc_inside<AssetPackInfo, 1024> m_packInfos;
    unsigned char pad_260B8[0x169C0];
    // made by the constructor (the name is not the original's)
    GfSlotMapping* m_slotMapping;
    unsigned char pad_3CA80[0x248];
};
}  // namespace gf

#endif
