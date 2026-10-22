#ifndef CLASSES_GF_GFMENUOBJCOMBOROUTE_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJCOMBOROUTE_MAINLISTENER_H

#include "classes/gf/GfMenuObjComboRoute.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B613E0
class GfMenuObjComboRoute::MainListener : public ::ui::UIObjectListener {
public:
    MainListener(GfMenuObjComboRoute* owner) : m_open(0), pad_10(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int m_open;  // 1 between the open event (0x21) and the close one (0x22) (the name is not the original's)
    unsigned char pad_10[0xC];
    GfMenuObjComboRoute* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
