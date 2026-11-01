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
    // whether the item box holds item 25305 (the item that opens a pouch slot)
    static bool isExistOpenItem();
    // how many of the driver's three pouch slots are open
    static unsigned int getOpenCount(unsigned int driver);
};

}  // namespace gf

#endif
