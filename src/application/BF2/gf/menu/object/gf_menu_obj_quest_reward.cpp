#include "classes/gf/GfMenuObjQuestReward.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjQuestReward::GfMenuObjQuestReward(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjQuestReward::~GfMenuObjQuestReward() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjQuestReward::open(GfMenuCallContext* context, bool flag) {
    if (context != nullptr && GfMenuObjUtil::checkCCNext(context, 0x21)) {
        ui::UIObjectAcc acc(context->m_handle);
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0 = flag;
        event.m_param1 = 0;
        GfMenuObject::sendEvent(context->m_handle, event, 0.0f);
    }
}

void GfMenuObjQuestReward::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (acc.m_object != nullptr) {
        GfMenuObject::attachExternalCall(0x21, acc.m_handle);
        GfMenuObject::initialize();
        acc.setSuspend(true);
    }
}

void GfMenuObjQuestReward::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjQuestReward::update() {
    GfMenuObject::update();
}

}  // namespace gf
