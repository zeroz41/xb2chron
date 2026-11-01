#ifndef ML_DRRESQUERYOBJ_H
#define ML_DRRESQUERYOBJ_H

#include "classes/ml/DrMan.h"
#include "grlib/CGLibOcclusionQuery.h"

namespace ml {
class DrPixlOccQuery;
class DrResUseQueryObj;

// One occlusion query of DrPixlOccQuery's pool. A DrResUseQueryObj owns it while m_user is set; bit 0 of m_flags
// marks a query begun this frame, bit 1 a query left unused for a frame (update frees it then), and bit
// (2 + DrMan::s_nDblNowIdx) a buffer slot that holds a result.
// Field names are not the original's.
class DrResQueryObj {
public:
    DrResQueryObj();
    ~DrResQueryObj();
    int getOccZPassCount();
    bool update();
    void begin();
    void end();

    // 0x00: links in DrPixlOccQuery's free or used list (null at either end)
    DrResQueryObj* m_next;              // 0x00
    DrResQueryObj* m_prev;              // 0x08
    grlib::CGLibOcclusionQuery m_query; // 0x10
    DrResUseQueryObj* m_user;           // 0x28
    void* m_userWork;                   // 0x30: cleared with m_user
    unsigned int m_flags;               // 0x38
};

// Takes a query from DrPixlOccQuery for one frame and reads its pixel count back (field names are not the
// original's).
class DrResUseQueryObj {
public:
    DrResUseQueryObj();
    ~DrResUseQueryObj();
    void update();
    void begin(DrPixlOccQuery* occ);
    void end();

    DrResQueryObj* m_query;  // 0x00
    int m_pixel;             // 0x08: the last getOccZPassCount
};

// A holder of one DrResQueryObj (the field name is not the original's).
class DrResQueryAcc {
public:
    DrResQueryAcc();
    void releaseQuery();

    DrResQueryObj* m_query;  // 0x00
};
}  // namespace ml

#endif
