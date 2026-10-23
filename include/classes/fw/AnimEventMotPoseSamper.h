#ifndef CLASSES_FW_ANIMEVENTMOTPOSESAMPER_H
#define CLASSES_FW_ANIMEVENTMOTPOSESAMPER_H

#include "classes/fw/AnimPoseSamper.h"

namespace fw {
// table 0x7100B40D20
class AnimEventMotPoseSamper : public ::fw::AnimPoseSamper {
public:
    AnimEventMotPoseSamper();
    virtual ~AnimEventMotPoseSamper();  // slot 0
    void resetPose();
};
}  // namespace fw

#endif
