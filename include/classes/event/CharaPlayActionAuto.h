#ifndef CLASSES_EVENT_CHARAPLAYACTIONAUTO_H
#define CLASSES_EVENT_CHARAPLAYACTIONAUTO_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3CC30
class CharaPlayActionAuto {
public:
    virtual ~CharaPlayActionAuto();  // slot 0
    virtual void init();  // slot 2
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
};
}  // namespace event

#endif
