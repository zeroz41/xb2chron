#ifndef CLASSES_UI_UIEVENTNUMBERCONDITION_H
#define CLASSES_UI_UIEVENTNUMBERCONDITION_H

#include "classes/ui/UIEventCondition.h"
#include "classes/ui/UIObjectNumberPlugin.h"

namespace ui {
// table 0x7100B746A8
class UIEventNumberCondition : public ::ui::UIEventCondition {
public:
    UIEventNumberCondition(unsigned int userValue0, unsigned int userValue1, const UIObjectNumberPlugin* plugin,
                           float rate)
        : UIEventCondition(userValue0, userValue1), m_plugin(plugin), m_state() {
        m_state.thresholdRate = rate;
        m_state.number = plugin->m_number;
        m_anyChange = 0;
    }
    UIEventNumberCondition(unsigned int userValue0, unsigned int userValue1, const UIObjectNumberPlugin* plugin)
        : UIEventCondition(userValue0, userValue1), m_plugin(plugin), m_state() {
        m_state.number = plugin->m_number;
        m_anyChange = 1;
    }
    virtual ~UIEventNumberCondition();  // slot 0
    virtual int update();  // slot 2
    virtual int getArg() const;  // slot 3
    static UIEventNumberCondition* create(unsigned int userValue0, unsigned int userValue1,
                                          const UIObjectNumberPlugin* plugin, float rate);
    static UIEventNumberCondition* create(unsigned int userValue0, unsigned int userValue1,
                                          const UIObjectNumberPlugin* plugin);
    // one aggregate: the constructors zero both members with one store, which setting the rate leaves in place
    struct State {
        float thresholdRate;  // where between the plugin's m_min and m_max the number is compared
        int number;           // the plugin's m_number as the last update saw it
    };
    const UIObjectNumberPlugin* m_plugin;
    State m_state;
    bool m_first = true;  // the next update evaluates even when the number has not changed
    int m_anyChange = 1;  // nonzero: any change raises event 4, with no threshold
};
}  // namespace ui

#endif
