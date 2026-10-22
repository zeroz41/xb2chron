#ifndef CLASSES_GF_GFOBJPROPERTY_H
#define CLASSES_GF_GFOBJPROPERTY_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfObjPropertyCharacter; }
namespace gf { class GfObjPropertyEnemy; }
namespace gf { class GfTargetProperty; }

namespace gf {
// table 0x7100B6A288; what an object's info holds about it (GfObjManager::createGfObjProperty stores
// GfObjProperty::create's at the info's 0x98, GfObjUtil::getProperty returns it): 0x90 bytes, the base of
// GfObjPropertyMap/Driver/Blade/Enemy/Npc/Mob/Gimmick..., chosen by GfObjUtil::getObjType
class GfObjProperty {
public:
    virtual ~GfObjProperty() {}  // slot 0
    GfObjPropertyEnemy* getEnemy();  // itself when its object is an enemy (GfObjUtil::getObjType 5), else none
    GF_OBJ_HANDLE* m_handle;  // create's; getEnemy asks GfObjUtil::getObjType about it
    // the character part of a driver, blade or enemy (GfObjPropertyDriver's and GfObjPropertyEnemy's constructors
    // point it at their GfObjPropertyCharacter at 0x88), none for the others; the name is not the original's
    GfObjPropertyCharacter* m_character;
    // what those targeting or following the object read (GfObjPropertyDriver's constructor points it at its own at
    // 0xC0, GfComPropertyPc::procMsgObjectFlushProperty fills it, the PCs' field AI reads it), none for the others;
    // the name is not the original's
    GfTargetProperty* m_target;
    unsigned char pad_20[0x70];  // a Vec3 (zero) at 0x20, a Quat (identity) at 0x30, a flag at 0x40, a word at 0x80
};
}  // namespace gf

#endif
