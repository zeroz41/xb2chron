#ifndef CLASSES_GF_SCOM_HOMURI_PARTS_H
#define CLASSES_GF_SCOM_HOMURI_PARTS_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B7B0
class SCOM_HOMURI_PARTS : public ::gf::SCOM {
public:
    explicit SCOM_HOMURI_PARTS(SCOM_TYPE type) : SCOM(type) {}
    // the destructor is implicit: its D0 sits in the unit's inline tail and exec is the key function
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // GfGameScene::setHomuriWeaponExtraMesh passes the party id of Homura's blade, its flag and its float
    static void create(unsigned int party, bool, float);

    // the names are not the original's: what create stores and exec reads
    unsigned int m_party;
    bool m_toMax;
    float m_time;
    float m_duration;
};
}  // namespace gf

#endif
