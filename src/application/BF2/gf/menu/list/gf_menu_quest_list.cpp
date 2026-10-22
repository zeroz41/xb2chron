#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UIListInfo.h"
#include "gf/QuestID.h"
#include "gf/QuestListAcc.h"
#include "gf/GfQuestInfo.h"
#include "classes/gf/GfMenuQuestList.h"
#include "mm/mtl/Vector.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfMenuQuestList::~GfMenuQuestList() {
    ;  // the original stores the table: its body had a statement the build compiles away
}

GfMenuQuestList* GfMenuQuestList::create() {
#line 41
    GfMenuQuestList* list = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuQuestList;
    list->addRef();
    return list;
}

}  // namespace gf
