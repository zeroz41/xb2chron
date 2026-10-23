#ifndef CLASSES_GF_SCOM_BATTLE_BGM_H
#define CLASSES_GF_SCOM_BATTLE_BGM_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B660
class SCOM_BATTLE_BGM : public ::gf::SCOM {
public:
    virtual bool exec(fw::UpdateInfo const&);  // slot 2

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_value;
};
}  // namespace gf

#endif
