#ifndef CLASSES_GF_GFEVTMODELBLADE_H
#define CLASSES_GF_GFEVTMODELBLADE_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfEvtModel.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B53DC8
class GfEvtModelBlade : public ::gf::GfEvtModel {
public:
    class StateEndBattle;
    class StateIdleBattle;
    class StateIdleField;
    class StateStartBattle;
    virtual ~GfEvtModelBlade();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
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
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
