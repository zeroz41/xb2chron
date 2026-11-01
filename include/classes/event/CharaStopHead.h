#ifndef CLASSES_EVENT_CHARASTOPHEAD_H
#define CLASSES_EVENT_CHARASTOPHEAD_H

#include "classes/event/ICmd.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3E5D8
class CharaStopHead : public ::event::ICmd {
public:
    virtual ~CharaStopHead() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual int update(event::ICmd::Param const&);  // slot 3
    gf::GF_OBJ_HANDLE* m_handle;  // 0x8: the character (update looks it up; the name is not the original's)
};
}  // namespace event

#endif
