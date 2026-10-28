#ifndef CLASSES_GMK_GMKFIELDLOCK_H
#define CLASSES_GMK_GMKFIELDLOCK_H

#include "classes/gmk/GmkCollision.h"

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "plugin/Bdat.h"
namespace gmk { class GmkFieldLockGob; }

namespace gmk {
// table 0x7100B6C4E8
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
class alignas(16) GmkFieldLock : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        BdatInfo() {}  // user-provided: Vector<BdatInfo>::resize stores only the defaults (pads left)
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        unsigned short m_condition = 0;  // the row's "Condition" (a GfGameCond id; 0: none)
        unsigned char m_rockType = 0;    // the row's "rockTYPE"
        unsigned short m_txtId = 0;      // the row's "txtID"
        ScenarioFlagCond m_scenarioFlag;  // the row's ScenarioFlagMin/Max
        QuestFlagCond m_questFlag;        // the row's QuestFlag/Min/Max
    };
    virtual ~GmkFieldLock();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(12);
    unsigned char pad_48[0x8];
    // its collision (1.0.0's GmkFieldLock::createGmkCollision creates it; the name is not the original's)
    GmkCollision m_collision;
    unsigned char pad_b0[0x20];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
