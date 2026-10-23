#ifndef CLASSES_GF_SCOM_BATTLE_TASK_RESET_H
#define CLASSES_GF_SCOM_BATTLE_TASK_RESET_H

#include "classes/gf/SCOM.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6ACA8; the PtrSingleton base at 0x20: the destructors store its table there and clear its instance,
// create asserts get()==0 (only one such request at a time)
class SCOM_BATTLE_TASK_RESET : public ::gf::SCOM, public ::mm::mtl::PtrSingleton< ::gf::SCOM_BATTLE_TASK_RESET> {
public:
    explicit SCOM_BATTLE_TASK_RESET(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create();

    // the name is not the original's: create sets it to 3, exec counts it down and acts at 0
    int m_wait;
};
}  // namespace gf

#endif
