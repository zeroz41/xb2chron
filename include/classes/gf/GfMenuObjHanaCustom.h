#ifndef CLASSES_GF_GFMENUOBJHANACUSTOM_H
#define CLASSES_GF_GFMENUOBJHANACUSTOM_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B62688
class GfMenuObjHanaCustom : public ::gf::GfMenuObject {
public:
    class EquipListListener;
    class ItemListListener;
    class MainListener;
    class PartsListListener;
    class PlanListener;
    virtual ~GfMenuObjHanaCustom();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
