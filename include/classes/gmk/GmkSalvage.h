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
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    // pops the treasures the salvage's raffle drew (GfGameSalvage::execPop)
    void popByRaffleResult();
};
}  // namespace gmk

#endif
