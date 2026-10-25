#ifndef CLASSES_EVENT_FADECTRL_H
#define CLASSES_EVENT_FADECTRL_H

namespace event {
// table 0x7100B3CF20
class FadeCtrl {
public:
    // a fade's priority (evt_post.playFade passes its 3rd parameter); 1.0.0's mangled names spell the type
    // event::FadeCtrl::PRIO, its values are not known
    enum PRIO {};
    virtual ~FadeCtrl();  // slot 0
};
}  // namespace event

#endif
