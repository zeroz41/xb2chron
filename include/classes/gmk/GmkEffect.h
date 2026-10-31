#ifndef CLASSES_GMK_GMKEFFECT_H
#define CLASSES_GMK_GMKEFFECT_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gmk/WeatherCond.h"
#include "classes/gmk/InOutDoorCond.h"
#include "classes/gmk/CloudCond.h"
#include <bitset>
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
    // the stores Vector<GmkEffect>::resize makes in each element
    GmkEffect() : pad_48(0), m_seq(nullptr), pad_a0(nullptr), pad_a8(0), m_effectHandle(0), pad_b0(1), pad_b1(0), pad_b2(0), pad_c0(0), pad_c1(0) {}
    virtual ~GmkEffect();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void debugUpdateMmf();  // slot 10
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(13);
    // what m_createInfo.m_data points at for an effect gimmick (create reads it; 4-aligned: create's reads of its
    // flags are widened to 2- and 4-byte loads; the struct and field names are not the original's)
    struct Data {
        unsigned int pad_0[5];
        // 0x14..0x1E: separate fields, not arrays (create's loads of 0x1A and 0x1C are widened: their alignment is
        // the field's, an array element's would be the array's)
        bool m_weather0;  // 0x14: WeatherCond bit 4
        bool m_weather1;  // 0x15: WeatherCond bit 0
        bool m_weather2;  // 0x16: bit 1
        bool m_weather3;  // 0x17: bit 2
        bool m_weather4;  // 0x18: bit 3
        bool m_time0;     // 0x19: TimeCond bit 0
        bool m_time1;     // 0x1A: bit 1
        bool m_time2;     // 0x1B: bit 2
        bool m_time3;     // 0x1C: bit 3
        bool m_time4;     // 0x1D: bit 4
        bool m_time5;     // 0x1E: bit 5
        bool m_inOutDoor0;  // 0x1F: InOutDoorCond's first flag
        bool m_inOutDoor1;  // 0x20: its second
        bool m_cloud[2];                     // 0x21: CloudCond 0 for the first alone, 1 for the second alone
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    // the step create installs
    void seqValidateResHandle(float);

    unsigned long pad_48;
    // 0x50..0x90: when it shows, from its gimmick data (create fills them; the names are not the original's)
    TimeCond m_popTime;            // the data's bytes 0x19..0x1E as bits 0..5
    WeatherCond m_popWeather;      // the data's bytes 0x14..0x18 as bits 4, 0..3
    InOutDoorCond m_popInOutDoor;  // the data's bytes 0x1F and 0x20
    CloudCond m_popCloud;          // the data's bytes 0x21/0x22: 0 for the first alone, 1 for the second alone
    // 0x90: the sequence step (create installs seqValidateResHandle, dispose clears it)
    void (GmkEffect::*m_seq)(float);
    void* pad_a0;  // dispose clears it
    unsigned char pad_a8;
    unsigned m_effectHandle;  // 0xac: the playing effect (dispose removes it from EffectManager; the name is not the original's)
    unsigned char pad_b0;
    unsigned char pad_b1;
    unsigned char pad_b2;
    std::bitset<3> m_flags;  // 0xb8: dispose resets it (the name is not the original's)
    unsigned char pad_c0;
    unsigned char pad_c1;
    // 0xc2..0xc8: tail padding; size 0xc8 from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
