#ifndef CLASSES_EVENT_EFFECTLINEARROT_H
#define CLASSES_EVENT_EFFECTLINEARROT_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E878
class EffectLinearRot : public ::event::ICmd {
public:
    virtual ~EffectLinearRot();  // slot 0
    virtual bool update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
