#ifndef CLASSES_EVENT_CHARAHIDEWPN_H
#define CLASSES_EVENT_CHARAHIDEWPN_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E728
class CharaHideWpn : public ::event::ICmd {
public:
    virtual ~CharaHideWpn();  // slot 0
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    unsigned char pad_8[0x10];  // CharaObj holds one at 0x938, the next command at +0x18
};
}  // namespace event

#endif
