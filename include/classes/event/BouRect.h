#ifndef CLASSES_EVENT_BOURECT_H
#define CLASSES_EVENT_BOURECT_H

#include "mm/Rect.h"
#include "mm/Vec3.h"

namespace event {
// table 0x7100B3DA20
// the rectangle is a base, not a member: Singleton<BouManager>::getPtr copies Rect<int>::zero() in before it stores
// the table
class BouRect : public mm::Rect<int> {
public:
    // inline: Singleton<BouManager>::getPtr builds BouManager's from Rect<int>::zero()
    BouRect() : mm::Rect<int>(mm::Rect<int>::zero()) {}
    virtual ~BouRect();  // slot 0
    // whether a world position's screen point (the current view's camera) lies in the rectangle, a negative
    // size spanning to the left/up of the corner (ObjectChara/ObjectEffect::OnBouRectSelect)
    bool isInside(const mm::Vec3& pos) const;
};
}  // namespace event

#endif
