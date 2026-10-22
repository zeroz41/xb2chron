#ifndef CLASSES_GF_GFMENUIDLIST_H
#define CLASSES_GF_GFMENUIDLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf {
// a GfMenuIDList's content: an id (GfMenuIDList::sortMissionComplete orders by it)
class MenuID {
public:
    unsigned int m_id;
    unsigned char pad_4[4];
};

// table 0x7100B5F3D0
class GfMenuIDList : public ::ui::UIListInfo< ::gf::MenuID> {
public:
    virtual ~GfMenuIDList();  // slot 0
    static GfMenuIDList* create();
};
}  // namespace gf

#endif
