#ifndef CLASSES_GF_GFMENUOBJCOMMONTEXT_SELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJCOMMONTEXT_SELECTLISTENER_H

#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B615B0
class GfMenuObjCommonText::SelectListener : public ::ui::UIObjectListener {
public:
    SelectListener(GfMenuObjCommonText* owner) : m_state(0), pad_10(), m_owner(owner) {}
    virtual ~SelectListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    int m_state;  // the name is not the original's
    unsigned char pad_10[0xC];
    unsigned char pad_1C[0x4];  // the constructor leaves it as it is (initialize zeroes 0xC..0x1B only)
    GfMenuObjCommonText* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif
