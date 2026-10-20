#ifndef CLASSES_FW_ANIMCOLPOSEMODIFIER_H
#define CLASSES_FW_ANIMCOLPOSEMODIFIER_H

namespace fw {
// table 0x7100B40B20
class AnimColPoseModifier {
public:
    virtual ~AnimColPoseModifier();  // slot 0
    virtual void apply();  // slot 2
};
}  // namespace fw

#endif
