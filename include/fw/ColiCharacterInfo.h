#ifndef FW_COLICHARACTERINFO_H
#define FW_COLICHARACTERINFO_H

#include "mm/Mat44.h"
#include "classes/fw/ColiObject.h"

namespace fw { class ColiUserData; }
namespace fw { class IColiEventListener; }

namespace fw {
// what ColiObject::setupColiCharacter builds a character's collision object from (no table; inline constructor:
// gmk::GmkCollision::create builds one on its stack, then sets the rest; the field names are not the original's,
// ColiPhantomInfo has the same layout)
class ColiCharacterInfo {
public:
    ColiCharacterInfo() : pad_0(0), m_hitMaterialFlag(~5u), m_scale(1.0f), m_shape(nullptr) {
        m_matrix = mm::Mat44::identity;
    }
    int pad_0;                            // the constructor's 0; no reader seen yet
    fw::ColiType m_followType;            // the object's m_followType
    int m_priority;                       // IDColiParmsBase::setPriority's
    unsigned int m_stateFlags;            // bits 0 and 1: IDColiParmsBase::setState (else clearState) of states 0, 1
    unsigned int m_hitMaterialFlag;       // as ColiObject::setHitMaterialFlag's (setOffMaterialBit of its complement)
    unsigned int pad_14;                  // GmkCollision::create sets it; no reader seen yet
    float m_scale;                        // the object's m_scale
    fw::ColiUserData* m_userData;         // the object's m_userData
    unsigned int m_eventMask;             // the object's m_eventMask
    unsigned char pad_2c[0x4];
    fw::IColiEventListener* m_listener;  // the object's m_listener
    unsigned char pad_38[0x8];
    mm::Mat44 m_matrix;                   // 0x40: the object's matrix at 0x60
    // its shape: the first word its kind (GfComCollider::createColi binds a pose modifier to a kind 5 one)
    const ColiShape* m_shape;
};
}  // namespace fw

#endif
