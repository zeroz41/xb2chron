#ifndef CLASSES_GMK_GMKSET_H
#define CLASSES_GMK_GMKSET_H

#include "classes/gmk/AGmkBase.h"

namespace gmk { class IGmkList; }

namespace gmk {
// table 0x7100B6BDF0
class GmkSet {
public:
    virtual ~GmkSet();  // slot 0
    virtual void createGmkLists(int);  // slot 2
    // its list of the gimmicks of a kind, none when it has none
    const IGmkList* getGmkList(GmkType type) const;
    IGmkList* getGmkList(GmkType type);
};
}  // namespace gmk

#endif
