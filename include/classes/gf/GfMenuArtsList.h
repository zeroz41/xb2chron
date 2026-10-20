#ifndef CLASSES_GF_GFMENUARTSLIST_H
#define CLASSES_GF_GFMENUARTSLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf { class MenuArtsInfo; }

namespace gf {
// table 0x7100B5F110
class GfMenuArtsList : public ::ui::UIListInfo<gf::MenuArtsInfo> {
public:
    virtual ~GfMenuArtsList();  // slot 0
};
}  // namespace gf

#endif
