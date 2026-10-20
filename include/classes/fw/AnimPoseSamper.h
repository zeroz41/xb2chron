#ifndef CLASSES_FW_ANIMPOSESAMPER_H
#define CLASSES_FW_ANIMPOSESAMPER_H

namespace fw {
// table 0x7100B40CD0
class AnimPoseSamper {
public:
    virtual ~AnimPoseSamper();  // slot 0
    virtual void samplePose();  // slot 2
};
}  // namespace fw

#endif
