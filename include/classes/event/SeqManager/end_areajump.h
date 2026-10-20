#ifndef CLASSES_EVENT_SEQMANAGER_END_AREAJUMP_H
#define CLASSES_EVENT_SEQMANAGER_END_AREAJUMP_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EDF0
class SeqManager::end_areajump : public ::event::ICmd {
public:
    virtual ~end_areajump();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
