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
};
}  // namespace gf

#endif
