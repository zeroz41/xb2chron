#ifndef CLASSES_EVENT_CHARASETIDLE_H
#define CLASSES_EVENT_CHARASETIDLE_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E760
class CharaSetIdle : public ::event::ICmd {
public:
    virtual ~CharaSetIdle();  // slot 0
    virtual void init();  // slot 2
    virtual bool update(event::ICmd::Param const&);  // slot 3
    // set to 0 by init (the command's step; the name is not the original's)
    int m_step;  // 0x8
    unsigned char pad_c[0x1c];  // CharaObj holds one at 0x5e0, the next command at 0x608
};
}  // namespace event

#endif
