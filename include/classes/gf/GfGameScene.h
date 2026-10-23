#ifndef CLASSES_GF_GFGAMESCENE_H
#define CLASSES_GF_GFGAMESCENE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameScene; }
namespace gf { enum GfPlayerDead : int; }

namespace gf {
// table 0x7100B55EF0
class GfGameScene : public ::mm::mtl::PtrSingleton< ::gf::GfGameScene> {
public:
    virtual ~GfGameScene();  // slot 0
    // GfPlayComSalvage's player pause: made when the command is, destroyed when it ends
    unsigned int createPlayerPause();
    void destroyPlayerPause(unsigned int pause);
    // how the player died (0 alive; GfPlayFactory::createGameOver sets 1 unless one is set)
    GfPlayerDead getDeadType();
    void setDeadType(GfPlayerDead type);
    bool isEnableFieldBladeChange() const;
    void requestFieldBladeChange();
    void setForceEventBgm(float time);
    // whether the party member with that id rides (GfGameRide asks it for the leader driver's setup's m_partyId)
    bool isRideParty(unsigned int id) const;
};
}  // namespace gf

#endif
