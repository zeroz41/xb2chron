#ifndef CLASSES_UI_UIOBJECTLISTENER_H
#define CLASSES_UI_UIOBJECTLISTENER_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace ui { struct EventData; }

namespace ui {
// table none (its derived classes'): what UIEventManager::registObjectListener hands a UI object's events
class UIObjectListener : public ::mm::mtl::ReferenceObject {
public:
    virtual void reciveEvent(const EventData& event, unsigned int handle);  // slot 2: event 2 terminates the object
};
}  // namespace ui

#endif
