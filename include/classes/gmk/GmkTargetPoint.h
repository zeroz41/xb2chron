#ifndef CLASSES_GMK_GMKTARGETPOINT_H
#define CLASSES_GMK_GMKTARGETPOINT_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B71710
class GmkTargetPoint : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkTargetPoint();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
};
}  // namespace gmk

#endif
