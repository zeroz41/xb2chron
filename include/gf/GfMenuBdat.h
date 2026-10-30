#ifndef GF_GFMENUBDAT_H
#define GF_GFMENUBDAT_H

namespace gf {
struct MenuOffset;

// the menus' BDAT helpers (functions, by their symbols)
class GfMenuBdat {
public:
    // looks the menus' tables up: MNU_OffsetList, MNU_IconList, MNU_Layer, FLD_FieldSkillList, ITM_CollectionList,
    // itm_collection, BTL_Arts_Dr (GfMenuManager::initialize's)
    static void initialize();
    // the BDAT file holding an item's name text, by its type
    static unsigned char* getItemTextFP(unsigned char type, unsigned short id);
    // the column GfMenuItemList's name sorts order items by; null when there is none
    static const char* getSortKeyName();
    // the BDAT file holding an item's row, by its type and id (1.0.0's name: 3.0.1's symbols spell it
    // fn_710034FBA0; 1.0.0's GfMenuItemList::sortNameAscending calls it at the same site with the same arguments)
    static unsigned char* getItemDataFP(unsigned char type, unsigned short id);
    // the BDAT file holding a blade's row and the row's id in it (GfMenuBladeList's name sorts read the sort key
    // column from it; the file and id are null when there is none)
    static unsigned char* getBladeDataFP(unsigned int blade, unsigned int& id);
    static bool isValidBdatID(unsigned char* bdat, int id);
    static int getIconIDFromWeatherType(unsigned int type);  // GfFieldWeather::getCurrentWtrType's
    static int getIconImageIndex(int icon);
    static int getValueLevel(unsigned char* bdat, unsigned int value);  // the level a table gives that value
    // an art's icon (its UI column, 1 when none); int: its body keeps the zero-extended column (callers narrow it)
    static int getIconIDFromArtsID(unsigned short arts);
    static void getMenuOffset(int id, MenuOffset& offset);  // the menu offset of that id (GfGameUtil::getUiOffsetId's)

    // the tables initialize looked up, in its order
    static unsigned char* s_BdatArray[7];
};

}  // namespace gf

#endif
