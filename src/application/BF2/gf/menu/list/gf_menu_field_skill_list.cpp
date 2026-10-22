#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UIListInfo.h"
#include "classes/gf/GfMenuFieldSkillList.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/Vector.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfMenuFieldSkillList::~GfMenuFieldSkillList() {
    ;  // the original stores the table: its body had a statement the build compiles away
}

GfMenuFieldSkillList* GfMenuFieldSkillList::create() {
#line 41
    GfMenuFieldSkillList* list = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuFieldSkillList;
    list->addRef();
    return list;
}

void GfMenuFieldSkillList::addFieldSkill(const MenuFieldSkill& skill) {
    for (unsigned int i = 0; i < getSize(); ++i) {
        MenuFieldSkill& entry = getContents(i);
        if (entry.m_id == skill.m_id) {
            entry.m_lv += skill.m_lv;
            if (entry.m_lv > 99) {
                entry.m_lv = 99;
            }
            return;
        }
    }
    addContents(skill);
}

void GfMenuFieldSkillList::addFieldSkillFromBlade(unsigned int blade) {
    if (!GfMenuObjUtil::isValidBlade(blade)) {
        return;
    }
    DataParamAcc acc(4, blade, GimmickType(0));
    if (acc.isValid()) {
        for (unsigned int i = 0; i < 3; ++i) {
            if (acc.getFieldSkill(i, false) != 0) {
                MenuFieldSkill skill;
                skill.m_id = acc.getFieldSkill(i, false);
                skill.m_lv = acc.getFieldSkillLevel(i, false);
                addFieldSkill(skill);
            }
        }
    }
}

}  // namespace gf
