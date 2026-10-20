#ifndef CLASSES_GF_GFMENUBLADELIST_H
#define CLASSES_GF_GFMENUBLADELIST_H

#include "classes/ui/UIListInfo.h"

namespace gf { class MenuBladeInfo; }

namespace gf {
// table 0x7100B5F180
class GfMenuBladeList : public ::ui::UIListInfo<gf::MenuBladeInfo> {
public:
    virtual ~GfMenuBladeList();  // slot 0
};
}  // namespace gf

#endif
