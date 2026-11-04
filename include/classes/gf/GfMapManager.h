#ifndef CLASSES_GF_GFMAPMANAGER_H
#define CLASSES_GF_GFMAPMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/gf/IGfObjListener.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/MapEff.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace fw { class DynamicWindResource; }
namespace fw { class ModelObject; }
namespace fw { class ColiObject; }
namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfMapManager; }
namespace fw { class EffectPack; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }
namespace mm { class Vec3; }

namespace gf {
// table 0x7100B59580; the object listener at 0x8 is what the constructor registers (GfObjManager::addListener(this +
// 8)) and the destructor removes, the event listener at 0x10 what the constructor adds (GfEvent::addEventCallback)
// and destroy removes. Builds the map's parts (effects, navigation, collision, lights, wind) when the map's object
// is set up and destroys them with it.
class GfMapManager : public ::mm::mtl::PtrSingleton< ::gf::GfMapManager>, public ::gf::IGfObjListener, public ::gf::IGfEvent {
public:
    // 1.0.0's; 3.0.1's build inlines it (its copy is dropped)
    GfMapManager(const GfSetupParam& param);
    void initialize(const GfSetupParam& param);  // 1.0.0's: adds the event listener
    void finalize();  // 1.0.0's: destroys the map's object, waits for it to go, removes the event listener
    virtual ~GfMapManager();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle, unsigned int flag);  // slot 2
    static void buildMapData(GF_OBJ_HANDLE* handle);
    void destroyMapData(GF_OBJ_HANDLE* handle);
    static fw::ModelObject* getModelObject();  // the map object's model (its GfComModel's)
    static GF_OBJ_HANDLE* getGfObjHandle();
    // SCOM_DESTROY_MAP_OBJ's request
    static void destroyObj();
    static bool isMapReady();
    static bool isExistObj();
    static unsigned int getMapJumpID();
    static unsigned int getMapID();
    // the pack at 0x48 (the type: GfFieldManager::getEffectPack's callers hand it to fw::EffectManager::create)
    static fw::EffectPack* getEffectPack();
    static void setEnvTime(unsigned int hour, unsigned int min);  // GfFieldManager::update passes GfFieldTime's
    // 2.0.0's symbols spell the float, which goes on to fw::RenderParam::setWeather
    static void setEnvWeather(unsigned int weather, float sec);
    static void setGlobalIBLReferencePos(const mm::Vec3& pos);
    virtual void gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const& info);  // slot 3
    static const char* getMapName();  // the current map's name, none when there is none
    void createWind();
    static fw::ColiObject* getColiObject();  // the ground collision's, none without a manager
    void postUpdate(const fw::UpdateInfo& info);
    void update(const fw::UpdateInfo& info);

    bool m_initialized;              // the event listener is added
    GF_OBJ_HANDLE* m_handle;         // the map's object (listenerGfObj keeps the one whose setup is the map's)
    unsigned int m_mapJumpID;        // gevMapjump's (getMapJumpID)
    unsigned int m_mapID;            // gevMapjump's (getMapID)
    GF_ASSET_HANDLE* m_assetHandle;  // the map object's asset, the parts are made from
    mm::mtl::IntrusivePtr<fw::DynamicWindResource> m_wind;  // createWind's, spanning the ground's bounds
    MapEff m_eff;
    MapNavi m_navi;
    MapColi m_coli;
    MapGIBL m_gibl;
    MapLIBL m_libl;
};
}  // namespace gf

#endif
