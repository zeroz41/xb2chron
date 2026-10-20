#ifndef CLASSES_EVENT_SEQMANAGER_END_EFF_H
#define CLASSES_EVENT_SEQMANAGER_END_EFF_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EAA8
class SeqManager::end_eff : public ::event::ICmd {
public:
    virtual ~end_eff();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
