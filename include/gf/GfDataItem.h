#ifndef GF_GFDATAITEM_H
#define GF_GFDATAITEM_H

namespace gf {
// the items' data, by their item id (functions, by its symbols)
class GfDataItem {
public:
    static const char* getName(unsigned int item);
    static int getRarity(unsigned int item);  // GfMenuItemAdapter::update_RareIcon's icon
    // the message table and row of the item's name
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int item);
};
}  // namespace gf

#endif
