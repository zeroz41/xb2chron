#ifndef CLASSES_GRLIB_CGLIBSHDLISTBASE_H
#define CLASSES_GRLIB_CGLIBSHDLISTBASE_H

#include "grlib/CGLibVtlMemPool.h"

namespace grlib {
// a template: 4 instances in the module
template <typename T0>
class CGLibShdListBase {
public:
    virtual ~CGLibShdListBase();  // slot 0

    // layer::LayerShdManager::shaderRelease releases the pool, destroys m_num entries of m_pList and frees m_pMem
    // (the names are not the original's)
    // the entry of the index (inline; the name is not the original's)
    T0& get(unsigned int idx) { return m_pList[idx]; }

    unsigned char pad_8[0x8];
    CGLibVtlMemPool m_memPool;  // 0x10
    T0* m_pList;                // 0x40
    void* m_pMem;               // 0x48
    int m_num;                  // 0x50
};
}  // namespace grlib

#endif
