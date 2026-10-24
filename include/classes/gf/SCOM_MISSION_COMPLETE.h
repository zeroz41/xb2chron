#ifndef CLASSES_GF_SCOM_MISSION_COMPLETE_H
#define CLASSES_GF_SCOM_MISSION_COMPLETE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B1B0
class SCOM_MISSION_COMPLETE : public ::gf::SCOM {
public:
    explicit SCOM_MISSION_COMPLETE(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(unsigned int);

    unsigned int m_mission;  // the name is not the original's: the mission create takes
};
}  // namespace gf

#endif
