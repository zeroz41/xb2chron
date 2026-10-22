#ifndef CLASSES_GF_GFMENUOBJFADE_LOADINGLISTENER_H
#define CLASSES_GF_GFMENUOBJFADE_LOADINGLISTENER_H

#include "classes/gf/GfMenuObjFade.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62308: listens to LAY_loading and LAY_saving
class GfMenuObjFade::LoadingListener : public ::ui::UIObjectListener {
public:
    LoadingListener(GfMenuObjFade* owner) : pad_c(), m_owner(owner) {}
    virtual ~LoadingListener() {}  // slot 0: weak, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2 (1.0.0's symbol)
    unsigned char pad_c[0x10];
    GfMenuObjFade* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
