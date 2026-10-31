#ifndef CLASSES_GF_GFMENUREFERENCEFS_H
#define CLASSES_GF_GFMENUREFERENCEFS_H

#include "classes/gf/GfMenuFieldSkillList.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/gf/GfAllocator.h"

// gf_menu_reference_fs.h as the menu folder's files include it (backslash included): create cites it
#define GF_MENU_REFERENCE_FS_PATH "D:/Monolithsoft/BF2/prog/application/BF2\\gf/menu/gf_menu_reference_fs.h"

namespace gf {
// table 0x7100B62578; a counted field skill a menu object shares with GfMenuFieldSkillAdapter
class GfMenuReferenceFs : public ::mm::mtl::ReferenceObject {
public:
    // a new one (GfMenuObjFieldSkill's constructor holds it; inline: the name is not the original's)
    static GfMenuReferenceFs* create() {
#line 57 GF_MENU_REFERENCE_FS_PATH
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuReferenceFs;
    }
    virtual ~GfMenuReferenceFs() {}  // slot 0: its D1 is the shared trivial one (ICF), the D0 is this unit's
    virtual void getFs(gf::MenuFieldSkill&) const;  // slot 2: copies m_fs out
    // the skill it holds (GfMenuObjFieldSkill::SkillInfoListener sets it from the owner's; the name is not the
    // original's)
    MenuFieldSkill m_fs;
};
}  // namespace gf

#endif
