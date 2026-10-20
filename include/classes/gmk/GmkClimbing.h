#ifndef CLASSES_GMK_GMKCLIMBING_H
#define CLASSES_GMK_GMKCLIMBING_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6E0A0
class GmkClimbing : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkClimbing();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
};
}  // namespace gmk

#endif
