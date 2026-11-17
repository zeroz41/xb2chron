#include "classes/gf/GfMenuObjOCG.h"
#include "classes/gf/GfMenuObjOCG/MainListener.h"
#include "classes/gf/GfMenuObjOCG/ResultListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuBattleAdapter.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/ui/UIEventManager.h"
#include "fw/LangUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/UIUtil.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

GfMenuObjOCG::GfMenuObjOCG(unsigned int handle)
    : GfMenuObject(handle), m_count(0), m_seq(this), m_ctrl(-1), m_animHandle(0), m_numbers(),
      m_se(0) {
    m_numbers[0] = GfMenuReferenceNumber::create();
    m_numbers[1] = GfMenuReferenceNumber::create();
}

GfMenuObjOCG::~GfMenuObjOCG() {
    m_numbers[0] = nullptr;
    m_numbers[1] = nullptr;
}

void GfMenuObjOCG::disp(bool disp) {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0x90));
    if (root.m_object != nullptr) {
        root.setDisp(disp);
    }
}

void GfMenuObjOCG::openGear() {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0x90));
    if (root.m_object != nullptr) {
        ui::UIObjectAcc special(root.searchChild("LAY_special"));
        root.setDisp(true);
        GfMenuObject::sendOpenEvent(special.m_handle, 0, 0.0f);
    }
}

void GfMenuObjOCG::closeGear() {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0x90));
    if (root.m_object != nullptr) {
        ui::UIObjectAcc special(root.searchChild("LAY_special"));
        GfMenuObject::sendCloseEvent(special.m_handle, 0, 0.0f);
    }
}

void GfMenuObjOCG::openResult(GfMenuCallContext* context, unsigned int first, unsigned int second) {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0x90));
    if (root.m_object != nullptr && GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc result(root.searchChild("LAY_result"));
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0 = first;
        event.m_param1 = second;
        GfMenuObject::sendEvent(result.m_handle, event, 0.0f);
        GfMenuObject::startCallContext(context, 0x90, result.m_handle);
    }
}

void GfMenuObjOCG::noticeExtend() {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0x90));
    if (root.m_object != nullptr) {
        ui::UIObjectAcc special(root.searchChild("LAY_special"));
        ui::EventData event;
        event.m_type = 0x102;
        GfMenuObject::sendEvent(special.m_handle, event, 0.0f);
    }
}

