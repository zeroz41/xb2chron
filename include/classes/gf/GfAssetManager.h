#ifndef CLASSES_GF_GFASSETMANAGER_H
#define CLASSES_GF_GFASSETMANAGER_H

#include "classes/ml/IWorkEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace gf { class GfAssetManager; }
namespace gf { class AssetPackInfo; }
namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GfInitParam; }
namespace gf { class GfAssetResource; }

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
    static unsigned int getUsedAssetPackInfo();
    static void build(const GfSetupParam& param);
    static void destroy();
    void update(const fw::UpdateInfo& info);
    virtual ~GfAssetManager();  // slot 0
    static void clear();
    // GfAssetSetup's destructor hands it the setup's handle
    static void lockEnterRersource(GF_ASSET_HANDLE* handle);
    static GF_ASSET_HANDLE* createAssetHandle(const GfInitParam& param);
    static AssetPackInfo* getAssetPackInfo(GF_ASSET_HANDLE* handle);
    // an asset's loaded file, none while it is not loaded
    static GfAssetResource* getResource(GF_ASSET_HANDLE* handle, GfFileIdx file, GfAssetType type);
};
}  // namespace gf

#endif
