#ifndef CLASSES_GMK_GMKDOOR_H
#define CLASSES_GMK_GMKDOOR_H

#include "mm/mtl/RTTI.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/BootedGmkCond.h"
class CBdatWrapper;
#include "classes/gmk/IGmkPhantomEventListener.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
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
        unsigned long m_openCamGimId = 0;       // the row's "open_camGim_ID" (column type 7)
        unsigned char m_openCamGimAtr = 0;      // the row's "open_camGim_ATR"
        bool m_closeLodAnime = false;           // flag "close_LODanime"
        bool m_closeSeType = false;             // flag "close_SE_type"
        unsigned char pad_1b;
        unsigned short m_closeSe = 0;           // the row's "close_SE"
        unsigned char m_closeSeSize = 10;       // the row's "close_SE_size"
        unsigned char pad_1f;
        unsigned long m_closeCamGimId = 0;      // the row's "close_camGim_ID" (column type 7)
        unsigned char m_closeCamGimAtr = 0;     // the row's "close_camGim_ATR"
        unsigned char pad_29[0x3];
        float m_doorNextwait = 0.0f;            // the row's "door_nextwait"
        unsigned long m_spCloseCamGimId = 0;    // the row's "sp_close_camGim_ID" (column type 7)
        unsigned char m_spCloseCamGimAtr = 0;   // the row's "sp_close_camGim_ATR"
        bool m_gmkCamPos = false;               // flag "gmkCamPos"
        BootedGmkCond m_bootedGmk;   // the row's OP_gimmickType/ID (isPopCondMatched tests it)
        BootedGmkCond m_bootedGmk2;  // two more <prefix>gimmickType/ID pairs (prefixes not read yet)
        BootedGmkCond m_bootedGmk3;
    };
    virtual ~GmkDoor();  // slot 0
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
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(41);
    unsigned char pad_58[0x308];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
