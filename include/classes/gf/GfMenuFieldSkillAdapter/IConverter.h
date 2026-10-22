#ifndef CLASSES_GF_GFMENUFIELDSKILLADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUFIELDSKILLADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuFieldSkillAdapter.h"

namespace gf {
// table none (its derived classes'): where a field skill adapter's update takes its skill from
class GfMenuFieldSkillAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual void getFieldSkill(MenuFieldSkill& skill) = 0;  // slot 2; leaves it as it is when there is none
};
}  // namespace gf

#endif
