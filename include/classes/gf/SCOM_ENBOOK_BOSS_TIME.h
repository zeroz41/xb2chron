#ifndef CLASSES_GF_SCOM_ENBOOK_BOSS_TIME_H
#define CLASSES_GF_SCOM_ENBOOK_BOSS_TIME_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B720
class SCOM_ENBOOK_BOSS_TIME : public ::gf::SCOM {
public:
    virtual ~SCOM_ENBOOK_BOSS_TIME();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
