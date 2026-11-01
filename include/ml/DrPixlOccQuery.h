#ifndef ML_DRPIXLOCCQUERY_H
#define ML_DRPIXLOCCQUERY_H

#include "ml/DrResQueryObj.h"

namespace ml {
class DrResQueryObj;
class DrShdDataList;
class DrShdDataObj;

class DrMan;
class DrPixlMan;

// DrPixlMan's pool of occlusion queries (DrPixlMan::m_occQuery): the constructor builds 0x800 DrResQueryObj in one
// allocation and links them into a free list; createObj moves the first free one to the used list and hands it out,
// or nullptr (DrResUseQueryObj::begin tests it). Field names are not the original's.
class DrPixlOccQuery {
public:
    DrPixlOccQuery(DrMan* drMan, DrPixlMan* pixlMan);
    DrResQueryObj* createObj();
    // moves obj from the used list to the end of the free list (1.0.0 has it out of line; 3.0.1 inlines it into
    // DrPixlMan::lastUpdate)
    void releaseObj(DrResQueryObj* obj) {
        DrResQueryObj* next = obj->m_next;
        DrResQueryObj* prev = obj->m_prev;
        if (next != nullptr) {
            if (prev != nullptr) {
                prev->m_next = next;
            }
            next->m_prev = prev;
        } else if (prev != nullptr) {
            prev->m_next = nullptr;
        }
        if (m_useTail == obj) {
            m_useTail = prev;
        }
        if (m_useHead == obj) {
            m_useHead = next;
            if (next != nullptr) {
                next->m_prev = nullptr;
            }
        }
        if (m_freeTail != nullptr) {
            m_freeTail->m_next = obj;
            obj->m_prev = m_freeTail;
            m_freeTail = obj;
        } else {
            m_freeHead = obj;
            m_freeTail = obj;
            obj->m_prev = nullptr;
        }
        obj->m_next = nullptr;
        m_freeCount++;
        m_useCount--;
    }

    DrMan* m_drMan;  // 0x0
    DrPixlMan* m_pixlMan;  // 0x8
    // the fields DrPixlMan::occRenderBegin sets up
    DrShdDataList* m_shdList;  // 0x10, occRenderBegin binds its box vertices
    DrShdDataObj* m_shader;  // 0x18, occRenderBegin sets it up (fetch 0)
    unsigned int m_occTypeOfs;  // 0x20: the shader's "OCC_TYPE" declaration offset
    int m_uniformOfs;  // 0x24, occRenderBegin: the shader's "U_POST" block offset
    int m_renderCount;  // 0x28, occRenderBegin clears it
    unsigned char pad_2C[0x14];
    DrResQueryObj* m_buffer;  // 0x40: the pool's allocation
    DrResQueryObj* m_freeHead;  // 0x48
    DrResQueryObj* m_freeTail;  // 0x50
    DrResQueryObj* m_useHead;  // 0x58
    DrResQueryObj* m_useTail;  // 0x60
    DrResQueryObj* m_objs;  // 0x68: the pool's elements (m_buffer)
    int m_useCount;  // 0x70
    int m_freeCount;  // 0x74
    int m_capacity;  // 0x78
};
}  // namespace ml

#endif
