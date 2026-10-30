#ifndef CLASSES_GMK_GMKEFFECT_H
#define CLASSES_GMK_GMKEFFECT_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/ScenarioFlagCond.h"
namespace gmk { class GmkEffectGobCustom; }

namespace gmk {
// table 0x7100B6C550
class GmkEffect : public ::gmk::AGmkBase {
public:
    // 10 bytes: Vector<BdatInfo>::expand copies n*10; the stores are initGmkBdatInfo's (0x71005E8AF4)
    class BdatInfo {
    public:
        // inline: initGmkBdatInfo inlines it (no symbol); the column names are the original's, the field names not
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
            m_scenarioFlag = ScenarioFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2), (unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2));
            m_questFlag = QuestFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2), (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1),
                                        (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1));
            m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
        }
        unsigned short m_condition;  // 0x0: "Condition"
        ScenarioFlagCond m_scenarioFlag;  // 0x2
        QuestFlagCond m_questFlag;  // 0x6
    };
    virtual ~GmkEffect();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void debugUpdateMmf();  // slot 10
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(13);
    unsigned char pad_48[0x48];
    void* pad_90;  // dispose clears 0x90..0xa8
    void* pad_98;
    void* pad_a0;
    unsigned char pad_a8[0x4];
    unsigned m_effectHandle;  // 0xac: the playing effect (dispose removes it from EffectManager; the name is not the original's)
    unsigned char pad_b0[0x8];
    unsigned long m_flags;  // 0xb8: dispose clears its low 3 bits (the name is not the original's)
    unsigned char pad_c0[0x8];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
