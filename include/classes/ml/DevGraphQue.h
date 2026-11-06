#ifndef CLASSES_ML_DEVGRAPHQUE_H
#define CLASSES_ML_DEVGRAPHQUE_H

#include "mm/Rect.h"
#include "classes/ml/GraphQue.h"
#include "classes/ml/reslist.h"
#include "ml/MlMem.h"
#include "mtl/MemManager.h"

namespace ml {
// ml::DevGraph's rectangle queue (DevGraph holds one at 0x330 and forwards pushRect/popRect to it)
class DevGraphQue {
public:
    DevGraphQue();
    // makes a queue of size bytes per half and keeps it (DevGraph::wkStandbyLogin)
    GraphQue* createQue(unsigned int size);
    void flushViewport();
    void pushRect(const mm::Rect<int>& a, const mm::Rect<int>& b, const mm::Rect<int>& c, bool flag);
    void popRect();
    // turns to the other half and empties every queue (DevGraph::wkTail inlines it; the name is not the original's)
    void flip() {
        m_side = (m_side == 0);
        for (reslist<GraphQue*>::iterator it = m_ques.begin(); it != m_ques.end(); ++it) {
            (*it)->reset();
        }
    }

    unsigned int m_side;          // 0x0 which half the queues fill (the name is not the original's)
    reslist<GraphQue*> m_ques;    // 0x8 the queues createQue makes (the name is not the original's)
    unsigned char pad_48[0x640];  // DevGraph::wkStandbyLogin allocates 0x688 bytes
};

inline GraphQue::GraphQue(DevGraphQue* owner, unsigned int size)
    : m_owner(owner), m_buf(), m_size(0), m_cur(nullptr), m_end(nullptr), pad_38(0), pad_40(0), pad_48(0) {
    m_buf[0] = static_cast<char*>(
        mtl::MemManager::allocate(MlMem::getProductMem(), size * 2, 0x20, false, "no name", 0));
    m_size = size;
    m_buf[1] = m_buf[0] + size;
    reset();
}

inline void GraphQue::reset() {
    char* buf = m_buf[m_owner->m_side];
    m_cur = buf;
    m_end = buf + m_size;
    pad_38 = 0;
    pad_40 = 0;
    pad_48 = 0;
}
}  // namespace ml

#endif
