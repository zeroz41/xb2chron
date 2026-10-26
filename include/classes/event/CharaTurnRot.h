#ifndef CLASSES_EVENT_CHARATURNROT_H
#define CLASSES_EVENT_CHARATURNROT_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E450
class CharaTurnRot {
public:
    virtual ~CharaTurnRot();  // slot 0
    virtual void init();  // slot 2
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
};
}  // namespace event

#endif
