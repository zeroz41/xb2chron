#ifndef CLASSES_GMK_GMKMOBLIST_H
#define CLASSES_GMK_GMKMOBLIST_H

#include "classes/gmk/GmkMob.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkMob; }
namespace gmk { class GmkMobGob; }

namespace gmk {
// table 0x7100B6DDF0
class GmkMobList : public ::gmk::TGmkList< ::gmk::GmkMob, ::gmk::GmkMob::BdatInfo, 4345677u, 2u, ::gmk::GmkMobGob> {
public:
    virtual ~GmkMobList();  // slot 0
    virtual void onResetUpdateGmkIndex();  // slot 18
};
}  // namespace gmk

#endif
