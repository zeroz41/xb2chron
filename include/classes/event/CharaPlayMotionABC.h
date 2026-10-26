#ifndef CLASSES_EVENT_CHARAPLAYMOTIONABC_H
#define CLASSES_EVENT_CHARAPLAYMOTIONABC_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3CCA0
class CharaPlayMotionABC : public ::event::ICmd {
public:
    virtual ~CharaPlayMotionABC();  // slot 0
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
};
}  // namespace event

#endif
