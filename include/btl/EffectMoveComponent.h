#ifndef BTL_EFFECTMOVECOMPONENT_H
#define BTL_EFFECTMOVECOMPONENT_H

namespace mm { class Vec3; }

namespace btl {
// an effect's movement (application/BF2/battle/EffectMoveComponent); EffectObject holds one at 0x1C0, up to its
// 0x270 field, so 0xB0 bytes
class EffectMoveComponent {
public:
    // what EffectObject::SetMoveParam passes on to Initialize
    struct MOVE_PARAM;

    EffectMoveComponent();
    void Initialize();
    void Initialize(const MOVE_PARAM& param);
    bool IsEnd(const mm::Vec3& pos, mm::Vec3& out, float rate) const;

    unsigned char pad_0[0xB0];
};
}  // namespace btl

#endif
