#ifndef FW_COLICHARACTERINFO_H
#define FW_COLICHARACTERINFO_H

namespace fw { class ColiUserData; }
namespace fw { class IColiEventListener; }

namespace fw {
// what ColiObject::setupColiCharacter builds a character's collision object from (no table; the field names are
// not the original's)
class ColiCharacterInfo {
public:
    unsigned char pad_0[0x20];
    fw::ColiUserData* m_userData;         // the object's m_userData
    unsigned int m_eventMask;             // the object's m_eventMask
    unsigned char pad_2c[0x4];
    fw::IColiEventListener* m_listener;  // the object's m_listener
    unsigned char pad_38[0x48];
    // its shape: the first word its kind (GfComCollider::createColi binds a pose modifier to a kind 5 one)
    const int* m_shape;
};
}  // namespace fw

#endif
