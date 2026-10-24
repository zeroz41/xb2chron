#define MM_LIB_FROM_MONOLIB_MM
#include "mm/mtl/FixedQueue.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/MsgParam.h"
#include "classes/ml/WorkObj.h"
#include "classes/ml/LibMain.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/DevFileTh.h"
#include "ml/WorkRootState.h"
#include "ml/WorkUtil.h"
#include "classes/ml/WorkControl.h"
#include "classes/ml/WorkSystem.h"

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

}  // namespace ml
