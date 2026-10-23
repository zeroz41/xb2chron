#ifndef CLASSES_GF_GFMENUDRIVERLIST_H
#define CLASSES_GF_GFMENUDRIVERLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf {
// a driver list's element (4 bytes: setupFromParty adds the drivers' BDAT ids); the field name is not the original's
class MenuDriverInfo {
public:
    unsigned int m_driver;
};

// table 0x7100B5F280
class GfMenuDriverList : public ::ui::UIListInfo< ::gf::MenuDriverInfo> {
public:
    GfMenuDriverList() {}  // the symbols name no copy (inline in create)
    virtual ~GfMenuDriverList();  // slot 0
    static GfMenuDriverList* create();
};
}  // namespace gf

#endif
