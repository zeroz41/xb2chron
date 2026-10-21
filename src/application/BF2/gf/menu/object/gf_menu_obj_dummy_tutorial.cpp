#include "gf/GfMenuObjDummyTutorial.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"

namespace gf {

void GfMenuObjDummyTutorial::open(GfMenuCallContext* context, const OpenParam& param) {
    if (!GfMenuObjUtil::checkCCStart(context)) {
        return;
    }
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x79));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0Short = param.m_id;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        GfMenuObject::startCallContext(context, 0x79, acc.m_handle);
    }
}

}  // namespace gf
