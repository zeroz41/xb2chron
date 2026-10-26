#include "classes/ml/WinProc.h"
#include "classes/ml/WinView.h"
#include "classes/ml/ProcDesktop.h"
#include "classes/apps/LauncherApp.h"
#include "ml/WorkUtil.h"
#include "classes/tl/TitleApp.h"
#include "mm/Col4.h"
#include "classes/fw/Framework.h"
#include "classes/fw/Applet.h"
#include "classes/tl/TitleApplet.h"

namespace tl {

const char* TitleApp::m_szTitle = "Title";
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100C232DA)
bool TitleApp::m_dlcCameraParam;

bool TitleApp::wkStandbyLogout() {
    if (!LauncherApp::wkStandbyLogout()) {
        return false;
    }
    ml::WinView::setInitialBackCol(mm::Col4(0.6f, 0.6f, 0.6f, 1.0f));
    return true;
}

TitleApp::~TitleApp() {}

}  // namespace tl
