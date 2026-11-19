#define MM_LIB_FROM_NAVI
#include "classes/navi/NvmshManager.h"
#include "classes/navi/NvmshAcObj.h"
#include "classes/navi/NvmshResMan.h"
#include "navi/NvmshAcMan.h"
#include "classes/ml/WorkCpu.h"
#include "ml/CriticalSection.h"
#include "mtl/MemManager.h"

namespace navi {

unsigned int NvmshManager::jobUpdate(void* man, void*) {
    NvmshManager* manager = static_cast<NvmshManager*>(man);
    manager->m_flags |= 0x20000;
    if (!(manager->m_flags & (!(manager->m_flags & 0x4) ? 0x1 : 0x8))) {
        manager->m_pResMan->update();
        manager->m_pAcMan->update(manager->m_pResMan);
    }
    manager->m_flags &= ~0x20000;
    return 0;
}

NvmshManager::~NvmshManager() {
    ml::WorkCpu::sync(m_jobGroup, static_cast<ml::WKCPU_SYNC>(0), static_cast<ml::CPUID>(0));
    ml::WorkCpu::removeAutoExecGrp(m_jobGroup);
    ml::WorkCpu::releaseGroupHandle(m_jobGroup);
    if (m_pResMan) {
        delete m_pResMan;
        m_pResMan = nullptr;
    }
    if (m_pAcMan) {
        delete m_pAcMan;
        m_pAcMan = nullptr;
    }
    if (m_hAlloc.m_handle != 0) {
        mtl::MemManager::erase(m_hAlloc);
        m_hAlloc = mtl::ALLOC_HANDLE();
    }
}

void NvmshManager::setupResource(const void* resource, const char* name) {
    m_pResMan->setupResource(static_cast<const unsigned char*>(resource), name);
}

void NvmshManager::releaseResource() { m_pResMan->releaseResource(); }

NvmshAcObj* NvmshManager::createObj() {
    static ml::CriticalSection s_cs;  // the name is not the original's
    ml::CS lock(s_cs);
    return static_cast<NvmshAcObj*>(m_pAcMan->createObj(m_hAlloc, m_pResMan));
}

void NvmshManager::releaseObj(NvmshAcObj* object) { m_pAcMan->releaseObj(object); }

}  // namespace navi
