#ifndef CLASSES_GF_GFFIELDENEMYSENSOR_H
#define CLASSES_GF_GFFIELDENEMYSENSOR_H

#include "classes/fw/IColiEventListener.h"
#include "classes/fw/ColiObject.h"
#include "classes/gmk/GmkAcc.h"

namespace gf {
// table 0x7100B65DE8
class GfFieldEnemySensor : public ::fw::IColiEventListener {
public:
    virtual void enter(fw::IColiEventListener::EnterInfo const&);  // slot 0
    virtual void leave(fw::IColiEventListener::LeaveInfo const&);  // slot 1
    // inline (GfBehaviorEnemyField's destructor calls this unit's weak copy): clears the flags, releases both
    // collision objects, then the gimmick access goes
    ~GfFieldEnemySensor() {
        pad_f0 = false;
        m_coli2Hit = false;
        pad_a8 = 0;
        if (m_coli2 != nullptr) {
            m_coli2->release();
            m_coli2 = nullptr;
        }
        m_coliHit = false;
        pad_99 = false;
        pad_90 = 0;
        if (m_coli != nullptr) {
            m_coli->release();
            m_coli = nullptr;
        }
    }

    unsigned char pad_8[0x80];
    // the collision objects whose events it watches; enter sets, leave clears the flag that follows each
    // (create releases both; the names are not the original's)
    fw::ColiObject* m_coli;
    unsigned long pad_90;
    bool m_coliHit;
    bool pad_99;
    unsigned char pad_9a[0x6];
    fw::ColiObject* m_coli2;
    unsigned int pad_a8;
    bool m_coli2Hit;
    unsigned char pad_ad[0x3];
    // the battle lock gimmick (type 11) the enemy is counted in (create makes it from its CreateInfo's row; the
    // name is not the original's)
    gmk::GmkAcc m_gmkAcc;
    bool pad_f0;
    unsigned char pad_f1[0xF];
};
}  // namespace gf

#endif
