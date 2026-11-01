#ifndef CLASSES_EVENT_EFFECTPLAYEVA_H
#define CLASSES_EVENT_EFFECTPLAYEVA_H

#include "classes/event/ICmd.h"
#include "classes/event/EffectEvaPlayer.h"

namespace event {
// table 0x7100B3E8E8
class EffectPlayEva : public ::event::ICmd {
public:
    // inline: its D2 sits after ~EffectObj (which calls it first), so update is the key function
    virtual ~EffectPlayEva() {}  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    // EffectObj holds one at 0x988; update plays the named eva on m_ctrl (the names are not the original's)
    EffectCtrl* m_ctrl;  // 0x8: update does nothing without it
    void* m_data;  // 0x10: the eva data played; term frees it from the MotstmManager stream
    float m_time;  // 0x18: frames left, val(2) at the start
    EffectEvaPlayer m_player;  // 0x20
};
}  // namespace event

#endif
