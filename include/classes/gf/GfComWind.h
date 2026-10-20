#ifndef CLASSES_GF_GFCOMWIND_H
#define CLASSES_GF_GFCOMWIND_H

#include "classes/gf/GfComponent.h"

namespace gf {
// table 0x7100B66438
class GfComWind : public ::gf::GfComponent {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComWind();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
};
}  // namespace gf

#endif
