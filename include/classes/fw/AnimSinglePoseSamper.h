#ifndef CLASSES_FW_ANIMSINGLEPOSESAMPER_H
#define CLASSES_FW_ANIMSINGLEPOSESAMPER_H

namespace fw {
// table 0x7100B40CA8
class AnimSinglePoseSamper {
public:
    virtual ~AnimSinglePoseSamper();  // slot 0
    virtual void samplePose();  // slot 2
};
}  // namespace fw

#endif
