#ifndef CLASSES_ML_DEVTOUCH_H
#define CLASSES_ML_DEVTOUCH_H

#include "classes/ml/IDevInputTouch.h"
#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Vec2.h"
#include "mm/mtl/FixedVector.h"

namespace ml {
namespace dev_touch_detail {
// a new touch's positions before it reports any: (-1, -1) (the file's static initializer sets it)
extern mm::Vec2 s_initPos;
}  // namespace dev_touch_detail

// table 0x7100B75FD8; its base at 0x1A8 is ml::IDevInputTouch (the touch device's callbacks), at 0x1B0 its
// singleton (the inline destructor stores PtrSingleton<ml::DevTouch>'s table there and clears its instance)
class DevTouch : public ::ml::WorkObj, public ::ml::IDevInputTouch, public ::mm::mtl::PtrSingleton<DevTouch> {
public:
    // one touch being tracked, by the device's finger id (the names are not the original's)
    struct Touch {
        long m_clock;           // 0x00 the clock when it went down (wkUpdate's base for m_time)
        float m_time;           // 0x08 seconds since it went down
        unsigned int m_id;      // 0x0C the device's finger id
        unsigned short pad_10;  // 0x10
        mm::Vec2 m_downPos;     // 0x20 where it went down
        mm::Vec2 m_pos;         // 0x30 where it is
        mm::Vec2 pad_40;        // 0x40
        mm::Vec2 m_move;        // 0x50 the last move (itMove: the new position less the old)
    };

    // inline: the original keeps its copies in the weak tail (wkUpdate is the key function)
    // inline: DevTouchNx's constructor runs it (the original has no out-of-line copy)
    DevTouch(const char* name, WorkObj* parent) : WorkObj(name, parent, 0) {}
    virtual ~DevTouch() {}  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    virtual void itDown(unsigned int id, float x, float y);  // slot 17
    virtual void itUp(unsigned int id, float x, float y);  // slot 18
    virtual void itMove(unsigned int id, float x, float y);  // slot 19
    virtual void updateDevice();  // slot 20
    virtual bool createDevice() = 0;  // slot 21
    virtual void releaseDevice() = 0;  // slot 22

    unsigned char pad_1b8[0x8];
    mm::mtl::FixedVector<Touch, 16> m_touch;  // 0x1C0
};
}  // namespace ml

#endif