void GfMenuObjOCG::initialize() {
    {
        ui::UIObjectAcc root(m_handle);
        root.setDispPriority(ui::UIUtil::getGroupPriority(2) + 1);
    }
    ui::UIObjectAcc main(m_handle, "LAY_main");
    mm::mtl::FixStr<32> name;
    GfMenuObject::attachExternalCall(0x90, main.m_handle);
    {
        ui::UIObjectAcc special(main.m_handle, "LAY_special");
#line 178
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(special.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuBattleAdapter::create(special.searchChild("IMG_special_count_dummy"), 0x29);
        GfMenuObject::addNumberEventCondition(special.m_handle, "IMG_special_count_dummy", 1, 0);
        for (int i = 0; i < 3; i++) {
            name.format("TXT_special_info_num@%02d", i + 1);
            if (special.searchChild(name.m_str) != 0) {
                GfMenuBattleAdapter* adapter = GfMenuBattleAdapter::create(special.searchChild(name.m_str), 0x2b);
                if (adapter != nullptr) {
                    adapter->m_index = i;
                }
            }
        }
        {
            ui::UIObjectAcc time(special.m_handle, "IMG_special_time");
            GfMenuBattleAdapter::create(time.m_handle, 0x2a);
            time.startAnimation("time", true);
        }
        {
            ui::UIObjectAcc countMax(special.m_handle, "IMG_special_count_max");
            unsigned int index;
            if (fw::LangUtil::getLangType() == 5) {
                index = 2;
            } else {
                index = fw::LangUtil::getLangType() == 4 ? 3 : 1;
            }
            countMax.setImageIndex(index);
        }
    }
    {
        ui::UIObjectAcc result(main.m_handle, "LAY_result");
        GfMenuReferenceAdapter::create(result.searchChild("TXT_result_total_num@01"), m_numbers[0], false);
        GfMenuReferenceAdapter::create(result.searchChild("TXT_result_total_num@02"), m_numbers[1], false);
#line 240
        ResultListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ResultListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(result.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::initialize();
}

void GfMenuObjOCG::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjOCG::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjOCG::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        acc.setSuspend(true);
        // falls through: the base listener handles the close too
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 2) {
            acc.setDisp(false);
            acc.setSuspend(true);
        }
        break;
    case 0xD:
        if (event.m_param1 == 1) {
            unsigned int count = event.m_param3;
            m_owner->refreshGearCount(count);
        }
        break;
    case 0x21:
        acc.setDisp(true);
        acc.setSuspend(false);
        {
            ui::UIObjectAcc eff(acc.m_handle, "IMG_special_start_eff");
            eff.startAnimation("start", false);
            eff.setDisp(true);
        }
        {
            ui::UIObjectAcc base(acc.m_handle, "IMG_special_base");
            base.startAnimation("loop", false);
        }
        {
            int ctrl = GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_special_main"), 1, 0);
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        }
        m_owner->refreshGearCount(0);
        if (m_owner->m_se != 0) {
            GfMenuObjUtil::stopSE(m_owner->m_se, 0.0f);
            m_owner->m_se = 0;
        }
        m_owner->m_se = GfMenuObjUtil::playSE("dlc_se_btl_bl40040117");
        break;
    case 0x22:
        {
            ui::UIObjectAcc eff(acc.m_handle, "IMG_special_start_eff");
            eff.stopAnimation();
            eff.setDisp(false);
        }
        {
            int ctrl = GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_special_main"), 2, 0);
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        }
        if (m_owner->m_se != 0) {
            GfMenuObjUtil::stopSE(m_owner->m_se, 0.0f);
            m_owner->m_se = 0;
        }
        break;
    case 0x102: {
        ui::UIObjectAcc time(acc.m_handle, "IMG_special_time");
        time.setAddColor(mm::Col3::white);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x4000000;
        param.m_color = mm::Col3::black;
        param.m_time = 0.5f;
        param.m_curve = 1;
        GfMenuObjUtil::startCtrl(time.m_handle, param, nullptr);
        GfMenuObjUtil::playSE(0x28);
        ui::UIObjectAcc eff(acc.m_handle, "IMG_special_start_eff");
        eff.startAnimation("start", false);
        eff.setDisp(true);
        break;
    }
    }
}

// refreshGearCount (0x71004498C4) is not here yet (the closest candidate keeps different values live)

void GfMenuObjOCG::ResultListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        acc.setDisp(false);
        acc.setSuspend(true);
    } else if (event.m_type == 0x21) {
        unsigned int first = (unsigned int)event.m_param0 < 100000000 ? event.m_param0 : 99999999;
        unsigned int second = (unsigned int)event.m_param1 < 100000000 ? event.m_param1 : 99999999;
        m_owner->m_numbers[0]->m_value = first;
        m_owner->m_numbers[0]->m_max = 99999999;
        m_owner->m_numbers[1]->m_value = second;
        m_owner->m_numbers[1]->m_max = 99999999;
        m_owner->m_ctrl = -1;
        m_owner->m_seq.clear();
        m_owner->m_seq.addWait(1);
        m_owner->m_seq.addJob(&GfMenuObjOCG::seqStartResult);
        acc.setSuspend(false);
    } else if (event.m_type == 0x101) {
        GfMenuObject::termCallContext(acc.m_handle);
        acc.setDisp(false);
        acc.setSuspend(true);
    } else {
        UIObjectListener::reciveEvent(event, handle);
    }
}

