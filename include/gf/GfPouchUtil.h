#ifndef GF_GFPOUCHUTIL_H
#define GF_GFPOUCHUTIL_H

namespace gf { struct SDataPouch; }
namespace fw { class UpdateInfo; }

namespace gf {

// the pouches' helpers (functions, by 1.0.0's symbols)
class GfPouchUtil {
public:
    static SDataPouch& getPouch(unsigned int driver, unsigned int pouch);
    static void updatePouch(unsigned int driver, unsigned int pouch, const SDataPouch& data, const ::fw::UpdateInfo& info);
    // unnamed (no symbol names it); updatePouch and setPouch call it. Takes one of the pouch's item from the box,
    // restarts its time, adds the item's favorite trust to the driver's blades and stores the pouch; with no item
    // left it empties the pouch and returns false
    static bool fn_71002FDB88(unsigned int driver, unsigned int pouch, SDataPouch& data);
    static void setPouch(unsigned int driver, unsigned int pouch, const SDataPouch& data);
    // whether the driver's pouch is open and no other pouch holds the item
    static bool isEnableSetItem(unsigned int driver, unsigned int pouch, unsigned int item);
    // opens the driver's first closed pouch with one open item (25305)
    static void execOpen(unsigned int driver);
    // whether the item box holds item 25305 (the item that opens a pouch slot)
    static bool isExistOpenItem();
    // how many of the driver's three pouch slots are open
    static unsigned int getOpenCount(unsigned int driver);
};

}  // namespace gf

#endif
