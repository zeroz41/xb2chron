#ifndef CLASSES_GF_LOCATORPRECIOUS_H
#define CLASSES_GF_LOCATORPRECIOUS_H

#include "classes/gf/AFieldLocator.h"

namespace gmk { class AGmkBase; }

namespace gf {
// a base of gf::LocatorPrecious no evidence names yet
class TUnk_B51CF0 {
public:
    virtual void onTraverse(gmk::AGmkBase const&) = 0;
};
// table 0x7100B51CA0; base at 0x18 unknown (TUnk_B51CF0)
class LocatorPrecious : public ::gf::AFieldLocator, public TUnk_B51CF0 {
public:
    virtual ~LocatorPrecious();  // slot 0
    virtual void getPosNum() const;  // slot 3
    virtual void getPos(unsigned int) const;  // slot 4
    virtual void update();  // slot 6
    virtual void onTraverse(gmk::AGmkBase const&);  // slot 7
};
}  // namespace gf

#endif
