#ifndef CLASSES_GF_GFMENUOBJDROPITEM_H
#define CLASSES_GF_GFMENUOBJDROPITEM_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61890
class GfMenuObjDropItem : public ::gf::GfMenuObject {
public:
    class DropItemInfo;
    class ListListener;
    GfMenuObjDropItem(unsigned int handle);
    virtual ~GfMenuObjDropItem();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // shows the screen of that type on a LAY_item_root copy (0 gold, 1 heal, 2 an item got, 3 an item sold, 4 ether),
    // with its value and item (the parameter names are not the original's)
    static void setupScreen(unsigned int handle, int type, int value, int item);
    // fits the type's background over its text (types 0-3)
    static void setupPlugin(unsigned int handle, unsigned int type);
    static void close(unsigned int handle);  // fades that copy out (event 0x22)
    static void closeAll();
};
}  // namespace gf

#endif
