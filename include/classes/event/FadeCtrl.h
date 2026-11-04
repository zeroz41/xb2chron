#ifndef CLASSES_EVENT_FADECTRL_H
#define CLASSES_EVENT_FADECTRL_H

#include "classes/gf/SCOM_FADE.h"
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
    void clear();  // ends every layer's pending fade (update), then drops the requests
    void update();  // hands each requested fade to gf::SCOM_FADE
    // 1.0.0's names (out of line there at 0x71000DFB10 / 0x71000DFAD0); inline in 3.0.1
    void fadein(int frame) {
        pad_8[0].pad_4 = true;
        pad_8[0].pad_5 = false;
        pad_8[0].pad_8 = frame;
        pad_8[0].pad_c = false;
        pad_8[1].pad_4 = true;
        pad_8[1].pad_5 = false;
        pad_8[1].pad_8 = frame;
        pad_8[1].pad_c = false;
        if (!(pad_68 & 1)) {
            pad_8[2].pad_4 = true;
            pad_8[2].pad_5 = false;
            pad_8[2].pad_8 = frame;
            pad_8[2].pad_c = false;
        }
    }
    void fadeout(int frame, PRIO prio, const mm::Col4* color) {
        Layer& layer = pad_8[prio];
        layer.pad_4 = true;
        layer.pad_5 = true;
        layer.pad_8 = frame;
        if (color) {
            layer.pad_c = true;
            layer.pad_10 = *color;
        } else {
            layer.pad_c = false;
        }
    }

    // one fade per layer (FadeManager::isFading asks gf::GfGameManager::isFading of each pad_0); the name is not
    // the original's
    struct Layer {
        Layer() : pad_4(false), pad_c(false) {}
        // FadeCtrl::update's per-layer step (the name is not the original's)
        void update() {
            if (pad_4) {
                gf::SCOM_FADE::createEvent(pad_0, pad_8, pad_5 ? (pad_c ? pad_10 : mm::Col4::black) : mm::Col4::zero);
                pad_4 = false;
                pad_c = false;
            }
        }

        unsigned int pad_0;  // 0x0: the gf::GfGameManager fade layer (0, 1, 2)
        bool pad_4;  // 0x4: a fade was requested (isFading reports it)
        bool pad_5;  // 0x5: fade out (fadeout sets it; update then fades to pad_10 or black, else to Col4::zero)
        unsigned int pad_8;  // 0x8: the fade's frame count (FadePlanner::play)
        bool pad_c;  // 0xc
        mm::Col4 pad_10;  // 0x10: the fade's colour
    };

    Layer pad_8[3];  // 0x8
    unsigned int pad_68;  // 0x68
};
}  // namespace event

#endif
