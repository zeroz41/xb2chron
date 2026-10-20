#ifndef CLASSES_EVENT_SEQMANAGER_EXEC_GRASS_H
#define CLASSES_EVENT_SEQMANAGER_EXEC_GRASS_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EA70
class SeqManager::exec_grass : public ::event::ICmd {
public:
    virtual ~exec_grass();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
