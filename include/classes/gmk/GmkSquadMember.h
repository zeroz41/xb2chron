#ifndef CLASSES_GMK_GMKSQUADMEMBER_H
#define CLASSES_GMK_GMKSQUADMEMBER_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B71058
class GmkSquadMember : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkSquadMember();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void debugUpdateMmf();  // slot 10
};
}  // namespace gmk

#endif
