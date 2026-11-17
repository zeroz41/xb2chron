#ifndef CLASSES_GF_GFMENUOBJWORLDMAP_MAPSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJWORLDMAP_MAPSELECTLISTENER_H

#include "classes/gf/GfMenuObjWorldMap.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B65088
class GfMenuObjWorldMap::MapSelectListener : public ::ui::UIObjectListener {
public:
    // its table's D1 slot is the base's destructor and its D0 frees it: an inline destructor (as other menus'
    // listeners); initialize news it as 0x28 bytes, clearing 0x0C-0x1C and storing the owner at 0x20
    MapSelectListener(GfMenuObjWorldMap* owner) : pad_0C(), pad_10(), m_owner(owner) {}
    virtual ~MapSelectListener() {}  // slot 0
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    // reciveEvent sets it to 1 when it shows LAY_area_tag_select and back to 0 when it fades that out
    int pad_0C;
    unsigned char pad_10[0xC];
    GfMenuObjWorldMap* m_owner;
};
}  // namespace gf

#endif
