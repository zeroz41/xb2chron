#include "classes/apps/FrameworkLauncher.h"
#include "classes/apps/LauncherApp.h"
#include "classes/fw/Framework.h"
#include "classes/fw/Applet.h"
#include "classes/ai/AiData.h"
#include "btl/Utility.h"
#include "classes/gf/GfGameParty.h"
#include "classes/btl/BattleGlobal.h"
#include "btl/Utility.h"
#include "classes/ai/AiData.h"
#include "classes/btl/BattleGlobal.h"
#include "gf/SDataEnemy.h"
#include "classes/apps/FrameworkLauncher.h"
#include "classes/apps/LauncherApp.h"
#include "classes/fw/Applet.h"
#include "classes/fw/Framework.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfBdatChrEnParam.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "fw/Transform.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjInfo.h"
#include "gf/SDataEnemy.h"
#include "mm/mtl/RTTI.h"

namespace apps {

ml::Scn* FrameworkLauncher::getScn() {
    if (sys() == nullptr) {
        return nullptr;
    }
    return sys()->m_scn;
}

ml::WinView* FrameworkLauncher::getView() {
    if (sys() == nullptr) {
        return nullptr;
    }
    return sys()->m_view;
}

void FrameworkLauncher::rdkReaded(const char*, void*, int) {}

bool FrameworkLauncher::isDebugPause() const { return m_debugPause; }

void FrameworkLauncher::stepDebugPause() {
    if (m_debugPauseStepOk) {
        m_request |= 0x200000;
    }
}

bool FrameworkLauncher::resetApp() {
    if (m_request & 0x70000000) {
        return false;
    }
    m_request |= 0x50000000;
    return true;
}

}  // namespace apps

namespace mm { namespace mtl {

}}  // namespace mm::mtl
