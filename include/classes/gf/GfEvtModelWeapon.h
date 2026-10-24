#ifndef CLASSES_GF_GFEVTMODELWEAPON_H
#define CLASSES_GF_GFEVTMODELWEAPON_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfEvtModel.h"
#include "classes/gf/GfAppendHandles.h"
#include "classes/gf/GfInitParamWeapon.h"

namespace gf {
// table 0x7100B53FA8
class GfEvtModelWeapon : public ::gf::GfEvtModel {
public:
    explicit GfEvtModelWeapon(GfInitParamWeapon& param);
    // a new model, its first reference taken
    static GfEvtModelWeapon* create(GfInitParamWeapon& param);
    virtual ~GfEvtModelWeapon();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void setWeaponBattleCommand();  // slot 8
    virtual void setWeaponFieldCommand();  // slot 9
    virtual void setWeaponBattleState();  // slot 10
    virtual void setWeaponFieldState();  // slot 11
    // the model's GfComPackAnim plays an animation's data
    void playAnimData(void* data);
    void setScale(float scale);
    // the model's GfComPackAnim: plays name, whether it has ended (also when there is none), its speed
    void playAnimCS(const char* name);
    bool isPlayEndAnimCS();
    void setAnimSpeedCS(float speed);
    static mm::mtl::RTTI m_rtti;
    // the weapon's objects: each gets the commands and states, the destructor destroys them (the name is not
    // the original's)
    GfAppendHandles m_weapons;
    unsigned int m_weaponId;  // the commands' and states' weapon (the name is not the original's)
};
}  // namespace gf

#endif
