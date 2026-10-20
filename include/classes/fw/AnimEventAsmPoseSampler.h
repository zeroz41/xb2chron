#ifndef CLASSES_FW_ANIMEVENTASMPOSESAMPLER_H
#define CLASSES_FW_ANIMEVENTASMPOSESAMPLER_H

namespace fw {
// table 0x7100B40D48
class AnimEventAsmPoseSampler {
public:
    virtual ~AnimEventAsmPoseSampler();  // slot 0
    virtual void samplePose();  // slot 2
};
}  // namespace fw

#endif
