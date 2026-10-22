#ifndef CLASSES_UI_UICTRLOBJECT_H
#define CLASSES_UI_UICTRLOBJECT_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/IntrusiveList.h"

namespace fw { class UpdateInfo; }
namespace ui { struct EventData; }

namespace ui {
// a parameter of an event a control sends (sendEvent copies its 4 bytes): UICtrlCursorSelect::update fills its
// halves apart (the new index, the old one), UICtrlRevolveSelect sends times and angles; the names of its fields are
// not the original's
union uiEventParam {
    int m_value;
    short m_half[2];
    float m_float;
};

// table 0x7100B74598; a control UICtrlManager runs (the constructor hands it to the manager) on an object: the
// manager holds a reference (addCtrlObject) and links it into its controls by the node base at 0x10
class UICtrlObject : public ::mm::mtl::ReferenceObject, public ::mm::mtl::IntrusiveListNodeBase {
public:
    UICtrlObject(unsigned int handle);
    virtual ~UICtrlObject();  // slot 0
    virtual void update(const fw::UpdateInfo& info) = 0;  // slot 2
    bool isTerm();  // the manager holds the only reference, or its object is gone
    void setupEventHanding(unsigned int handle, unsigned short id);
    static unsigned short getEventCtrlObjID(const EventData& event);
    static unsigned short getEventType(const EventData& event);
    // an event (0xE) to the object setupEventHanding named, its first parameter the type over the id
    void sendEvent(unsigned short type, const uiEventParam* param0, const uiEventParam* param1,
                   const uiEventParam* param2);
    unsigned int m_handle;       // the object it controls
    unsigned int m_eventHandle;  // setupEventHanding: the object sendEvent sends to (0: none)
    unsigned short m_eventId;    // setupEventHanding: the low half of sendEvent's first parameter
};
}  // namespace ui

#endif
