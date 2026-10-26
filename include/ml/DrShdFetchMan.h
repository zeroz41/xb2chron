#ifndef ML_DRSHDFETCHMAN_H
#define ML_DRSHDFETCHMAN_H

#include "ml/DrResFetch.h"

namespace ml {
class DrMan;
struct MdsMatVertexInfo;

// A model vertex fetch DrShdFetchMan shares between materials with the same attributes (1.0.0's
// DrShdFetchObj(unsigned int, unsigned int, unsigned int, int, MdsMatVertexInfo const*) and ~DrShdFetchObj; both
// inline in 3.0.1). The field names are not the original's.
class DrShdFetchObj {
public:
    ~DrShdFetchObj() { m_fetch.clearWork(); }

    DrShdFetchObj* m_pPrev;  // 0x0
    DrShdFetchObj* m_pNext;  // 0x8
    unsigned int m_attrBits[2];  // 0x10: a bit per attribute slot
    unsigned int m_strideSum;  // 0x18: the attributes' summed second halfword
    int m_refCount;  // 0x1C
    DrResFetch m_fetch;  // 0x20
};

// DrShdMan's list of model vertex fetches (0x20 bytes; constructor and destructor inline in 3.0.1, out of line in
// 1.0.0). The field names are not the original's.
class DrShdFetchMan {
public:
    DrShdFetchMan(DrMan* drMan) : m_pTop(nullptr), m_pEnd(nullptr), m_pDrMan(drMan), m_num(0) {}
    ~DrShdFetchMan() {
        DrShdFetchObj* obj = m_pTop;
        while (obj != nullptr) {
            DrShdFetchObj* next = obj->m_pNext;
            delete obj;
            obj = next;
        }
    }
    DrShdFetchObj* createFetchObj(int num, const MdsMatVertexInfo* info);

    DrShdFetchObj* m_pTop;  // 0x0
    DrShdFetchObj* m_pEnd;  // 0x8
    DrMan* m_pDrMan;  // 0x10
    int m_num;  // 0x18
};
}  // namespace ml

#endif
