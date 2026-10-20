#ifndef CLASSES_GF_SCOM_TARGET_UI_H
#define CLASSES_GF_SCOM_TARGET_UI_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B570
class SCOM_TARGET_UI : public ::gf::SCOM {
public:
    virtual ~SCOM_TARGET_UI();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
