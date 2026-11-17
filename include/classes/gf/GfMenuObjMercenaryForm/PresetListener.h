#ifndef CLASSES_GF_GFMENUOBJMERCENARYFORM_PRESETLISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYFORM_PRESETLISTENER_H

#include "classes/gf/GfMenuObjMercenaryForm.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B63460
class GfMenuObjMercenaryForm::PresetListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    PresetListener(GfMenuObjMercenaryForm* owner) : m_load(), pad_10(), m_owner(owner) {}
    virtual ~PresetListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // the open event's (0x21) first parameter: 0 saves the team into the chosen preset (seqPresetSave), others load
    // it (seqPresetLoad) when event 8 comes with m_param1 1. The name is not the original's
    int m_load;
    unsigned char pad_10[0xC];
    GfMenuObjMercenaryForm* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
