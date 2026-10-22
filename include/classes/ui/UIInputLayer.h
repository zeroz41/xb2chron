#ifndef CLASSES_UI_UIINPUTLAYER_H
#define CLASSES_UI_UIINPUTLAYER_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/FixedVector.h"
#include "ui/EventData.h"

namespace ui { class IUIInputSelectionChecker; }
namespace ui { class UIInputPad; }
namespace ui { class UIInputWheel; }
namespace ui { class UIInputPointer; }

namespace ui {
// table 0x7100B74AD0; counted (ui::UIObjFactory::setupObjectInput holds a reference while it attaches the layer)
class UIInputLayer : public ::mm::mtl::ReferenceObject {
public:
    // a pad button the layer turns into an event of its own (0x10 bytes: update tests the button and the two flags,
    // setActionEnable finds the entry by m_action); the names are not the original's
    struct ActionInfo {
        unsigned short m_pad;     // a UI pad button (UIUtil::convUIPadToFWPad)
        unsigned short m_action;  // what update's second event carries
        unsigned char pad_04[0xA];
        bool m_repeat;  // the button's repeat counts too
        bool m_enable;  // setActionEnable
    };
    // what the constructor copies (the derived layers' setups start with it); the name of its member is not the
    // original's
    class InputSetup {
    public:
        mm::mtl::FixedVector<ActionInfo, 27> m_actions;
    };

    UIInputLayer(unsigned int id, unsigned int handle, const InputSetup& setup);
    virtual ~UIInputLayer();  // slot 0
    virtual EventData* getInputEventExt() = 0;  // slot 2
    virtual bool hasEventExt() const { return false; }  // slot 3
    virtual void clear();  // slot 4
    virtual void clearExt();  // slot 5
    virtual UIInputPad* castUIInputPad();  // slot 6
    virtual UIInputWheel* castUIInputWheel();  // slot 7
    virtual UIInputPointer* castUIInputPointer();  // slot 8
    virtual bool updateImpl() = 0;  // slot 9
    bool changeSelect(int select, unsigned char param);  // raises a selection event (6) when it changes
    bool isEnableSelect(int select);  // what m_checker says, true without one

    unsigned char pad_0C[0x4];
    EventData m_event;  // the event update raised (6: the selection changed, m_select's new and old values)
    unsigned char pad_28[0x18];
    unsigned char pad_40[0x4];
    unsigned int m_selectMax;  // setupSelection's count
    int m_select;              // the selected index, -1 for none (resetSelection)
    bool m_selectEnable;       // changeSelect changes nothing while it is clear; the name is not the original's
    InputSetup m_setup;
    IUIInputSelectionChecker* m_checker;  // UIInputManager::setSelectionChecker
};
}  // namespace ui

#endif
