#ifndef CLASSES_EVENT_CHARAPLAYFACIAL_H
#define CLASSES_EVENT_CHARAPLAYFACIAL_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E610
class CharaPlayFacial {
public:
    virtual ~CharaPlayFacial();  // slot 0
    virtual void init();  // slot 2
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    // set to 0 by init (the command's step; the name is not the original's)
    int m_step;  // 0x8
};
}  // namespace event

#endif
