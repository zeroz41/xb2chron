#ifndef CLASSES_FW_ANIMPOSEMODIFIER_H
#define CLASSES_FW_ANIMPOSEMODIFIER_H

namespace fw {
// table 0x7100B40C80
class AnimPoseModifier {
public:
    virtual ~AnimPoseModifier();  // slot 0
    virtual void apply();  // slot 2
};
}  // namespace fw

#endif
