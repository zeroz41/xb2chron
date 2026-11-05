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
    // its gimmick data (m_createInfo.m_data): how its squad's members stand (GmkSquad::seqInit counts them from it,
    // updateMemberPosRotY_MemberDef_Circle scatters them within the radius; the names are not the original's)
    struct Data {
        // 2: on a circle (GmkSquad::seqInit takes the member count from the squad's CreateInfo); 1: the gimmick
        // set's squad members from m_firstMember to m_lastMember
        int m_memberDefType;
        float m_radius;     // 0x4: the circle's (scaled by the squad's pad_2c)
        int m_firstMember;  // 0x8
        int m_lastMember;   // 0xc
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(39);
    // an 8-byte field the constructor clears (Vector<T>::resize stores 0 at 0x48); meaning unknown
    void* pad_48;
};
}  // namespace gmk

#endif
