#ifndef CLASSES_GF_GFMENUOBJSORT_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJSORT_MAINLISTENER_H

#include "classes/gf/GfMenuObjSort.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B64A40: LAY_main's listener (initialize news it)
class GfMenuObjSort::MainListener : public ::ui::UIObjectListener {
public:
    MainListener(GfMenuObjSort* owner) : m_openIndex(0), pad_10(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    // the list's index when the menu opened: a decision on another one relabels the caller (the name is not the
    // original's)
    unsigned int m_openIndex;
    unsigned char pad_10[0xC];
    GfMenuObjSort* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif
