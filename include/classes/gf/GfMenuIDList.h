#ifndef CLASSES_GF_GFMENUIDLIST_H
#define CLASSES_GF_GFMENUIDLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf { class MenuID; }

namespace gf {
// table 0x7100B5F3D0
class GfMenuIDList : public ::ui::UIListInfo< ::gf::MenuID> {
public:
    virtual ~GfMenuIDList();  // slot 0
};
}  // namespace gf

#endif
