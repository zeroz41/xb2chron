#ifndef CLASSES_GF_SCOM_EXEC_MOUNT_H
#define CLASSES_GF_SCOM_EXEC_MOUNT_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B420
class SCOM_EXEC_MOUNT : public ::gf::SCOM {
public:
    virtual ~SCOM_EXEC_MOUNT();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
