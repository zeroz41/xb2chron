#ifndef CLASSES_FW_EFFECTPOINT_H
#define CLASSES_FW_EFFECTPOINT_H

namespace fw {
// table 0x7100B41648
class EffectPoint {
public:
    virtual ~EffectPoint();  // slot 0

    int m_refCount;  // EffectCasterBase's constructor counts it (the name is not the original's)
    // EffectCasterBase::changeLayer sets it to the caster's new layer (the name is not the original's)
    unsigned int m_layer;
};
}  // namespace fw

#endif
