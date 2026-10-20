#ifndef CLASSES_EVENT_EFFECTPLAYEFF_H
#define CLASSES_EVENT_EFFECTPLAYEFF_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E808
class EffectPlayEff : public ::event::ICmd {
public:
    virtual ~EffectPlayEff();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
};
}  // namespace event

#endif
