#ifndef CLASSES_GF_GFWEAPON_H
#define CLASSES_GF_GFWEAPON_H

#include "classes/gf/GfAppendHandles.h"

namespace gf {
// table 0x7100B54DE8: its slot 0 is GfAppendHandles's destructor, so the destructor is inline
class GfWeapon : public ::gf::GfAppendHandles {
public:
    virtual ~GfWeapon() {}  // slot 0
    // Placeholder name: nothing names it in either version (1.0.0's copy at 0x710031E054 is unnamed too). A member
    // because GfGameMount::attach calls it on its m_weapon (x0) twice, once per set. What it does: for each of the
    // ten objects of the set in use whose GfObj has a GfComAsm (obj+0x48, isKindOf GfComAsm::m_rtti), it makes the
    // idle state name GfGameUtil::makeWeaponStateIdle gives for the weapon's owner (GfGameUtil::getWeaponOwner of the
    // object's handle) and whether that owner is in battle, and sets it on layer 0 (GfComAsm::setState).
    void fn_71002AE854();
};
}  // namespace gf

#endif
