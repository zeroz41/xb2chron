#ifndef CLASSES_GF_GFMENUOBJEVTHEATER_TUNK_B621A0_H
#define CLASSES_GF_GFMENUOBJEVTHEATER_TUNK_B621A0_H

#include "classes/gf/GfMenuObjEvTheater.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B621A0. Unnamed class (TUnk_<table low address>): the symbols leave it unnamed (no RTTI in 3.0.1). It
// shows the event preview ("IMG_preview" from the owner's m_msgList bdat "image_id"; it opens "LAY_sub" again on a
// cancel), so it may be 1.0.0's ScreenListener, which nothing proves.
class GfMenuObjEvTheater::PreviewListener : public ::ui::UIObjectListener {
public:
    virtual ~PreviewListener() {}  // slot 0: its D1 slot is the base's destructor, its D0 (0x7100405304) weak
    // slot 2: event 0x21 shows the preview image and queues seqWaitStreaming on the owner's m_seq; 3 (1) enables input
    // and queues a 60-frame wait and seqStartInput; 8 (2) goes back to LAY_sub; 0x105 opens the operation guide
    virtual void reciveEvent(ui::EventData const&, unsigned int);
    // the layout of the other gf_menu_obj listeners (initialize, which constructs it, is not written yet)
    // 0xC: 1 while the operation guide event 0x105 opened for this object is open (the name is not the original's)
    int m_guideOpen;
    unsigned char pad_10[0x10];
    GfMenuObjEvTheater* m_owner;  // 0x20
};
}  // namespace gf

#endif
