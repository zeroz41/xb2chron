#ifndef GF_GFGAMEUTILSKIPTRAVEL_H
#define GF_GFGAMEUTILSKIPTRAVEL_H

namespace gf {
// class name from the symbols (gf::GfGameUtilSkipTravel); only static helpers
class GfGameUtilSkipTravel {
public:
    // named by the symbols: whether the map jump may be skip-travelled to: its row in the map's
    // <map>_FLD_LandmarkPop table (column MAPJUMPID) has no stoff_cndID condition or one that does not hold
    static bool isEnableSkipTravel(unsigned int mapJump);
};
}  // namespace gf

#endif
