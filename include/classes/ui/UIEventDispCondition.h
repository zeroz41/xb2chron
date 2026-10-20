#ifndef CLASSES_UI_UIEVENTDISPCONDITION_H
#define CLASSES_UI_UIEVENTDISPCONDITION_H

#include "classes/ui/UIEventCondition.h"
#include "classes/ui/UIObjectDispPlugin.h"

namespace ui {
// table 0x7100B74638
class UIEventDispCondition : public ::ui::UIEventCondition {
public:
    UIEventDispCondition(unsigned int userValue0, unsigned int userValue1, const UIObjectDispPlugin* plugin)
        : UIEventCondition(userValue0, userValue1), m_disp(false) {
        m_plugin = plugin;
        m_disp = !plugin->m_disp;  // so the first update reports the plugin's state
    }
    virtual ~UIEventDispCondition();  // slot 0
    virtual int update();  // slot 2
    static UIEventDispCondition* create(unsigned int userValue0, unsigned int userValue1,
                                        const UIObjectDispPlugin* plugin);
    const UIObjectDispPlugin* m_plugin;
    bool m_disp;  // the plugin's m_disp as the last update saw it
};
}  // namespace ui

#endif
