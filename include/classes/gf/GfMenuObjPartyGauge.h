#ifndef CLASSES_GF_GFMENUOBJPARTYGAUGE_H
#define CLASSES_GF_GFMENUOBJPARTYGAUGE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B63F40
class GfMenuObjPartyGauge : public ::gf::GfMenuObject {
public:
    class GaugeListener;
    virtual ~GfMenuObjPartyGauge();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
