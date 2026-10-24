#ifndef CLASSES_GF_GFEVTMODELDRIVER_H
#define CLASSES_GF_GFEVTMODELDRIVER_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfEvtModel.h"
#include "classes/gf/GfInitParamDriver.h"
#include "ai/Fsm.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B53C88
class GfEvtModelDriver : public ::gf::GfEvtModel {
public:
    class StateEndBattle;
    class StateIdleBattle;
    class StateIdleField;
    class StateStartBattle;
    // makes the driver (GfObjFactory::createDriver) and its states: idle in the field (0), idle in battle (1),
    // starting (2) and ending (3) a battle
    explicit GfEvtModelDriver(GfInitParamDriver& param);
    virtual ~GfEvtModelDriver();  // slot 0
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
    // a new driver model, its first reference taken
    static GfEvtModelDriver* create(GfInitParamDriver& param);
    // the weapon's (right: its first object, left: its second) GfComPackAnim: plays name, whether it has ended
    // (also when there is none), its speed
    void playAnimWeaponRightCS(const char* name);
    bool isPlayEndAnimWeaponRightCS();
    void setAnimSpeedWeaponRightCS(float speed);
    void playAnimWeaponLeftCS(const char* name);
    bool isPlayEndAnimWeaponLeftCS();
    void setAnimSpeedWeaponLeftCS(float speed);
    // shows or hides the objects mounted on attachment 1 (their normal alpha 1 or 0)
    void setDispJiji(bool disp);
    static mm::mtl::RTTI m_rtti;

    ai::Fsm m_fsm;  // the four states (the name is not the original's)
    // the driver's blade: its init parameter's, else the driver's own (DataParamAcc::getBlade) (the name is not
    // the original's)
    unsigned int m_bladeId;
};
}  // namespace gf

#endif
