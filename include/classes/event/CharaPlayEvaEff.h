#ifndef CLASSES_EVENT_CHARAPLAYEVAEFF_H
#define CLASSES_EVENT_CHARAPLAYEVAEFF_H

#include "classes/event/ICmd.h"
#include "classes/event/CharaEvaPlayerEff.h"

namespace gf { class GfEvtModel; }

namespace event {
// table 0x7100B3E6F0
class CharaPlayEvaEff : public ::event::ICmd {
public:
    // inline: its D2 sits before ~CharaObj (which calls it first), so update is the key function
    CharaPlayEvaEff() : m_flags(0), m_model(nullptr), m_effectPlayer(nullptr), m_data(nullptr) {}
    virtual ~CharaPlayEvaEff() {}  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    // CharaObj holds one at 0x8e0; update plays the named model's "_eff.eva" on m_model (the names are not the
    // original's)
    // bit 0: m_data is held (term frees it), bit 1: no end time (val(2) <= 0)
    unsigned int m_flags;  // 0x8
    gf::GfEvtModel* m_model;  // 0x10: update does nothing without it or its object
    CharaEffectPlayer* m_effectPlayer;  // 0x18: passed to m_player.play
    void* m_data;  // 0x20: the eva data played; freed from the MotstmManager stream in stream mode
    float m_time;  // 0x28: frames left, val(2) at the start
    CharaEvaPlayerEff m_player;  // 0x30
};
}  // namespace event

#endif
