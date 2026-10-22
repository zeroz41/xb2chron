#ifndef CLASSES_GF_GFOBJPROPERTY_H
#define CLASSES_GF_GFOBJPROPERTY_H

#include "mm/Quat.h"
#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfObjPropertyBlade; }
namespace gf { class GfObjPropertyDriver; }
namespace gf { class GfObjPropertyCharacter; }
namespace gf { class GfObjPropertyEnemy; }
namespace gf { class GfTargetProperty; }

namespace gf {
// table 0x7100B6A288; what an object's info holds about it (GfObjManager::createGfObjProperty stores
// GfObjProperty::create's at the info's 0x98, GfObjUtil::getProperty returns it): 0x90 bytes, the base of
// GfObjPropertyMap/Driver/Blade/Enemy/Npc/Mob/Gimmick..., chosen by GfObjUtil::getObjType
class GfObjProperty {
public:
    explicit GfObjProperty(GF_OBJ_HANDLE* handle)
        : m_handle(handle), m_character(nullptr), m_target(nullptr), pad_40(false), pad_80(0) {
        pad_20 = mm::Vec3::zero;
        pad_30 = mm::Quat::identity;
    }
    virtual ~GfObjProperty() {}  // slot 0
    // the property for the handle's object, of the class its type (GfObjUtil::getObjType) calls for; none for
    // type 2 and the unknown ones
    static GfObjProperty* create(GF_OBJ_HANDLE* handle);
    GfObjPropertyDriver* getDriver();  // itself when its object is a driver (GfObjUtil::getObjType 3), else none
    GfObjPropertyBlade* getBlade();  // itself when its object is a blade (GfObjUtil::getObjType 4), else none
    GfObjPropertyEnemy* getEnemy();  // itself when its object is an enemy (GfObjUtil::getObjType 5), else none
    GF_OBJ_HANDLE* m_handle;  // create's; getEnemy asks GfObjUtil::getObjType about it
    // the character part of a driver, blade or enemy (GfObjPropertyDriver's and GfObjPropertyEnemy's constructors
    // point it at their GfObjPropertyCharacter at 0x88), none for the others; the name is not the original's
    GfObjPropertyCharacter* m_character;
    // what those targeting or following the object read (GfObjPropertyDriver's constructor points it at its own at
    // 0xC0, GfComPropertyPc::procMsgObjectFlushProperty fills it, the PCs' field AI reads it), none for the others;
    // the name is not the original's
    GfTargetProperty* m_target;
    // the constructor sets these (a zero vector, the identity rotation, false and 0); nothing in 3.0.1 reads them.
    // The class is 16-aligned: GfObjPropertyMap and the others with no fields of their own take 0x90 bytes, while
    // GfObjPropertyDriver's first field reuses the tail at 0x88
    alignas(16) mm::Vec3 pad_20;
    mm::Quat pad_30;
    bool pad_40;
    unsigned char pad_41[0x3F];
    unsigned int pad_80;
};
}  // namespace gf

#endif
