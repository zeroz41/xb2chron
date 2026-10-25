#ifndef CLASSES_EVENT_EFFECTCTRL_H
#define CLASSES_EVENT_EFFECTCTRL_H

namespace event {
// table 0x7100B3CE50
class EffectCtrl {
public:
    virtual ~EffectCtrl();  // slot 0
    void kill();
};
}  // namespace event

#endif
