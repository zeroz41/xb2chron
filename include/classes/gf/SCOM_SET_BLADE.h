#ifndef CLASSES_GF_SCOM_SET_BLADE_H
#define CLASSES_GF_SCOM_SET_BLADE_H

#include "classes/gf/SCOM.h"
#include "gf/GfReqParam.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B600
class SCOM_SET_BLADE : public ::gf::SCOM {
public:
    virtual ~SCOM_SET_BLADE();  // slot 0
    SCOM_SET_BLADE(SCOM_TYPE type, const RQ_SETUP_BLADE& setup) : SCOM(type), m_setup(setup) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // queues a type-81 request with the driver's blades (none for driver 0, which returns -1); once the game is
    // cleared, blade slots 3 and 4 become 1002 and 1003 when a slot holds 1001, else none
    static unsigned long create(const RQ_SETUP_BLADE& setup);

    RQ_SETUP_BLADE m_setup;  // the name is not the original's
};
}  // namespace gf

#endif
