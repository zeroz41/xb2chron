#ifndef CLASSES_GMK_GMKSQUADMEMBER_H
#define CLASSES_GMK_GMKSQUADMEMBER_H

#include "classes/gmk/AGmkBase.h"
namespace gmk { class GmkSquadMemberGobCustom; }

namespace gmk {
// table 0x7100B71058
class GmkSquadMember : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {};
    virtual ~GmkSquadMember();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void debugUpdateMmf() {}  // slot 10
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(40);
    unsigned char pad_48[0x8];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
