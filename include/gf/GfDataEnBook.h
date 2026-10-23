#ifndef GF_GFDATAENBOOK_H
#define GF_GFDATAENBOOK_H

namespace gf {
// (functions, by their symbols)
class GfDataEnBook {
public:
    // SCOM_ENBOOK_IN_BATTLE / _DEFEAT_ENEMY / _DEAD_PLAYER pass their request's value
    static void setAttackFlag(unsigned int);
    static void incDefeatNum(unsigned int);
    static void incDeadNum(unsigned int);
    static unsigned int getEnBoolId(unsigned int arrange);
};
}  // namespace gf

#endif
