#include "ptlib/StackAllocater.h"
#include "ptlib/ParticleSystem.h"
#include "mm/MMStdBase.h"
#include "new"

namespace ptlib {

StaticAllocObj* StaticAllocObj::create(unsigned int size, const char* file, unsigned int line) {
    StaticAllocObj* s_pIns =
        static_cast<StaticAllocObj*>(ParticleManager::sysAlloc(size + sizeof(StaticAllocObj) * 2, 16, file, line));
    efAstMsg("s_pIns", "alloc miss");
    if (s_pIns != nullptr) {
        new (s_pIns) StaticAllocObj(size);
    }
    return s_pIns;
}

void StaticAllocObj::destroy(StaticAllocObj* pObj) {
    if (pObj != nullptr) {
        pObj->~StaticAllocObj();
        ParticleManager::sysFree(pObj);
    }
}

void* StaticAllocObj::sysAlloc(unsigned int size, unsigned int align, const char* file, unsigned int line) {
    unsigned int rest = size % align;
    if (rest != 0) {
        size = size + align - rest;
    }
    unsigned int used = m_used + size;
    if (used > m_size) {
#line 78
        MM_ASSERT(0);
        efAstMsg("0", "memory empty");
        return nullptr;
    }
    void* p = m_pTop + m_used;
    m_used = used;
    return p;
}

}  // namespace ptlib
