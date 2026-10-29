#ifndef CLASSES_EVENT_CHARAPLAYEVAEFF_H
#define CLASSES_EVENT_CHARAPLAYEVAEFF_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E6F0
class CharaPlayEvaEff : public ::event::ICmd {
public:
    virtual ~CharaPlayEvaEff();  // slot 0
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    unsigned char pad_8[0x28];  // CharaObj holds one at 0x8e0, the next table store (a CharaEvaPlayerEff) at +0x30
};
}  // namespace event

#endif
