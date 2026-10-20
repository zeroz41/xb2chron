#ifndef CLASSES_GF_SCOM_ADD_WP_H
#define CLASSES_GF_SCOM_ADD_WP_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B060
class SCOM_ADD_WP : public ::gf::SCOM {
public:
    virtual ~SCOM_ADD_WP();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
