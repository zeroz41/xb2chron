#define MM_LIB_FROM_MONOLIB_MM
#include "mm/mtl/FixedQueue.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/MsgParam.h"
#include "classes/ml/WorkObj.h"
#include "classes/ml/LibMain.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/DevFileTh.h"
#include "mtl/MemManager.h"
#include "ml/WorkRootState.h"
#include "ml/WorkUtil.h"
#include "ml/MlMem.h"
#include "classes/ml/WorkControl.h"
#include "classes/ml/WorkSystem.h"
#include "mm/mtl/FixedList.h"
#include "mtl/AllocHandle.h"

namespace ml {

LibMain::~LibMain() {}

bool LibMain::isInitialized() {
    LibMain* main = get();
    if (main == nullptr) {
        return false;
    }
    return main->isLoggedIn();
}

bool LibMain::wkStandbyLogin() {
    if (mm::mtl::PtrSingleton<DevFileTh>::get() != nullptr && DevFileTh::isInitialized() &&
        WorkCpu::isInitialized()) {
        return WorkObj::wkStandbyLogin();
    }
    return false;
}

bool LibMain::wkStandbyLogout() {
    // the count read first, the system tested first (the original's order)
    int childNum = m_child.size();
    wkCheckTimeout(30000, mm::mtl::PtrSingleton<WorkSystem>::get() == nullptr && childNum == 0,
                   "ログアウトに失敗しました");
    if (m_child.size() == 0 && mm::mtl::PtrSingleton<WorkSystem>::get() == nullptr) {
        return WorkObj::wkStandbyLogout();
    }
    return false;
}

LibMain* LibMain::create() {
    WorkControl* parent = mm::mtl::PtrSingleton<WorkControl>::get();
    LibMain* main = new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) LibMain(parent);
    WorkRootState::entryWork(main, parent, false);
    return main;
}

namespace {
// a static of its own that MlMem::initialize and terminate pass through: guarded, constructing nothing (the name is
// not the original's)
mtl::MemManager& memManager() {
    static mtl::MemManager s_manager;
    return s_manager;
}
}  // namespace

// the allocators MlMem hands out, and the extra ones 1.0.0's addExtMem kept (the names are not the original's; the
// compiler merges the four into one block)
static mtl::ALLOC_HANDLE s_productMem;
static mtl::ALLOC_HANDLE s_debugMem;
static mtl::ALLOC_HANDLE s_graphicMem;
static mm::mtl::FixedList<mtl::ALLOC_HANDLE, 64> s_extMem;

void MlMem::initialize() {
    memManager().initialize();
}

void MlMem::terminate() {
    memManager().terminate();
}

void MlMem::setProductMem(mtl::ALLOC_HANDLE handle) {
    s_productMem = handle;
}

mtl::ALLOC_HANDLE MlMem::getProductMem() {
    return s_productMem;
}

void MlMem::setDebugMem(mtl::ALLOC_HANDLE handle) {
    s_debugMem = handle;
}

mtl::ALLOC_HANDLE MlMem::getDebugMem() {
    return s_debugMem;
}

void MlMem::setGraphicMem(mtl::ALLOC_HANDLE handle) {
    s_graphicMem = handle;
}

mtl::ALLOC_HANDLE MlMem::getGraphicMem() {
    return s_graphicMem;
}

}  // namespace ml
