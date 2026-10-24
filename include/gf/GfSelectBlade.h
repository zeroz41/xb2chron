#ifndef GF_GFSELECTBLADE_H
#define GF_GFSELECTBLADE_H

namespace gf {
// the blades chosen for the party's drivers (functions, by 1.0.0's symbols)
class GfSelectBlade {
public:
    // forgets the blade set a driver slot starts its battles with (GfGameScene::gevChangeParty resets slots 0-2)
    static void resetStartBattleSetId(unsigned int slot);
};
}  // namespace gf

#endif
