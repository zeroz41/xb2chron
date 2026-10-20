#ifndef CLASSES_EVENT_MANAGER_H
#define CLASSES_EVENT_MANAGER_H

#include "classes/ml/IWorkBackground.h"
#include "classes/ml/IWorkEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace event { class Manager; }
namespace ml { class EventView; }

namespace event {
// table 0x7100B3E2F8
class Manager : public ::mm::mtl::PtrSingleton< ::event::Manager>, public ::ml::IWorkEvent, public ::ml::IWorkBackground {
public:
    virtual ~Manager();  // slot 0
    virtual void OnKeyDown(ml::EventView*);  // slot 2
    virtual void bkgHomeMenu(bool);  // slot 3
};
}  // namespace event

#endif
