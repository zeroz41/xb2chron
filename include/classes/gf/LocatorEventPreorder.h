#ifndef CLASSES_GF_LOCATOREVENTPREORDER_H
#define CLASSES_GF_LOCATOREVENTPREORDER_H

#include "classes/gf/AFieldLocator.h"

namespace gf {
// table 0x7100B51D08
class LocatorEventPreorder : public ::gf::AFieldLocator {
public:
    virtual ~LocatorEventPreorder();  // slot 0
    virtual void getPosNum() const;  // slot 3
    virtual void getPos(unsigned int) const;  // slot 4
    virtual void update();  // slot 6
};
}  // namespace gf

#endif
