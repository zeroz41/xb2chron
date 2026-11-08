#ifndef CLASSES_GMK_GMKCLIMBING_H
#define CLASSES_GMK_GMKCLIMBING_H

#include "classes/gmk/AGmkBase.h"
#include "mm/Vec3.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/BootedGmkCond.h"
#include "classes/gf/GfMenuCallContext.h"
class CBdatWrapper;
namespace gmk { class GmkClimbingGob; }

namespace gmk {
// table 0x7100B6E0A0
// 16-aligned through m_iconPos (TGmkList::createGmk reserves its Vector with alignment 16)
class alignas(16) GmkClimbing : public ::gmk::AGmkBase {
public:
    // its size: the element size of Vector<BdatInfo>::resize 0x710061F874 (whose constructor sets its fields; their defaults are not written yet)
    class BdatInfo {
    public:
        // user-provided: Vector<BdatInfo>::resize stores the defaults only (no zeroing of the pads first)
        BdatInfo() {}
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isPopCondMatched() const;
        unsigned short m_condition = 0;       // the row's "Condition" (a GfGameCond id; 0: none)
        unsigned short m_climiconRadius = 3;  // the row's "climiconRadius"
        ScenarioFlagCond m_scenarioFlag;      // the row's ScenarioFlagMin/Max
        QuestFlagCond m_questFlag;            // the row's QuestFlag/Min/Max
        BootedGmkCond m_bootedGmk;            // the row's OP_gimmickType/ID
    };
    virtual ~GmkClimbing();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    // the row (as in the sibling gimmicks; the name is not the original's)
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    void createIcon();
    void updateIcon();
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(46);
    // user-provided: Vector<GmkClimbing>::resize stores the defaults below only (no zero fill of the element first)
    GmkClimbing() {}
    // 0x48: its field icon's menu call context, held while the icon is open (createIcon creates it and opens
    // GfMenuObjFieldIcon with it; dispose closes the icon and releases it; the name is not the original's)
    gf::GfMenuCallContext* m_iconContext = nullptr;
    // 0x50: where the icon shows: create copies the gimmick's position and raises it by a GIMMICK parameter (the
    // 16-aligned field: resize copies Vec3::zero's x, y, z; size 0x60, the stride; the name is not the original's)
    mm::Vec3 m_iconPos = mm::Vec3::zero;
};
}  // namespace gmk

#endif
