#ifndef CLASSES_GF_GFEVTMODELENEMY_H
#define CLASSES_GF_GFEVTMODELENEMY_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfEvtModel.h"
#include "classes/gf/GfInitParamEnemy.h"
#include "ai/Fsm.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B53F08
class GfEvtModelEnemy : public ::gf::GfEvtModel {
public:
    class StateEndBattle;
    class StateIdleBattle;
    class StateIdleField;
    class StateStartBattle;
    // makes the enemy (GfObjFactory::createEnemy) and its states: idle in the field (0), idle in battle (1),
    // starting (2) and ending (3) a battle
    explicit GfEvtModelEnemy(GfInitParamEnemy& param);
    virtual ~GfEvtModelEnemy();  // slot 0
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

    ai::Fsm m_fsm;  // the four states (the name is not the original's)
};
}  // namespace gf

#endif
