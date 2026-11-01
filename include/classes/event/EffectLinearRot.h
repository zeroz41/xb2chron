#ifndef CLASSES_EVENT_EFFECTLINEARROT_H
#define CLASSES_EVENT_EFFECTLINEARROT_H

#include "classes/event/AnmVec.h"
#include "classes/event/ICmd.h"

namespace event { class EffectCtrl; }

namespace event {
// table 0x7100B3E878
class EffectLinearRot : public ::event::ICmd {
public:
    // inline: D2 is emitted after its first use (EffectObj's destructor), D0 sits in CharaObj's tail; update is the
    // key function
    virtual ~EffectLinearRot() {}  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3

    EffectCtrl* m_ctrl;  // 0x8: EffectObj::play stores &EffectObj::m_ctrl (update writes its m_rot)
    AnmVec m_anm;  // 0x10; the names are not the original's
};
}  // namespace event

#endif
