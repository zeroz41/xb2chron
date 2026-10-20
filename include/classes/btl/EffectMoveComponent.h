#ifndef CLASSES_BTL_EFFECTMOVECOMPONENT_H
#define CLASSES_BTL_EFFECTMOVECOMPONENT_H

namespace mm { class Vec3; }

namespace btl {
// table none (its derived classes')
class EffectMoveComponent {
public:
    virtual ~EffectMoveComponent();  // slot 0
    virtual void UpdateNormal(float, float, mm::Vec3 const&);  // slot 2
};
}  // namespace btl

#endif
