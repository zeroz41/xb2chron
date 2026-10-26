#ifndef CLASSES_EVENT_CHARAPLAYMOTION_H
#define CLASSES_EVENT_CHARAPLAYMOTION_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3CC68
class CharaPlayMotion : public ::event::ICmd {
public:
    virtual ~CharaPlayMotion();  // slot 0
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
};
}  // namespace event

#endif
