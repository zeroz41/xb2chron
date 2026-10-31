#ifndef GRLIB_CGLIBBUFFSAMPLERTBL_H
#define GRLIB_CGLIBBUFFSAMPLERTBL_H

#include "grlib/GrlTypes.h"
#include "mm/Col4.h"
#include "grlib/CGLibSamplerDescriptor.h"

namespace grlib {

// a sampler's state (0x18 bytes), what CGLibBuffSamplerTbl::allocSampler shares a sampler object by. The bit
// positions are CGLibSampler's setters'; the field names are not the original's.
struct CGLibWkrSamplerParams {
    CGLibWkrSamplerParams() : m_clampS(0), m_clampT(0), m_clampR(0), m_compare(0), m_magFilter(0), m_minFilter(0),
        m_aniso(0), m_border(0), m_pad(0), m_borderColor(1.0f, 1.0f, 1.0f, 1.0f), m_lod(0.0f) {}

    unsigned int m_clampS : 4;     // bits 0..3
    unsigned int m_clampT : 4;     // bits 4..7
    unsigned int m_clampR : 4;     // bits 8..11
    unsigned int m_compare : 4;    // bits 12..15: setDepthCompare
    unsigned int m_magFilter : 1;  // bit 16
    unsigned int m_minFilter : 5;  // bits 17..21
    unsigned int m_aniso : 4;      // bits 22..25
    unsigned int m_border : 1;     // bit 26: a clamp mode above 5 (the border modes) is in use
    unsigned int m_pad : 5;        // bits 27..31: unused
    mm::Col4 m_borderColor;        // 0x04
    float m_lod;                   // 0x14: setLOD
};

// a sampler the table hands out, shared by every user of the same state (0x98 bytes; the field names are not the
// original's)
class CGLibBuffResSamObj {
public:
    CGLibBuffResSamObj() : m_pPrev(nullptr), m_pNext(nullptr), m_refCount(0), m_hash(0) {}

    CGLibBuffResSamObj* m_pPrev;     // 0x00: in the list the object is in
    CGLibBuffResSamObj* m_pNext;     // 0x08
    CGLibWkrSamplerParams m_params;  // 0x10: the state it was made for
    CGLibSamplerParam m_param;       // 0x28
    short m_refCount;                // 0x90: its users (allocSampler adds one, freeSampler drops one)
    short m_hash;                    // 0x92: its bucket in CGLibBuffSamplerTbl::m_hashList
};

// the shared sampler objects (CGLibSystemContext holds one at 0x608)
class CGLibBuffSamplerTbl {
public:
    // a null-ended list of objects, linked through their m_pPrev/m_pNext (the name is not the original's)
    struct ObjList {
        ObjList() : m_pHead(nullptr), m_pTail(nullptr) {}
        void clear() {
            m_pHead = nullptr;
            m_pTail = nullptr;
        }
        void push_back(CGLibBuffResSamObj* obj) {
            if (m_pTail == nullptr) {
                m_pHead = obj;
                m_pTail = obj;
                obj->m_pPrev = nullptr;
            } else {
                m_pTail->m_pNext = obj;
                obj->m_pPrev = m_pTail;
                m_pTail = obj;
            }
            obj->m_pNext = nullptr;
        }
        void remove(CGLibBuffResSamObj* obj) {
            CGLibBuffResSamObj* prev = obj->m_pPrev;
            CGLibBuffResSamObj* next = obj->m_pNext;
            if (prev == nullptr) {
                if (next == nullptr) {
                    m_pHead = nullptr;
                    m_pTail = nullptr;
                } else {
                    m_pHead = next;
                    next->m_pPrev = nullptr;
                }
            } else if (next == nullptr) {
                m_pTail = prev;
                prev->m_pNext = nullptr;
            } else {
                prev->m_pNext = next;
                obj->m_pNext->m_pPrev = obj->m_pPrev;
            }
            obj->m_pPrev = nullptr;
            obj->m_pNext = nullptr;
        }

        CGLibBuffResSamObj* m_pHead;
        CGLibBuffResSamObj* m_pTail;
    };

    CGLibBuffSamplerTbl();
    ~CGLibBuffSamplerTbl();
    // releases every object and frees the buffer
    void release();
    // makes num objects (in the free list) in a buffer from handle; the bytes taken
    unsigned int setup(mtl::ALLOC_HANDLE handle, unsigned int num);
    CGLibBuffResSamObj* allocSampler(const CGLibWkrSamplerParams& params);
    // drops a reference to the object (and clears the pointer)
    void freeSampler(CGLibBuffResSamObj*& pObj);

    CGLibBuffResSamObj* m_pBuff;  // 0x000: the objects
    int m_useNum;                 // 0x008: the objects in use
    unsigned int m_num;           // 0x00C
    ObjList m_hashList[128];      // 0x010: the objects in use, by a hash of their state
    ObjList m_freeList;           // 0x810: the unused objects (allocSampler takes the first)
    ObjList m_releaseList;        // 0x820: the objects freeSampler hands back, until their delayed release
};

}  // namespace grlib

#endif
