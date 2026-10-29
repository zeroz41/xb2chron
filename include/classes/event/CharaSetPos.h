#ifndef CLASSES_EVENT_CHARASETPOS_H
#define CLASSES_EVENT_CHARASETPOS_H

#include "classes/event/ICmd.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3E3A8
class CharaSetPos : public ::event::ICmd {
public:
    // the table's slot 0 holds ICmd's destructor: inline, update is the key function
    virtual ~CharaSetPos() {}  // slot 0
    virtual bool update(event::ICmd::Param const&);  // slot 3
    // the object update moves (-1: none; CharaObj's constructor stores -1); the name is not the original's
    gf::GF_OBJ_HANDLE* m_handle;  // 0x8
};
}  // namespace event

#endif
