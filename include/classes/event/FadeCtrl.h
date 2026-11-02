#ifndef CLASSES_EVENT_FADECTRL_H
#define CLASSES_EVENT_FADECTRL_H

#include "mm/Col4.h"

namespace event {
// table 0x7100B3CF20
class FadeCtrl {
public:
    // a fade's priority (evt_post.playFade passes its 3rd parameter); 1.0.0's mangled names spell the type
    // event::FadeCtrl::PRIO, its values are not known
    enum PRIO {};
    // inline (no symbol): Singleton<FadeCtrl>::getPtr builds it in place (FadeManager::isFading, FadePlanner::play)
    FadeCtrl() : pad_68(0) {
        pad_8[0].pad_0 = 0;
        pad_8[1].pad_0 = 1;
        pad_8[2].pad_0 = 2;
    }
    virtual ~FadeCtrl();  // slot 0

    // one fade per layer (FadeManager::isFading asks gf::GfGameManager::isFading of each pad_0); the name is not
    // the original's
    struct Layer {
        Layer() : pad_4(false), pad_c(false) {}

        unsigned int pad_0;  // 0x0: the gf::GfGameManager fade layer (0, 1, 2)
        bool pad_4;  // 0x4: a fade was requested (isFading reports it)
        bool pad_5;  // 0x5: fade in (FadePlanner::play sets it for its in types)
        unsigned int pad_8;  // 0x8: the fade's frame count (FadePlanner::play)
        bool pad_c;  // 0xc
        mm::Col4 pad_10;  // 0x10: the fade's colour
    };

    Layer pad_8[3];  // 0x8
    unsigned int pad_68;  // 0x68
};
}  // namespace event

#endif
