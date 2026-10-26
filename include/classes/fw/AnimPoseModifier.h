#ifndef CLASSES_FW_ANIMPOSEMODIFIER_H
#define CLASSES_FW_ANIMPOSEMODIFIER_H

namespace fw {
// table 0x7100B40C80
class AnimPoseModifier {
public:
    AnimPoseModifier();
    virtual ~AnimPoseModifier();  // slot 0
    virtual void apply();  // slot 2
    unsigned char pad_8[0x1080];  // 0x1088 bytes: GfComModel holds one at 0x40, its volume fade follows at 0x10c8
};
}  // namespace fw

#endif
