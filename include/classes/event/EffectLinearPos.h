#ifndef CLASSES_EVENT_EFFECTLINEARPOS_H
#define CLASSES_EVENT_EFFECTLINEARPOS_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E840
class EffectLinearPos : public ::event::ICmd {
public:
    virtual ~EffectLinearPos();  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
