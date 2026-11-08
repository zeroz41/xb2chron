#ifndef GF_GFDATASHOP_H
#define GF_GFDATASHOP_H

namespace gf {
// the shops' game data (functions, by 1.0.0's symbols)
class GfDataShop {
public:
    // the privilege item a shop grants, 0 for none (GfGameScene::gevExecBuy asks shop 39)
    static unsigned int getItemBit(unsigned int shop);
    static unsigned int getPrivilegeItem(unsigned int shop);
    // symbol 0x7100252AC8; GfShopUtil::execBuy passes the shop and the item bought
    static void setBuyItem(unsigned int shop, unsigned int item);
};
}  // namespace gf

#endif
