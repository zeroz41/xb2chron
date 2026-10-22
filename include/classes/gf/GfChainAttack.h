#ifndef CLASSES_GF_GFCHAINATTACK_H
#define CLASSES_GF_GFCHAINATTACK_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfChainAttack; }
namespace gf { class GfWeapon; }

namespace gf {
// table 0x7100B54718; the chain attack's driver models: one per party member, made while the battle model view
// opens
class GfChainAttack : public ::mm::mtl::PtrSingleton< ::gf::GfChainAttack> {
public:
    // inline: create makes it (the symbols name no constructor)
    // (create's code stores the handles last to first)
    GfChainAttack() : m_state(0) {
        for (int i = 2; i >= 0; i--) {
            m_drivers[i] = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        }
    }
    virtual ~GfChainAttack();  // slot 0

    // a driver model for each of the party's first three drivers
    void createPartyDriver();
    void startSetup();
    void updateForSetup(const fw::UpdateInfo& info);
    void updateForPlay(const fw::UpdateInfo& info);
    void update(const fw::UpdateInfo& info);
    static GfChainAttack* create();
    static void destroy();
    int getState() const;
    gf::GF_OBJ_HANDLE* getDriverByPartyId(unsigned int id) const;
    gf::GfWeapon* getWeaponByPartyId(unsigned int id) const;

    // (the field names are not the original's)
    int m_state;  // 0 idle, 1 setting up (startSetup), 2 playing (once the models have loaded)
    mm::mtl::Delegate<void(const fw::UpdateInfo&)> m_update;  // update calls it: the state's update function
    gf::GF_OBJ_HANDLE* m_drivers[3];  // createPartyDriver's, by party index; -1 for none
};
}  // namespace gf

#endif
