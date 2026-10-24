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
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function of the GfWeapon unit
// (its address lies there; no this). What it does: the model name of driver id from GfBdatChrDr
// (getChrDrModel2, getChrDrCondition with GfGameCond::isGameCond, then BDAT columns by the driver's id),
// first trying fn_71002DF4C4(id, third argument); for driver 6 with the second argument set it also ORs in
// fn_710024F910's result. GfAssetSetupDriver's getMdlFile/getArcFile pass (id, create type in {2, 3, 11},
// create type == 3), GfAssetSetupNpc::getMdlFile (id, false, create type == 3) for ids below 26.
const char* fn_71002DF39C(unsigned int driverId, bool createTypeIn2311, bool createType3);
}  // namespace gf

#endif
