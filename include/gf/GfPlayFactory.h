#ifndef GF_GFPLAYFACTORY_H
#define GF_GFPLAYFACTORY_H

namespace gf {
// the sequential play's factory (functions, by its symbols)
class GfPlayFactory {
public:
    // queues the chain attack's play; false while the game is left for debugging or the control is not free
    static bool createChainAttack();
};
}  // namespace gf

#endif
