#ifndef GF_GFDATABLADEARTSN_H
#define GF_GFDATABLADEARTSN_H

namespace gf {
// a blade's arts buffs, read from GfBdatBtl's BTL_Buff table (functions, by its symbols)
class GfDataBladeArtsN {
public:
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int buff);
    static bool getCaption(unsigned char*& bdat, unsigned int& id, unsigned int buff);
};
}  // namespace gf

#endif
