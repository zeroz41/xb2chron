#ifndef CLASSES_GF_GFFIELDGIMMICK_H
#define CLASSES_GF_GFFIELDGIMMICK_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/IGfEvent.h"
#include "classes/gf/IGfObjListener.h"
#include "classes/gf/GfGmkLocatorAtlas.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/GmkAccManager.h"
#include "classes/gmk/GmkDoorPhantomManager.h"
#include "classes/gmk/GmkDmgPhantomManager.h"
#include "classes/gmk/GmkAntiBladeAreaManager.h"
#include "classes/gmk/GmkCtrlVolSeManager.h"
#include "classes/gf/GfAllocator.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/Map.h"

namespace gf { class GfSetupParam; class MapjumpCallbackInfo; class GF_OBJ_HANDLE; class GF_SLOT_HANDLE; enum GEV : int; enum RELOAD_BDAT : int; enum ActivateType : int; }
namespace fw { class UpdateInfo; }

namespace gf {
// the mob slots (GfFieldGimmick holds one at 0xF940; its update and createMobInfos are gf_field_gimmick's)
// table-less; constructed and destroyed inline in GfFieldGimmick's constructor and destructor (1.0.0 has its
// constructor and disposeMobInfos out of line)
class GfMobSlotManager {
public:
    // one mob slot and its squared distance (createMobInfos pushes them; the names are not the original's)
    struct MobInfo {
        GF_SLOT_HANDLE* m_handle;
        float m_distSq;
    };

    GfMobSlotManager() : m_popDistSqLimit(1.0e12f) {
        m_slotDistSqs.setAllocator(getAllocator(ALLOCATOR(0)));
    }
    ~GfMobSlotManager() {
        disposeMobInfos();
    }

    void disposeMobInfos() {
        m_mobInfos.clear();
    }
    bool addFailedPopDistSq(float distSq);
    void update();
    void createMobInfos();

    mm::mtl::FixedVector<MobInfo, 64> m_mobInfos;  // 0x0 (the names of the fields are not the original's)
    mm::mtl::Map<GF_SLOT_HANDLE*, float> m_slotDistSqs;  // 0x408
    // ascending (addFailedPopDistSq inserts each before the first that is not smaller)
    mm::mtl::FixedVector<float, 64> m_failedPopDistSqs;  // 0x420
    // createMobInfos sets it to the last failed distance, or 0 when there are more mobs than GfObj capacity
    float m_popDistSqLimit;  // 0x528
};
}  // namespace gf

