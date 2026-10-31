#ifndef CLASSES_EVENT_CHARAEVAPLAYEREFF_H
#define CLASSES_EVENT_CHARAEVAPLAYEREFF_H

class RchaChrEff;
namespace gf { class GfEvtModel; }
namespace event { class CharaEffectPlayer; }

namespace event {
// table 0x7100B3CC10
class CharaEvaPlayerEff {
public:
    virtual ~CharaEvaPlayerEff();  // slot 0
    // play (0x71000E2E28) stores its model and player here, then a new RchaChrEff it sets up (the names are not the
    // original's)
    gf::GfEvtModel* m_model;  // 0x8
    CharaEffectPlayer* m_player;  // 0x10
    RchaChrEff* m_rcha;  // 0x18
    unsigned int pad_20;  // 0x20: play clears it
};
}  // namespace event

#endif
