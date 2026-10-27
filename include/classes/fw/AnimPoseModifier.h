#ifndef CLASSES_FW_ANIMPOSEMODIFIER_H
#define CLASSES_FW_ANIMPOSEMODIFIER_H

#include "mm/mtl/IntrusivePtr.h"

namespace fw {
class ReferenceFrame;
// table 0x7100B40C80
class AnimPoseModifier {
public:
    // makes frame follow the pose's bone (GfComModel::createBoneReferenceFrameImpl)
    void bindReferenceFrameToBone(unsigned short bone, mm::mtl::IntrusivePtr<ReferenceFrame>& frame);
    AnimPoseModifier();
    virtual ~AnimPoseModifier();  // slot 0
    virtual void apply();  // slot 2
    unsigned char pad_8[0x1080];  // 0x1088 bytes: GfComModel holds one at 0x40, its volume fade follows at 0x10c8
};
}  // namespace fw

#endif
