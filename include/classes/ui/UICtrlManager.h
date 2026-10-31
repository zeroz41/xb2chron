#ifndef CLASSES_UI_UICTRLMANAGER_H
#define CLASSES_UI_UICTRLMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ui/UICtrl.h"
#include "classes/ui/UICtrlMethodAddColor.h"
#include "classes/ui/UICtrlMethodAlpha.h"
#include "classes/ui/UICtrlMethodBright.h"
#include "classes/ui/UICtrlMethodMotion.h"
#include "classes/ui/UICtrlMethodMulColor.h"
#include "classes/ui/UICtrlMethodPos.h"
#include "classes/ui/UICtrlMethodRot.h"
#include "classes/ui/UICtrlMethodScale.h"
#include "classes/ui/UIDisplayInfo.h"
#include "classes/ui/UITransform.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusiveList.h"
#include "ui/UIUtil.h"

namespace fw { class UpdateInfo; }
namespace ui { class UICtrlManager; }
namespace ui { class IUICtrlUpdater; }
namespace ui { class UICtrlObject; }
namespace ui { class UIObject; }

namespace ui {
// table 0x7100B74498
class UICtrlManager : public ::mm::mtl::PtrSingleton< ::ui::UICtrlManager> {
public:
    // a control on an object: the methods the add*Method calls set up, the run startCtrl starts with them, and the
    // object's transform and display information as reserveCtrlSlot found them (the names are not the original's)
    struct CtrlSlot {
        UICtrlMethodPos m_pos;
        UICtrlMethodScale m_scale;
        UICtrlMethodAlpha m_alpha;
        UICtrlMethodBright m_bright;
        UICtrlMethodRot m_rot;
        UICtrlMethodMulColor m_mulColor;
        UICtrlMethodAddColor m_addColor;
        UICtrlMethodMotion m_motion;
        UICtrl m_ctrl;
        mm::mtl::FixedVector<UICtrl::Method, 5> m_methods;  // the add*Method calls', handed to m_ctrl by startCtrl
        float m_delayTime;     // setDelayTime's; reserveCtrlSlot zeroes it
        unsigned int m_handle;  // the object's handle (0: the slot is free of a handle)
        UIObject* m_object;    // referenced while reserved
        bool m_loop;           // reserveCtrlSlot's: the run loops
        // startCtrl's; bit 1: releasing the slot terminates the object, bit 3: stopping it restores the defaults
        unsigned int m_flags = 0;
        unsigned int m_eventHandle;  // the object told when the control ends (changeEventHandleObject's)
        unsigned int m_ctrlParam;    // startCtrl's last argument
        UITransform m_defTransform;      // the object's as reserveCtrlSlot found it (0x30 bytes, 16-aligned)
        UIDisplayInfo m_defDisplayInfo;  // the object's as reserveCtrlSlot found it
    };

    UICtrlManager();
    virtual ~UICtrlManager();  // slot 0
    void update(const fw::UpdateInfo& info);
    void releaseCtrlSlot(int slot);
    void setDefault(int slot);
    void stopCtrl(int slot, bool release, bool notify);
    int reserveCtrlSlot(unsigned int handle, bool loop);
    int getCtrlSlot(unsigned int handle);  // the slot of the control running on the handle, -1 for none
    // the object told when that control (what startCtrl returned) ends
    void changeEventHandleObject(int slot, unsigned int handle);
    void setDelayTime(int slot, float time);
    void addPositionMethod(int slot, short x, short y, CURVE_TYPE curve);
    void addScaleMethod(int slot, float x, float y, CURVE_TYPE curve);
    void addAlphaMethod(int slot, float alpha, CURVE_TYPE curve);
    void addBrightMethod(int slot, float bright, CURVE_TYPE curve);
    void addRotMethod(int slot, float rot, CURVE_TYPE curve);
    void addMulColorMethod(int slot, const mm::Col3& color, CURVE_TYPE curve);
    void addAddColorMethod(int slot, const mm::Col3& color, CURVE_TYPE curve);
    void addMotionMethod(int slot, const char* file, const char* name);
    void addUndoMethod(int slot, CURVE_TYPE curve);
    void startCtrl(int slot, float duration, unsigned int flags, unsigned int param);
    void getDefaultTransfom(int slot, UITransform& transform);
    void getDefaultDisplayInfo(int slot, UIDisplayInfo& info);
    void setSpeedFactor(int slot, float factor);
    void addCtrlObject(UICtrlObject* object);  // takes a reference to it and runs it
    void addUpdater(IUICtrlUpdater& updater);  // links it into the updaters it runs each frame, unless linked
    void delUpdater(IUICtrlUpdater& updater);  // unlinks it, if linked
    bool isBusyCtrl(int slot);

    CtrlSlot m_slots[128];
    mm::mtl::IntrusiveList<UICtrlObject> m_ctrlObjects;  // addCtrlObject's, each referenced
    mm::mtl::IntrusiveList<mm::mtl::IntrusiveListNodeBase> m_updaters;  // addUpdater's (their m_node)
};
}  // namespace ui

#endif
