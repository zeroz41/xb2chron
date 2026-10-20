#ifndef CLASSES_GF_GFCOMVISIBLE_H
#define CLASSES_GF_GFCOMVISIBLE_H

#include "classes/gf/GfComponent.h"

namespace gf {
// table 0x7100B66808
class GfComVisible : public ::gf::GfComponent {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComVisible();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
};
}  // namespace gf

#endif
