#ifndef CLASSES_EVENT_CHARASETROT_H
#define CLASSES_EVENT_CHARASETROT_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E3E0
class CharaSetRot : public ::event::ICmd {
public:
    virtual ~CharaSetRot();  // slot 0
    virtual bool update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
