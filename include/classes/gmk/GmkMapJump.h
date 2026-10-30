#ifndef CLASSES_GMK_GMKMAPJUMP_H
#define CLASSES_GMK_GMKMAPJUMP_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkPhantom.h"
#include "plugin/Bdat.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/ScenarioFlagCond.h"
namespace gmk { class GmkMapJumpGob; }

namespace gmk {
// table 0x7100B6CEA8
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (its GmkPhantom)
class alignas(16) GmkMapJump : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        // inline: initGmkBdatInfo inlines it (no symbol); the column names are the original's, the field names not
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
            m_mapJumpId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "MapJumpId", row, 2);
            m_scenarioFlag = ScenarioFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2), (unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2));
            m_questFlag = QuestFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2), (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1),
                                        (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1));
            m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
        }
        unsigned short m_mapJumpId;  // 0x0: "MapJumpId"
        unsigned short m_condition;  // 0x2: "Condition"
        ScenarioFlagCond m_scenarioFlag;  // 0x4
        QuestFlagCond m_questFlag;  // 0x8
    };
    // user-provided: construct_n<GmkMapJump> stores the defaults below only (no zero fill of the element first)
    GmkMapJump() {}
    virtual ~GmkMapJump();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(44);
    // 0x50 (0x48..0x4f: a hole): construct_n<GmkMapJump> inlines GmkPhantom's constructor here (the name is not
    // the original's)
    GmkPhantom m_phantom;
    // two bytes (construct_n<GmkMapJump> addresses its element from 0xe1; one halfword store clears both)
    unsigned char pad_e0 = 0;
    unsigned char pad_e1 = 0;  // (0xe2..0xef: tail padding; the size: TGmkList::getInst's stride)
};
}  // namespace gmk

#endif
