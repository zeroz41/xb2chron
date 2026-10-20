#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UIEventDispCondition.h"
#include "ui/UIUtil.h"

namespace ui {

UIEventDispCondition::~UIEventDispCondition() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

UIEventDispCondition* UIEventDispCondition::create(unsigned int userValue0, unsigned int userValue1,
                                                   const UIObjectDispPlugin* plugin) {
    if (plugin == nullptr) {
        return nullptr;
    }
#line 43
    return new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__)
        UIEventDispCondition(userValue0, userValue1, plugin);
}

int UIEventDispCondition::update() {
    bool disp = m_plugin->m_disp;
    int event = 0;
    if (disp != m_disp) {
        event = disp ? 5 : 6;
    }
    m_disp = disp;
    return event;
}

}  // namespace ui
