#ifndef CLASSES_GF_SCOM_REFRESH_COMPASS_H
#define CLASSES_GF_SCOM_REFRESH_COMPASS_H

#include "classes/gf/SCOM.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AC58; the PtrSingleton base at 0x20: the destructors store its table there and clear its instance,
// create asserts get()==0 (only one such request at a time)
class SCOM_REFRESH_COMPASS : public ::gf::SCOM, public ::mm::mtl::PtrSingleton< ::gf::SCOM_REFRESH_COMPASS> {
public:
    explicit SCOM_REFRESH_COMPASS(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create();

    // the name is not the original's: create sets it to 3, exec counts it down and acts at 0
    int m_wait;
};
}  // namespace gf

#endif
