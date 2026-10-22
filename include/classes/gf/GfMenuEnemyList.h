#ifndef CLASSES_GF_GFMENUENEMYLIST_H
#define CLASSES_GF_GFMENUENEMYLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf {
// an enemy list's element (8 bytes: UIListInfo<MenuEnemyInfo>'s buffer grows by 8)
class MenuEnemyInfo {
public:
    unsigned char pad_00[8];
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
