#ifndef GF_GFMENUBDAT_H
#define GF_GFMENUBDAT_H

namespace gf {
struct MenuOffset;

// the menus' BDAT helpers (functions, by their symbols)
class GfMenuBdat {
public:
    static bool isValidBdatID(unsigned char* bdat, int id);
    static int getIconIDFromWeatherType(unsigned int type);  // GfFieldWeather::getCurrentWtrType's
    static int getIconImageIndex(int icon);
    static unsigned short getIconIDFromArtsID(unsigned short arts);
    static void getMenuOffset(int id, MenuOffset& offset);  // the menu offset of that id (GfGameUtil::getUiOffsetId's)
};

}  // namespace gf

#endif