bool GfMenuObjOCG::seqStartResult() {
    mm::Pnt<short> pos;
    ui::UIObjectAcc result(m_handle, "LAY_result");
    result.setDisp(true);
    {
        ui::UIObjectAcc base(result.m_handle, "IMG_result_base");
        base.startAnimation("start", false);
        m_animHandle = base.m_handle;
    }
    {
        mm::Rect<short> rect;
        result.getLayoutRect("dlc240_result", rect);
        {
            ui::UIObjectAcc total(result.m_handle, "LAY_result_total@01");
            pos.x = rect.x;
            pos.y = rect.y + 5;
            total.setPos(pos);
            pos.x -= 30;
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x80;
            param.m_startFlags = 8;
            param.m_pos = pos;
            param.m_time = 8.0f / 3.0f;
            param.m_curve = 1;
            GfMenuObjUtil::startCtrl(total.m_handle, param, nullptr);
        }
        {
            ui::UIObjectAcc total(result.m_handle, "LAY_result_total@02");
            pos.x = rect.x;
            pos.y = rect.y - 5;
            total.setPos(pos);
            pos.x += 30;
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x80;
            param.m_pos = pos;
            param.m_startFlags = 8;
            param.m_time = 8.0f / 3.0f;
            param.m_curve = 1;
            GfMenuObjUtil::startCtrl(total.m_handle, param, nullptr);
        }
    }
    {
        ui::UIObjectAcc index(result.m_handle, "TXT_result_total_index@01");
        index.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_r_early";
        param.m_setDefault = true;
        param.m_startFlags = 8;
        GfMenuObjUtil::startCtrl(index.m_handle, param, nullptr);
    }
    {
        ui::UIObjectAcc index(result.m_handle, "TXT_result_total_index@02");
        index.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l_early";
        param.m_setDefault = true;
        param.m_startFlags = 8;
        GfMenuObjUtil::startCtrl(index.m_handle, param, nullptr);
    }
    {
        ui::UIObjectAcc num0(result.m_handle, "TXT_result_total_num@01");
        ui::UIObjectAcc num1(result.m_handle, "TXT_result_total_num@02");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "sample";
        param.m_motion = "fadein";
        param.m_setDefault = true;
        param.m_startFlags = 8;
        GfMenuObjUtil::startCtrl(num0.m_handle, param, nullptr);
        int ctrl = GfMenuObjUtil::startCtrl(num1.m_handle, param, nullptr);
        num0.setAlpha(0.0f);
        num1.setAlpha(0.0f);
        m_ctrl = ctrl;
    }
    m_seq.addJob(&GfMenuObjOCG::seqCtrlWait);
    m_seq.addJob(&GfMenuObjOCG::seqAnimWait);
    m_seq.addJob(&GfMenuObjOCG::seqCloseResult);
    GfMenuObjUtil::playJingle(0xe);
    return true;
}

bool GfMenuObjOCG::seqCtrlWait() {
    if (m_ctrl != -1) {
        if (GfMenuObjUtil::isBusyCtrl(m_ctrl)) {
            return false;
        }
        m_ctrl = -1;
    }
    return true;
}

bool GfMenuObjOCG::seqAnimWait() {
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

bool GfMenuObjOCG::seqCloseResult() {
    ui::UIObjectAcc result(m_handle, "LAY_result");
    {
        ui::UIObjectAcc base(result.m_handle, "IMG_result_base");
        base.startAnimation("end", false);
        m_animHandle = base.m_handle;
    }
    {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_r_early";
        param.m_setDefault = true;
        param.m_startFlags = 10;
        GfMenuObjUtil::startCtrl(result.m_handle, param, "LAY_result_total@01");
    }
    {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_l_early";
        param.m_setDefault = true;
        param.m_startFlags = 10;
        m_ctrl = GfMenuObjUtil::startCtrl(result.m_handle, param, "LAY_result_total@02");
    }
    m_seq.addJob(&GfMenuObjOCG::seqCtrlWait);
    m_seq.addJob(&GfMenuObjOCG::seqAnimWait);
    m_seq.addJob(&GfMenuObjOCG::seqEndResult);
    return true;
}

bool GfMenuObjOCG::seqEndResult() {
    ui::UIObjectAcc result(m_handle, "LAY_result");
    ui::EventData event;
    event.m_type = 0x101;
    GfMenuObject::sendEvent(result.m_handle, event, 0.0f);
    return true;
}

}  // namespace gf
