#ifndef CLASSES_EVENT_CHARAFADE_H
#define CLASSES_EVENT_CHARAFADE_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E7D0
class CharaFade : public ::event::ICmd {
public:
    virtual ~CharaFade();  // slot 0
    virtual bool update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
