#ifndef CLASSES_EVENT_CHARAPLAYTALK_H
#define CLASSES_EVENT_CHARAPLAYTALK_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E648
class CharaPlayTalk {
public:
    virtual ~CharaPlayTalk();  // slot 0
    virtual void init();  // slot 2
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
};
}  // namespace event

#endif
