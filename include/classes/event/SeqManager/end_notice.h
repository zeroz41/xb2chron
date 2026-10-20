#ifndef CLASSES_EVENT_SEQMANAGER_END_NOTICE_H
#define CLASSES_EVENT_SEQMANAGER_END_NOTICE_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EED0
class SeqManager::end_notice : public ::event::ICmd {
public:
    virtual ~end_notice();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
