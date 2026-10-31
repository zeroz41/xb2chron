#ifndef CLASSES_GMK_GMKDOOR_H
#define CLASSES_GMK_GMKDOOR_H

#include "mm/mtl/RTTI.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/BootedGmkCond.h"
class CBdatWrapper;
#include "classes/gmk/IGmkPhantomEventListener.h"
#include "classes/gmk/GmkCamera.h"
#include "classes/gmk/GmkPhantom.h"
#include "classes/gmk/GmkPhantomSimple.h"
#include "classes/gmk/GmkCtrlVolSe.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
#include "classes/gf/GfGameFlag.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
namespace gmk { class GmkDoorGob; }

namespace gmk {
// a base of gmk::GmkDoor no evidence names yet
class TUnk_B6CDB0 {
public:
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) = 0;
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&) = 0;
};
// a base of gmk::GmkDoor no evidence names yet
class TUnk_B6CDD0 {
public:
    virtual const mm::mtl::RTTI* getRTTI() const = 0;
};
// table 0x7100B6CD30; base at 0x48 unknown (TUnk_B6CDB0), base at 0x50 unknown (TUnk_B6CDD0)
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
class alignas(16) GmkDoor : public ::gmk::AGmkBase, public TUnk_B6CDB0, public TUnk_B6CDD0 {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        // user-provided: Vector<BdatInfo>::resize stores the defaults only (no zeroing of the pads first)
        BdatInfo() {}
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isPopCondMatched() const;
        // 1.0.0 has these three out of line (gmk::GmkDoor::BdatInfo::isGfObjMustExist() etc.); 3.0.1 inlines them
        // (update, create)
        bool isGfObjMustExist() const {
            if (m_lodModel == 0) {
                return false;
            }
            switch (m_responseType) {
            case 1:
            case 2:
            case 5:
            case 6:
                return true;
            default:
                return false;
            }
        }
        bool isPhantomMustExist() const {
            if (m_lodModel == 0) {
                return false;
            }
            switch (m_responseType) {
            case 3:
            case 4:
            case 6:
            case 7:
                return true;
            default:
                return false;
            }
        }
        // defined inline in the unit (it reads GfFieldGimmick)
        inline bool isLoadSaveData() const;
        unsigned short m_condition = 0;         // the row's "Condition" (a GfGameCond id; 0: none)
        unsigned char m_responseType = 0;       // the row's "response_type"
        unsigned char m_responseChr = 0;        // the row's "response_CHR"
        unsigned short m_nameRadius = 0;        // the row's "nameRadius"
        unsigned short m_lodModel = 0;          // the row's "LODmodel"
        unsigned short m_missMsgId = 0;         // the row's "missMSG_ID"
        bool m_openLodAnime = false;            // flag "open_LODanime"
        bool m_openSeType = false;              // flag "open_SE_type"
        unsigned short m_openSe = 0;            // the row's "open_SE"
        unsigned char m_openSeSize = 10;        // the row's "open_SE_size"
        unsigned char pad_f;
        const char* m_openCamGimId = nullptr;   // the row's "open_camGim_ID" (column type 7: a string)
        unsigned char m_openCamGimAtr = 0;      // the row's "open_camGim_ATR"
        bool m_closeLodAnime = false;           // flag "close_LODanime"
        bool m_closeSeType = false;             // flag "close_SE_type"
        unsigned char pad_1b;
        unsigned short m_closeSe = 0;           // the row's "close_SE"
        unsigned char m_closeSeSize = 10;       // the row's "close_SE_size"
        unsigned char pad_1f;
        const char* m_closeCamGimId = nullptr;  // the row's "close_camGim_ID" (column type 7: a string)
        unsigned char m_closeCamGimAtr = 0;     // the row's "close_camGim_ATR"
        unsigned char pad_29[0x3];
        float m_doorNextwait = 0.0f;            // the row's "door_nextwait"
        const char* m_spCloseCamGimId = nullptr;  // the row's "sp_close_camGim_ID" (column type 7: a string)
        unsigned char m_spCloseCamGimAtr = 0;   // the row's "sp_close_camGim_ATR"
        bool m_gmkCamPos = false;               // flag "gmkCamPos"
        BootedGmkCond m_bootedGmk;   // the row's gimmickType/ID, no prefix (isPopCondMatched tests it)
        BootedGmkCond m_bootedGmk2;  // the row's OP_gimmickType/ID
        BootedGmkCond m_bootedGmk3;  // the row's SPOP_gimmickType/ID
    };
    // inline: Vector<GmkDoor>::resize builds each in place (its camera with no CreateInfo)
    GmkDoor() : m_camera(nullptr) {}
    virtual ~GmkDoor();  // slot 0
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 11
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&);  // slot 12
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&);  // slot 13
    static mm::mtl::RTTI m_rtti;
    // its state, kept in the local game flag getGameFlagId() (setProgress picks the sequence step by it: 0
    // seqDoor_BeforeBoot, 1 seqDoor_Booted, 2 seqDoor_Shutdowned, 3 seqDoor_SpBooted)
    enum Progress : int {};
    // the switch setLodSwitch gives the LOD model's switch parts (0 and 1: switch id 2, 2: switch id 1)
    enum LodSwitch : int {};
    // 1.0.0 has these out of line (the same names); 3.0.1 inlines them into their callers
    int getGameFlagId() const { return m_createInfo.m_bdatId + 38070; }
    Progress getProgress() const { return Progress(gf::GfGameFlag::getLocal(2, getGameFlagId())); }
    bool isLocked() const {
        const BdatInfo* info = getBdatInfo();
        // the original tests the condition's fields off the row, not through BootedGmkCond::isSet
        return info->m_responseType == 5 || (info->m_bootedGmk2.m_gimmickType != 0 &&
                                             info->m_bootedGmk2.m_gimmickId != 0 && !info->m_bootedGmk2.isMatch());
    }
    bool isSpLocked() const {
        const BdatInfo* info = getBdatInfo();
        return info->m_bootedGmk3.m_gimmickType != 0 && info->m_bootedGmk3.m_gimmickId != 0 &&
               !info->m_bootedGmk3.isMatch();
    }
    void validateLocSwitchState() {
        LodSwitch lodSwitch;
        switch (getProgress()) {
        case 0:
        case 2:
            lodSwitch = isLocked() ? LodSwitch(0) : LodSwitch(2);
            break;
        case 1:
            lodSwitch = isSpLocked() ? LodSwitch(1) : LodSwitch(2);
            break;
        case 3:
            lodSwitch = LodSwitch(2);
            break;
        default:
            lodSwitch = LodSwitch(0);
            break;
        }
        setLodSwitch(lodSwitch);
    }
    void spBootGmk(bool anim, bool camera) {
        if (getProgress() == 3) {
            return;
        }
        const BdatInfo* info = getBdatInfo();
        if (info->m_openLodAnime) {
            openDoor(anim);
        } else {
            closeDoor(anim);
        }
        createGmkCamera(info->m_spCloseCamGimId, info->m_spCloseCamGimAtr, camera);
        m_doorWait = anim ? info->m_doorNextwait : 0.0f;
        setProgress(Progress(3));
    }
    void shutdownGmk(bool anim, bool camera) {
        if (getProgress() == 2) {
            return;
        }
        const BdatInfo* info = getBdatInfo();
        if (info->m_closeLodAnime) {
            closeDoor(anim);
        } else {
            openDoor(anim);
        }
        createGmkCamera(info->m_closeCamGimId, info->m_closeCamGimAtr, camera);
        setProgress(Progress(2));
    }
    void disposeGmkCamera() { m_camera.dispose(); }
    void disposeGfObjHandle() {
        if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            gf::GfObjAcc acc(m_gob);
            if (acc.m_obj != nullptr) {
                acc.setUserData(gf::GfObjUserData(0), 0);
            }
            gf::GfObjUtil::destroy(m_gob);
            m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        }
    }
    void pollBootGmk() {
        if (!pad_2b1 && !m_phantom.pad_83) {
            return;
        }
        switch (getBdatInfo()->m_responseType) {
        case 3:
        case 4:
        case 7:
            break;
        default:
            return;
        }
        const BdatInfo* info = getBdatInfo();
        if (info->m_bootedGmk2.isSet() && !info->m_bootedGmk2.isMatch()) {
            return;
        }
        bootGmk(false, true);
    }
    // defined inline in the unit (it reads GfFieldSound and SoundManager)
    inline bool isSeLoop(bool mapPack, unsigned short se) const;
    void setProgress(Progress progress);
    void seqDoor_BeforeBoot(float dt);
    void setLodSwitch(LodSwitch lodSwitch);
    void openDoor(bool anim);
    void closeDoor(bool anim);
    void bootGmk(bool anim, bool camera);
    void createGfObjHandle();
    void createGmkPhantom();
    void createGmkCamera(const char* name, unsigned char attr, bool play);
    void createSe(bool mapPack, unsigned short se, unsigned char size);
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(41);
    void seqDoor_Booted(float dt);
    void seqDoor_Shutdowned(float dt);
    void seqDoor_SpBooted(float dt);
    void disposeGmkPhantom();
    unsigned char pad_58[0x8];
    // 0x60, 0x1c0, 0x250, 0x2e0: the destructor destroys them in reverse (the names are not the original's)
    GmkCamera m_camera;
    GmkPhantom m_phantom;
    GmkPhantomSimple m_phantomSimple;
    // 0x2b0: cleared by update after it copied it to 0x2b1 (pollBootGmk tests 0x2b1; meaning not known)
    bool pad_2b0;
    bool pad_2b1;
    unsigned char pad_2b2[0x6];
    // 0x2b8: its game object (onGobEvent forgets it when it goes away; -1: none; the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gob;
    float m_doorWait;  // 0x2c0: seqDoor_SpBooted counts it up to the row's door_nextwait (the name is not the original's)
    unsigned char pad_2c4[0x4];
    // 0x2c8: the sequence step update runs (setProgress sets it; the name is not the original's)
    void (GmkDoor::*m_seq)(float dt);
    unsigned char pad_2d8[0x8];
    GmkCtrlVolSe m_ctrlVolSe;  // 0x2e0; size 0x360 from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
