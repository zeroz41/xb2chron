#include "classes/gf/GfMenuObjNamedDialog.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfGameUtil.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

GfMenuObjNamedDialog::GfMenuObjNamedDialog(unsigned int handle) : GfMenuObject(handle), m_list(nullptr) {
    m_list = GfMenuIDList::create();
}

GfMenuObjNamedDialog::~GfMenuObjNamedDialog() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

void GfMenuObjNamedDialog::open(unsigned int row) {
    bool enable = GfMenuObjUtil::isValidExpansion(3) ? GfGameManager::isClearGame() : GfGameManager::isEnableNamedRecord();
    if (!enable) {
        return;
    }
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8A));
    if (acc.m_object != nullptr) {
        int index = GfGameUtil::getNamedListIndex(row);
        if (index != 0) {
            GfMenuObject::sendOpenEvent(acc.m_handle, index, 0.0f);
        }
    }
}

// close (0x7100445258) and initialize (0x71004452C4) are not here yet: see the report

void GfMenuObjNamedDialog::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjNamedDialog::update() {
    GfMenuObject::update();
}

// TUnk_B638A8::reciveEvent (0x7100445478) is not here yet: see the report

}  // namespace gf
