#include "classes/ml/WinView.h"
#include "classes/tl/TitleApplet.h"
#include "classes/tl/TitleApp.h"
#include "classes/fw/Framework.h"
#include "classes/fw/Applet.h"
#include "mm/Col4.h"
#include "gf/GfSetupParam.h"
#include "classes/gf/GfManager.h"
#include "classes/tl/TitleMain.h"

namespace tl {

TitleApplet::TitleApplet() {}

TitleApplet::~TitleApplet() {}

void TitleApplet::initialize(const fw::Framework& framework) {
    gf::GfSetupParam param;
    param.m_scn = m_env.m_scn;
    param.m_view = m_env.m_view;
    param.pad_10 = m_env.pad_0;
    param.m_execState = static_cast<gf::EXEC_STATE>(2);  // EXEC_STATE has no known enumerator names
    param.m_view->m_backCol = mm::Col4::black;
    param.m_dlcCameraParam = TitleApp::m_dlcCameraParam;
    gf::GfManager::build(param);
    TitleMain::create();
}

void TitleApplet::finalize(const fw::Framework& framework) {
    TitleMain::destroy();
    gf::GfManager::destroy();
}

void TitleApplet::update(const fw::UpdateInfo& info) {
    gf::GfManager::update(info);
    TitleMain::update(info);
}

void TitleApplet::updateAfterLayer(const fw::UpdateInfo& info) {
    gf::GfManager::updateAfterLayer(info);
}

void TitleApplet::postUpdate(const fw::UpdateInfo& info) {
    gf::GfManager::postUpdate(info);
}

}  // namespace tl
