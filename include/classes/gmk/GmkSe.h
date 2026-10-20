#ifndef CLASSES_GMK_GMKSE_H
#define CLASSES_GMK_GMKSE_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6C5B8
class GmkSe : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkSe();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
};
}  // namespace gmk

#endif
