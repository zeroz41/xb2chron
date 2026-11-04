#ifndef CLASSES_GF_GFFOBJMANAGER_H
#define CLASSES_GF_GFFOBJMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedList.h"
#include "gf/GfFobjGottenEffectManager.h"
#include "gf/GfFobjSeManager.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfFobjManager; }
namespace gf { class GfFobjDropitem; }
namespace gf { class GfDropitemParams; }
namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace gf { enum GEV : int; }
#include "classes/gf/IGfObjListener.h"

namespace gf {
// table 0x7100B52978; the object listener at 0x8 is what the constructor registers (GfObjManager::addListener(this +
// 8)) and the destructor removes
class GfFobjManager : public ::mm::mtl::PtrSingleton< ::gf::GfFobjManager>, public ::gf::IGfObjListener, public ::gf::IGfEvent {
public:
    typedef mm::mtl::FixedList<GfFobjDropitem*, 1024> DropitemList;  // by its symbols (the typedef's name is not the original's)

    GfFobjManager(const GfSetupParam& param);
    void initialize(const GfSetupParam& param);
    virtual ~GfFobjManager();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();
    static void update(const fw::UpdateInfo& info);
    // 2.0.0's symbols name it. What it does: sets m_leaderBonus from the party leader's driver: 0 for none; driver 12:
    // the table 0x7B member 0 row 0x5D float; else the sum of "Param1" over the driver's equipment enhances
    // (GfDataDriver::getEquipAcceEnahnce) whose "EnhanceEffect" (table 0x2C) is 0xFB, times 0.01.
    void updateEnhanceEffect();
    static GfDropitemParams* getDropitemParams();
    // 2.0.0's symbols name it. What it does: m_seManager.rebuildForGameType() (looks the sound pack up again);
    // GfFieldManager's rebuildForGameType calls it.
    void rebuildForGameType();
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
    void leaveGameField(GF_OBJ_HANDLE* handle);
    static void registFiledObj(GfFobjDropitem* item);
    static bool isExistObj();
    static void destroyObj();
    virtual void gevPlayEvent(gf::GEV, unsigned int);  // slot 3
    virtual void gevGameObjLeave(gf::GF_OBJ_HANDLE*);  // slot 4

    // the items registFiledObj takes, until their objects enter the field (the name is not the original's)
    DropitemList m_registList;
    // the items whose objects entered the field (listenerGfObj's event 2) (the name is not the original's)
    DropitemList m_fieldList;
    bool m_initialized;  // 1.0.0's isInitialized reads it
    GfDropitemParams* m_dropitemParams;  // getDropitemParams'
    unsigned char* m_dropitemListFP;   // RSC_dropitemList(Ira), once loaded (the name is not the original's)
    unsigned char* m_dropitemParamFP;  // RSC_dropitemParam, once loaded (the name is not the original's)
    bool m_eventDisp;  // what setEventDisp gets (the name is not the original's)
    // GfReqCommand::execWaitEvent ramps it from 0 to 40 over the wait's last 0.5 or 1.5 seconds, then sets 1000 and
    // 0 (GfPlayCommand's clears it too); the name is not the original's
    float m_waitEventValue;
    bool m_waitEvent;  // set while execWaitEvent ramps m_waitEventValue (the name is not the original's)
    GfFobjGottenEffectManager m_gottenEffect;  // the name is not the original's
    GfFobjSeManager m_seManager;                // the name is not the original's
    float m_leaderBonus;  // updateEnhanceEffect's (the name is not the original's)
    float m_settingValue;  // the table 0x7B member 0 row 0x49 float (the name is not the original's)
};
}  // namespace gf

#endif
