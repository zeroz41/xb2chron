#ifndef CLASSES_GF_GFEVTMODELBLADE_H
#define CLASSES_GF_GFEVTMODELBLADE_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfEvtModel.h"
#include "classes/gf/GfInitParamBlade.h"
#include "ai/Fsm.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B53DC8
class GfEvtModelBlade : public ::gf::GfEvtModel {
public:
    class StateEndBattle;
    class StateIdleBattle;
    class StateIdleField;
    class StateStartBattle;
    // makes the blade (GfObjFactory::createBlade) and its states: idle in the field (0), idle in battle (1),
    // starting (2) and ending (3) a battle
    explicit GfEvtModelBlade(GfInitParamBlade& param);
    virtual ~GfEvtModelBlade();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void update(fw::UpdateInfo const&);  // slot 3
    virtual void setDispWeapon(bool);  // slot 4
    virtual void setDispWeapon(bool, bool);  // slot 5
    virtual GF_OBJ_HANDLE* getWeaponHandleRight() const;  // slot 6
    virtual GF_OBJ_HANDLE* getWeaponHandleLeft() const;  // slot 7
    virtual void setWeaponBattleCommand();  // slot 8
    virtual void setWeaponFieldCommand();  // slot 9
    virtual void setWeaponBattleState();  // slot 10
    virtual void setWeaponFieldState();  // slot 11
    virtual void setWeaponBattleMount();  // slot 12
    virtual void setWeaponFieldMount();  // slot 13
    // a new blade model, its first reference taken
    static GfEvtModelBlade* create(GfInitParamBlade& param);
    // the weapon's (right: its first object, left: its second) GfComPackAnim: plays name, whether it has ended
    // (also when there is none), its speed
    void playAnimWeaponRightCS(const char* name);
    bool isPlayEndAnimWeaponRightCS();
    void setAnimSpeedWeaponRightCS(float speed);
    void playAnimWeaponLeftCS(const char* name);
    bool isPlayEndAnimWeaponLeftCS();
    void setAnimSpeedWeaponLeftCS(float speed);
    static mm::mtl::RTTI m_rtti;

    ai::Fsm m_fsm;  // the four states (the name is not the original's)
};
}  // namespace gf

#endif
