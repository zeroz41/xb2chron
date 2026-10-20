#ifndef CLASSES_GF_GFEVTMODELENEMY_H
#define CLASSES_GF_GFEVTMODELENEMY_H

#include "classes/gf/GfEvtModel.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B53F08
class GfEvtModelEnemy : public ::gf::GfEvtModel {
public:
    class StateEndBattle;
    class StateIdleBattle;
    class StateIdleField;
    class StateStartBattle;
    virtual ~GfEvtModelEnemy();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void update(fw::UpdateInfo const&);  // slot 3
    virtual void setDispWeapon(bool);  // slot 4
    virtual void setDispWeapon(bool, bool);  // slot 5
    virtual void getWeaponHandleRight() const;  // slot 6
    virtual void getWeaponHandleLeft() const;  // slot 7
    virtual void setWeaponBattleCommand();  // slot 8
    virtual void setWeaponFieldCommand();  // slot 9
    virtual void setWeaponBattleState();  // slot 10
    virtual void setWeaponFieldState();  // slot 11
    virtual void setWeaponBattleMount();  // slot 12
    virtual void setWeaponFieldMount();  // slot 13
};
}  // namespace gf

#endif
