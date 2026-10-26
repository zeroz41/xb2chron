#ifndef CLASSES_EVENT_CHARAPLAYEVA_H
#define CLASSES_EVENT_CHARAPLAYEVA_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E6B8
class CharaPlayEva : public ::event::ICmd {
public:
    virtual ~CharaPlayEva();  // slot 0
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
};
}  // namespace event

#endif
