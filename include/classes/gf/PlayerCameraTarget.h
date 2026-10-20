#ifndef CLASSES_GF_PLAYERCAMERATARGET_H
#define CLASSES_GF_PLAYERCAMERATARGET_H

#include "classes/gf/IGfEvent.h"

namespace fw { class UpdateInfo; }

namespace gf {
// a base of gf::PlayerCameraTarget no evidence names yet
class TUnk_B45B48 {
public:
    virtual ~TUnk_B45B48();
    virtual void getRTTI() const = 0;
    virtual void update(fw::UpdateInfo const&) = 0;
    virtual void requestResetCamera() = 0;
    virtual void gevPartyMemberOK(bool) = 0;
    unsigned char pad_8[0x8];  // fields: size from where the next base starts
};
// a base of gf::PlayerCameraTarget no evidence names yet
class TUnk_B45B88 {
public:
    virtual ~TUnk_B45B88();
};
// table 0x7100B45B48; base at 0x0 unknown (TUnk_B45B48), base at 0x10 unknown (TUnk_B45B88)
class PlayerCameraTarget : public TUnk_B45B48, public TUnk_B45B88, public ::gf::IGfEvent {
public:
    virtual ~PlayerCameraTarget();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void update(fw::UpdateInfo const&);  // slot 3
    virtual void requestResetCamera();  // slot 4
    virtual void gevPartyMemberOK(bool);  // slot 5
};
}  // namespace gf

#endif
