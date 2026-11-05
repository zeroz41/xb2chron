#ifndef CLASSES_EVENT_BOURECT_H
#define CLASSES_EVENT_BOURECT_H

#include "mm/Rect.h"

namespace event {
// table 0x7100B3DA20
// the rectangle is a base, not a member: Singleton<BouManager>::getPtr copies Rect<int>::zero() in before it stores
// the table
class BouRect : public mm::Rect<int> {
public:
    // inline: Singleton<BouManager>::getPtr builds BouManager's from Rect<int>::zero()
    BouRect() : mm::Rect<int>(mm::Rect<int>::zero()) {}
    virtual ~BouRect();  // slot 0
};
}  // namespace event

#endif
