#ifndef CLASSES_EVENT_EFFECTPLAYEVA_H
#define CLASSES_EVENT_EFFECTPLAYEVA_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E8E8
class EffectPlayEva : public ::event::ICmd {
public:
    virtual ~EffectPlayEva();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
};
}  // namespace event

#endif
