#ifndef CLASSES_GF_SCOM_ENBOOK_DEAD_PLAYER_H
#define CLASSES_GF_SCOM_ENBOOK_DEAD_PLAYER_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B780
class SCOM_ENBOOK_DEAD_PLAYER : public ::gf::SCOM {
public:
    virtual ~SCOM_ENBOOK_DEAD_PLAYER();  // slot 0
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
