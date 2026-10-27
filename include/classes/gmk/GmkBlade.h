#ifndef CLASSES_GMK_GMKBLADE_H
#define CLASSES_GMK_GMKBLADE_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/TimeCond.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkBladeGob; }

namespace gmk {
// table 0x7100B6E108
class GmkBlade : public ::gmk::AGmkBase {
public:
    // a gimmick row (its size: the element size of its Vector<BdatInfo>::resize)
    class BdatInfo {
    public:
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isPopCommonCondMatched() const;
        // GfGmkBladeTraverser::onTraverse compares it with its own; the row's "BladeSizeCheck" (the field names are
        // not the original's: the row's column names)
        unsigned char m_kind;  // 0x0
        unsigned short m_condition;       // 0x2: "Condition"
        unsigned short m_battleReaction;  // 0x4: "BattleReaction" (1: not in a battle)
        ScenarioFlagCond m_scenarioFlag;  // 0x6
        TimeCond m_timeRange;    // 0x10: "TimeRange"
        float m_visibleXZSq;     // 0x20: "Visible_XZ" squared
        float m_visibleYSq;      // 0x24: "Visible_Y" squared
        float m_invisibleXZSq;   // 0x28: "Invisible_XZ" (at least Visible_XZ + 1) squared
        float m_invisibleYSq;    // 0x2C: "Invisible_Y" (at least Visible_Y + 1) squared
    };
    virtual ~GmkBlade();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(47);
    // its game object (dispose clears its user data, destroys it and stores -1; the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gob;  // fields: size from TGmkList::getInst's stride
    // GfGmkBladeTraverser::onTraverse compares it with its id, or with 1001 and 1002 (the name is not the original's)
    int m_bladeId;  // 0x50
    unsigned char pad_54[0x4];
};
}  // namespace gmk

#endif
