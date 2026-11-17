#ifndef CLASSES_GMK_GMKCOLLISION_H
#define CLASSES_GMK_GMKCOLLISION_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/IColiEventListener.h"
#include "classes/fw/ColiObject.h"
#include "classes/fw/ColiUserData.h"
#include "mm/Vec3.h"

namespace gmk {
// a base of gmk::GmkCollision no evidence names yet; a fw::ColiUserData (GmkCollision::m_rtti's base, and create
// hands the collision object `this` as its user data)
class TUnk_B6BEE8 : public fw::ColiUserData {
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
        m_name = nullptr;
    }
    // what create builds the collision object from (create's parameter; kept in m_info). The field names are not
    // the original's: create reads m_type 1 as a sphere (m_size[0]), 2 as a capsule (m_size[0..1]), 3 as a box
    // (m_size[0..2]), and m_pos/m_rot as the collision's position and rotation angles
    class CreateInfo {
    public:
        // user-provided: Vector<GmkFieldLock/GmkBattleLock>::resize store these, no zero fill; its copy is its
        // own (mm::Vec3), so the gimmick's copy copies it apart from the fields after it
        CreateInfo() : m_type(0), m_pos(0.0f, 0.0f, 0.0f), m_rot(0.0f, 0.0f, 0.0f), pad_30(false) {
            // a loop: the locks' createGmkCollision store size[2], then size[0..1] as one word pair
            for (int i = 0; i < 3; i++) {
                m_size[i] = 0.0f;
            }
        }
        unsigned int m_type;
        mm::Vec3 m_pos;     // 0x10
        mm::Vec3 m_rot;     // 0x20
        bool pad_30;        // 0x30: set with a capsule or box (create then makes m_type 2 unless 2 or 3)
        float m_size[3];    // 0x34
    };
    // user-provided: Vector<GmkFieldLock/GmkBattleLock>::resize store these defaults only (no zero fill)
    GmkCollision() : m_name(nullptr), m_coliObject(nullptr), m_leaderEntered(false), m_leaderLeft(false), m_leaderInside(false) {}
    void create(const CreateInfo& info);
    static mm::mtl::RTTI m_rtti;
    CreateInfo m_info;  // 0x10: create keeps a copy (the name is not the original's)
    // the gimmick's INFO name (the locks' createGmkCollision take LvlbInfo::m_name; dispose clears it; the name is
    // not the original's)
    const char* m_name;
    // the collision object it listens to, referenced while held (the name is not the original's)
    fw::ColiObject* m_coliObject;
    // 0x60: the party leader's collider entered (enter sets it; the names are not the original's)
    bool m_leaderEntered;
    bool m_leaderLeft;  // 0x61: leave sets it
    bool m_leaderInside;  // 0x62: enter sets it, leave clears it (0x63..0x6f: tail padding, not stored)
};
}  // namespace gmk

#endif
