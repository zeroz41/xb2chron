#ifndef GF_GFDATABATTLE_H
#define GF_GFDATABATTLE_H

namespace gf {
// the battle data (functions, by their symbols; the code lives in the GfDataBlade unit)
class GfDataBattle {
public:
    // a class's name message (GfBdatBtl::getBTL_ClassName) and the message table (GfBdatMsg::getFpBtlClass); false
    // for class 0 or no name
    static bool getClassName(unsigned char*& fp, unsigned int& id, unsigned int cls);
};
}  // namespace gf

#endif
