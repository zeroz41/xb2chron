#ifndef GRLIB_CGLIBBUFFFIXALLOC_H
#define GRLIB_CGLIBBUFFFIXALLOC_H

#include "mtl/AllocHandle.h"
#include "grlib/CGLibMemPool.h"

namespace grlib {

// fixed-size slots handed out by id: a bit per slot says it is in use (1.0.0's symbols name the functions; the
// field names are not the original's)
class CGLibBuffFixAlloc {
public:
    CGLibBuffFixAlloc();
    ~CGLibBuffFixAlloc();
    // frees the slots and the bits
    void releaseTbl();
    // the bits for num slots of size bytes (from hTbl), and the slots themselves (from hBuff, at the alignment)
    void setupTbl(mtl::ALLOC_HANDLE hTbl, mtl::ALLOC_HANDLE hBuff, unsigned int num, unsigned int size,
                  unsigned int alignment);
    void setupTbl(mtl::ALLOC_HANDLE hTbl, unsigned int num, unsigned int size);
    // as setupTbl, the slots' memory being buffSize bytes
    void setupFixTbl(mtl::ALLOC_HANDLE hTbl, mtl::ALLOC_HANDLE hBuff, unsigned int num, unsigned int size,
                     unsigned int buffSize, unsigned int alignment);
    unsigned int allocID();
    // takes the next id (marks it used, moves on to the following one) and returns it
    int createBuff();
    int allocSub();
    void freeID(unsigned int id);
    // frees the slot p points to
    void freeBuffer(void* p);
    // a slot's memory (the name is not the original's)
    unsigned char* getBuffer(unsigned int id) const { return m_pBuff + id * m_elemSize; }
    unsigned char* m_pBuff;       // 0x00: the slots
    unsigned long* m_pBits;       // 0x08: a bit per slot, set while it is used
    unsigned int m_elemSize;      // 0x10: the bytes of one slot
    int m_useNum;                 // 0x14: the slots in use
    int m_nextID;                 // 0x18: where the next allocID looks first
    int m_num;                    // 0x1C: the slots
    unsigned int m_bitsNum;       // 0x20: the words of m_pBits
    unsigned int m_bitsIdx;       // 0x24: the word allocID searches from
};
// the occlusion report slots (CGLibSystemContext::m_occlusion; 1.0.0's CGLibBuffOcclusion_plf functions are its
// platform part's, an empty base: getBufferSize is the slot size)
class CGLibBuffOcclusion_plf {
public:
    unsigned int getBufferSize();
    void createPlf(unsigned int num, unsigned char* pBuff) {}
    void releasePlf() {}
};
class CGLibBuffOcclusion : public CGLibBuffFixAlloc, public CGLibBuffOcclusion_plf {
public:
    CGLibBuffOcclusion();
    ~CGLibBuffOcclusion();
    void release();
    void createOcclusion(unsigned int num);
};
// the texture slots (0xC0 bytes each); the platform part keeps the slots' top (1.0.0: createPlf stores it, at 0)
class CGLibBuffTexture_plf {
public:
    CGLibBuffTexture_plf() : m_pTop(nullptr) {}
    void createPlf(unsigned int num, unsigned char* pBuff) { m_pTop = pBuff; }
    void releasePlf() { m_pTop = nullptr; }
    unsigned char* m_pTop;  // 0x0
};
class CGLibBuffTexture : public CGLibBuffFixAlloc, public CGLibBuffTexture_plf {
public:
    CGLibBuffTexture();
    ~CGLibBuffTexture();
    void release();
    void createTexture(unsigned int num);
};
// the NVNmemoryPool slots CGLibMemPool takes its pool object from (0x100 bytes each)
class CGLibBuffMemPoolTbl : public CGLibBuffFixAlloc {
public:
    CGLibBuffMemPoolTbl();
    ~CGLibBuffMemPoolTbl();
    void release();
    void createMemPoolTbl(unsigned int num);
};
// fixed-size uniform slots in one GPU memory pool
class CGLibBuffMinUniform : public CGLibBuffFixAlloc {
public:
    CGLibBuffMinUniform();
    ~CGLibBuffMinUniform();
    void release();
    void createUniform(unsigned int size, unsigned int elemSize);
    CGLibMemPool m_pool;  // 0x28: holds m_pBuff (the name is not the original's)
};

}  // namespace grlib

#endif
