#ifndef CLASSES_GF_SCOM_ACCESS_TARGET_H
#define CLASSES_GF_SCOM_ACCESS_TARGET_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B6B540
class SCOM_ACCESS_TARGET : public ::gf::SCOM {
public:
    virtual ~SCOM_ACCESS_TARGET();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
    // queues one: the PC's access target becomes handle's (-1: none)
    static void create(gf::GF_OBJ_HANDLE* handle);
};
}  // namespace gf

#endif
