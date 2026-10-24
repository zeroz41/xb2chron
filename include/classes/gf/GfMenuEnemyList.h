#ifndef CLASSES_GF_GFMENUENEMYLIST_H
#define CLASSES_GF_GFMENUENEMYLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf {
// an enemy list's element (8 bytes: UIListInfo<MenuEnemyInfo>'s buffer grows by 8)
class MenuEnemyInfo {
public:
    // the enemy (a CHR_EnArrange row: GfMenuReference::addEnemyLink fills it; the name is not the original's)
    unsigned int m_enemyId;
    unsigned char pad_04[4];
};

// table 0x7100B5F2F0
class GfMenuEnemyList : public ::ui::UIListInfo< ::gf::MenuEnemyInfo> {
public:
    GfMenuEnemyList();
    virtual ~GfMenuEnemyList();  // slot 0
    static GfMenuEnemyList* create();
};
}  // namespace gf

#endif
