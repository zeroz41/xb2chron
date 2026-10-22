#ifndef CLASSES_GF_GFMENUREFERENCEFS_H
#define CLASSES_GF_GFMENUREFERENCEFS_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace gf { class MenuFieldSkill; }

namespace gf {
// table 0x7100B62578; a counted field skill a menu object shares with GfMenuFieldSkillAdapter
class GfMenuReferenceFs : public ::mm::mtl::ReferenceObject {
public:
    virtual ~GfMenuReferenceFs();  // slot 0
    virtual void getFs(gf::MenuFieldSkill&) const;  // slot 2
};
}  // namespace gf

#endif
