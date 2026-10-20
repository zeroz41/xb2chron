#ifndef CLASSES_GF_SCOM_ADD_MERCENARIES_POINT_H
#define CLASSES_GF_SCOM_ADD_MERCENARIES_POINT_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B150
class SCOM_ADD_MERCENARIES_POINT : public ::gf::SCOM {
public:
    virtual ~SCOM_ADD_MERCENARIES_POINT();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
