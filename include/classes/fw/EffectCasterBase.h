#ifndef CLASSES_FW_EFFECTCASTERBASE_H
#define CLASSES_FW_EFFECTCASTERBASE_H

namespace fw {
// table 0x7100B41320
class EffectCasterBase {
public:
    virtual void vf0() = 0;  // slot 0
    virtual void vf1() = 0;  // slot 1
    virtual ~EffectCasterBase();  // slot 2
};
}  // namespace fw

#endif
