#ifndef ML_DRRESOCCUNIFORMOBJ_H
#define ML_DRRESOCCUNIFORMOBJ_H

#include "mm/Mat44.h"

namespace ml {
class DrMan;

// A per-frame pool of m_max matrices for occlusion draws, allocated from DrMan::m_allocHandle; begin() resets the
// count and getMatTbl() hands out the next one (nullptr once full). Field names are not the original's.
class DrResOccUniformObj {
public:
    DrResOccUniformObj(DrMan* man, int max);
    ~DrResOccUniformObj();
    void begin();
    void end();
    mm::Mat44* getMatTbl();
    mm::Mat44* getMatTbl(int idx);

    int m_max;             // 0x00
    int m_cnt;             // 0x04
    void* m_buf;           // 0x08: the allocation (freed by the destructor)
    mm::Mat44* m_matTbl;   // 0x10
};
}  // namespace ml

#endif
