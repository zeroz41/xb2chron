#include "classes/gf/TUnk_B64F08.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfDataBlade.h"
#include "ui/EventData.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuBattleAdapter.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

namespace {
// LAY_main's parts hidden (the name is not the original's)
void hideParts(unsigned int handle) {
    ui::UIObjectAcc parts(handle, "LAY_main");
    parts.setDispChild(false, "LAY_en");
    parts.setDispChild(false, "LAY_arts");
    parts.setDispChild(false, "LAY_char");
    parts.setDispChild(false, "LAY_time");
    parts.setDispChild(false, "IMG_eff");
}
}  // namespace

bool TUnk_B64F08::fn_71004944B8(int blade) {
    if (blade == 0x412) {
        return false;
    }
    if (GfGameManager::isClearGame()) {
        return true;
    }
    return GfDataBlade::fn_7100231884() > 2000;
}

TUnk_B64F08::TUnk_B64F08(unsigned int handle)
    : GfMenuObject(handle), m_seq(this), m_ctrl(-1), m_animHandle(0), m_result(0), m_drivers(nullptr) {
    m_drivers = GfMenuDriverList::create();
    ui::UIListInfoBase::SetupParam param;
    m_drivers->setup(getAllocator(ALLOCATOR(0)), param);
    m_drivers->clear();
}

TUnk_B64F08::~TUnk_B64F08() {
    if (m_drivers != nullptr) {
        m_drivers->release();
        m_drivers = nullptr;
    }
}

void TUnk_B64F08::fn_7100494708(GfMenuCallContext* context, const OpenParam& param) {
    if (GfMenuObjUtil::fn_710048FD30(1)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8b));
        if (acc.m_object != nullptr && GfMenuObjUtil::checkCCStart(context)) {
            ui::EventData event;
            event.m_type = 0x21;
            event.m_param0 = param.m_driver;
            event.m_paramShort[2] = param.m_flag;
            event.m_param23 = param.m_target;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
            GfMenuObject::startCallContext(context, 0x8b, acc.m_handle);
        }
        return;
    }
    context->abort();
}

void TUnk_B64F08::fn_71004947C4(unsigned int value, GfMenuCallContext* context) {
    if (GfMenuObjUtil::fn_710048FD30(1)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8b));
        if (acc.m_object != nullptr) {
            if (context != nullptr && GfMenuObjUtil::checkCCStart(context)) {
                GfMenuObject::startCallContext(context, 0x8b, acc.m_handle);
            }
            ui::EventData event;
            event.m_type = 0x100;
            event.m_param0 = value;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
        return;
    }
    context->abort();
}

void TUnk_B64F08::initialize() {
    if (GfMenuObjUtil::fn_710048FD30(1)) {
        ui::UIObjectAcc acc(m_handle, "LAY_main");
        GfMenuObject::attachExternalCall(0x8b, acc.m_handle);
#line 149
        TUnk_B64F50* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B64F50(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuCharDataAdapter::createFromDriverList(acc.searchChild("IMG_char_face"), 3, m_drivers, 0, false);
        {
            ui::UIObjectAcc gauge(acc.m_handle, "IMG_time_gauge");
            GfMenuBattleAdapter::create(gauge.m_handle, 0x1e);
            gauge.startAnimation("gauge", true);
        }
        GfMenuObject::initialize();
    }
}

void TUnk_B64F08::finalize() {
    if (GfMenuObjUtil::fn_710048FD30(1)) {
        GfMenuObject::finalize();
    }
}

void TUnk_B64F08::update() {
    if (GfMenuObjUtil::fn_710048FD30(1)) {
        m_seq.update();
        GfMenuObject::update();
    }
}

// TUnk_B64F50::reciveEvent (0x7100494AC4) is not here yet: see the report

bool TUnk_B64F08::fn_7100494DEC() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    main.setDisp(true);
    main.setAlpha(1.0f);
    hideParts(m_handle);
    m_seq.addJob(&TUnk_B64F08::fn_7100494F1C);
    return true;
}

// fn_7100494F1C, fn_71004950AC and fn_710049523C are not here yet: see the report

bool TUnk_B64F08::fn_71004953CC() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObject::termCallContext(main.m_handle);
    m_result = 0;
    m_seq.addJob(&TUnk_B64F08::fn_7100495470);
    return true;
}

bool TUnk_B64F08::fn_7100495470() {
    if (m_result == 0) {
        return false;
    }
    if (m_result == 1) {
        m_seq.addJob(&TUnk_B64F08::fn_710049553C);
    } else {
        m_seq.addJob(&TUnk_B64F08::fn_7100495724);
    }
    return true;
}

// fn_710049553C is not here yet: see the report

bool TUnk_B64F08::fn_7100495724() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    m_ctrl = GfMenuObjUtil::setCommonFadeOut(main.m_handle, 0, 0);
    m_seq.addJob(&TUnk_B64F08::fn_7100495960);
    m_seq.addJob(&TUnk_B64F08::fn_7100495918);
    return true;
}

bool TUnk_B64F08::fn_7100495820() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    main.setDispChild(false, "LAY_en");
    main.setDispChild(false, "LAY_arts");
    main.setDispChild(false, "LAY_char");
    main.setDispChild(false, "LAY_time");
    GfMenuObjUtil::playSE("se_btl_bl_shulk19");
    return true;
}

bool TUnk_B64F08::fn_71004958B4() {
    bool done = true;
    if (m_animHandle != 0) {
        ui::UIObjectAcc anim(m_animHandle);
        if (anim.isPlayingAnimation()) {
            done = false;
        } else {
            m_animHandle = 0;
        }
    }
    return done;
}

bool TUnk_B64F08::fn_7100495918() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObject::sendCloseEvent(main.m_handle, 0, 0.0f);
    return true;
}

bool TUnk_B64F08::fn_7100495960() {
    if (m_ctrl != -1) {
        if (GfMenuObjUtil::isBusyCtrl(m_ctrl)) {
            return false;
        }
        m_ctrl = -1;
    }
    return true;
}

}  // namespace gf
