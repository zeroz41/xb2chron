#ifndef CLASSES_EVENT_RANDPLAYER_RESET_H
#define CLASSES_EVENT_RANDPLAYER_RESET_H

#include "classes/event/ICmd.h"
#include "classes/event/RandPlayer.h"

namespace event {
// table 0x7100B3F0C8
class RandPlayer::Reset : public ::event::ICmd {
public:
    virtual ~Reset();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
