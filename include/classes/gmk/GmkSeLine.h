#ifndef CLASSES_GMK_GMKSELINE_H
#define CLASSES_GMK_GMKSELINE_H

#include "classes/gmk/AGmkBase.h"
#include "mm/mtl/IntrusiveList.h"
namespace gmk { class GmkSeLineGobCustom; }

namespace gmk {
// table 0x7100B6C620
// its node (a second, non-polymorphic base at 0x48) links it into TGmkActiveList<GmkSeLine> (dispose unlinks it)
class GmkSeLine : public ::gmk::AGmkBase, public mm::mtl::IntrusiveListNodeBase {
public:
    virtual ~GmkSeLine();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    // its step while in TGmkActiveList<GmkSeLine> (GmkManager::seqUpdate calls it for each)
    void updateInActiveList(float);
    virtual void debugDraw() const;  // slot 7
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(16);
    // the stores Vector<GmkSeLine>::resize makes in each element (0x58 a halfword, 0x5c..0x69 one zeroed run)
    GmkSeLine() : pad_58(0), m_seHandle(0), pad_60() {}
    unsigned short pad_58;
    unsigned m_seHandle;  // 0x5c: the playing sound (dispose stops it; the name is not the original's)
    unsigned char pad_60[0x9];  // fields (expand copies 0x58..0x69)
    // 0x69..0x70: tail padding; size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
