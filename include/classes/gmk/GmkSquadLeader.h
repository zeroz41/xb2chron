#ifndef CLASSES_GMK_GMKSQUADLEADER_H
#define CLASSES_GMK_GMKSQUADLEADER_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B70F40
class GmkSquadLeader : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkSquadLeader();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void debugDraw() const {}  // slot 7
    virtual void debugUpdateMmf() {}  // slot 10
    virtual void getBindedSquadMemberList() const;  // slot 11
};
}  // namespace gmk

#endif
