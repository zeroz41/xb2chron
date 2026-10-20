#ifndef CLASSES_GMK_GMKSETOFSALVAGECHILDREN_H
#define CLASSES_GMK_GMKSETOFSALVAGECHILDREN_H

#include "classes/gmk/GmkSet.h"

namespace gmk {
// table 0x7100B6E3E8
class GmkSetOfSalvageChildren : public ::gmk::GmkSet {
public:
    virtual ~GmkSetOfSalvageChildren();  // slot 0
    virtual void createGmkLists(int);  // slot 2
};
}  // namespace gmk

#endif
