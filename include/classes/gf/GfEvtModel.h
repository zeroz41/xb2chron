#ifndef CLASSES_GF_GFEVTMODEL_H
#define CLASSES_GF_GFEVTMODEL_H

#include "mm/mtl/RTTI.h"
#include "classes/mm/mtl/ReferenceObject.h"
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfInitParam.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedList.h"
#include "mm/Vec3.h"

namespace gf {
// Placeholder name: 1.0.0 leaves it unnamed too (fn_7100309D10, called from the same states). A free function
// because it takes no model, only the object handle: GfEvtModelDriver::StateStartBattle::enter and the blade's
// battle states pass their owner's handle and the battle command and state strings GfGameUtil::makeCommandBattle
// and makeStateBattle made. Its body (168 bytes at 0x710029C9B4) is in this unit.
void fn_710029C9B4(GF_OBJ_HANDLE* handle, mm::mtl::FixStr<32>& command, mm::mtl::FixStr<32>& state);

// table 0x7100B53BE8; base at 0x0 a counted object (mm::mtl::ReferenceObject: the create functions add the
// first reference, destroy releases pad_28 with reference_object.h's `m_RefCount > 0`), base at 0x10 the object
// listener (its table at
// 0x7100B53C80 holds listenerGfObj's thunk alone; the constructors register it with GfObjManager::addListener)
class GfEvtModel : public ::mm::mtl::ReferenceObject, public IGfObjListener {
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
    virtual GF_OBJ_HANDLE* getWeaponHandleRight() const;  // slot 6
    virtual GF_OBJ_HANDLE* getWeaponHandleLeft() const;  // slot 7
    virtual void setWeaponBattleCommand();  // slot 8
    virtual void setWeaponFieldCommand();  // slot 9
    virtual void setWeaponBattleState();  // slot 10
    virtual void setWeaponFieldState();  // slot 11
    virtual void setWeaponBattleMount();  // slot 12
    virtual void setWeaponFieldMount();  // slot 13
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 14
    // lets the mounted models go, releases pad_28 and destroys the object (GfGameEvent::destroyEvtModel first;
    // the destructor calls it)
    void destroy();
    // takes this model off model's mount (destroy hands each mounted model this one)
    void resetMount(GfEvtModel* model);
    // mounts this model on model's bone (once: not while mounted, not twice in model's list): takes a reference,
    // keeps model in pad_28 and the bone in pad_30, then execMount; the short form passes mm::Vec3::zero twice
    void setMount(GfEvtModel* model, const char* bone);
    void setMount(GfEvtModel* model, const char* bone, const mm::Vec3& pos, const mm::Vec3& rot);
    // places model (mounted on this one) at pos with the Euler rotation rot and attaches it to the bone in its
    // pad_30 unless already attached or busy ("MT_met" first mounts this model's attach 1)
    void execMount(GfEvtModel* model, const mm::Vec3& pos, const mm::Vec3& rot);
    // whether an attached object (attaches 0-3) or the model's own object is not valid yet (GfGameObj::isValidGameObj
    // with a local message; the parameter is not used)
    bool isBusy(mm::mtl::FixStr<128>* name) const;
    // the UI-layer counterpart of an init parameter's layer (GfGameEvent::createEventObj passes pad_40 while a
    // full-screen menu is up)
    static unsigned int changeLayerUI(unsigned int layer);
    static mm::mtl::RTTI m_rtti;

    // which model: 0 a driver, 1 a blade, 5 an enemy (what each constructor passes) (the name is not the original's)
    unsigned int m_modelType;
    // the object's id, from its init parameters (the derived constructors' DataParamAcc reads it) (the name is
    // not the original's)
    unsigned int m_objId;
    // the object the model shows: -1 until the derived constructor makes it (GfObjFactory::createDriver); the
    // states pass it to GfMountManager and GfGameUtil (the name is not the original's)
    GF_OBJ_HANDLE* m_handle;
    // the model this one is mounted on (setMount stores it, resetMount and listenerGfObj (the object going, event 3)
    // clear it); a counted object destroy releases;
    // zeroed by the constructor
    GfEvtModel* pad_28;
    mm::mtl::FixStr<32> pad_30;  // made empty by the constructor
    // the models mounted on this one (FixedList<GfEvtModel*, 32>::erase is in the unit; resetMount/setMount
    // use it) (the name is not the original's)
    mm::mtl::FixedList<GfEvtModel*, 32> m_mountList;  // 0x58..0x298
};
}  // namespace gf

#endif
