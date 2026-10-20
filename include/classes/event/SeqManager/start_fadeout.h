#ifndef CLASSES_EVENT_SEQMANAGER_START_FADEOUT_H
#define CLASSES_EVENT_SEQMANAGER_START_FADEOUT_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EBF8
class SeqManager::start_fadeout : public ::event::ICmd {
public:
    virtual ~start_fadeout();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
