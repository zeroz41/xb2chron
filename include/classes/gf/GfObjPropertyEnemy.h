#ifndef CLASSES_GF_GFOBJPROPERTYENEMY_H
#define CLASSES_GF_GFOBJPROPERTYENEMY_H

#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObjPropertyCharacter.h"
#include "mm/mtl/FixedVector.h"

namespace gf {
// table 0x7100B6A2E8; an enemy's property (GfObjProperty::create's for type 5, 0x160 bytes; GfObjProperty::getEnemy
// returns the property itself as one)
class GfObjPropertyEnemy : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyEnemy(GF_OBJ_HANDLE* handle);
    virtual ~GfObjPropertyEnemy() {}  // slot 0

    GfObjPropertyCharacter m_characterPart;  // 0x88: m_character points at it (the name is not the original's)
    // 0xC0..0x120 (but m_resAttrs) are cleared by the constructor's body only
    unsigned short pad_C0;
    // what GfMenuGfObjAdapter's callbacks show (update_EN_<name>; the field names are not the original's)
    bool m_scout;
    unsigned char pad_C3;
    unsigned int m_artsId;  // the art it is using (0: none)
    // a message for the art (GfMenuObjVision::MainListener::reciveEvent shows it in TXT_arts, its id as 16 bits, 0 read as 1) and
    // the message data it is in (the names are not the original's)
    unsigned int m_artsNameId;
    unsigned char* m_artsNameBdat;
    unsigned int m_weakAttr;  // bit n: weak to element n (1..8)
    // the elemental combo on the enemy and its level (1.0.0's GfMenuElementComboAdapter::getTargetElementComboId
    // and getTargetElementComboLv return them; the field names are not the original's)
    unsigned int m_elementComboId;
    float m_elementComboTime;  // the rest, 0..1
    bool m_elementComboSuspend;
    unsigned int m_elementComboLv;
    // the fight combo on it (update_EN_FightCombo*; the field names are not the original's)
    unsigned int m_fightCombo;  // 0 none, else 1 + its icon
    float m_fightComboTime;     // the rest, 0..1
    bool m_fightComboSuspend;
    int m_elemEffId;  // update_EN_ElemEffID's number
    // per element (1..8): bit 0 on, bit 1 target, bit 2 burst, and a level (update_EN_ResAttr*)
    struct ResAttr {
        ResAttr() : m_flags(0), m_level(0) {}
        unsigned short m_flags;
        unsigned short m_level;
    };
    ResAttr m_resAttrs[9];
    // the elements shown, by GfMenuGfObjAdapter::m_index, and their count
    mm::mtl::FixedVector<unsigned int, 10> m_resAttrList;
    unsigned int pad_150;
    bool pad_154;  // update_EN_Angry's answer
    bool pad_155;  // update_EN_Awake's answer
    unsigned char pad_156[0xA];
};
}  // namespace gf

#endif
