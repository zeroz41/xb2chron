#ifndef CLASSES_GF_SCOM_ENBOOK_IN_BATTLE_H
#define CLASSES_GF_SCOM_ENBOOK_IN_BATTLE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B6F0
class SCOM_ENBOOK_IN_BATTLE : public ::gf::SCOM {
public:
    virtual ~SCOM_ENBOOK_IN_BATTLE();  // slot 0
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
