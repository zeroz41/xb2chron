#ifndef CLASSES_GF_GFMENUOBJENVIRONMENTINFO_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJENVIRONMENTINFO_LISTLISTENER_H

#include "classes/gf/GfMenuObjEnvironmentInfo.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B61DB0
class GfMenuObjEnvironmentInfo::ListListener : public ::ui::UIObjectListener {
public:
    // its state: a 4-aligned aggregate at 0xC (event 1 stores 0x10-0x17 as one 8-byte store, which fields of the
    // listener itself, 8-aligned at 0x10, would merge with 0xC instead); the names are not the original's
    struct State {
        int m_open;     // 1 while faded in: open (0x21) fades in, close (0x22) out
        int m_enabled;  // GfMenuFlag 30 clear: enable (0x100) and disable (0x101) set it
        int m_ctrl;     // the slot of its last fade
        int pad_0C;
    };
    ListListener(GfMenuObjEnvironmentInfo* owner) : m_state(), m_owner(owner) {}
    virtual ~ListListener() {}  // slot 0: weak, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    State m_state;
    GfMenuObjEnvironmentInfo* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
