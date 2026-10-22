#ifndef CLASSES_GF_GFMENUFIELDSKILLLIST_H
#define CLASSES_GF_GFMENUFIELDSKILLLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf {
// a GfMenuFieldSkillList's content: a field skill and its level (GfMenuFieldSkillAdapter shows them)
class MenuFieldSkill {
public:
    MenuFieldSkill() : m_id(0), m_lv(0) {}
    unsigned short m_id;  // 0: none
    unsigned char m_lv;
    // copies take it (GfMenuFieldSkillAdapter::create's is one 4-byte copy), the constructor leaves it
    unsigned char pad_3;
};

// table 0x7100B5F360
class GfMenuFieldSkillList : public ::ui::UIListInfo< ::gf::MenuFieldSkill> {
public:
    virtual ~GfMenuFieldSkillList();  // slot 0
};
}  // namespace gf

#endif
