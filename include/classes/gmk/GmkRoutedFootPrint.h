#ifndef CLASSES_GMK_GMKROUTEDFOOTPRINT_H
#define CLASSES_GMK_GMKROUTEDFOOTPRINT_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/ScenarioFlagCond.h"
namespace gmk { class GmkRoutedFootPrintGobCustom; }

namespace gmk {
// table 0x7100B6D238
class GmkRoutedFootPrint : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        // user-provided: Vector<BdatInfo>::resize/extend store each field (no zero fill of the padding)
        BdatInfo() : m_footEffect(nullptr), m_condition(0) {}
        // inline: initGmkBdatInfo inlines it (no symbol); the column names are the original's, the field names not
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
            m_footEffect = reinterpret_cast<const char*>(Bdat::getValCheck(bdat.m_fp, "FootEffect", row, 7));
            m_scenarioFlag = ScenarioFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2), (unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2));
            m_questFlag = QuestFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2), (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1),
                                        (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1));
            m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
        }
        const char* m_footEffect;  // 0x0: "FootEffect"
        unsigned short m_condition;  // 0x8: "Condition"
        ScenarioFlagCond m_scenarioFlag;  // 0xa
        QuestFlagCond m_questFlag;  // 0xe
        // (0x12..0x18: tail padding, neither stored by resize nor copied)
    };
    GmkRoutedFootPrint() {}  // inline, user-provided: the defaults are stored by Vector<T>::resize/extend, no zero fill
    virtual ~GmkRoutedFootPrint();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(54);
    void* pad_48 = nullptr;
    void* pad_50 = nullptr;
    void* pad_58 = nullptr;  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
