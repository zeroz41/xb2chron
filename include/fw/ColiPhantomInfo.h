#ifndef FW_COLIPHANTOMINFO_H
#define FW_COLIPHANTOMINFO_H

#include "mm/Mat44.h"
#include "classes/fw/ColiObject.h"

namespace fw { class ColiUserData; }
namespace fw { class IColiEventListener; }

namespace fw {
// what ColiObject::setupColiPhantom builds a phantom's collision object from (no table; inline constructor: the
// gimmick phantoms' create build one on their stack, then set the follow type and pad_14; the field names are not
// the original's, ColiCharacterInfo has the same layout)
class ColiPhantomInfo {
public:
    ColiPhantomInfo()
        : pad_0(1), m_priority(100), m_stateFlags(3), m_hitMaterialFlag(~5u), m_scale(1.0f), m_userData(nullptr),
          m_eventMask(0), m_listener(nullptr), m_shape(nullptr) {
        m_matrix = mm::Mat44::identity;
    }
    int pad_0;                            // the constructor's 1; no reader seen yet
    fw::ColiType m_followType;            // the object's m_followType
    int m_priority;                       // IDColiParmsBase::setPriority's
    unsigned int m_stateFlags;            // bits 0 and 1: IDColiParmsBase::setState (else clearState) of states 0, 1
    unsigned int m_hitMaterialFlag;       // as ColiObject::setHitMaterialFlag's (setOffMaterialBit of its complement)
    unsigned int pad_14;                  // the phantoms' create set it; no reader seen yet
    float m_scale;                        // the object's m_scale
    fw::ColiUserData* m_userData;         // the object's m_userData
    unsigned int m_eventMask;             // the object's m_eventMask
    unsigned char pad_2c[0x4];
    fw::IColiEventListener* m_listener;  // the object's m_listener
    unsigned char pad_38[0x8];
    mm::Mat44 m_matrix;                   // 0x40: the object's matrix at 0x60
    const ColiShape* m_shape;             // 0x80: its shape, the first word its kind
};
}  // namespace fw

#endif
