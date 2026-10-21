#ifndef CLASSES_GF_GFEVTMODELWEAPON_H
#define CLASSES_GF_GFEVTMODELWEAPON_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfEvtModel.h"

namespace gf {
// table 0x7100B53FA8
class GfEvtModelWeapon : public ::gf::GfEvtModel {
public:
    virtual ~GfEvtModelWeapon();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void setWeaponBattleCommand();  // slot 8
    virtual void setWeaponFieldCommand();  // slot 9
    virtual void setWeaponBattleState();  // slot 10
    virtual void setWeaponFieldState();  // slot 11
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
