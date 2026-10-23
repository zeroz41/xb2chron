#ifndef CLASSES_GF_SCOM_DEAD_PARTICLE_H
#define CLASSES_GF_SCOM_DEAD_PARTICLE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6ABC8
class SCOM_DEAD_PARTICLE : public ::gf::SCOM {
public:
    virtual ~SCOM_DEAD_PARTICLE();  // slot 0
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
