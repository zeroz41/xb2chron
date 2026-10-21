#ifndef CLASSES_GMK_GMKCOLLISION_H
#define CLASSES_GMK_GMKCOLLISION_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/IColiEventListener.h"

namespace gmk {
// a base of gmk::GmkCollision no evidence names yet
class TUnk_B6BEE8 {
public:
    virtual const mm::mtl::RTTI* getRTTI() const = 0;
    virtual ~TUnk_B6BEE8();
    virtual void enter(fw::IColiEventListener::EnterInfo const&) = 0;
    virtual void leave(fw::IColiEventListener::LeaveInfo const&) = 0;
};
// table 0x7100B6BEE8; base at 0x0 unknown (TUnk_B6BEE8)
class GmkCollision : public TUnk_B6BEE8, public ::fw::IColiEventListener {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GmkCollision();  // slot 1
    virtual void enter(fw::IColiEventListener::EnterInfo const&);  // slot 3
    virtual void leave(fw::IColiEventListener::LeaveInfo const&);  // slot 4
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gmk

#endif
