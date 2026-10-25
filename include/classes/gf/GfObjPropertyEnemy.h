#ifndef CLASSES_GF_GFOBJPROPERTYENEMY_H
#define CLASSES_GF_GFOBJPROPERTYENEMY_H

#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObjPropertyCharacter.h"

namespace gf {
// table 0x7100B6A2E8; an enemy's property (GfObjProperty::create's for type 5, 0x160 bytes; GfObjProperty::getEnemy
// returns the property itself as one)
class GfObjPropertyEnemy : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyEnemy(GF_OBJ_HANDLE* handle);
    virtual ~GfObjPropertyEnemy() {}  // slot 0

    GfObjPropertyCharacter m_characterPart;  // 0x88: m_character points at it (the name is not the original's)
    unsigned char pad_C0[0x2];
    // what GfMenuGfObjAdapter's callbacks show (update_EN_<name>; the field names are not the original's)
    bool m_scout;
    unsigned char pad_C3[0x1];
    unsigned int m_artsId;  // the art it is using (0: none)
    unsigned char pad_C8[0x10];
    unsigned int m_weakAttr;  // bit n: weak to element n (1..8)
    // the elemental combo on the enemy and its level (1.0.0's GfMenuElementComboAdapter::getTargetElementComboId
    // and getTargetElementComboLv return them; the field names are not the original's)
    unsigned int m_elementComboId;
    float m_elementComboTime;  // the rest, 0..1
    bool m_elementComboSuspend;
    unsigned char pad_E5[0x3];
    unsigned int m_elementComboLv;
    // the fight combo on it (update_EN_FightCombo*; the field names are not the original's)
    unsigned int m_fightCombo;  // 0 none, else 1 + its icon
    float m_fightComboTime;     // the rest, 0..1
    bool m_fightComboSuspend;
    unsigned char pad_F5[0x3];
    int m_elemEffId;  // update_EN_ElemEffID's number
    // per element (1..8): bit 0 on, bit 1 target, bit 2 burst, and a level (update_EN_ResAttr*)
    struct ResAttr {
        unsigned short m_flags;
        unsigned short m_level;
    };
    ResAttr m_resAttrs[9];
    // the elements shown, by GfMenuGfObjAdapter::m_index, and their count
    unsigned int m_resAttrList[10];
    unsigned long m_resAttrCount;
    unsigned char pad_150[0x4];
    bool pad_154;  // fn_710033FB0C's answer
    bool pad_155;  // fn_710033FB70's answer
    unsigned char pad_156[0xA];
};
}  // namespace gf

#endif
