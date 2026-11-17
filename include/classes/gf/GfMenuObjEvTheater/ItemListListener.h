#ifndef CLASSES_GF_GFMENUOBJEVTHEATER_ITEMLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJEVTHEATER_ITEMLISTLISTENER_H

#include "classes/gf/GfMenuObjEvTheater.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// _ZTVN2gf18GfMenuObjEvTheater16ItemListListenerE: the sound settings' list (m_levels / m_levelObjList)
class GfMenuObjEvTheater::ItemListListener : public ::ui::UIObjectListener {
public:
    virtual ~ItemListListener() {}  // slot 0: its D1 slot is the base's destructor, its D0 weak
    // slot 2: 0x21 / 0x22 open and close the list (0x21 builds it from m_appliedOption), 6 moves the selection,
    // 8 changes a level (9 / 10), applies (2) or opens the defaults dialog (0xB), 0x41 resets the levels to their
    // defaults when the dialog answers
    virtual void reciveEvent(ui::EventData const&, unsigned int);
    // reciveEvent passes it to convOptionDataToLevelList as the category (initialize, which constructs the listener,
    // is not written yet; what it holds is not known)
    unsigned int pad_0C;
    unsigned char pad_10[0x10];
    GfMenuObjEvTheater* m_owner;  // 0x20
};
}  // namespace gf

#endif
