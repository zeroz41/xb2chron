#ifndef GF_GFGAMEUTILNANAKOORI_H
#define GF_GFGAMEUTILNANAKOORI_H

namespace gf {
// game helpers for Poppi's mercenary missions and Tora's workshop (functions, by 1.0.0's symbols)
class GfGameUtilNanakoori {
public:
    // whether the mission flag change completes a mission (GfGameScene::gevMercenariesMissionFlag passes its first
    // two arguments)
    static bool checkCompleteMission(unsigned int mission, unsigned int flag);
};
}  // namespace gf

#endif
