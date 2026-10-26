#ifndef CLASSES_GRLIB_CGLIBSHDLISTBASE_H
#define CLASSES_GRLIB_CGLIBSHDLISTBASE_H

#include "grlib/CGLibVtlMemPool.h"
#include "grlib/CGLibMemHandle.h"
#include "mtl/MemManager.h"
#include <new>

namespace grlib {
// the head of a shader package createPacShader reads (the names are not the original's)
struct CGLibShdPacHeader {
    unsigned char pad_0[0x8];
    unsigned int m_entryOfs;  // 0x8: CGLibShdPacEntry[m_num]
    int m_num;                // 0xC
    unsigned int m_extOfs;    // 0x10: CGLibShdPacExt[m_extNum]
    int m_extNum;             // 0x14
    unsigned int m_shdOfs;    // 0x18: the entries' shader data are relative to it
    unsigned char pad_1C[0x4];
    unsigned int m_bufOfs;    // 0x20: the GPU code the pool holds
    unsigned int m_bufSize;   // 0x24
    unsigned int m_progOfs;   // 0x28
    unsigned char pad_2C[0x8];
    unsigned int m_version;   // 0x34
};
// an extension entry of a package: DrShdLgtMan::reloadShader takes the list entry of m_idx for each (the names
// are not the original's)
struct CGLibShdPacExt {
    unsigned char pad_0[0x4];
    unsigned int m_idx;  // 0x4
    unsigned char pad_8[0x4];
};
// one shader of a package (the names are not the original's)
struct CGLibShdPacEntry {
    unsigned int m_ofs;  // from CGLibShdPacHeader::m_shdOfs
    unsigned char pad_4[0x4];
};

// a template: 4 instances in the module
template <typename T0>
class CGLibShdListBase {
public:
    CGLibShdListBase() : m_pList(nullptr), m_pMem(nullptr), m_num(0) {}
    virtual ~CGLibShdListBase() { release(); }  // slot 0

    // releases the pool, destroys m_num entries of m_pList and frees m_pMem
    void release() {
        m_memPool.release();
        if (m_pMem != nullptr) {
            for (int i = 0; i < m_num; i++) {
                m_pList[i].~T0();
            }
            m_num = 0;
            if (m_pMem != nullptr) {
                mtl::MemManager::deallocate(m_pMem, 0, false);
                m_pMem = nullptr;
            }
        }
    }
    // builds the list from a shader package of the version (the parameter names are not the original's)
    bool createPacShader(const void* pac, unsigned int version, bool flag);
    // the entry of the index (inline; the name is not the original's)
    T0& get(unsigned int idx) { return m_pList[idx]; }

    const CGLibShdPacHeader* m_pPac;  // 0x8 (the field names are not the original's)
    CGLibVtlMemPool m_memPool;  // 0x10
    T0* m_pList;                // 0x40
    void* m_pMem;               // 0x48
    int m_num;                  // 0x50
    int m_extNum;               // 0x54, the package's m_extNum
};

}  // namespace grlib

#endif
