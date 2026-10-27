#ifndef CLASSES_GMK_GMKMAPGIMMICK_H
#define CLASSES_GMK_GMKMAPGIMMICK_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gmk/WeatherCond.h"
#include "classes/gmk/BootedGmkCond.h"
class CBdatWrapper;

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// table 0x7100B6CB08
class GmkMapGimmick : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize (0x7100632548 allocates count * 0x38; TGmkList<GmkMapGimmick>::~TGmkList (0x71005C74F4) frees the buffer with no destructor loop); the fields are not read yet
    class BdatInfo {
    public:
        // user-provided: Vector<BdatInfo>::resize stores the defaults only (no zeroing of the pads first)
        BdatInfo() {}
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isPopCondMatched() const;
        unsigned short m_condition = 0;   // the row's "Condition" (a GfGameCond id; 0: none)
        unsigned short m_nameRadius = 5;  // the row's "nameRadius"
        unsigned short m_mapobjId = 0;    // the row's "mapobjID"
        unsigned short m_effectId = 0;    // the row's "effectID" (only when GfGameManager::fn_71002A9E68())
        bool m_msgRay = false;            // flag "MSG_ray"
        TimeCond m_popTime;        // the row's "popTime"
        WeatherCond m_popWeather;  // the row's "popWeather"
        BootedGmkCond m_bootedGmk;  // the row's OP_gimmickType/ID
    };
    virtual ~GmkMapGimmick();  // slot 0
    void setSolved() const;
    void validateEffectWithoutLodControl(int lodId, bool flag) const;
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x21);
    unsigned char pad_48[0x68];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
