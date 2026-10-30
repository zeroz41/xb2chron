#ifndef CLASSES_GMK_GMKSQUADLEADER_H
#define CLASSES_GMK_GMKSQUADLEADER_H

#include "classes/gmk/AGmkBase.h"
namespace gmk { class GmkSquadLeaderGobCustom; }

namespace gmk {
// table 0x7100B70F40
class GmkSquadLeader : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {};
    GmkSquadLeader() : pad_48(nullptr) {}  // inline: resize/extend construct in place with these stores
    virtual ~GmkSquadLeader();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void debugDraw() const {}  // slot 7
    virtual void debugUpdateMmf() {}  // slot 10
    // the GmkSquadMember list of the gimmick set that made its list (GmkSet::createGmkLists passes the set as the
    // list's CreateInfo::m_param)
    virtual IGmkList* getBindedSquadMemberList() const;  // slot 11
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(39);
    // an 8-byte field the constructor clears (Vector<T>::resize stores 0 at 0x48); meaning unknown
    void* pad_48;
};
}  // namespace gmk

#endif
