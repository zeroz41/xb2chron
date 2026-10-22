#ifndef GF_GFDATABLADE_H
#define GF_GFDATABLADE_H

namespace gf {
// the blades' game data (functions, by its symbols)
class GfDataBlade {
public:
    static bool isRareBlade(unsigned int blade);
    // a game flag: Pyra's name shown as Mythra's (GfMenuObjNameSelect sets it from the name picked)
    static void setHomuriNameHikari(bool hikari);
};
}  // namespace gf

#endif
