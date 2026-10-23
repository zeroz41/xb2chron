#include "mm/mtl/Vector.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UIListInfo.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfMenuDriverList::~GfMenuDriverList() {
    ;  // the original stores the table: its body had a statement the build compiles away
}

GfMenuDriverList* GfMenuDriverList::create() {
#line 44
    GfMenuDriverList* list = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuDriverList();
    list->addRef();
    return list;
}

}  // namespace gf
