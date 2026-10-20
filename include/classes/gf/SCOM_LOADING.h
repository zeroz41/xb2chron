#ifndef CLASSES_GF_SCOM_LOADING_H
#define CLASSES_GF_SCOM_LOADING_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B390
class SCOM_LOADING : public ::gf::SCOM {
public:
    virtual ~SCOM_LOADING();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
