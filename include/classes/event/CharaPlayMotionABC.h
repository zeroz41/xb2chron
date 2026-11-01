#ifndef CLASSES_EVENT_CHARAPLAYMOTIONABC_H
#define CLASSES_EVENT_CHARAPLAYMOTIONABC_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3CCA0
class CharaPlayMotionABC : public ::event::ICmd {
public:
    virtual ~CharaPlayMotionABC();  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    unsigned char pad_8[0x78];  // CharaObj holds one at 0x6d0, the next command at +0x80
};
}  // namespace event

#endif
