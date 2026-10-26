#ifndef CLASSES_GF_GFMENUOBJCOMMONTEXT_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJCOMMONTEXT_MAINLISTENER_H

#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B614C0
class GfMenuObjCommonText::MainListener : public ::ui::UIObjectListener {
public:
    MainListener(GfMenuObjCommonText* owner) : m_state(0), pad_10(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    int m_state;  // the name is not the original's
    unsigned char pad_10[0x10];
    GfMenuObjCommonText* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif
