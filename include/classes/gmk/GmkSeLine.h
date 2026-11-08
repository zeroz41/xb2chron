#ifndef CLASSES_GMK_GMKSELINE_H
#define CLASSES_GMK_GMKSELINE_H

#include "classes/gmk/AGmkBase.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/gmk/GmkSe.h"
namespace gmk { class GmkSeLineGobCustom; }

namespace gmk {
// table 0x7100B6C620
// its node (a second, non-polymorphic base at 0x48) links it into TGmkActiveList<GmkSeLine> (dispose unlinks it)
class GmkSeLine : public ::gmk::AGmkBase, public mm::mtl::IntrusiveListNodeBase {
public:
    // its data in the gimmick section (m_createInfo.m_data): isPlayerInsideAabb tests the player against the box
    // [m_aabbMin, m_aabbMax); debugDraw draws lines through the GmkSeLinePoint gimmicks m_pointBegin..m_pointEnd - 1
    // (the struct and field names are not the original's)
    struct Data {
        float m_aabbMin[3];
        unsigned m_pointBegin;
        float m_aabbMax[3];
        unsigned m_pointEnd;
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    // its row's BdatInfo: GmkSe's (TGmkList<GmkSeLine, GmkSe::BdatInfo, ...>)
    const GmkSe::BdatInfo* getBdatInfo() const { return static_cast<const GmkSe::BdatInfo*>(m_createInfo.m_bdatInfo); }
    virtual ~GmkSeLine();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    // its step while in TGmkActiveList<GmkSeLine> (GmkManager::seqUpdate calls it for each)
    void updateInActiveList(float);
    virtual void debugDraw() const;  // slot 7
    // starts its sound (update calls it once the pop conditions hold and the player is inside the box)
    void createInst();
    bool isPlayerInsideAabb() const;
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(16);
    // the stores Vector<GmkSeLine>::resize makes in each element (0x58 a halfword, 0x5c..0x69 one zeroed run)
    GmkSeLine() : m_popCondMatched(false), m_played(false), m_seHandle(0), pad_60(0), pad_64() {}
    // 0x58: update stores BdatInfo::isPopCondMatched's answer here; debugDraw draws yellow while set, gray otherwise
    // (the name is not the original's)
    bool m_popCondMatched;
    // 0x59: createInst sets it once its sound starts; a play_once row plays no more after that (the name is not the
    // original's)
    bool m_played;
    unsigned m_seHandle;  // 0x5c: the playing sound (dispose stops it; the name is not the original's)
    unsigned pad_60;  // createInst clears it
    unsigned char pad_64[0x5];  // fields (expand copies 0x58..0x69)
    // 0x69..0x70: tail padding; size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
