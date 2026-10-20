#ifndef CLASSES_EVENT_SEQMANAGER_EXEC_H
#define CLASSES_EVENT_SEQMANAGER_EXEC_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EA00
class SeqManager::exec : public ::event::ICmd {
public:
    virtual ~exec();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
