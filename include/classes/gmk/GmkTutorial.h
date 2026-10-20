#ifndef CLASSES_GMK_GMKTUTORIAL_H
#define CLASSES_GMK_GMKTUTORIAL_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6D308
class GmkTutorial : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkTutorial();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
};
}  // namespace gmk

#endif
