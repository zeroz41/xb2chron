#ifndef CLASSES_UI_UIEVENTPOSCONDITION_H
#define CLASSES_UI_UIEVENTPOSCONDITION_H

#include "classes/ui/UIEventCondition.h"
#include "classes/ui/UIObjectPosPlugin.h"

namespace ui {
// table 0x7100B746D8
class UIEventPosCondition : public ::ui::UIEventCondition {
public:
    UIEventPosCondition(unsigned int userValue0, unsigned int userValue1, const UIObjectPosPlugin* plugin)
        : UIEventCondition(userValue0, userValue1), m_screenAdjusting(false) {
        m_plugin = plugin;
        m_screenAdjusting = !plugin->m_screenAdjusting;  // so the first update reports the plugin's state
    }
    virtual ~UIEventPosCondition();  // slot 0
    virtual int update();  // slot 2
    static UIEventPosCondition* create(unsigned int userValue0, unsigned int userValue1,
                                       const UIObjectPosPlugin* plugin);
    const UIObjectPosPlugin* m_plugin;
    bool m_screenAdjusting;  // the plugin's m_screenAdjusting as the last update saw it
};
}  // namespace ui

#endif
