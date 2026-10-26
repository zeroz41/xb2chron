#ifndef CLASSES_GF_GFMENUMAPINFO_H
#define CLASSES_GF_GFMENUMAPINFO_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Pnt.h"
#include "mm/mtl/FixStr.h"

namespace gf { class GfMenuMapInfo; }

namespace gf {
// table 0x7100B5EDC0
class GfMenuMapInfo : public ::mm::mtl::PtrSingleton< ::gf::GfMenuMapInfo> {
public:
    virtual ~GfMenuMapInfo();  // slot 0
    // the current map's segment image offset (GfMenuObjMinimap2::refreshMapPosition centers its map image by it);
    // false when there is none
    static bool getMapSegImageOffs(mm::Pnt<short>& offs);
    // the file name of the current map's segment image at that column and row (GfMenuObjMinimap2's map listener
    // streams the 3x3 segments by it); false when there is none
    static bool getMapSegImageName(unsigned int column, unsigned int row, mm::mtl::FixStr<64>& name);
};
}  // namespace gf

#endif
