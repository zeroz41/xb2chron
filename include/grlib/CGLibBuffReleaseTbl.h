#ifndef GRLIB_CGLIBBUFFRELEASETBL_H
#define GRLIB_CGLIBBUFFRELEASETBL_H

#include "grlib/CGLibMemHandle.h"

namespace grlib {

// GPU objects whose release waits until the GPU is done with them (CGLibBuffReleaseTbl). The field names are not
// the original's.
class CGLibReleaseObj_plf {
public:
    struct wrkRelease {
        union Res {
            Res() : m_obj() {}
            struct Obj {
                void* m_pObj;   // 0x00: the NVN object (pool, texture) or the sampler's CGLibBuffResSamObj
                void* m_pBuff;  // 0x08: memory freed with it
            } m_obj;
            CGLibMemType m_mem;  // release_vertex: the CGLibMemHandle block it frees
        } m_res;                     // 0x00
        int m_textureID;            // 0x10: the texture descriptor id, -1 for none
        int m_samplerID;            // 0x14: the sampler descriptor id, -1 for none
        unsigned int m_use : 1;     // 0x18 bit 0: the entry holds an object
        unsigned int m_mempool : 1; // bit 1: m_pObj is a pool of the context's m_memPoolTbl to finalize
        unsigned int m_texture : 1; // bit 2: m_pObj is a texture to finalize
        unsigned int m_pad : 13;
        unsigned int m_type : 16;   // bits 16..31: the s_callRelease index
        unsigned int pad_1C;
    };
    static void release_mempool(wrkRelease& work);
    static void release_textrue(wrkRelease& work);
    static void release_sampler(wrkRelease& work);
    static void release_vertex(wrkRelease& work);
    static void (*s_callRelease[4])(wrkRelease& work);
};

class CGLibReleaseObj : public CGLibReleaseObj_plf {
public:
    CGLibReleaseObj();
    ~CGLibReleaseObj();
    void release();
    wrkRelease m_work;          // 0x00
    CGLibReleaseObj* m_pNext;   // 0x20
};

class CGLibBuffReleaseTbl {
public:
    // a singly linked list of entries (the name is not the original's)
    struct List {
        void push(CGLibReleaseObj* pObj) {
            if (m_pTail == nullptr) {
                m_pHead = pObj;
            } else {
                m_pTail->m_pNext = pObj;
            }
            m_pTail = pObj;
            pObj->m_pNext = nullptr;
        }
        CGLibReleaseObj* pop() {
            CGLibReleaseObj* pObj = m_pHead;
            if (pObj != nullptr) {
                m_pHead = pObj->m_pNext;
                if (m_pHead == nullptr) {
                    m_pTail = nullptr;
                }
                pObj->m_pNext = nullptr;
            }
            return pObj;
        }
        CGLibReleaseObj* m_pHead;  // 0x0
        CGLibReleaseObj* m_pTail;  // 0x8
    };
    CGLibBuffReleaseTbl();
    ~CGLibBuffReleaseTbl();
    void release();
    int setup(unsigned int num);
    CGLibReleaseObj* createObj();
    void update();
    int m_num;                 // 0x00
    CGLibReleaseObj* m_pTbl;   // 0x08
    List m_free;               // 0x10
    List m_stock[2];           // 0x20: per CGLibManager stack index, released by update two frames on
};

}  // namespace grlib

#endif
