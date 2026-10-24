#ifndef CLASSES_GF_GFMAPMANAGER_H
#define CLASSES_GF_GFMAPMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfMapManager; }
namespace fw { class EffectPack; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }
#include "classes/gf/IGfObjListener.h"

namespace gf {
// a base of gf::GfMapManager no evidence names yet
class TUnk_B595B0 {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
};
// table 0x7100B59580; base at 0x8 unknown (TUnk_B595B0)
class GfMapManager : public ::mm::mtl::PtrSingleton< ::gf::GfMapManager>, public TUnk_B595B0, public ::gf::IGfEvent {
public:
    // SCOM_DESTROY_MAP_OBJ's request
    static void destroyObj();
    // the pack at 0x48 (the type: GfFieldManager::getEffectPack's callers hand it to fw::EffectManager::create)
    static fw::EffectPack* getEffectPack();
    static const char* getMapName();  // the current map's name, none when there is none
    static void setEnvTime(unsigned int hour, unsigned int min);  // GfFieldManager::update passes GfFieldTime's
    static void build(const GfSetupParam& param);
    static void destroy();
    void update(const fw::UpdateInfo& info);
    void postUpdate(const fw::UpdateInfo& info);
    virtual ~GfMapManager();  // slot 0
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 3
};
}  // namespace gf

#endif
