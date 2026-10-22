#ifndef GF_GFMENUBDAT_H
#define GF_GFMENUBDAT_H

namespace gf {

// the menus' BDAT helpers (functions, by their symbols)
class GfMenuBdat {
public:
    static bool isValidBdatID(unsigned char* bdat, int id);
};

}  // namespace gf

#endif
