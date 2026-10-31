#ifndef GF_GFDATAENBOOK_H
#define GF_GFDATAENBOOK_H

namespace gf { class SDataGame; }

namespace gf {
// (functions, by their symbols)
class GfDataEnBook {
public:
    // SCOM_ENBOOK_IN_BATTLE / _DEFEAT_ENEMY / _DEAD_PLAYER pass their request's value
    static void setAttackFlag(unsigned int);
    static void incDefeatNum(unsigned int);
    static void incDeadNum(unsigned int);
    static unsigned int getEnBoolId(unsigned int arrange);
    static unsigned int getDefeatNum(unsigned int arrange);  // local flag 0x20, the book row + 0x142
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit between GfDataEnBook::getDefeatNum and incDefeatNum. What it does: getDefeatNum on the given game data
    // (its local flags at +0xFBBC4): 0 for arrangement 0 or no book row. Caller: fn_71002E2F4C.
    static unsigned int fn_7100253EB4(const SDataGame& game, unsigned int arrange);
    // local flag (1, book + 48590) of the arrangement's enemy book row; false for none
    static bool isAttackFlag(unsigned int arrange);
};
}  // namespace gf

#endif
