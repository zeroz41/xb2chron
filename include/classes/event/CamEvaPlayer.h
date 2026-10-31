#ifndef CLASSES_EVENT_CAMEVAPLAYER_H
#define CLASSES_EVENT_CAMEVAPLAYER_H

class RchaCam;
namespace event { class CamBase; }

namespace event {
// table 0x7100B3C7D8
class CamEvaPlayer {
public:
    virtual ~CamEvaPlayer();  // slot 0
    // play (0x71000CA354) clears and frees the previous RchaCam, then stores its camera and a new RchaCam it sets up
    // (the names are not the original's)
    CamBase* m_cam;  // 0x8
    RchaCam* m_rcha;  // 0x10
};
}  // namespace event

#endif
