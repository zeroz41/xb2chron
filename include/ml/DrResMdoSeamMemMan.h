#ifndef ML_DRRESMDOSEAMMEMMAN_H
#define ML_DRRESMDOSEAMMEMMAN_H

#include "classes/ml/DrResMdoSeamMemObj.h"

namespace ml {
// A doubly linked list of T through T's m_prev/m_next (DrResMdoSeamMemMan keeps its memory blocks in two). The field
// names are not the original's.
template <class T>
class DrResChankList {
public:
    // the links a T can take from a base (DrCalcTexStmObj does: its constructor zeroes them before its table is
    // stored; the name is not the original's)
    struct Node {
        Node() : m_prev(), m_next() {}
        T* m_prev;
        T* m_next;
    };
    void changeList(T* obj, T* next);
    // unlinks obj (inline: the name is not the original's)
    void remove(T* obj) {
        T* prev = obj->m_prev;
        T* next = obj->m_next;
        if (prev == nullptr) {
            if (next == nullptr) {
                m_head = nullptr;
                m_tail = nullptr;
            } else {
                m_head = next;
                next->m_prev = nullptr;
            }
        } else if (next == nullptr) {
            m_tail = prev;
            prev->m_next = nullptr;
        } else {
            prev->m_next = next;
            obj->m_next->m_prev = obj->m_prev;
        }
        obj->m_prev = nullptr;
        obj->m_next = nullptr;
    }
    // links obj after pos (inline: the name is not the original's)
    void insertNext(T* pos, T* obj) {
        T* next = pos->m_next;
        pos->m_next = obj;
        obj->m_prev = pos;
        if (next == nullptr) {
            obj->m_next = nullptr;
            m_tail = obj;
        } else {
            obj->m_next = next;
            next->m_prev = obj;
        }
    }

    // links obj at the end (inline: the name is not the original's)
    void pushBack(T* obj) {
        if (m_tail == nullptr) {
            m_head = obj;
            m_tail = obj;
            obj->m_prev = nullptr;
        } else {
            m_tail->m_next = obj;
            obj->m_prev = m_tail;
            m_tail = obj;
        }
        obj->m_next = nullptr;
    }
    T* m_head;  // 0x0
    T* m_tail;  // 0x8
};
// The seam resource memory: m_objs (m_objNum blocks) linked into m_memList (the blocks covering the memory, in use or
// free) and m_spareList (unused block objects createFreeObj splits a free block with). The field names are not the
// original's.
class DrResMdoSeamMemMan {
public:
    DrResMdoSeamMemMan();
    ~DrResMdoSeamMemMan();
    // takes num block objects and the memory mem (size bytes): the first block covers it all, the rest are spares
    void setupMem(int num, unsigned char* mem, int size, unsigned int, unsigned int);
    void releaseMem();
    DrResMdoSeamMemObj* createFreeObj(unsigned int size);
    DrResMdoSeamMemObj* createBackFreeObj(unsigned int size);
    DrResMdoSeamMemObj* createParentFreeObj(DrResMdoSeamMemObj* parent, unsigned int size);
    void releaseFreeObj(DrResMdoSeamMemObj* obj);
    void clearMemObj(DrResMdoSeamMemObj* obj, DrResChankList<DrResMdoSeamMemObj>& list);

    DrResChankList<DrResMdoSeamMemObj> m_memList;    // 0x00
    DrResChankList<DrResMdoSeamMemObj> m_spareList;  // 0x10
    int m_memSize;                                   // 0x20: setupMem's size
    int pad_24;                                      // 0x24: zeroed by the constructor, setupMem's 4th argument
    int pad_28;                                      // 0x28: setupMem's 5th argument
    unsigned int m_flags;                            // 0x2C: 2 = releaseFreeObj clears the block from m_cache
    unsigned int m_objNum;                           // 0x30
    DrResMdoSeamMemObj* m_objs;                      // 0x38
    unsigned char pad_40[0x200];
    DrResMdoSeamMemObj* m_cache[0x40];               // 0x240: m_cacheNum entries
    unsigned char pad_440[0x4];
    int m_cacheNum;                                  // 0x444
};
}  // namespace ml

#endif
