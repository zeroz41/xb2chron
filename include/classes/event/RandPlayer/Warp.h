#ifndef CLASSES_EVENT_RANDPLAYER_WARP_H
#define CLASSES_EVENT_RANDPLAYER_WARP_H

#include "classes/event/ICmd.h"
#include "classes/event/RandPlayer.h"

namespace event {
// table 0x7100B3F020
class RandPlayer::Warp : public ::event::ICmd {
public:
    virtual ~Warp() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual bool update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
