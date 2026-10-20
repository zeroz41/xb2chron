#ifndef CLASSES_GF_GFMENUENEMYLIST_H
#define CLASSES_GF_GFMENUENEMYLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf { class MenuEnemyInfo; }

namespace gf {
// table 0x7100B5F2F0
class GfMenuEnemyList : public ::ui::UIListInfo< ::gf::MenuEnemyInfo> {
public:
    virtual ~GfMenuEnemyList();  // slot 0
};
}  // namespace gf

#endif
