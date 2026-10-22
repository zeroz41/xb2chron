#ifndef CLASSES_GF_SCOM_ACHIEV_INC_H
#define CLASSES_GF_SCOM_ACHIEV_INC_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AA60
class SCOM_ACHIEV_INC : public ::gf::SCOM {
public:
    virtual ~SCOM_ACHIEV_INC();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
    // queues a request that adds value to achievement counter type (type 0x22 also counts salvage-shop requests)
    static void create(unsigned int type, int value, unsigned int);
};
}  // namespace gf

#endif
