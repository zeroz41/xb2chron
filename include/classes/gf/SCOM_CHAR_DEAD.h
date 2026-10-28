#ifndef CLASSES_GF_SCOM_CHAR_DEAD_H
#define CLASSES_GF_SCOM_CHAR_DEAD_H

#include "classes/gf/SCOM.h"
#include "gf/MsgObjectNotifyDead.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6A9E0
class SCOM_CHAR_DEAD : public ::gf::SCOM {
public:
    // queues the death of an object (GfPlayComPlayerDead's start and replaceDeadType: the controlled mover); like the
    // other SCOMs' create it returns the command's handle
    static unsigned long create(GF_OBJ_HANDLE* handle, const MsgObjectNotifyDead& msg);
    virtual bool exec(fw::UpdateInfo const&);  // slot 2

    // the names are not the original's: create stores the dead object and a copy of its message
    GF_OBJ_HANDLE* m_handle;
    MsgObjectNotifyDead m_msg;
};
}  // namespace gf

#endif
