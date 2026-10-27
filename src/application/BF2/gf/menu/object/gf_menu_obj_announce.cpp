#include "classes/gf/TUnk_B5F9E8.h"
#include "classes/gf/TUnk_B5F9E8.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuTypes.h"

namespace gf {

TUnk_B5F9E8::~TUnk_B5F9E8() {
    if (m_idList != nullptr) {
        m_idList->release();
        m_idList = nullptr;
    }
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
}

void TUnk_B5F9E8::fn_710038289C() {
    GfMenuTypes::Param param;
    param.m_menuId = 1;
    GfMenuFullScreen::registLayerParam(0x47, param);
}

void TUnk_B5F9E8::finalize() {
    GfMenuObjOperationInfo::setDisp(true);
    GfMenuObject::finalize();
}

void TUnk_B5F9E8::update() {
    m_seq.update();
    m_mainSeq.update();
    GfMenuObject::update();
}

}  // namespace gf
