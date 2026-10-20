#ifndef CLASSES_GF_SCOM_LEVELUP_DEVELOP_H
#define CLASSES_GF_SCOM_LEVELUP_DEVELOP_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B120
class SCOM_LEVELUP_DEVELOP : public ::gf::SCOM {
public:
    virtual ~SCOM_LEVELUP_DEVELOP();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
