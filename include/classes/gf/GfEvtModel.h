#ifndef CLASSES_GF_GFEVTMODEL_H
#define CLASSES_GF_GFEVTMODEL_H

#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { namespace IGfObjListener { enum OBJEVT : int; }}

namespace gf {
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
    unsigned char pad_8[0x8];  // fields: size from where the next base starts
};
// a base of gf::GfEvtModel no evidence names yet
class TUnk_B53C70 {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
};
// table 0x7100B53BE8; base at 0x0 unknown (TUnk_B53BE8), base at 0x10 unknown (TUnk_B53C70)
class GfEvtModel : public TUnk_B53BE8, public TUnk_B53C70 {
public:
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
};
}  // namespace gf

#endif
