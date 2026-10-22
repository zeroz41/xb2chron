#ifndef CLASSES_GF_GFMENUOBJSKIPTIME_H
#define CLASSES_GF_GFMENUOBJSKIPTIME_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectTimePlugin.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"

namespace ui { class UIObjectAcc; }

namespace gf {
// table 0x7100B64960
class GfMenuObjSkipTime : public ::gf::GfMenuObject {
public:
    class MainListener;
    class TimeChangeListener;
    GfMenuObjSkipTime(unsigned int handle);
    virtual ~GfMenuObjSkipTime();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // shows the time now and the time to skip to on the layout: the plugin of the second's text
    static ui::UIObjectTimePlugin* setupTimeChange(ui::UIObjectAcc& acc, GameTime& time, GameTime& newTime);
    static void refreshSelect(ui::UIObjectAcc& acc, unsigned int select);  // marks tag 1 or 2 selected
    // 1.0.0's (out of line there; 3.0.1 has no copies): the common fades, heard by the handle's object
    static int setFadeIn(unsigned int handle) {
        int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    static int setFadeOut(unsigned int handle) {
        int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    // 1.0.0's (out of line there): a time plugin's hour, minute and second
    static void setTime(ui::UIObjectTimePlugin* plugin, GameTime& time) {
        plugin->setHour(time.hour);
        plugin->setMin(time.min);
        plugin->setSec(time.sec);
    }
    // 1.0.0's (out of line there): an event of that type and first parameter, through UIManager
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        ui::EventData event;
        event.m_type = type;
        event.m_param0 = param;
        ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
    // the time to skip to's text plugin, which the time change's cursor updates (the name is not the original's)
    ui::UIObjectTimePlugin* m_timePlugin;
    GameTime m_time;     // the time when it opened (the name is not the original's)
    GameTime m_newTime;  // the time to skip to: its hour follows the cursor (the name is not the original's)
};
}  // namespace gf

#endif
