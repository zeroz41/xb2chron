#ifndef CLASSES_EVENT_SEQMANAGER_END_CHANGE_H
#define CLASSES_EVENT_SEQMANAGER_END_CHANGE_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EDB8
class SeqManager::end_change : public ::event::ICmd {
public:
    virtual ~end_change();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
