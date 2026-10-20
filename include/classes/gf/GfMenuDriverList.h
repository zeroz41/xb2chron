#ifndef CLASSES_GF_GFMENUDRIVERLIST_H
#define CLASSES_GF_GFMENUDRIVERLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf { class MenuDriverInfo; }

namespace gf {
// table 0x7100B5F280
class GfMenuDriverList : public ::ui::UIListInfo<gf::MenuDriverInfo> {
public:
    virtual ~GfMenuDriverList();  // slot 0
};
}  // namespace gf

#endif
