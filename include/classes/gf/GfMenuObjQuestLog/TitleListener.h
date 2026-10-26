#ifndef CLASSES_GF_GFMENUOBJQUESTLOG_TITLELISTENER_H
#define CLASSES_GF_GFMENUOBJQUESTLOG_TITLELISTENER_H

#include "classes/gf/GfMenuObjQuestLog.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B644E8
class GfMenuObjQuestLog::TitleListener : public ::ui::UIObjectListener {
public:
    // its table's D1 slot is the base's destructor and its D0 frees it: an inline destructor (as other menus'
    // listeners); the layout after the reference count is the other gf_menu_obj listeners' (pad_0C, owner at 0x20)
    TitleListener(GfMenuObjQuestLog* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TitleListener() {}  // slot 0
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjQuestLog* m_owner;
};
}  // namespace gf

#endif
