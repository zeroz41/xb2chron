#ifndef CLASSES_EVENT_CHARASETIDLE_H
#define CLASSES_EVENT_CHARASETIDLE_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E760
class CharaSetIdle : public ::event::ICmd {
public:
    virtual ~CharaSetIdle();  // slot 0
    virtual void init();  // slot 2
    virtual void update(event::ICmd::Param const&);  // slot 3
    // set to 0 by init (the command's step; the name is not the original's)
    int m_step;  // 0x8
};
}  // namespace event

#endif
