#ifndef CLASSES_GF_GFMENUFIELDSKILLADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUFIELDSKILLADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuFieldSkillAdapter.h"

namespace gf { class MenuFieldSkill; }

namespace gf {
// table 0x7100B5BDC0
class GfMenuFieldSkillAdapter::ListConverter {
public:
    virtual ~ListConverter();  // slot 0
    virtual void getFieldSkill(gf::MenuFieldSkill&);  // slot 2
};
}  // namespace gf

#endif
