#ifndef CLASSES_EVENT_EFFECTCTRL_H
#define CLASSES_EVENT_EFFECTCTRL_H

#include "mm/Col4.h"
#include "mm/Vec3.h"

namespace event { class IAttachActor; }

namespace event {
// table 0x7100B3CE50
class EffectCtrl {
public:
    virtual ~EffectCtrl();  // slot 0
    void kill();
    void update();
    void setCaster(IAttachActor* caster);

    unsigned char pad_8[0x158];
    // the transform and colour EffectObj's linear commands write (EffectObj::play hands them &EffectObj::m_ctrl);
    // ScriptEffectScale and ScriptEffectColor save and restore m_scale and m_color; the names are not the original's
    mm::Vec3 m_pos;  // 0x160
    mm::Vec3 m_rot;  // 0x170
    mm::Vec3 m_scale;  // 0x180
    mm::Col4 m_color;  // 0x190
};
}  // namespace event

#endif