namespace gf {
// static helpers of gf_field_gimmick.cpp (only the ones gf_field_locator calls are declared)
// a PtrSingleton: GfPlayComEventFade reaches it through PtrSingleton<GfFieldGimmick>::sys()
// table 0x7100B51738; bases at 0x8 (IGfObjListener) and 0x10 (IGfEvent)
class GfFieldGimmick : public ::mm::mtl::PtrSingleton< ::gf::GfFieldGimmick>, public ::gf::IGfObjListener, public ::gf::IGfEvent {
public:
    GfFieldGimmick(const GfSetupParam& param);
    // the key function: the table is emitted here
    virtual ~GfFieldGimmick();  // slot 0
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 3
    virtual void gevBladeActivate(unsigned int, gf::ActivateType, gf::ActivateType);  // slot 4
    // IGfEvent's slot 36 (its thunk sits there in the IGfEvent part of the table); new in 3.0.1
    virtual void gevPlayEvent(gf::GEV, unsigned int);  // slot 5
    // 1.0.0's out-of-line members, inline in 3.0.1 (its constructor and destroy hold their code)
    void initialize(const GfSetupParam& param);
    void finalize();
    // the FLD_maplist id of the map an RSC_GmkSetList row belongs to
    static int getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(int gmkSetId);
    static int getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(int mapId);
    static int getBdatIdOfActiveGmkAntiBladeArea();  // GfGameUtil::getAntiBladeAreaBdatId forwards here
    // whether the map's gimmick sets are ready (GfAutoTalkManager::seqInit waits for it)
    static bool isGmkSetReady();
    // SCOM_CREATE_GMK_SET / SCOM_DESTROY_GMK_SET's exec pass their gimmick set id
    static bool createGmkSet(int gmkSetId);
    static void disposeGmkSet(int gmkSetId);
    // GfFieldManager's forwards (its initialize, finalize and update call them)
    static void build(const GfSetupParam& param);
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has GmkCtrlVolSeManager::update(float)
    // directly followed by GfFieldGimmick::createGmkSet). A member because its unit's functions are GfFieldGimmick's
    // (it sits before createGmkSet). What it does: nothing (a bare return); GfFieldManager::postUpdate calls it last,
    // passing its fw::UpdateInfo.
    static void fn_710026B74C(const fw::UpdateInfo& info);
    unsigned char pad_18[0x8];
    gmk::GmkManager m_gmkMgr;  // 0x20 (the name is not the original's)
    unsigned char pad_F3A0[0x10];
    gmk::GmkAccManager m_accMgr;  // 0xF3B0 (the names of the managers are not the original's)
    gmk::GmkDoorPhantomManager m_doorPhantomMgr;  // 0xF3E8
    gmk::GmkDmgPhantomManager m_dmgPhantomMgr;  // 0xF418
    unsigned char pad_F428[0x30];
    gmk::GmkAntiBladeAreaManager m_antiBladeAreaMgr;  // 0xF458
    gmk::GmkCtrlVolSeManager m_ctrlVolSeMgr;  // 0xF480
    // cleared by the constructor (its use is not known; the name is not the original's)
    bool m_unknownFlag0;  // 0xF4A0
    unsigned char pad_F4A1[0x7];
    // set by initialize, cleared by finalize (1.0.0's isInitialized returns it; the name is not the original's)
    bool m_initialized;  // 0xF4A8
    unsigned char pad_F4A9[0x3];
    // an event fade's state: the destructor clears m_active alone (it destroys this between the locator atlas
    // and the volume SE manager; the names are not the original's)
    struct EventFade {
        EventFade() : m_active(false), m_gmkUpdated(false), m_viewReady(false), m_time(0.0f) {}
        ~EventFade() {
            m_active = false;
        }
        // an event fade is running: GfPlayComEventFade's update sets it as it starts the fade, its end() clears it
        bool m_active;  // 0xF4AC
        // set once the gimmick manager's immediate update has gone through, then the view is waited for (update)
        bool m_gmkUpdated;  // 0xF4AD
        // the view is valid, or 10 seconds of the fade have passed (update)
        bool m_viewReady;  // 0xF4AE
        float m_time;  // 0xF4B0: the fade's time so far (update adds each frame's step)
    };
    EventFade m_eventFade;  // 0xF4AC
    unsigned char pad_F4B4[0xC];
    // the locator atlas of the menus' maps (GfMenuObjWorldMap::update updates it, finalize recreates it from its
    // own CreateInfo; the name is not the original's). Its constructor runs at 0xF4C0 in GfFieldGimmick's.
    GfGmkLocatorAtlas m_locatorAtlas;  // 0xF4C0
    GfMobSlotManager m_mobSlotMgr;  // 0xF940
    // the constructor sets these four as one word (0, 1, 1, 1); the other three's uses are not known (the names are
    // not the original's)
    bool m_unknownFlag1;  // 0xFE70
    // GfGameManager::isEnableOpenMainMenu answers false while it is clear; update sets it to whether the player's
    // position is savable (GfGameUtil::isPointSavable; the name is not the original's)
    bool m_enableOpenMainMenu;  // 0xFE71
    bool m_unknownFlag2;  // 0xFE72
    bool m_unknownFlag3;  // 0xFE73
    unsigned char pad_FE74[0xC];
};
}  // namespace gf

#endif
