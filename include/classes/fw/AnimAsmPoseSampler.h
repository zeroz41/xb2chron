#ifndef CLASSES_FW_ANIMASMPOSESAMPLER_H
#define CLASSES_FW_ANIMASMPOSESAMPLER_H

namespace fw {
// table 0x7100B40CF8
class AnimAsmPoseSampler {
public:
    virtual ~AnimAsmPoseSampler();  // slot 0
    virtual void samplePose();  // slot 2
};
}  // namespace fw

#endif
