#ifndef CLASSES_EVENT_EFFECTEVAPLAYER_H
#define CLASSES_EVENT_EFFECTEVAPLAYER_H

class RchaEff;
namespace event { class EffectCtrl; }

namespace event {
// table 0x7100B3CE70
class EffectEvaPlayer {
public:
    virtual ~EffectEvaPlayer();  // slot 0
    void play(EffectCtrl* ctrl, void* data);
    void update(float step);
    // 1.0.0's EffectEvaPlayer::stop (0x71000DAC30; 3.0.1 inlines it into EffectPlayEva::update)
    void stop() {
        if (m_rcha) {
            delete m_rcha;
            m_rcha = nullptr;
        }
        m_ctrl = nullptr;
    }
    // play (0x71000F1510) stores its EffectCtrl here, then a new RchaEff it sets up (the names are not the original's)
    EffectCtrl* m_ctrl;  // 0x8
    RchaEff* m_rcha;  // 0x10
    unsigned int pad_18;  // 0x18: play clears it
};
}  // namespace event

#endif
