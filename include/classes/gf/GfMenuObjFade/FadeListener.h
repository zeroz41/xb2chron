#ifndef CLASSES_GF_GFMENUOBJFADE_FADELISTENER_H
#define CLASSES_GF_GFMENUOBJFADE_FADELISTENER_H

#include "classes/gf/GfMenuObjFade.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B622E0: listens to a channel's image (IMG_fade%02d)
class GfMenuObjFade::FadeListener : public ::ui::UIObjectListener {
public:
    FadeListener(GfMenuObjFade* owner) : m_channel(0), m_ctrl(0), pad_14(), m_owner(owner) {}
    virtual ~FadeListener() {}  // slot 0: weak, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // the channel of the last fade (event 0x100), which the fade's start (0xA) and end (0xB) game events carry
    // (the names of the fields are not the original's)
    int m_channel;
    int m_ctrl;  // the slot of the running fade's control, -1 for none
    unsigned char pad_14[8];
    GfMenuObjFade* m_owner;  // what initialize makes it for

private:
    // reciveEvent's: a fade's start (0xA) or end (0xB) on a channel as a game event from the image (inlined; the name
    // is not the original's)
    static void pushFadeEvent(unsigned int handle, unsigned short type, unsigned char channel);
};
}  // namespace gf

#endif
