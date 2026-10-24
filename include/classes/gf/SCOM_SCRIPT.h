#ifndef CLASSES_GF_SCOM_SCRIPT_H
#define CLASSES_GF_SCOM_SCRIPT_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_SCOM_HANDLE; }

namespace gf {
// table 0x7100B6B3C0
class SCOM_SCRIPT : public ::gf::SCOM {
public:
    virtual ~SCOM_SCRIPT();  // slot 0
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // queues a script command: GfFieldZoneScript::execScript runs a script with it (id 1), destroyScript passes
    // a null name
    // a null name; returns the request's handle (GfPlayComAfterEventScript waits on it with GfReqSmallCom::isValid)
    static GF_SCOM_HANDLE* create(unsigned int id, const char* name, bool flag);
};
}  // namespace gf

#endif
