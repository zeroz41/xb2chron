#include "ui/EventData.h"
#include "gf/GfMenuSequence.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfDataBlade.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuObjBladeName.h"
#include "classes/gf/GfMenuObjBladeName/MainListener.h"
#include "classes/gf/GfMenuObjBladeName.h"
#include "classes/gf/GfMenuObjBladeName/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuSequence.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjBladeName::GfMenuObjBladeName(unsigned int handle) : GfMenuObject(handle), m_seq(this), m_leaving(false) {}

GfMenuObjBladeName::~GfMenuObjBladeName() {}

void GfMenuObjBladeName::open(GfMenuCallContext* context) {
    if (GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x81));
        if (acc.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x21;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
            GfMenuObject::startCallContext(context, 0x81, acc.m_handle);
        }
    }
}

void GfMenuObjBladeName::close() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x81));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjBladeName::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x81, acc.m_handle);
#line 116
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_bl_name"), 2, 0, false);
    GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_bl_name_shadow"), 2, 0, false);
    GfMenuObject::initialize();
}

void GfMenuObjBladeName::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBladeName::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjBladeName::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 0x21:
        m_owner->m_seq.clear();
        m_owner->m_seq.addJob(&GfMenuObjBladeName::seqStart);
        break;
    case 0x22: {
        m_owner->m_seq.clear();
        {
            ui::UIObjectAcc base(acc.m_handle, "IMG_bl_name_base");
            base.stopAnimation();
            base.setDisp(false);
        }
        {
            ui::UIObjectAcc name(acc.m_handle, "TXT_bl_name");
            ui::UIObjectAcc shadow(acc.m_handle, "TXT_bl_name_shadow");
            GfMenuObjUtil::stopCtrl(GfMenuObjUtil::getCtrlID(name.m_handle));
            name.setDisp(false);
            GfMenuObjUtil::stopCtrl(GfMenuObjUtil::getCtrlID(shadow.m_handle));
            shadow.setDisp(false);
        }
        {
            ui::UIObjectAcc main(acc.m_handle);
            GfMenuObjUtil::stopCtrl(GfMenuObjUtil::getCtrlID(main.m_handle));
            main.setDisp(false);
        }
        break;
    }
    case 0x101:
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

// seqStart (0x710039B604) is not here yet: no candidate is identical (see the report)

bool GfMenuObjBladeName::seqApperRare() {
    ui::UIObjectAcc base(m_handle, "IMG_bl_name_base");
    base.setDisp(true);
    base.startAnimation("rare", false);
    seqApperName();
    return true;
}

bool GfMenuObjBladeName::seqApperWait() {
    ui::UIObjectAcc base(m_handle, "IMG_bl_name_base");
    if (base.isPlayingAnimation()) {
        return false;
    }
    m_seq.addWait(30);
    m_seq.addJob(&GfMenuObjBladeName::seqLeave);
    return true;
}

bool GfMenuObjBladeName::seqApperNormal() {
    ui::UIObjectAcc base(m_handle, "IMG_bl_name_base");
    base.setDisp(true);
    base.startAnimation("common", false);
    return true;
}

// 1.0.0 has an out-of-line copy here that no job queues; 3.0.1's linker dropped it, and seqApperRare inlines it
inline bool GfMenuObjBladeName::seqApperName() {
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_zoom";
    param.m_motion = "fade_in";
    param.m_startFlags = 10;
    GfMenuObjUtil::startCtrl(m_handle, param, "TXT_bl_name");
    GfMenuObjUtil::startCtrl(m_handle, param, "TXT_bl_name_shadow");
    return true;
}

bool GfMenuObjBladeName::seqLeave() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    bool done = false;
    if (!m_leaving) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = 0.2f;
        param.m_startFlags = 10;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        m_leaving = true;
    } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.m_handle))) {
        m_leaving = false;
        {
            ui::UIObjectAcc base(m_handle, "IMG_bl_name_base");
            base.setDisp(false);
        }
        acc.setDisp(false);
        GfMenuObject::termCallContext(acc.m_handle);
        done = true;
    }
    return done;
}

}  // namespace gf
