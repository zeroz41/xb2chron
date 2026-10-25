#ifndef GF_PARAMRETURNTITLE_H
#define GF_PARAMRETURNTITLE_H

namespace gf {
// what a return to the title is made with (2 bytes: GfPlayComReturnTitle::create copies it as a halfword,
// GfPlayComReturnTitle::update reads each byte); the field names are not the original's
class ParamReturnTitle {
public:
    // update first waits until no enemy or party member voice plays (GfPlayFactory::createGameOver sets it)
    bool m_waitVoice;
    // update counts a game clear (GfGameUtil::incGameClearCount) first (the sys plugin's returnTitle sets it)
    bool m_gameClear;
};
}  // namespace gf

#endif
