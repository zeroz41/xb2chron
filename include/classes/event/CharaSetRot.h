#ifndef CLASSES_EVENT_CHARASETROT_H
#define CLASSES_EVENT_CHARASETROT_H

#include "classes/event/ICmd.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3E3E0
class CharaSetRot : public ::event::ICmd {
public:
    virtual ~CharaSetRot();  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    // the object update turns (-1: none; CharaObj's constructor stores -1); the name is not the original's
    gf::GF_OBJ_HANDLE* m_handle;  // 0x8
};
}  // namespace event

#endif
