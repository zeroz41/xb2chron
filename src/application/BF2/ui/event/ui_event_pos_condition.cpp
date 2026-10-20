#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UIEventPosCondition.h"
#include "ui/UIUtil.h"

namespace ui {

UIEventPosCondition::~UIEventPosCondition() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

UIEventPosCondition* UIEventPosCondition::create(unsigned int userValue0, unsigned int userValue1,
                                                 const UIObjectPosPlugin* plugin) {
    if (plugin == nullptr) {
        return nullptr;
    }
#line 43
    return new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__)
        UIEventPosCondition(userValue0, userValue1, plugin);
}

int UIEventPosCondition::update() {
    bool adjusting = m_plugin->m_screenAdjusting;
    int event = 0;
    if (adjusting != m_screenAdjusting) {
        event = adjusting ? 7 : 8;
    }
    m_screenAdjusting = adjusting;
    return event;
}

}  // namespace ui
