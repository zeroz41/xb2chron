#ifndef CLASSES_UI_UIINPUTMANAGER_H
#define CLASSES_UI_UIINPUTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ui/UIInputPointer.h"
#include "mm/mtl/IntrusiveList.h"

namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B74B30
class UIInputManager : public mm::mtl::PtrSingleton<UIInputManager> {
public:
    // A registered layer, referenced until releaseInputLayer removes it. Field names describe their uses.
    struct InputLayerInfo : public mm::mtl::IntrusiveListNodeBase {
        UIInputLayer* m_layer;
        unsigned int m_handle;  // CRC of the registration name
        unsigned int m_target;  // migrateInput's replacement event recipient, zero for the layer's object
        unsigned char m_enabled;
    };
    typedef mm::mtl::IntrusiveList<InputLayerInfo> InputList;

    UIInputManager();
    virtual ~UIInputManager();  // slot 0
    void update(const fw::UpdateInfo& info);
    void sendEvent(InputLayerInfo& info);
    void enable();
    void disable();
    unsigned int registInputLayer(UIInputLayer* layer, const char* name);
    void releaseInputLayer(unsigned int handle);
    void setupInputSelection(unsigned int handle, int select, unsigned int max);
    void resetInputSelection(unsigned int handle);
    void setSelectionChecker(unsigned int handle, IUIInputSelectionChecker* checker);
    void setInputActionEnable(unsigned int handle, unsigned int action, bool enable);
    unsigned int searchInputHandle(unsigned int object);
    UIInputLayer* getInputLayer(unsigned int handle);
    bool migrateInput(unsigned int handle, unsigned int target);
    void enableInput(unsigned int handle);
    void disableInput(unsigned int handle);
    bool isEnableInput(unsigned int handle);
    void setPadLineSelection(unsigned int handle, unsigned int max);
    void setPadLineSelectionLoop(unsigned int handle, bool loop);
    void setPadPageSize(unsigned int handle, unsigned int size);
    void setPadHideSelect(unsigned int handle, bool hide);
    void setupPointerSelection(unsigned int handle, const UIInputPointer::SelectionSetup& setup);
    void changePointerPos(unsigned int handle, const mm::Pnt<short>& pos);
    void changeRegionScale(unsigned int handle, float scale);
    // 2.0.0's symbols name it. What it does: for the layer of that handle, asks it (slot 6) for its pad selection and,
    // when that has one, stores the value (+0x3F0) and the rows its count (+0x44) fills at that many each, rounded up
    // (+0x3F4). Its one caller is GfMenuObject::setupPadLineSelectionForce, which passes the handle searchInputHandle
    // found and its own second argument.
    void setPadLineSelectionForce(unsigned int handle, unsigned int value);

    InputList m_layers;
    unsigned int m_minimumLayerHandle;  // update stops at a layer below this handle
    bool m_enabled;
};
}  // namespace ui

#endif
