#ifndef CLASSES_EVENT_CHARALINERROT_H
#define CLASSES_EVENT_CHARALINERROT_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E4C0
class CharaLinerRot : public ::event::ICmd {
public:
    virtual ~CharaLinerRot();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
