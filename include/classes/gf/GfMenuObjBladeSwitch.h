#ifndef CLASSES_GF_GFMENUOBJBLADESWITCH_H
#define CLASSES_GF_GFMENUOBJBLADESWITCH_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B603C0
class GfMenuObjBladeSwitch : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjBladeSwitch();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
