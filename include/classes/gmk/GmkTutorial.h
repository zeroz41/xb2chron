#ifndef CLASSES_GMK_GMKTUTORIAL_H
#define CLASSES_GMK_GMKTUTORIAL_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkPhantom.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "plugin/Bdat.h"

namespace gmk {
// table 0x7100B6D308
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
    // its node (a second, non-polymorphic base at 0x48) links it into TGmkActiveList<GmkTutorial>
class alignas(16) GmkTutorial : public ::gmk::AGmkBase, public mm::mtl::IntrusiveListNodeBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        // user-provided: Vector<BdatInfo>::resize stores the defaults only (no zeroing of the pads first)
        BdatInfo() {}
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isCondMatched() const;
        unsigned char m_sysMultiFlag = 0;  // the row's "SysMultiFlag"
        unsigned char pad_1;
        ScenarioFlagCond m_scenarioFlag;  // the row's ScenarioFlagMin (up to 0xFFFF when set)
        QuestFlagCond m_questFlag;        // the row's QuestFlag/Min/Max
    };
    GmkTutorial() {}  // inline: construct_n<GmkTutorial> constructs in place with these stores
    virtual ~GmkTutorial();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x39);
    void disposeGmkPhantom();
    // the local game flag it reads: its BDAT row id + 54162
    unsigned int getGameFlagId() const;
    // 0x58..0x60: padding (the copies of Vector<T>::expand copy nothing there)
    GmkPhantom m_phantom;  // 0x60 (the name is not the original's)
    bool pad_f0 = false;  // the constructor clears it (meaning unknown)
    // 0xf1..0x100: tail padding (not copied); size from TGmkList::getInst's stride (0x100)
};
}  // namespace gmk

#endif
