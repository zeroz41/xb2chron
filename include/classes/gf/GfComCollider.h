#ifndef CLASSES_GF_GFCOMCOLLIDER_H
#define CLASSES_GF_GFCOMCOLLIDER_H

#include "classes/fw/IColiEventListener.h"
#include "classes/gf/GfComponent.h"

namespace gf {
// a base of gf::GfComCollider no evidence names yet
class TUnk_B66270 {
public:
    virtual void enter(fw::IColiEventListener::EnterInfo const&) = 0;
    virtual void leave(fw::IColiEventListener::LeaveInfo const&) = 0;
    virtual void contact(fw::IColiEventListener::EnterInfo const&) = 0;
};
// table 0x7100B66220; base at 0x10 unknown (TUnk_B66270)
class GfComCollider : public ::gf::GfComponent, public TUnk_B66270 {
public:
    class UserData;
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComCollider();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual void enter(fw::IColiEventListener::EnterInfo const&);  // slot 5
    virtual void leave(fw::IColiEventListener::LeaveInfo const&);  // slot 6
    virtual void contact(fw::IColiEventListener::EnterInfo const&);  // slot 7
};
}  // namespace gf

#endif
