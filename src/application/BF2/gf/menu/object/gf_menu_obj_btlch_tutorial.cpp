#include "classes/gf/TUnk_B60848.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuTypes.h"

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAA1C8)
bool TUnk_B60848::s_exists;

TUnk_B60848::TUnk_B60848(unsigned int handle)
    : GfMenuObject(handle), m_seq(this), m_mainSeq(this), m_context(nullptr), pad_388(0), m_idList(nullptr),
      pad_398(false) {
    m_context = GfMenuCallContext::create();
    m_idList = GfMenuIDList::create();
    s_exists = true;
}

TUnk_B60848::~TUnk_B60848() {
    if (m_idList != nullptr) {
        m_idList->release();
        m_idList = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    s_exists = false;
}

void TUnk_B60848::fn_71003B2A90(unsigned int menuId) {
    GfMenuTypes::Param param;
    param.m_menuId = menuId;
    GfMenuFullScreen::registLayerParam(0x67, param);
}

void TUnk_B60848::fn_71003B2ABC(int param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x89));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc tutorial(acc.m_handle, "LAY_tutorial");
        GfMenuObject::sendOpenEvent(tutorial.m_handle, param, 0.0f);
    }
}

bool TUnk_B60848::fn_71003B2B30() {
    return s_exists;
}

void TUnk_B60848::finalize() {
    GfMenuObject::finalize();
}

void TUnk_B60848::update() {
    m_mainSeq.update();
    m_seq.update();
    GfMenuObject::update();
}

bool TUnk_B60848::fn_71003B3ECC() {
    return !ui::UIManager::get()->isLoading();
}

}  // namespace gf
