#ifndef CLASSES_GMK_GMKSET_H
#define CLASSES_GMK_GMKSET_H

namespace gmk {
// table 0x7100B6BDF0
class GmkSet {
public:
    virtual ~GmkSet();  // slot 0
    virtual void createGmkLists(int);  // slot 2
};
}  // namespace gmk

#endif
