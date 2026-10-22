#ifndef CLASSES_GMK_GMKSELINE_H
#define CLASSES_GMK_GMKSELINE_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6C620
class GmkSeLine : public ::gmk::AGmkBase {
public:
    virtual ~GmkSeLine();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
};
}  // namespace gmk

#endif
