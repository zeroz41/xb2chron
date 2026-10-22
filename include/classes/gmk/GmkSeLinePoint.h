#ifndef CLASSES_GMK_GMKSELINEPOINT_H
#define CLASSES_GMK_GMKSELINEPOINT_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B700B0
class GmkSeLinePoint : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkSeLinePoint();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
};
}  // namespace gmk

#endif
