#ifndef CLASSES_GF_GFMENUOBJHANAPARTSMAKE_H
#define CLASSES_GF_GFMENUOBJHANAPARTSMAKE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B628B0
class GfMenuObjHanaPartsMake : public ::gf::GfMenuObject {
public:
    class ItemListListener;
    class MainListener;
    class NumSelectListener;
    class PartsListListener;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it stores the 1-byte
    // static at 0x7100EAB878 (this unit's .bss) that only initialize() and update() otherwise read and write.
    // What it does: sets that byte to 1. Caller: GfMenuManager::gevItemAdd when the count is below 1.
    static void fn_71004181A8();
    virtual ~GfMenuObjHanaPartsMake();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
