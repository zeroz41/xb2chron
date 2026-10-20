#ifndef CLASSES_FW_ANIMVOLUMEFADEMODIFIER_H
#define CLASSES_FW_ANIMVOLUMEFADEMODIFIER_H

namespace fw {
// table 0x7100B40B48
class AnimVolumeFadeModifier {
public:
    virtual ~AnimVolumeFadeModifier();  // slot 0
    virtual void apply();  // slot 2
};
}  // namespace fw

#endif
