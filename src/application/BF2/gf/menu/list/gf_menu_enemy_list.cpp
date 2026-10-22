#include "mm/mtl/Vector.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UIListInfo.h"
#include "classes/gf/GfMenuEnemyList.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfMenuEnemyList::GfMenuEnemyList() {}

GfMenuEnemyList::~GfMenuEnemyList() {
    ;  // the original stores the table: its body had a statement the build compiles away
}

GfMenuEnemyList* GfMenuEnemyList::create() {
#line 40
    GfMenuEnemyList* list = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuEnemyList();
    list->addRef();
    return list;
}

}  // namespace gf
