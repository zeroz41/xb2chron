#ifndef CLASSES_GF_GFMENUZONEMAPLIST_H
#define CLASSES_GF_GFMENUZONEMAPLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf {
// a GfMenuZoneMapList's content (0x18 bytes): a map or point and the name GfMenuZoneMapAdapter shows for it
struct MenuZoneMapInfo {
    // GfMenuZoneMapList::create's inlined construction of m_dummy zeroes bytes 0 to 0x15 and leaves 0x16
    MenuZoneMapInfo() : m_mapId(0), m_param(0), pad_8(), m_priority(0) {}
    // GfMenuZoneMapAdapter::ListConverter::getMapId's (the name is not the original's); sortPriority's second key
    unsigned int m_mapId;
    unsigned int m_param;  // GfMenuZoneMapAdapter::ListConverter::getParam's (the name is not the original's)
    unsigned char pad_8[0xC];
    unsigned short m_priority;  // sortPriority's first key (the name is not the original's)
    unsigned char pad_16[2];
};

// table 0x7100B5F7D0
class GfMenuZoneMapList : public ::ui::UIListInfo< ::gf::MenuZoneMapInfo> {
public:
    virtual ~GfMenuZoneMapList();  // slot 0
    // GfMenuZoneMapAdapter::ListConverter::isGroupMode's; 1.0.0's constructor clears it (the name is not the
    // original's)
    bool m_groupMode;
};
}  // namespace gf

#endif
