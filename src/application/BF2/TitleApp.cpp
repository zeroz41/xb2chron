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
// 2.0.0's symbols name it
bool TitleApplet::s_bGameTypeIra;

bool TitleApp::wkStandbyLogout() {
    if (!LauncherApp::wkStandbyLogout()) {
        return false;
    }
    ml::WinView::setInitialBackCol(mm::Col4(0.6f, 0.6f, 0.6f, 1.0f));
    return true;
}

TitleApp::~TitleApp() {}

}  // namespace tl
