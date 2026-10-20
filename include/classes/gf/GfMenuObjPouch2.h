#ifndef CLASSES_GF_GFMENUOBJPOUCH2_H
#define CLASSES_GF_GFMENUOBJPOUCH2_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B641A0
class GfMenuObjPouch2 : public ::gf::GfMenuObject {
public:
    class FilterListener2;
    class ItemListListener;
    class MainListener;
    class PartyInfoListener;
    class ResultListener;
    class SlotListener;
    virtual ~GfMenuObjPouch2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
