#ifndef CLASSES_GF_GFMENUOBJECT_H
#define CLASSES_GF_GFMENUOBJECT_H

#include "classes/ui/UIInputPointer.h"
#include "mm/mtl/IntrusiveList.h"

namespace gf { class GfMenuCallContext; }
namespace gf { namespace GfMenuTypes { struct Param; }}
namespace ui { struct EventData; }
namespace ui { class UIStr; }
namespace ui { class UIListInfoBase; }
namespace ui { class IUIInputSelectionChecker; }

namespace gf {
// table 0x7100B5EE40
class GfMenuObject {
public:
    GfMenuObject(unsigned int handle);
    virtual ~GfMenuObject();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    virtual void reloadParam();  // slot 5
    virtual void eventHudSceneChange(unsigned int);  // slot 6
    // GfMenuCallManager's, without one nothing (0/false): attach a UI object handle under an id, the handle attached
    // under one, a call context started on one
    static void attachExternalCall(unsigned int id, unsigned int handle);
    static void detachExternalCall(unsigned int id);
    static bool existAttachedObject(unsigned int id);
    static unsigned int getAttachedObject(unsigned int id);
    // GfMenuCallManager's texts, by the id registString hands out: what menu events pass instead of the text
    static unsigned short registString(const ui::UIStr& text);
    static void releaseString(unsigned short id);
    static const ui::UIStr& getString(unsigned short id);
    static void startCallContext(GfMenuCallContext* context, unsigned int id, unsigned int handle);
    static void nextCallContext(GfMenuCallContext* context, unsigned int id);
    // game events (UIManager::requestGameEvent) for the call context running on a handle: hand it a result (8),
    // end it (9)
    static void addResultCallContext(unsigned int handle, unsigned int result, int);
    static void termCallContext(unsigned int handle);
    static void setCallContextEventHandler(GfMenuCallContext* context, unsigned int handle);
    // UIInputManager's, on the input layer of the handle's object (searchInputHandle), nothing without one
    static void setupInputSelection(unsigned int handle, int index, unsigned int count);
    static void resetInputSelection(unsigned int handle);
    // the list's selection and size; for a list of one column, its page's rows as the pad's page size too
    static void setupInputSelectionFromList(unsigned int handle, const ui::UIListInfoBase& list);
    static void setInputSelectionChecker(unsigned int handle, ui::IUIInputSelectionChecker* checker);
    static void setupPadLineSelection(unsigned int handle, unsigned int count);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's setupPadLineSelection is followed by
    // setPadLineSelectionLoop). A member because it sits among GfMenuObject's input wrappers and has their shape.
    // What it does: UIInputManager::fn_7100679754 with the input handle of the handle's object and the second
    // argument; no caller in the module.
    static void fn_7100362A08(unsigned int handle, unsigned int value);
    static void setPadLineSelectionLoop(unsigned int handle, bool loop);
    static void setPadLoopSetting(unsigned int handle, bool loop);
    static void setupPointerSelection(unsigned int handle, const ui::UIInputPointer::SelectionSetup& setup);
    static void changePointerPos(unsigned int handle, const mm::Pnt<short>& pos);
    static void changePointerRegionScale(unsigned int handle, float scale);
    // UIInputManager's input on the handle moves its selection to that object (marked as one); its code keeps no
    // result (the zero path returns without setting one)
    static void migrateInput(unsigned int handle, unsigned int object);
    static void enableInput(unsigned int handle);
    static void disableInput(unsigned int handle);
    // GfMenuFullScreen's input objects
    static bool setFSInputObject(unsigned int index, unsigned int handle);
    static unsigned int getFSInputObject(unsigned int index);
    static void enableFSInput(unsigned int index);
    static void disableFSInput();
    static void setInputActionEnable(unsigned int handle, unsigned int action, bool enable);
    // UIManager::requestObjectEvent for a handle that is not 0
    static void sendEvent(unsigned int handle, const ui::EventData& event, float delay);
    // sendEvent of an open (0x21) or close (0x22) event with that first parameter (the parameter names are not the
    // original's)
    static void sendOpenEvent(unsigned int handle, int param, float delay);
    static void sendCloseEvent(unsigned int handle, int param, float delay);
    // the same, to the parent of the handle's object (nothing without one)
    static void sendEventToParent(unsigned int handle, const ui::EventData& event, float delay);
    // conditions (UIEventManager::addCondition) on the handle's child of that name (the handle's own object
    // without one), for an object that has the plugin each watches: a number condition (with a threshold rate),
    // a display condition (on its duplicated child of that index, with the last argument), a position condition.
    // The values go to the condition as its user values (the parameter names are not the original's)
    static void addNumberEventCondition(unsigned int handle, const char* child, unsigned int event, unsigned int value,
                                        float rate);
    static void addNumberEventCondition(unsigned int handle, const char* child, unsigned int event, unsigned int value);
    static void addDispEventCondition(unsigned int handle, const char* child, unsigned int event, unsigned int value,
                                      bool duplicated);
    static void addPosEventCondition(unsigned int handle, const char* child, unsigned int event, unsigned int value);
    // what startCtrl returned, so the object hears when that control ends
    static void hookCtrlEvent(unsigned int handle, int ctrl);
    // the same for an animation the handle's object plays: the object hears when it ends. 3.0.1's takes a third
    // value, which UIAnimationManager keeps with the target (1.0.0's has two parameters; the name of the third is not
    // the original's)
    static void hookAnimationEvent(unsigned int handle, unsigned int target, unsigned int param);
    // game event 7 (UIManager::requestGameEvent) with the two flags
    static void closeFSLayer(unsigned int handle, bool, bool);
    // the menu's row (BDAT 0x173): its layer (1 for none), icon (0 for none), text and description (the message
    // file, BDAT 0x119, and the message id; false for none)
    static unsigned int getMenuLayerID(unsigned int menuId);  // a 16-bit value, zero-extended (its code masks it)
    static unsigned int getMenuIconID(unsigned int menuId);  // a 16-bit value, zero-extended (its code masks it)
    static bool getMenuText(unsigned int menuId, unsigned char*& file, unsigned int& msgId);
    static bool getMenuDesc(unsigned int menuId, unsigned char*& file, unsigned int& msgId);
    // game events 1 and 3 (UIManager::requestGameEvent) for a full-screen sub layer
    static void changeFSSubLayer(unsigned int handle, unsigned short, unsigned short layer, bool);
    static void returnFSSubLayer(unsigned int handle, unsigned short group);
    static void returnFSSubLayer(GfMenuObject* object);  // its handle, its layer's group
    // GfMenuFullScreen's, for a full-screen layer
    static void registFSLayerObject(unsigned int layer, unsigned int handle);
    static void setFSShadowLayer(unsigned int layer, bool shadow);
    static void registFSLayerParam(unsigned int layer, const GfMenuTypes::Param& param);
    static bool getFSLayerParam(unsigned int layer, GfMenuTypes::Param& param);
    static void removeFSLayerParam(unsigned int layer);
    // UIManager's object timers (the time in seconds) and UITimerManager's speed of the object's first timer
    static void registTimer(unsigned int handle, unsigned short id, float time, bool loop);
    static void releaseTimer(unsigned int handle);
    static void setTimerSpeedFactor(unsigned int handle, float factor);
    // a registered text, on a text object; the id is released after
    static void setText(unsigned int handle, unsigned short id);
    // the constructor links it to itself (the name is not the original's)
    mm::mtl::IntrusiveListNodeBase m_listNode;
    unsigned int m_handle;  // its UI object's: the constructor's, cleared by finalize
    // the constructor clears it; initialize sets bit 0, finalize bit 1 (the name is not the original's)
    unsigned int m_stateFlags;
    unsigned int m_fsLayer;  // the full-screen layer it shows in (getFSLayerParam, setFSShadowLayer)
    // its derived classes' fields start at 0x24, in its tail padding (GfMenuObjMercenaryRoot's constructor stores an
    // int there, GfMenuObjBladeSwitch's three bools)
};
}  // namespace gf

#endif
