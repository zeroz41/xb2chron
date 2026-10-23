#ifndef CLASSES_GF_SCOM_QUEST_REACH_H
#define CLASSES_GF_SCOM_QUEST_REACH_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B4B0
class SCOM_QUEST_REACH : public ::gf::SCOM {
public:
    explicit SCOM_QUEST_REACH(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long createDiscoverLandmark(unsigned int);
    static unsigned long createArriveLandmark(unsigned int);
    static unsigned long createArrivePlace(unsigned int);

    // the names are not the original's: what the create functions store (their arguments, in order)
    int m_value;
    unsigned int m_value2;
};
}  // namespace gf

#endif
