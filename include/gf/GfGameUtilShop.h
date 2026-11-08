#ifndef GF_GFGAMEUTILSHOP_H
#define GF_GFGAMEUTILSHOP_H

namespace gf {
// the shops' helpers (functions, by its symbols)
class GfGameUtilShop {
public:
    // whether the item box holds every item (at least 1 each) the exchange task's five slots ask for (GfBdatShop's
    // getShopChangeTaskSetItem/Number; the parameter name is not the original's)
    static bool hasChangeItem(unsigned int task);
    // pays an inn's price and adds development points for the zone (the parameter names are not the original's)
    static void execPayInn(unsigned int shop, unsigned int money, bool twice);
    // exchanges the task (BDAT 0xF2 row) at the shop's exchange (symbol _ZN2gf14GfGameUtilShop14execChangeItemEjj;
    // the parameter names are not the original's)
    static void execChangeItem(unsigned int task, unsigned int param);
    // an inn's price after the zone's development discount, at least 1; 0 when the shop is no inn
    static unsigned int getNeedMoneyForInn(unsigned int shop);
};
}  // namespace gf

#endif
