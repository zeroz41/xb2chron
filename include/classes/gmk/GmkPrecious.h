#ifndef CLASSES_GMK_GMKPRECIOUS_H
#define CLASSES_GMK_GMKPRECIOUS_H

#include "classes/gmk/AGmkBase.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "plugin/Bdat.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gmk/WeatherCond.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkPreciousGob; }

namespace gmk {
// table 0x7100B6CB70
// a second, non-polymorphic base at 0x48: Vector<T>::resize links its node to itself BEFORE storing GmkPrecious's
// table (a base's construction), then stores the members
class GmkPrecious : public ::gmk::AGmkBase, public ::mm::mtl::IntrusiveListNodeBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        // user-provided: Vector<BdatInfo>::resize stores the defaults only (no zeroing of the pads first)
        BdatInfo() {}
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isPopCondMatched() const;
        // the precious item's id: LocatorPrecious::onTraverse compares it with its id, which create() looks up in
        // the gimmick sheets' "itmID" column. The name is not the original's.
        unsigned short m_itmId = 0;
        unsigned short m_condition = 0;  // the row's "Condition" (a GfGameCond id; 0: none)
        unsigned short m_questId = 0;    // the row's "QuestID"
        ScenarioFlagCond m_scenarioFlag;  // the row's ScenarioFlagMin/Max
        QuestFlagCond m_questFlag;        // the row's QuestFlag/Min/Max
        TimeCond m_popTime;        // the row's "POP_TIME"
        WeatherCond m_popWeather;  // the row's "popWeather"
    };
    GmkPrecious() {}  // inline, user-provided: the defaults are stored by Vector<T>::resize/extend, no zero fill
    virtual ~GmkPrecious();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    bool isObtained() const;
    // AGmkBase's row as this kind's BdatInfo; the name is not the original's
    const BdatInfo* getBdatInfo() const {
        return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
    }
    static const gmk::GmkType TYPE = gmk::GmkType(34);
    long pad_58 = -1;
    unsigned int pad_60 = 0;
    unsigned char pad_64[0x4];
    void* pad_68 = nullptr;
    unsigned int pad_70 = 0;
    unsigned char pad_74 = 1;  // the data ends here: Vector<T>::expand's implicit copy copies up to it; the rest is alignment
};
}  // namespace gmk

#endif
