#ifndef CLASSES_EVENT_EFFECTLINEARCOL_H
#define CLASSES_EVENT_EFFECTLINEARCOL_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E8B0
class EffectLinearCol : public ::event::ICmd {
public:
    virtual ~EffectLinearCol();  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
