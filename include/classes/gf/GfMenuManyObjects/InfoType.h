#ifndef CLASSES_GF_GFMENUMANYOBJECTS_INFOTYPE_H
#define CLASSES_GF_GFMENUMANYOBJECTS_INFOTYPE_H

#include "classes/gf/GfMenuManyObjects.h"

namespace gf {
// table 0x7100B60DA0: what a kind's queue holds for one open object (its kinds derive from it)
class GfMenuManyObjects::InfoType {
public:
    InfoType(unsigned int handle) : m_handle(handle) {}
    virtual void dispose() {}  // slot 0: weak (gf_menu_obj_chain_icon's copy is the one kept)
    unsigned int m_handle;  // the object's UI handle (remove looks for it); the name is not the original's
};
}  // namespace gf

#endif
