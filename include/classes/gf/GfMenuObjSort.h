#ifndef CLASSES_GF_GFMENUOBJSORT_H
#define CLASSES_GF_GFMENUOBJSORT_H

namespace gf {
// a class with no table: what is declared inside it
class GfMenuObjSort {
public:
    class MainListener;
    // 1.0.0 symbols (the parameter names are not the original's): GfMenuObjPouch2 sorts its stock list (menu 0x10)
    // by the sort id of its sort index, and opens the sort menu with that index
    static unsigned short getSortID(unsigned short menu, unsigned short index);
    static void open(unsigned int handle, unsigned int caller, unsigned short menu, unsigned short index);
    // sets the object of that handle's text to the sort id's label (ids below 100: BDAT 0x14E's message, else a
    // field skill's name; the parameter names are not the original's)
    static void setSortLabelText(unsigned short sortId, unsigned int handle);
};
}  // namespace gf

#endif
