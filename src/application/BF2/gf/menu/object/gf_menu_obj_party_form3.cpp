#include "classes/gf/GfMenuObjPartyForm3.h"
#include "classes/gf/GfMenuObjPartyForm3.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"

namespace gf {

void GfMenuObjPartyForm3::registOpenParam(const OpenParam& openParam) {
    GfMenuTypes::Param param;
    param.m_halves.m_type = openParam.m_value;
    GfMenuFullScreen::registLayerParam(GfMenuObject::getMenuLayerID(0x24), param);
}

void GfMenuObjPartyForm3::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjPartyForm3::update() {
    m_seq.update();
    GfMenuObject::update();
}

bool GfMenuObjPartyForm3::seqAnnounceChange() {
    if (GfMenuObjUtil::fn_710048FD30(3) && m_openType == 2) {
        return true;
    }
    if (m_announceContext != nullptr) {
        return m_announceContext->isTerm();
    }
    m_announceContext = GfMenuCallContext::create();
    GfMenuObjCommonText::open(m_announceContext, 13, 0);
    return false;
}

bool GfMenuObjPartyForm3::seqWaitOpenEnd() {
    ui::UIObjectAcc acc(m_handle, "LAY_dr_select");
    GfMenuObject::enableInput(acc.m_handle);
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuObjMainMenu2::setCloseKeyEnable(true);
    }
    return true;
}

}  // namespace gf
