#include "classes/gf/GfMenuZoneMapList.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfMenuZoneMapList::~GfMenuZoneMapList() {
    ;  // the original stores the table: its body had a statement the build compiles away
}

GfMenuZoneMapList* GfMenuZoneMapList::create() {
#line 36
    GfMenuZoneMapList* list = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuZoneMapList;
    list->addRef();
    return list;
}

void GfMenuZoneMapList::sortFromPriority() {
    sort(sortPriority);
}

bool GfMenuZoneMapList::sortPriority(const MenuZoneMapInfo& a, const MenuZoneMapInfo& b) {
    if (a.m_priority == b.m_priority) {
        return a.m_mapId < b.m_mapId;
    }
    return a.m_priority < b.m_priority;
}

}  // namespace gf
