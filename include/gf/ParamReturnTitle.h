#ifndef GF_PARAMRETURNTITLE_H
#define GF_PARAMRETURNTITLE_H

namespace gf {
// what a return to the title is made with (2 bytes: GfPlayComReturnTitle::create copies it as a halfword)
class ParamReturnTitle {
public:
    // why the game returns to the title (GfPlayFactory::createGameOver passes 1); the name is not the original's
    unsigned short m_reason;
};
}  // namespace gf

#endif
