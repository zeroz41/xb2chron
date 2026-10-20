#ifndef CLASSES_GF_SCOM_ENBOOK_DEFEAT_ENEMY_H
#define CLASSES_GF_SCOM_ENBOOK_DEFEAT_ENEMY_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B750
class SCOM_ENBOOK_DEFEAT_ENEMY : public ::gf::SCOM {
public:
    virtual ~SCOM_ENBOOK_DEFEAT_ENEMY();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
