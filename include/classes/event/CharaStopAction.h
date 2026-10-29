#ifndef CLASSES_EVENT_CHARASTOPACTION_H
#define CLASSES_EVENT_CHARASTOPACTION_H

#include "classes/event/ICmd.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3E568
class CharaStopAction : public ::event::ICmd {
public:
    // the table's slot 0 holds ICmd's destructor: inline, update is the key function
    virtual ~CharaStopAction() {}  // slot 0
    virtual bool update(event::ICmd::Param const&);  // slot 3
    // the object whose event animation update returns to idle; the name is not the original's
    gf::GF_OBJ_HANDLE* m_handle;  // 0x8
};
}  // namespace event

#endif
