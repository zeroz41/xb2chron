#ifndef CLASSES_GF_LOCATORPRECIOUSPREORDER_H
#define CLASSES_GF_LOCATORPRECIOUSPREORDER_H

#include "classes/gf/AFieldLocator.h"

namespace gf {
// table 0x7100B51D50
class LocatorPreciousPreorder : public ::gf::AFieldLocator {
public:
    virtual ~LocatorPreciousPreorder();  // slot 0
    virtual void getPosNum() const;  // slot 3
    virtual void getPos(unsigned int) const;  // slot 4
    virtual void update();  // slot 6
};
}  // namespace gf

#endif
