#ifndef CLASSES_EVENT_FADEPLANNER_H
#define CLASSES_EVENT_FADEPLANNER_H

#include "mm/Col4.h"

namespace event {
// table 0x7100B3CF40
class FadePlanner {
public:
    // which planned fade (indexes pad_c; update passes 0..3); 1.0.0's mangled names spell the type, its values are
    // not known
    enum TYPE {};

    FadePlanner() : pad_8(0) {}  // inline (no symbol; FadeManager's constructor inlines it)
    virtual ~FadePlanner() {}  // slot 0
    void update(float);  // counts each pending entry's timer down by the frame step and plays it at < 0
    void play(TYPE type);

    // one planned fade per FadePlanner::TYPE (play(type) indexes it, update counts each timer down); the name is
    // not the original's
    struct Entry {
        Entry() : pad_0(0), pad_4(0), pad_8(0), pad_c(0), pad_10(mm::Col4::black), pad_20(0.0f) {}

        unsigned int pad_0;  // 0x0: flags (bit 2: the timer at 0x20 runs; update clears it when it fires)
        unsigned int pad_4;  // 0x4: play passes it on as the fade's value (0 while event::SkipManager skips)
        unsigned int pad_8;  // 0x8
        unsigned int pad_c;  // 0xc: the event::FadeCtrl slot play writes
        mm::Col4 pad_10;  // 0x10: the colour play copies into that slot
        float pad_20;  // 0x20: the timer update counts down
    };

    unsigned int pad_8;  // 0x8
    Entry pad_c[4];  // 0xc
};
}  // namespace event

#endif
