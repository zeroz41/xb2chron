#ifndef CLASSES_GMK_GMKEFFECT_H
#define CLASSES_GMK_GMKEFFECT_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6C550
class GmkEffect : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkEffect();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void debugUpdateMmf();  // slot 10
};
}  // namespace gmk

#endif
