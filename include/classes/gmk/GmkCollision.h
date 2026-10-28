#ifndef CLASSES_GMK_GMKCOLLISION_H
#define CLASSES_GMK_GMKCOLLISION_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/IColiEventListener.h"
#include "classes/fw/ColiObject.h"

namespace gmk {
// a base of gmk::GmkCollision no evidence names yet
class TUnk_B6BEE8 {
public:
    virtual const mm::mtl::RTTI* getRTTI() const = 0;
    virtual ~TUnk_B6BEE8() {}  // inline: ~GmkCollision calls no base destructor
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
    // 1.0.0 has it out of line (0x88 bytes); 3.0.1 inlines it into the destructor and the locks' dispose: it
    // detaches the collision object from this listener and releases it
    void dispose() {
        if (m_coliObject != nullptr) {
            m_coliObject->setUserData(nullptr);
            // the original reads the pointer once for these two (an inlined helper's this)
            fw::ColiObject* coli = m_coliObject;
            coli->m_eventMask = 0;
            coli->m_listener = nullptr;
            if (m_coliObject != nullptr) {
                m_coliObject->release();
                m_coliObject = nullptr;
            }
        }
        pad_50 = nullptr;
    }
    static mm::mtl::RTTI m_rtti;
    unsigned char pad_10[0x40];
    void* pad_50;  // dispose clears it
    // the collision object it listens to, referenced while held (the name is not the original's)
    fw::ColiObject* m_coliObject;
    // 0x60: the party leader's collider entered (enter sets it; the names are not the original's)
    bool m_leaderEntered;
    bool m_leaderLeft;  // 0x61: leave sets it
    bool m_leaderInside;  // 0x62: enter sets it, leave clears it
    unsigned char pad_63[0x5];
};
}  // namespace gmk

#endif
