#ifndef CLASSES_GF_SCOM_SCRIPT_H
#define CLASSES_GF_SCOM_SCRIPT_H

#include "classes/gf/SCOM.h"
#include "mm/mtl/FixStr.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_SCOM_HANDLE; }

namespace gf {
// table 0x7100B6B3C0
class SCOM_SCRIPT : public ::gf::SCOM {
public:
    // the destructor is implicit: slot 0 holds SCOM's, D0 only frees
    SCOM_SCRIPT(SCOM_TYPE type, unsigned int id, const mm::mtl::FixStr<32>& name, bool flag)
        : SCOM(type), m_id(id), m_name(name), m_step(0), m_flag(flag) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // queues a script command: GfFieldZoneScript::execScript runs a script with it (id 1), destroyScript passes
    // a null name
    // a null name; returns the request's handle (GfPlayComAfterEventScript waits on it with GfReqSmallCom::isValid)
    static GF_SCOM_HANDLE* create(unsigned int id, const char* name, bool flag);

    // the names below are not the original's: create stores its arguments (the name without path or extension)
    unsigned int m_id;
    mm::mtl::FixStr<32> m_name;
    int m_step;   // exec: 0 load, 1 wait for the start, 2 wait while active
    bool m_flag;  // create's flag: after the start, keep the request until the script ends
};
}  // namespace gf

#endif
