#ifndef CLASSES_EVENT_SEQMANAGER_START_FORM_H
#define CLASSES_EVENT_SEQMANAGER_START_FORM_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3ECD8
class SeqManager::start_form : public ::event::ICmd {
public:
    virtual ~start_form();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
