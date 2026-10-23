#ifndef CLASSES_GF_SCOM_BC_PARTICLE_H
#define CLASSES_GF_SCOM_BC_PARTICLE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6ABF8
class SCOM_BC_PARTICLE : public ::gf::SCOM {
public:
    virtual ~SCOM_BC_PARTICLE();  // slot 0
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
