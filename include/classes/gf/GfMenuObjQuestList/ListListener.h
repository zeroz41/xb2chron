#ifndef CLASSES_GF_GFMENUOBJQUESTLIST_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJQUESTLIST_LISTLISTENER_H

#include "classes/gf/GfMenuObjQuestList.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B64400
class GfMenuObjQuestList::ListListener : public ::ui::UIObjectListener {
public:
    // its table's D1 slot is the base's destructor and its D0 frees it: an inline destructor (as other menus'
    // listeners); initialize/initializeSub new it as 0x28 bytes, clearing 0x0C-0x1C and storing the owner at 0x20
    ListListener(GfMenuObjQuestList* owner) : pad_0C(), m_owner(owner) {}
    virtual ~ListListener() {}  // slot 0
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjQuestList* m_owner;
};
}  // namespace gf

#endif
