#ifndef CLASSES_GF_SCOM_POPUP_H
#define CLASSES_GF_SCOM_POPUP_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AB98
class SCOM_POPUP : public ::gf::SCOM {
public:
    virtual ~SCOM_POPUP();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
    // queues an affinity chart achievement popup for a blade's skill line and level; the request's ID
    static unsigned long createAchievement(unsigned int blade, unsigned int line, unsigned int level);
};
}  // namespace gf

#endif
