#ifndef CLASSES_GF_GFMENUZONEMAPLIST_H
#define CLASSES_GF_GFMENUZONEMAPLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf { class MenuZoneMapInfo; }

namespace gf {
// table 0x7100B5F7D0
class GfMenuZoneMapList : public ::ui::UIListInfo< ::gf::MenuZoneMapInfo> {
public:
    virtual ~GfMenuZoneMapList();  // slot 0
};
}  // namespace gf

#endif
