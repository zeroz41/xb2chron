#ifndef CLASSES_GF_GFFIELDENEMYSENSOR_H
#define CLASSES_GF_GFFIELDENEMYSENSOR_H

#include "classes/fw/IColiEventListener.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {
// table 0x7100B65DE8
class GfFieldEnemySensor : public ::fw::IColiEventListener {
public:
    virtual void enter(fw::IColiEventListener::EnterInfo const&);  // slot 0
    virtual void leave(fw::IColiEventListener::LeaveInfo const&);  // slot 1

    unsigned char pad_8[0x80];
    // the collision objects whose events it watches; enter sets, leave clears the flag that follows each
    // (create releases both; the names are not the original's)
    mm::mtl::IntrusivePtr<fw::ColiObject> m_coli;
    unsigned char pad_90[0x8];
    bool m_coliHit;
    unsigned char pad_99[0x7];
    mm::mtl::IntrusivePtr<fw::ColiObject> m_coli2;
    unsigned char pad_a8[0x4];
    bool m_coli2Hit;
    unsigned char pad_ad[0x3];
};
}  // namespace gf

#endif
