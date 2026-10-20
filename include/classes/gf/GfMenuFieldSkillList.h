#ifndef CLASSES_GF_GFMENUFIELDSKILLLIST_H
#define CLASSES_GF_GFMENUFIELDSKILLLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf { class MenuFieldSkill; }

namespace gf {
// table 0x7100B5F360
class GfMenuFieldSkillList : public ::ui::UIListInfo<gf::MenuFieldSkill> {
public:
    virtual ~GfMenuFieldSkillList();  // slot 0
};
}  // namespace gf

#endif
