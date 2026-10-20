#ifndef CLASSES_GF_GFMENUOBJBLEQUIP_H
#define CLASSES_GF_GFMENUOBJBLEQUIP_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B60430
class GfMenuObjBlEquip : public ::gf::GfMenuObject {
public:
    class ItemSelectListener;
    class MainListener;
    class SlotListener;
    virtual ~GfMenuObjBlEquip();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
