#ifndef CLASSES_GF_GFFIELDENEMYSENSOR_H
#define CLASSES_GF_GFFIELDENEMYSENSOR_H

#include "classes/fw/IColiEventListener.h"
#include "classes/fw/ColiObject.h"
#include "classes/gmk/GmkAcc.h"
#include "mm/Mat44.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class IGfBehFieldOwner; }

namespace gf {
// table 0x7100B65DE8
class GfFieldEnemySensor : public ::fw::IColiEventListener {
public:
    virtual void enter(fw::IColiEventListener::EnterInfo const&);  // slot 0
    virtual void leave(fw::IColiEventListener::LeaveInfo const&);  // slot 1
    // inline (GfBehaviorEnemyField's destructor calls this unit's weak copy): clears the flags, releases both
    // collision objects, then the gimmick access goes
    ~GfFieldEnemySensor() { dispose(); }
    // releases its collision objects and clears what they found (inline in GfBehaviorEnemyField::dispose and the
    // destructor; the name is not the original's)
    void dispose() {
        pad_f0 = false;
        m_coli2Hit = false;
        m_radiusSq = 0.0f;
        if (m_coli2 != nullptr) {
            m_coli2->release();
            m_coli2 = nullptr;
        }
        m_coliHit = false;
        pad_99 = false;
        m_rangeSq = 0.0f;
        m_cosHalfAngle = 0.0f;
        if (m_coli != nullptr) {
            m_coli->release();
            m_coli = nullptr;
        }
    }

    // what create copies to 0x10 (GfBehaviorEnemyField::createSensor fills it; the field names are not the original's)
    struct CreateInfo {
        CreateInfo() : m_mtx(mm::Mat44::identity), m_bdatId(-1), m_enArrangeId(-1), m_lockId(-1), m_lockIndex(-1) {}
        mm::Mat44 m_mtx;            // its owner's transform
        unsigned int m_bdatId;      // GfObjSetup::m_bdatId of its object
        unsigned int m_enArrangeId; // its object's CHR_EnArrange row (pad_54)
        // what IGfBehFieldOwner::getGmkBattleLockInfo gives
        int m_lockId;
        int m_lockIndex;
    };
    // disposes, keeps info and reads its rows
    void create(const CreateInfo& info);
    // GfBehaviorEnemyField::update runs it each frame with its object and owner
    void update(gf::GF_OBJ_HANDLE* handle, const gf::IGfBehFieldOwner& owner);
    // reads its CHR_EnArrange row's SearchRange / SearchAngle (pad_60 bit 0) and SearchRadius (bit 1) into
    // m_rangeSq, m_cosHalfAngle and m_radiusSq (BDAT 0x8b; the field names are not the original's)
    void createBy_CHR_EnArrange();

    unsigned char pad_8[0x4c];
    unsigned int pad_54;  // its CHR_EnArrange row (createBy_CHR_EnArrange)
    unsigned char pad_58[0x8];
    unsigned char pad_60;  // bit 0: it searches by range and angle, bit 1: by radius (createBy_CHR_EnArrange)
    unsigned char pad_61[0x27];
    // the collision objects whose events it watches; enter sets, leave clears the flag that follows each
    // (create releases both; the names are not the original's)
    fw::ColiObject* m_coli;
    float m_rangeSq;       // SearchRange squared
    float m_cosHalfAngle;  // the cosine of half SearchAngle (degrees)
    bool m_coliHit;
    bool pad_99;
    unsigned char pad_9a[0x6];
    fw::ColiObject* m_coli2;
    float m_radiusSq;  // SearchRadius squared
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
