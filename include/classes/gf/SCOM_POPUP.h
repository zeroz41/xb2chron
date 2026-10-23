#ifndef CLASSES_GF_SCOM_POPUP_H
#define CLASSES_GF_SCOM_POPUP_H

#include "classes/gf/SCOM.h"
#include "classes/gf/GfMenuObjPopup.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AB98
class SCOM_POPUP : public ::gf::SCOM {
public:
    explicit SCOM_POPUP(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long createAffinity(unsigned int, unsigned int, unsigned int);
    static unsigned long createIdea(unsigned int, unsigned int, unsigned int);
    static unsigned long createPouch(unsigned int, unsigned int, unsigned int);
    static unsigned long createDevelop(unsigned int, unsigned int);
    static unsigned long createCrystalOK(unsigned int);
    static unsigned long createMercenaryReturn(unsigned int, unsigned int);
    static unsigned long createMercenaryAdd(unsigned int);
    static unsigned long createArts(unsigned int, unsigned int);
    // queues an affinity chart achievement popup for a blade's skill line and level; the request's ID
    static unsigned long createAchievement(unsigned int blade, unsigned int line, unsigned int level);

    // the names are not the original's: the popup to open, and the frames exec waits first (create sets 20)
    GfMenuObjPopup::OpenParam m_param;
    int m_wait;
};
}  // namespace gf

#endif
