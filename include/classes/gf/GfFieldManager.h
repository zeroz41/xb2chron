#ifndef CLASSES_GF_GFFIELDMANAGER_H
#define CLASSES_GF_GFFIELDMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/gf/IGfObjListener.h"
#include "classes/gf/GfObjManager.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace fw { class EffectPack; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfFieldManager; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }
namespace gf { enum RELOAD_BDAT : int; }
namespace mm { class Vec3; }

namespace gf {
// table 0x7100B51F08; the object listener at 0x8 is what the constructor registers (GfObjManager::addListener(this +
// 8)) and the destructor removes, the event listener at 0x10 what initialize adds (GfEvent::addEventCallback) and
// finalize removes. Builds and destroys the field's managers and forwards the game's events and updates to them.
class GfFieldManager : public ::mm::mtl::PtrSingleton< ::gf::GfFieldManager>, public ::gf::IGfObjListener, public ::gf::IGfEvent {
public:
    // inline: 3.0.1 has no copy of it (build inlines it)
    GfFieldManager(const GfSetupParam& param) : m_initialized(false), m_enemyBaloonRadius(0.0f) {
        initialize(param);
        GfObjManager::addListener(this, static_cast<IGfObjListener::OBJEVT>(0));
    }
    void initialize(const GfSetupParam& param);
    virtual ~GfFieldManager();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();
    static void clear();
    static void setupGame();
    // 2.0.0's symbols name it. What it does: calls GfFobjManager::rebuildForGameType on GfFobjManager's instance when
    // there is one; tl::TitleStateChangeGameType's update calls it on the instance (x0 is the instance it tested), so
    // a member, not static.
    void rebuildForGameType();
    void setSuspendGame(bool suspend);
    static bool isExistObj();
    // SCOM_DESTROY_FIELD_OBJ's request
    static void destroyObj();
    static fw::EffectPack* getEffectPack();
    static bool execMapScript(const char* name);
    static void destroyMapScript();
    static bool isExecMapScriptBusy();
    static bool isDestroyMapScriptBusy();
    static float getEnemyBaloonRadius();
    static const char* getMapName();  // the current map's name, none when there is none
    static bool getLandmarkNameId(unsigned char*& bdat, int& id);  // the current location's name in a message table
    // 1.0.0's name and arguments (its body stores the same fields; 3.0.1's skips map 0x3A)
    static void setLandmarkPoint(unsigned int point, const mm::Vec3& pos, float rotY);
    static unsigned int getLandmarkPoint();
    static const mm::Vec3& getLandmarkPos();
    static float getLandmarkRotY();
    void postUpdate(const fw::UpdateInfo& info);
    void update(const fw::UpdateInfo& info);
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 3
    virtual void gevReloadBdat(gf::RELOAD_BDAT, unsigned int);  // slot 4
    virtual void gevBattleStart();  // slot 5
    virtual void gevBattleEnd();  // slot 6
    virtual void gevGameMapModel(gf::GF_OBJ_HANDLE*, bool);  // slot 7
    virtual void gevPause(unsigned int, unsigned int);  // slot 8
    virtual void gevPlayEvent(gf::GEV, unsigned int);  // slot 9

    bool m_initialized;  // 0x18: initialize sets it as it ends, finalize clears it (the name is not the original's)
    // 0x1C: the current map's FLD_maplist balloondisp_r (named after getEnemyBaloonRadius; not the original's name)
    float m_enemyBaloonRadius;
};
}  // namespace gf

#endif
