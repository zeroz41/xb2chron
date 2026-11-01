#ifndef CLASSES_GF_SCOM_HOMURI_PARTS_H
#define CLASSES_GF_SCOM_HOMURI_PARTS_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B7B0
class SCOM_HOMURI_PARTS : public ::gf::SCOM {
public:
    virtual ~SCOM_HOMURI_PARTS();  // slot 0
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // GfGameScene::setHomuriWeaponExtraMesh passes the party id of Homura's blade, its flag and its float
    static void create(unsigned int party, bool, float);
};
}  // namespace gf

#endif
