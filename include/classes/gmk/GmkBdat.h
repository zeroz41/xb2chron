#ifndef CLASSES_GMK_GMKBDAT_H
#define CLASSES_GMK_GMKBDAT_H

namespace gmk {
// table 0x7100B6BEC8
class GmkBdat {
public:
    virtual ~GmkBdat();  // slot 0
    // not virtual: the destructor and its callers call it directly
    void dispose();
};
}  // namespace gmk

#endif
