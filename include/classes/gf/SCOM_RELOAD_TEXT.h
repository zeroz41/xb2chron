#ifndef CLASSES_GF_SCOM_RELOAD_TEXT_H
#define CLASSES_GF_SCOM_RELOAD_TEXT_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B3F0
class SCOM_RELOAD_TEXT : public ::gf::SCOM {
public:
    virtual ~SCOM_RELOAD_TEXT();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
