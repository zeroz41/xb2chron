#ifndef CLASSES_EVENT_CHARASETPOS_H
#define CLASSES_EVENT_CHARASETPOS_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E3A8
class CharaSetPos : public ::event::ICmd {
public:
    virtual ~CharaSetPos();  // slot 0
    virtual bool update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
