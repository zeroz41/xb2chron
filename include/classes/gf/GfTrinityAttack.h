#ifndef CLASSES_GF_GFTRINITYATTACK_H
#define CLASSES_GF_GFTRINITYATTACK_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfTrinityAttack; }
namespace gf { class GfWeapon; }

namespace gf {
// table 0x7100B56AB0; the trinity attack: a blade made for the party leader's attack, whose weapon the leader
// takes while it lasts
class GfTrinityAttack : public ::mm::mtl::PtrSingleton< ::gf::GfTrinityAttack> {
public:
    // inline: create makes it (the symbols name no constructor)
    GfTrinityAttack() : m_state(0), m_blade(reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {}
    virtual ~GfTrinityAttack();  // slot 0

    // the blade the attack makes: 1011 when the leader (driver 1) has blade 1001 engaged and 1011 set, 1001 the
    // other way round, 0 otherwise
    unsigned int getBladeId() const;
    // whether the blade or its weapon's objects are still loading
    bool isLoading() const;
    void startAttack();
    void updateForSetup(const fw::UpdateInfo& info);
    void endAttack();
    void updateForPlay(const fw::UpdateInfo& info);
    void update(const fw::UpdateInfo& info);
    static GfTrinityAttack* create();
    static void destroy();
    int getState() const;
    gf::GF_OBJ_HANDLE* getBlade() const;
    gf::GfWeapon* getWeapon() const;

    // (the field names are not the original's)
    int m_state;  // 0 idle, 1 setting up (startAttack), 2 playing (once the blade has loaded)
    mm::mtl::Delegate<void(const fw::UpdateInfo&)> m_update;  // update calls it: the state's update function
    gf::GF_OBJ_HANDLE* m_blade;  // startAttack's blade, -1 for none
};
}  // namespace gf

#endif
