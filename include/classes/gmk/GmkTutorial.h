#ifndef CLASSES_GMK_GMKTUTORIAL_H
#define CLASSES_GMK_GMKTUTORIAL_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "plugin/Bdat.h"

namespace gmk {
// table 0x7100B6D308
class GmkTutorial : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        unsigned char m_sysMultiFlag;  // the row's "SysMultiFlag"
        unsigned char pad_1;
        ScenarioFlagCond m_scenarioFlag;  // the row's ScenarioFlagMin (up to 0xFFFF when set)
        QuestFlagCond m_questFlag;        // the row's QuestFlag/Min/Max
    };
    virtual ~GmkTutorial();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x39);
    unsigned char pad_48[0xb8];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
