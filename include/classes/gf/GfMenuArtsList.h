#ifndef CLASSES_GF_GFMENUARTSLIST_H
#define CLASSES_GF_GFMENUARTSLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf {
// an arts list's element (8 bytes: UIListInfo<MenuArtsInfo>'s buffer grows by 8)
class MenuArtsInfo {
public:
    unsigned char pad_00[8];
};

// table 0x7100B5F110
class GfMenuArtsList : public ::ui::UIListInfo< ::gf::MenuArtsInfo> {
public:
    virtual ~GfMenuArtsList();  // slot 0
    static GfMenuArtsList* create();
};
}  // namespace gf

#endif
