#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UIEventNumberCondition.h"
#include "ui/UIUtil.h"

namespace ui {

UIEventNumberCondition::~UIEventNumberCondition() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

UIEventNumberCondition* UIEventNumberCondition::create(unsigned int userValue0, unsigned int userValue1,
                                                       const UIObjectNumberPlugin* plugin, float rate) {
    if (plugin == nullptr) {
        return nullptr;
    }
#line 67
    return new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__)
        UIEventNumberCondition(userValue0, userValue1, plugin, rate);
}

UIEventNumberCondition* UIEventNumberCondition::create(unsigned int userValue0, unsigned int userValue1,
                                                       const UIObjectNumberPlugin* plugin) {
    if (plugin == nullptr) {
        return nullptr;
    }
#line 82
    return new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__)
        UIEventNumberCondition(userValue0, userValue1, plugin);
}

int UIEventNumberCondition::update() {
    const UIObjectNumberPlugin* plugin = m_plugin;
    float rate = m_state.thresholdRate;
    int number = plugin->m_number;
    int min = plugin->m_min;
    int max = plugin->m_max;
    int last = m_state.number;
    if (number == last && !m_first) {
        return 0;
    }
    int event;
    if (m_anyChange != 0) {
        event = 4;
    } else {
        int threshold = static_cast<int>(rate * static_cast<float>(max - min)) + min;
        if (threshold == number) {
            event = 1;
        } else if (number < threshold && last >= threshold) {
            event = 2;
        } else {
            event = number > threshold && last <= threshold ? 3 : 0;
        }
    }
    m_state.number = number;
    m_first = false;
    return event;
}

int UIEventNumberCondition::getArg() const {
    return m_plugin->m_number;
}

}  // namespace ui
