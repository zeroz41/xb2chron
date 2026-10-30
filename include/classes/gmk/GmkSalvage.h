#ifndef CLASSES_GMK_GMKSALVAGE_H
#define CLASSES_GMK_GMKSALVAGE_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// table 0x7100B6C990
class GmkSalvage : public ::gmk::AGmkBase {
public:
    // its size: the element size of Vector<BdatInfo>::resize 0x710063195C (zero-filled); initGmkBdatInfo fills it
    class BdatInfo {
    public:
        // inline: TGmkList::initGmkBdatInfo has no call of it
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
            m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
        }
        bool isCondMatched() const;
        unsigned short m_condition;  // the row's "Condition" (a GfGameCond id; 0: none)
    };
    virtual ~GmkSalvage();  // slot 0
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    // its kind (TGmkList<GmkSalvage>::getGmkType returns 31; GmkSet::createGmkLists puts GmkSalvageList at index 31; the
    // name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(31);
    // pops the treasures the salvage's raffle drew (GfGameSalvage::execPop)
    void popByRaffleResult();

    unsigned char pad_48[0xe1];
    unsigned char pad_129;  // GmkSalvageLocator::syncDepopTboxes sets it to 1, its dispose sets it too
    unsigned char pad_12a[0x6];  // size 0x130: TGmkList<GmkSalvage>::getInst's stride
};
}  // namespace gmk

#endif
