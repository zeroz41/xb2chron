#ifndef CLASSES_GF_SCOM_FIELD_SKILL_H
#define CLASSES_GF_SCOM_FIELD_SKILL_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AA90
class SCOM_FIELD_SKILL : public ::gf::SCOM {
public:
    virtual ~SCOM_FIELD_SKILL();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
