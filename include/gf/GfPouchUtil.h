#ifndef GF_GFPOUCHUTIL_H
#define GF_GFPOUCHUTIL_H

namespace gf { struct SDataPouch; }

namespace gf {

// the pouches' helpers (functions, by 1.0.0's symbols)
class GfPouchUtil {
public:
    static SDataPouch& getPouch(unsigned int driver, unsigned int pouch);
    // whether the item box holds item 25305 (the item that opens a pouch slot)
    static bool isExistOpenItem();
    // how many of the driver's three pouch slots are open
    static unsigned int getOpenCount(unsigned int driver);
};

}  // namespace gf

#endif
