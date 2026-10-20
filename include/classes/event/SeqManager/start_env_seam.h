#ifndef CLASSES_EVENT_SEQMANAGER_START_ENV_SEAM_H
#define CLASSES_EVENT_SEQMANAGER_START_ENV_SEAM_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3ED48
class SeqManager::start_env_seam : public ::event::ICmd {
public:
    virtual ~start_env_seam();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
