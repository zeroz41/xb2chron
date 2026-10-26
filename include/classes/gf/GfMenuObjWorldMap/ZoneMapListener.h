#ifndef CLASSES_GF_GFMENUOBJWORLDMAP_ZONEMAPLISTENER_H
#define CLASSES_GF_GFMENUOBJWORLDMAP_ZONEMAPLISTENER_H

#include "classes/gf/GfMenuObjWorldMap.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B65100
class GfMenuObjWorldMap::ZoneMapListener : public ::ui::UIObjectListener {
public:
    // its table's D1 slot is the base's destructor and its D0 frees it: an inline destructor (as other menus'
    // listeners); initialize news it as 0x28 bytes, clearing 0x0C-0x1C and storing the owner at 0x20
    ZoneMapListener(GfMenuObjWorldMap* owner) : pad_0C(), m_owner(owner) {}
    virtual ~ZoneMapListener() {}  // slot 0
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjWorldMap* m_owner;
};
}  // namespace gf

#endif
