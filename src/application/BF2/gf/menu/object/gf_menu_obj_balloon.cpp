#include "classes/gf/GfMenuObjBalloon.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuCallManager.h"
#include "classes/gf/GfMenuStrLinker.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObjFade.h"
#include "classes/gf/GfMenuPosAdapter.h"
#include "classes/gf/GfReqManager.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfReqCommand.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"
#include "ui/UIUtil.h"

namespace gf {

GfMenuObjBalloon::~GfMenuObjBalloon() {
    m_getItems.assign(mm::mtl::IntrusivePtr<GfMenuReferenceItem>());
    m_values.clear();
    if (m_moneyList != nullptr) {
        m_moneyList->release();
        m_moneyList = nullptr;
    }
    if (m_itemList != nullptr) {
        m_itemList->release();
        m_itemList = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
}

void GfMenuObjBalloon::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBalloon::update() {
    m_seq.update();
    GfMenuObject::update();
}

bool GfMenuObjBalloon::seqSave() {
    m_saveRequest = GfReqCommand::fn_7100554234(SAVESLOT(0x16));
    GfMenuObjFade::dispSaving(true, 0);
    return true;
}

bool GfMenuObjBalloon::seqSaveWait() {
    if (GfReqManager::isValid(m_saveRequest)) {
        return false;
    }
    GfMenuObjFade::dispSaving(false, 0);
    m_saveRequest = -1;
    GfMenuObject::addResultCallContext(ui::UIObjectAcc(m_handle, "LAY_select").m_handle, 2, 0);
    return true;
}

void GfMenuObjBalloon::close(GfMenuCallContext* context, bool flag) {
    if (!context->isActive()) {
        return;
    }
    if (context->isTerm()) {
        return;
    }
    unsigned int handle = 0;
    switch (context->m_objectId) {
    case 2:
    case 3:
        handle = GfMenuObject::getAttachedObject(2);
        break;
    case 4:
        handle = GfMenuObject::getAttachedObject(4);
        break;
    case 5:
        handle = GfMenuObject::getAttachedObject(5);
        break;
    case 7:
        handle = GfMenuObject::getAttachedObject(7);
        break;
    case 8:
        handle = GfMenuObject::getAttachedObject(8);
        break;
    case 9:
        handle = GfMenuObject::getAttachedObject(9);
        break;
    }
    unsigned int target = context->m_handle;
    if (ui::UIUtil::isValid(target)) {
        GfMenuObject::nextCallContext(context, 6);
        ui::EventData event;
        event.m_type = 0x103;
        event.m_param2 = flag;
        event.m_param3 = ui::UIObjectAcc(target).getDuplicateIndex();
        GfMenuObject::sendEvent(handle, event, 0.0f);
    }
}

void GfMenuObjBalloon::nextEvent(GfMenuCallContext* context, const NextParam& param) {
    if (context->isActive() && (context->m_objectId & ~1u) == 2) {
        unsigned int handle = GfMenuObject::getAttachedObject(2);
        unsigned int target = context->m_handle;
        if (ui::UIUtil::isValid(target)) {
            GfMenuObject::nextCallContext(context, 3);
            unsigned short text = GfMenuObject::registString(ui::UIStr(param.m_bdat, param.m_msgId));
            ui::EventData event;
            event.m_type = 0x104;
            event.m_param0 = text;
            event.m_param3 = ui::UIObjectAcc(target).getDuplicateIndex();
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

}  // namespace gf
