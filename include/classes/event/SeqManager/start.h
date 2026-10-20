#ifndef CLASSES_EVENT_SEQMANAGER_START_H
#define CLASSES_EVENT_SEQMANAGER_START_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EBC0
class SeqManager::start : public ::event::ICmd {
public:
    virtual ~start();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
