#ifndef CLASSES_GMK_IGMKPHANTOMEVENTLISTENER_H
#define CLASSES_GMK_IGMKPHANTOMEVENTLISTENER_H

namespace gmk {
// table 0x7100B6F228
class IGmkPhantomEventListener {
public:
    class OnEnterInfo;
    class OnLeaveInfo;
    virtual void vf0() = 0;  // slot 0
    virtual void vf1() = 0;  // slot 1
};
}  // namespace gmk

#endif
