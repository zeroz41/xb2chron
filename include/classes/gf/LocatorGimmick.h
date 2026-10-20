#ifndef CLASSES_GF_LOCATORGIMMICK_H
#define CLASSES_GF_LOCATORGIMMICK_H

#include "classes/gf/AFieldLocator.h"

namespace gf {
// table 0x7100B51D98
class LocatorGimmick : public ::gf::AFieldLocator {
public:
    virtual ~LocatorGimmick();  // slot 0
    virtual void getPosNum() const;  // slot 3
    virtual void getPos(unsigned int) const;  // slot 4
    virtual void update();  // slot 6
};
}  // namespace gf

#endif
