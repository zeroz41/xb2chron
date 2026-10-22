#ifndef CLASSES_UI_UIOBJECTDISPPLUGIN_H
#define CLASSES_UI_UIOBJECTDISPPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UICtrlSimple.h"
#include "classes/ui/UICtrlSimpleUpdater.h"

namespace ui { class UIObjectAcc; }
namespace ui { class UIObjectAlphaParam; }

namespace ui {
// table 0x7100B75078
class UIObjectDispPlugin : public ::ui::UIObjectPlugin {
public:
    // the bits of m_modeFlags (setAlphaMode, setReverseMode, setFadeMode, setSuspendMode)
    enum {
        MODE_ALPHA = 1 << 0,    // execute shows the object and gives its display state as its alpha
        MODE_REVERSE = 1 << 1,  // execute shows the object while m_disp is false
        MODE_FADE = 1 << 2,     // setFadeMode: the alpha fades over m_fadeTime (sets MODE_ALPHA too)
        MODE_SUSPEND = 1 << 3,  // execute suspends the object while it is hidden
    };
    UIObjectDispPlugin();
    virtual ~UIObjectDispPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    static UIObjectDispPlugin* create(unsigned int handle);
    void init(unsigned int handle);  // takes the object's display state
    void setDisp(bool disp);
    void setAlphaMode(bool on);
    void setReverseMode(bool on);
    void setSuspendMode(bool on);
    void setDispControl(bool on);
    void setFollowObjHandle(unsigned int handle);
    void setFadeMode(float time);
    static mm::mtl::RTTI m_rtti;
    bool m_dispControl;  // setDispControl
    bool m_disp;         // setDisp
    unsigned char pad_1E[0x2];
    unsigned int m_modeFlags;        // MODE_*
    unsigned int m_followObjHandle;  // setFollowObjHandle
    UIObjectAlphaParam* m_alphaParam;  // the fade's alpha: execute creates it the first time it fades
    UICtrlSimple<1> m_fade;            // setDisp starts it from the current alpha to 0 or 1
    // runs m_fade while UICtrlManager has it: setDisp adds it, and execute and the destructor remove it
    UICtrlSimpleUpdater<UICtrlSimple<1> > m_fadeUpdater;
    float m_fadeTime;  // setFadeMode
    // derived plugins' fields start at 0x7C, in this class's tail padding
};
}  // namespace ui

#endif
