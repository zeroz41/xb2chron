#ifndef CLASSES_GMK_GMKNPC_H
#define CLASSES_GMK_GMKNPC_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "classes/gmk/AGmkNpc.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/TimeCond.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkNpcGob; }
namespace mm { class Vec3; }

namespace gmk {
// table 0x7100B6DA48; secondary base AGmkNpc at 0x48 (its sub-table 0x7100B6DB08)
class GmkNpc : public ::gmk::AGmkBase, public ::gmk::AGmkNpc {
public:
    // its size: the element size of its Vector<BdatInfo>::resize (which stores these defaults); the field names
    // are not the original's: the row's column names that create reads
    class BdatInfo {
    public:
        // user-provided: Vector<BdatInfo>::resize stores the defaults only (no zeroing of the element first)
        BdatInfo() {}
        // out of line: initGmkBdatInfo calls it (symbol 0x710058E934)
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        // the row's pop conditions for the gimmick (debugDraw asks it while the gimmick is valid)
        bool isPopCommonCondMatched(const AGmkBase& gmk) const;
        unsigned short m_condition = 0;       // 0x0: "Condition" (read only when Group is 0)
        unsigned short m_group = 0;           // 0x2: "Group"
        unsigned short m_battleReaction = 0;  // 0x4: "BattleReaction"
        ScenarioFlagCond m_scenarioFlag;      // 0x6: "ScenarioFlagMin/Max"
        QuestFlagCond m_questFlag;            // 0xA: "QuestFlag/Min/Max"
        TimeCond m_timeRange;                 // 0x10: "TimeRange"
        float m_visibleXZSq = 0.0f;           // 0x20: "Visible_XZ" squared
        float m_visibleYSq = 0.0f;            // 0x24: "Visible_Y" squared
        float m_invisibleXZSq = 0.0f;         // 0x28: "Invisible_XZ" (at least Visible_XZ + 1) squared
        float m_invisibleYSq = 0.0f;          // 0x2C: "Invisible_Y" (at least Visible_Y + 1) squared
    };
    virtual ~GmkNpc();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual bool isPopCondMatched() const;  // slot 11
    virtual void isDepopCondMatched() const;  // slot 12
    virtual void vf4();  // slot 13 (AGmkNpc slot 4)
    virtual void vf5();  // slot 14 (AGmkNpc slot 5)
    virtual unsigned char* getBindedBdatFp() const;  // slot 15
    virtual int getBindedBdatId() const;  // slot 16
    virtual bool findPopPosRot(mm::Vec3&, mm::Vec3&) const;  // slot 17
    virtual void bindToGameObj(gf::GF_OBJ_HANDLE*) const;  // slot 18
    virtual void unbindToGameObj(gf::GF_OBJ_HANDLE*) const;  // slot 19
    virtual void validateDisp() const;  // slot 20
    virtual void debugUpdate(float) {}  // slot 21
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(3);
    gf::GF_OBJ_HANDLE* getGobInst() const;  // its game object (-1: none)
    // user-provided: Vector<GmkNpc>::resize stores the defaults below only (no zero fill of the element first)
    GmkNpc() {}
    unsigned char pad_68 = 1;
    unsigned char pad_69 = 1;  // fields: size from TGmkList::getInst's stride (0x70)
};
}  // namespace gmk

#endif
