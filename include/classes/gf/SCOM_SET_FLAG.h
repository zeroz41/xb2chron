#ifndef CLASSES_GF_SCOM_SET_FLAG_H
#define CLASSES_GF_SCOM_SET_FLAG_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B5A0
class SCOM_SET_FLAG : public ::gf::SCOM {
public:
    virtual ~SCOM_SET_FLAG();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
