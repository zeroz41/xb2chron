#ifndef GF_GFDATASHOP_H
#define GF_GFDATASHOP_H

namespace gf {
// the shops' game data (functions, by 1.0.0's symbols)
class GfDataShop {
public:
    // the privilege item a shop grants, 0 for none (GfGameScene::gevExecBuy asks shop 39)
    static unsigned int getItemBit(unsigned int shop);
    static unsigned int getPrivilegeItem(unsigned int shop);
};
}  // namespace gf

#endif
