#ifndef CLASSES_GF_SCOM_CHAR_DEAD_H
#define CLASSES_GF_SCOM_CHAR_DEAD_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6A9E0
class SCOM_CHAR_DEAD : public ::gf::SCOM {
public:
    virtual ~SCOM_CHAR_DEAD();  // slot 0
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
