#ifndef ML_DRIBLMAN_H
#define ML_DRIBLMAN_H

#include "mm/mtl/FixedList.h"

namespace ml {
class DrIBLObj;
class DrMan;

// one per view in DrMan (0x140); its update is in the DrEnvironmentAnim unit. The field names are not the
// original's.
class DrIBLMan {
public:
    DrIBLMan(DrMan* drMan, int view);
    ~DrIBLMan();
    void update();

    DrMan* m_drMan;  // 0x0: update hands it to DrIBLObj::initialize
    int m_view;  // 0x8
    // 0x10: the objects update tests the view against; the destructor deletes them
    mm::mtl::FixedList<DrIBLObj*, 32> m_objList;
    // 0x250: the objects stocked for the frame, by DrMan::s_nDblIdx (update moves them to m_objList)
    mm::mtl::FixedList<DrIBLObj*, 32> m_stockList[2];
    // 0x6D0: the objects update deletes
    mm::mtl::FixedList<DrIBLObj*, 32> m_releaseList;
    // 0x910: update's pick of m_objList, the one whose hit has the highest priority
    DrIBLObj* m_curObj;
};
}  // namespace ml

#endif
