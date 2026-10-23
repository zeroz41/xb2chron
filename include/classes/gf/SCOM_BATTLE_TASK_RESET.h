#ifndef CLASSES_GF_SCOM_BATTLE_TASK_RESET_H
#define CLASSES_GF_SCOM_BATTLE_TASK_RESET_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// a base of gf::SCOM_BATTLE_TASK_RESET no evidence names yet
class TUnk_B6ACD8 {
public:
    virtual ~TUnk_B6ACD8();
};
// table 0x7100B6ACA8; base at 0x20 unknown (TUnk_B6ACD8)
class SCOM_BATTLE_TASK_RESET : public ::gf::SCOM, public TUnk_B6ACD8 {
public:
    virtual ~SCOM_BATTLE_TASK_RESET();  // slot 0
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
