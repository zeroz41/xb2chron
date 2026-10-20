#ifndef CLASSES_GF_GFMENUFIELDSKILLADAPTER_REFERENCECONVERTER_H
#define CLASSES_GF_GFMENUFIELDSKILLADAPTER_REFERENCECONVERTER_H

#include "classes/gf/GfMenuFieldSkillAdapter.h"

namespace gf { class MenuFieldSkill; }

namespace gf {
// table 0x7100B5BDE8
class GfMenuFieldSkillAdapter::ReferenceConverter {
public:
    virtual ~ReferenceConverter();  // slot 0
    virtual void getFieldSkill(gf::MenuFieldSkill&);  // slot 2
};
}  // namespace gf

#endif
