#ifndef GF_GFMENUBDAT_H
#define GF_GFMENUBDAT_H

namespace gf {
struct MenuOffset;

// the menus' BDAT helpers (functions, by their symbols)
class GfMenuBdat {
public:
    // the column GfMenuItemList's name sorts order items by; null when there is none
    static const char* getSortKeyName();
    // the BDAT file holding an item's row, by its type and id (1.0.0's name: 3.0.1's symbols spell it
    // fn_710034FBA0; 1.0.0's GfMenuItemList::sortNameAscending calls it at the same site with the same arguments)
    static unsigned char* getItemDataFP(unsigned char type, unsigned short id);
    static bool isValidBdatID(unsigned char* bdat, int id);
    static int getIconIDFromWeatherType(unsigned int type);  // GfFieldWeather::getCurrentWtrType's
    static int getIconImageIndex(int icon);
    static unsigned short getIconIDFromArtsID(unsigned short arts);
    static void getMenuOffset(int id, MenuOffset& offset);  // the menu offset of that id (GfGameUtil::getUiOffsetId's)
};

}  // namespace gf

#endif
