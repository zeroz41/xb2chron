#ifndef CLASSES_EVENT_CAMEVAPLAYEREFF_H
#define CLASSES_EVENT_CAMEVAPLAYEREFF_H

#include "classes/RchaCamEff.h"

namespace event {
// table 0x7100B3C7F8
class CamEvaPlayerEff {
public:
    virtual ~CamEvaPlayerEff();  // slot 0
    void update(float step);  // CamMotion::update calls it with the frame's step (3.0.1 symbol)
    // play (0x71000CA924) clears and frees the previous one, then stores a new RchaCamEff it sets up (the name is not
    // the original's)
    // 1.0.0's CamEvaPlayerEff::stop (0x71000AF0E8; 3.0.1 inlines it): clears and frees the RchaCamEff
    void stop() {
        if (m_rcha) {
            m_rcha->clear();
            if (m_rcha) {
                delete m_rcha;
                m_rcha = nullptr;
            }
        }
    }
    // named by the symbols: frees the previous RchaCamEff and sets up a new one on data
    void play(void* data);
    RchaCamEff* m_rcha;  // 0x8
    unsigned int pad_10;  // 0x10: play clears it
};
}  // namespace event

#endif
