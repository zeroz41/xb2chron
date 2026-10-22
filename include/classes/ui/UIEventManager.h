#ifndef CLASSES_UI_UIEVENTMANAGER_H
#define CLASSES_UI_UIEVENTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusiveList.h"
#include "ui/EventData.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIEventManager; }
namespace ui { class UIEventCondition; }
namespace ui { class UIGameListener; }
namespace ui { class UIObjectListener; }

namespace ui {
// table 0x7100B74668: the UI objects' listeners and conditions, and the events queued for them and for the game
class UIEventManager : public ::mm::mtl::PtrSingleton< ::ui::UIEventManager> {
public:
    // an event waiting to be handed out (1.0.0's pushObjectEvent and pushGameEvent take one, stepEventInfo counts
    // its delay down); the field names are not the original's
    struct EventInfo {
        // the delay starts at 0, stored before the event's parameters (UITimerManager::update)
        EventInfo() : m_delay(0.0f) {}
        unsigned int m_handle;  // the object's
        float m_delay;          // the time left before it is handed out
        EventData m_data;
    };
    // an object's listener and conditions, under its handle (the name is not the original's)
    struct ListenerNode : public mm::mtl::IntrusiveListNodeBase {
        unsigned int m_handle;
        UIObjectListener* m_listener;    // referenced while registered
        UIEventCondition* m_conditions;  // addCondition's, linked through their m_next, each referenced
    };

    UIEventManager();
    virtual ~UIEventManager();  // slot 0
    void update(const fw::UpdateInfo& info);
    void pushObjectEvent(const EventInfo& info);
    // true when the event is due; otherwise counts its delay down by time (1.0.0 has it; 3.0.1 inlines every call)
    bool stepEventInfo(EventInfo& info, float time);
    void registObjectListener(unsigned int handle, UIObjectListener* listener);  // it takes a reference
    void removeObjectListener(unsigned int handle);
    void addCondition(unsigned int handle, UIEventCondition* condition);  // it takes a reference
    void pushGameEvent(const EventInfo& info);  // dropped while no game listener is set
    void setGameListener(UIGameListener* listener);
    bool isObjectListenerFull();  // always false

    mm::mtl::IntrusiveList<ListenerNode> m_listeners;
    mm::mtl::FixedVector<EventInfo, 256> m_objectEvents;  // pushObjectEvent's, handed to the objects' listeners
    UIGameListener* m_gameListener;                       // setGameListener's
    mm::mtl::FixedVector<EventInfo, 256> m_gameEvents;    // pushGameEvent's, handed to m_gameListener
};
}  // namespace ui

#endif
