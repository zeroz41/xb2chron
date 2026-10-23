#ifndef CLASSES_GF_GFEVTMODEL_H
#define CLASSES_GF_GFEVTMODEL_H

#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfInitParam.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedList.h"

namespace gf {
// Placeholder name: 1.0.0 leaves it unnamed too (fn_7100309D10, called from the same states). A free function
// because it takes no model, only the object handle: GfEvtModelDriver::StateStartBattle::enter and the blade's
// battle states pass their owner's handle and the battle command and state strings GfGameUtil::makeCommandBattle
// and makeStateBattle made. Its body (168 bytes at 0x710029C9B4) is in this unit.
void fn_710029C9B4(GF_OBJ_HANDLE* handle, mm::mtl::FixStr<32>& command, mm::mtl::FixStr<32>& state);

// a base of gf::GfEvtModel no evidence names yet
class TUnk_B53BE8 {
public:
    virtual ~TUnk_B53BE8();
    virtual const mm::mtl::RTTI* getRTTI() const = 0;
    virtual void update(fw::UpdateInfo const&) = 0;
    virtual void setDispWeapon(bool) = 0;
    virtual void setDispWeapon(bool, bool) = 0;
    virtual void getWeaponHandleRight() const = 0;
    virtual void getWeaponHandleLeft() const = 0;
    virtual void setWeaponBattleCommand() = 0;
    virtual void setWeaponFieldCommand() = 0;
    virtual void setWeaponBattleState() = 0;
    virtual void setWeaponFieldState() = 0;
    virtual void setWeaponBattleMount() = 0;
    virtual void setWeaponFieldMount() = 0;
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
    // zeroed when it is made (every GfEvtModel constructor's first store); what it holds is not known yet
    TUnk_B53BE8() : pad_8(0) {}
    unsigned int pad_8;
    unsigned char pad_c[0x4];  // fields: size from where the next base starts
};
// table 0x7100B53BE8; base at 0x0 unknown (TUnk_B53BE8), base at 0x10 the object listener (its table at
// 0x7100B53C80 holds listenerGfObj's thunk alone; the constructors register it with GfObjManager::addListener)
class GfEvtModel : public TUnk_B53BE8, public IGfObjListener {
public:
    // inline: the GfEvtModelDriver, Blade and Enemy constructors start with its stores and listener registration
    GfEvtModel(unsigned int modelType, unsigned int objId)
        : m_modelType(modelType), m_objId(objId), m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), pad_28(nullptr) {
        GfObjManager::addListener(this, static_cast<IGfObjListener::OBJEVT>(0));
    }
    virtual ~GfEvtModel();  // slot 0
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
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 14
    static mm::mtl::RTTI m_rtti;

    // which model: 0 a driver, 1 a blade, 5 an enemy (what each constructor passes) (the name is not the original's)
    unsigned int m_modelType;
    // the object's id, from its init parameters (the derived constructors' DataParamAcc reads it) (the name is
    // not the original's)
    unsigned int m_objId;
    // the object the model shows: -1 until the derived constructor makes it (GfObjFactory::createDriver); the
    // states pass it to GfMountManager and GfGameUtil (the name is not the original's)
    GF_OBJ_HANDLE* m_handle;
    void* pad_28;  // zeroed by the constructor; setMount tests it
    mm::mtl::FixStr<32> pad_30;  // made empty by the constructor
    // the models mounted on this one (FixedList<GfEvtModel*, 32>::erase is in the unit; resetMount/setMount
    // use it) (the name is not the original's)
    mm::mtl::FixedList<GfEvtModel*, 32> m_mountList;  // 0x58..0x298
};
}  // namespace gf

#endif
