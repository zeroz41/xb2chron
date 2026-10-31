#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_BOOSTERNUMLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_BOOSTERNUMLISTENER_H

#include "classes/gf/GfMenuObjBladeCreate.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B60188
class GfMenuObjBladeCreate::BoosterNumListener : public ::ui::UIObjectListener {
public:
    // the layout after the reference count is the other gf_menu_obj listeners' (owner at 0x20: reciveEvent reads the
    // owner there); an inline destructor, as MainListener's
    BoosterNumListener(GfMenuObjBladeCreate* owner) : m_shown(0), m_decided(0), pad_14(), m_owner(owner) {}
    virtual ~BoosterNumListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // 1 while faded in: 0x21 fades in only from 0, 0x22 fades out only from 1, 1 hides and resets it (the name is
    // not the original's)
    unsigned int m_shown;
    // 1 once the number was decided (input 1), what its close event (3, 2) sends on as 0x103's parameter; the
    // name is not the original's
    unsigned int m_decided;
    unsigned char pad_14[0xC];
    GfMenuObjBladeCreate* m_owner;  // (the name is not the original's)
};
}  // namespace gf

#endif
