#ifndef CLASSES_EVENT_EFFECTOBJ_H
#define CLASSES_EVENT_EFFECTOBJ_H

#include "classes/event/EffectCtrl.h"

namespace event {
// table 0x7100B3CE90
class EffectObj {
public:
    virtual ~EffectObj();  // slot 0
    void playAnim(const char* name, float frame);

    unsigned char pad_8[0x48];
    EffectCtrl m_ctrl;  // 0x50; the name is not the original's
};
}  // namespace event

#endif
