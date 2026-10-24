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
    explicit GmkMobList(unsigned int updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame), m_resetCount(0) {}
    virtual ~GmkMobList();  // slot 0
    virtual void onResetUpdateGmkIndex();  // slot 18
    // onResetUpdateGmkIndex counts the wraps of the update index and resets it every second one (the name is
    // not the original's)
    unsigned int m_resetCount;  // 0x228
    unsigned char pad_22c[0x4];
};
}  // namespace gmk

#endif
