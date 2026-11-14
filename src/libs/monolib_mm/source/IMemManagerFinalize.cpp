#define MM_LIB_FROM_MONOLIB_MM
#include "ml/WorkRootMem.h"
#include "ml/WorkRoot.h"
#include "ml/MlMem.h"
#include "mtl/MemManager.h"
#include "mtl/AllocHandle.h"
#include "mm/mtl/FixedVector.h"
#include <stdlib.h>

namespace ml {
namespace _wrootm {

// the memories' names (WorkRootMem::initialize passes them to MemManager::create); these globals' names are
// the original's (symbols _ZN2ml7_wrootm...)
const char* s_szMemProduct = "MLSYSHANDLE";
const char* s_szMemDebug = "MLDEBHANDLE";
const char* s_szMemGraphic = "MLGRAHANDLE";
const char* s_szMemTemp = "TEMP";
const char* s_szWorkStateMem = "WorkStateSystem";
const char* s_szWorkStateMemD = "WorkStateDebug";

mtl::ALLOC_HANDLE s_hMemFG;
mtl::ALLOC_HANDLE s_hMemTEMP;
mm::mtl::FixedVector<IMemManagerFinalize*, 32> g_FinalizeCallback;
mtl::ALLOC_HANDLE s_hStateMem;
mtl::ALLOC_HANDLE s_hStateMemDebug;

}  // namespace _wrootm

void WorkRootMem::finalize() {
    for (unsigned int i = 0; i < _wrootm::g_FinalizeCallback.size(); i++) {
        IMemManagerFinalize* callback = _wrootm::g_FinalizeCallback.begin()[i];
        if (callback != nullptr) {
            callback->finalize();
        }
    }
    _wrootm::g_FinalizeCallback.clear();

    if (_wrootm::s_hStateMemDebug.m_handle != 0) {
        mtl::MemManager::erase(_wrootm::s_hStateMemDebug);
        _wrootm::s_hStateMemDebug.m_handle = 0;
    }
    if (_wrootm::s_hStateMem.m_handle != 0) {
        mtl::MemManager::erase(_wrootm::s_hStateMem);
        _wrootm::s_hStateMem.m_handle = 0;
    }
    if (_wrootm::s_hMemTEMP.m_handle != 0) {
        mtl::MemManager::erase(_wrootm::s_hMemTEMP);
        _wrootm::s_hMemTEMP.m_handle = 0;
    }
    if (MlMem::getDebugMem().m_handle != 0) {
        mtl::MemManager::erase(MlMem::getDebugMem());
        MlMem::getDebugMem() = mtl::ALLOC_HANDLE();
    }
    if (MlMem::getGraphicMem().m_handle != 0) {
        mtl::MemManager::erase(MlMem::getGraphicMem());
        MlMem::getGraphicMem() = mtl::ALLOC_HANDLE();
    }
    if (MlMem::getProductMem().m_handle != 0) {
        mtl::MemManager::erase(MlMem::getProductMem());
        MlMem::getProductMem() = mtl::ALLOC_HANDLE();
    }
    free(WorkRoot::getParam()->m_productMem);
}

mtl::ALLOC_HANDLE WorkRootMem::getMemTMP() {
    return _wrootm::s_hMemTEMP;
}

mtl::ALLOC_HANDLE WorkRootMem::getMemState() {
    return _wrootm::s_hStateMem;
}

}  // namespace ml
