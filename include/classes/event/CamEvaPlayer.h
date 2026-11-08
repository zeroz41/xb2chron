#ifndef CLASSES_EVENT_CAMEVAPLAYER_H
#define CLASSES_EVENT_CAMEVAPLAYER_H

#include "mm/Vec3.h"
#include "classes/RchaCam.h"

class RchaCam;
namespace event { class CamBase; }

namespace event {
// table 0x7100B3C7D8
class CamEvaPlayer {
public:
    virtual ~CamEvaPlayer();  // slot 0
    void update(float step);  // CamMotion::update calls it with the frame's step (3.0.1 symbol)
    // play (0x71000CA354) clears and frees the previous RchaCam, then stores its camera and a new RchaCam it sets up
    // (the names are not the original's)
    // 1.0.0's CamEvaPlayer::stop (0x71000AD588; 3.0.1 inlines it): clears and frees the RchaCam, forgets the camera
    void stop() {
        if (m_rcha) {
            m_rcha->clear();
            if (m_rcha) {
                delete m_rcha;
                m_rcha = nullptr;
            }
        }
        m_cam = nullptr;
    }
    // named by the symbols: frees the previous RchaCam, keeps the camera, sets up a new RchaCam on data and keeps pos
    void play(CamBase* cam, void* data, const mm::Vec3& pos);
    CamBase* m_cam;  // 0x8
    RchaCam* m_rcha;  // 0x10
    unsigned int pad_18;  // 0x18: play clears it
    mm::Vec3 m_pos;  // 0x20: play copies its position argument here; the name is not the original's
    unsigned int pad_30;  // 0x30: play clears it
};
}  // namespace event

#endif
