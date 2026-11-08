#ifndef GF_GFSHOPUTIL_H
#define GF_GFSHOPUTIL_H

namespace gf { struct GfItemHandle; }

namespace gf {

// the shops' buy and sell helpers (functions, by their symbols)
class GfShopUtil {
public:
    // buys num of the item at the shop's price: 0 done, 1 the box cannot take them, 3 not enough money (the
    // result's type is not known)
    static int execBuy(unsigned int item, unsigned int num, unsigned int shop);
    // sells num of the item (one by its handle when the handle is set): 0 done, 4 the item cannot be sold, 2 the box
    // holds fewer (the result's type is not known)
    static int execSell(unsigned int item, unsigned int num, unsigned int shop, GfItemHandle handle);
};

}  // namespace gf

#endif
