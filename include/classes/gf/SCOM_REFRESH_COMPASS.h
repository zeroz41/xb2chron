#ifndef CLASSES_GF_SCOM_REFRESH_COMPASS_H
#define CLASSES_GF_SCOM_REFRESH_COMPASS_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// a base of gf::SCOM_REFRESH_COMPASS no evidence names yet
class TUnk_B6AC88 {
public:
    virtual ~TUnk_B6AC88();
};
// table 0x7100B6AC58; base at 0x20 unknown (TUnk_B6AC88)
class SCOM_REFRESH_COMPASS : public ::gf::SCOM, public TUnk_B6AC88 {
public:
    virtual ~SCOM_REFRESH_COMPASS();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
