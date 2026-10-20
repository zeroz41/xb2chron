#ifndef CLASSES_EVENT_SEQMANAGER_START_CAPTURE_WAIT_H
#define CLASSES_EVENT_SEQMANAGER_START_CAPTURE_WAIT_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3E990
class SeqManager::start_capture_wait : public ::event::ICmd {
public:
    virtual ~start_capture_wait();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
