#include "classes/gf/GfMenuObjButtonChallenge2.h"
#include "classes/gf/GfMenuObjButtonChallenge2/MainListener.h"
#include "classes/gf/GfMenuObjButtonChallenge2/RingListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/ui/UICtrlManager.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIShapeRing.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "ui/UIUtil.h"

namespace gmo_button_challenge2 {
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAA1CC). initialize keeps LAY_main's
// display priority; open gives it back to the opened object's parent outside battle. External: the code reaches it
// through the GOT
unsigned int dispPriority;
}  // namespace gmo_button_challenge2

namespace gf {

GfMenuObjButtonChallenge2::~GfMenuObjButtonChallenge2() {
    if (m_updater1.m_ctrl != nullptr) {
        ui::UICtrlManager::get()->delUpdater(m_updater1);
    }
    m_updater1.m_ctrl = nullptr;
    if (m_updater2.m_ctrl != nullptr) {
        ui::UICtrlManager::get()->delUpdater(m_updater2);
    }
    m_updater2.m_ctrl = nullptr;
    if (m_updater3.m_ctrl != nullptr) {
        ui::UICtrlManager::get()->delUpdater(m_updater3);
    }
    m_updater3.m_ctrl = nullptr;
}

void GfMenuObjButtonChallenge2::initialize() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    if (main.m_object != nullptr) {
        gmo_button_challenge2::dispPriority = ui::UIObjectAcc(m_handle).getDispPriority();
        ui::UIObjectAcc(m_handle).setAlpha(1.0f);
        GfMenuObject::attachExternalCall(0x4B, main.m_handle);
        {
#line 146
            MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(main.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        GfMenuObject::initialize();
        int count = main.countChild("LAY_challenge_v2@%02d", 1);
        {
        mm::mtl::FixStr<32> name;
        ui::UIObjectAcc(main.m_handle, "POL_ring_v2@01").getSize(true, m_ringSize, m_ringSize);
        ui::UIObjectAcc(main.m_handle, "POL_challenge_hit_a@01").getSize(true, m_hitSize, m_hitSize);
        for (int i = 0; i != count;) {
            i++;
            name.format("LAY_challenge_v2@%02d", i);
#line 163
            RingListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) RingListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(main.searchChild(name.m_str), listener);
            if (listener != nullptr) {
                listener->release();
            }
            name.format("IMG_challenge_btn_push_eff@%02d", i);
            ui::UIObjectAcc(main.m_handle, name.m_str).setIgnoreSize(true);
        }
        }
        ui::UIObjectAcc guide(main.m_handle, "LAY_guide_contents");
        GfMenuObjUtil::FitOption option;
        option.m_keepScaleY = true;
        GfMenuObjUtil::createFitPlugin(main.searchChild("IMG_guide_bg"), guide.m_handle, 0x18, 0, option);
        guide.getPosCenter(m_guidePos);
    }
}

void GfMenuObjButtonChallenge2::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjButtonChallenge2::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjButtonChallenge2::open(GfMenuCallContext* context, unsigned int id, bool flag0, bool flag1) {
    OpenParam param;
    importOpenParam(param, id);
    param.m_option.m_flag0 = flag0;
    param.m_option.m_flag1 = flag1;
    open(context, param, 0);
}

void GfMenuObjButtonChallenge2::open(GfMenuCallContext* context, unsigned int id, const OptionParam& option) {
    OpenParam param;
    importOpenParam(param, id);
    param.m_option = option;
    open(context, param, 0);
}

void GfMenuObjButtonChallenge2::openSequence(GfMenuCallContext* context, unsigned int id, bool flag0, bool flag1) {
    unsigned short challenge = Bdat::getVal(GfDataBdat::getFP(0xF9), "challenge01", id);
    if (challenge == 0) {
        return;
    }
    OpenParam param;
    importOpenParam(param, challenge);
    param.m_option.m_flag0 = flag0;
    param.m_option.m_flag1 = flag1;
    open(context, param, id);
}

void GfMenuObjButtonChallenge2::resume(GfMenuCallContext* context) {
    if (GfMenuObjUtil::checkCCNext(context, 0x4B)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x4B));
        if (acc.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x101;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjButtonChallenge2::close(GfMenuCallContext* context) {
    if (GfMenuObjUtil::checkCCNext(context, 0x4B)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x4B));
        if (acc.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x22;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjButtonChallenge2::setSpeedFactor(GfMenuCallContext* context, float factor) {
    if (GfMenuObjUtil::checkCCNext(context, 0x4B)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x4B));
        if (acc.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x102;
            event.m_param0Float = factor;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

bool GfMenuObjButtonChallenge2::seqStart() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    main.setDisp(true);
    m_score = 0;
    m_index = 0;
    pad_84 = 0;
    pad_88 = 0;
    pad_330.clear();
    m_speedFactor = 1.0f;
    GfMenuObject::enableInput(ui::UIObjectAcc(m_handle, "LAY_main").m_handle);
    pad_358 = false;
    m_resultSent = false;
    m_seq.addJob(&GfMenuObjButtonChallenge2::seqAppearCursor);
    return true;
}

void GfMenuObjButtonChallenge2::setupV2(const OpenParam& param) {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    mm::mtl::FixStr<32> name;
    if (m_param.m_buttons.empty()) {
        GfMenuObject::termCallContext(main.m_handle);
    } else {
        for (unsigned int i = 0; i < m_param.m_buttons.size(); i++) {
            name.format("LAY_challenge_v2@%02d", i + 1);
            GfMenuObject::sendOpenEvent(main.searchChild(name.m_str), i, 0.0f);
        }
        m_index = 0;
        pad_84 = 0;
        pad_498 = 0;
        pad_49C = 0;
        pad_490 = 0;
        pad_494 = 0.0f;
    }
}

bool GfMenuObjButtonChallenge2::seqClose() {
    if (pad_330.empty()) {
        ui::UIObjectAcc main(m_handle, "LAY_main");
        if (m_param.m_option.m_speed > 0.0f) {
            if (main.isDisp()) {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 2;
                param.m_time = m_param.m_option.m_speed;
                param.m_startFlags = 10;
                pad_330.push_back(GfMenuObjUtil::startCtrl(main.m_handle, param, nullptr));
            }
        } else {
            main.setDisp(false);
        }
    }
    for (unsigned int* it = pad_330.begin(); it != pad_330.end();) {
        if (GfMenuObjUtil::isBusyCtrl(*it)) {
            ++it;
        } else {
            it = pad_330.erase(it);
        }
    }
    return pad_330.empty();
}

bool GfMenuObjButtonChallenge2::seqEnd() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    main.setDisp(false);
    GfMenuObject::termCallContext(GfMenuObject::getAttachedObject(0x4B));
    return true;
}

void GfMenuObjButtonChallenge2::setRingScaleV2(unsigned int index, float scale) {
    mm::mtl::FixStr<32> name;
    name.format("POL_ring_v2@%02d", index + 1);
    ui::UIShape* shape;
    {
        ui::UIObjectAcc acc(m_handle, name.m_str);
        shape = acc.getShape();
        if (shape == nullptr || !shape->getRTTI()->isKindOf(&ui::UIShapeRing::m_rtti)) {
            return;
        }
    }
    static_cast<ui::UIShapeRing*>(shape)->setScale(scale);
}

void GfMenuObjButtonChallenge2::nextChallenge() {
    m_index++;
    if (m_index == m_param.m_buttons.size()) {
        if (!m_resultSent) {
            unsigned int handle = GfMenuObject::getAttachedObject(0x4B);
            unsigned int score = m_score;
            if (pad_90 != 0) {
                score = m_score / (pad_94 + 1);
            }
            GfMenuObject::addResultCallContext(handle, 2, score);
            m_resultSent = true;
        }
        m_seq.addJob(&GfMenuObjButtonChallenge2::seqCheckSequence);
    } else {
        setup(m_param, m_index, false);
        m_seq.addJob(&GfMenuObjButtonChallenge2::seqAppearCursor);
    }
}

bool GfMenuObjButtonChallenge2::seqAppearCursor() {
    if (m_param.m_option.m_flag0) {
        return false;
    }
    if (pad_330.empty()) {
        ui::UIObjectAcc challenge(m_handle, "LAY_challenge_v2@04");
        ui::UIShape* shape;
        {
            ui::UIObjectAcc acc(m_handle, "POL_ring_v2@04");
            shape = acc.getShape();
            if (shape == nullptr || !shape->getRTTI()->isKindOf(&ui::UIShapeRing::m_rtti)) {
                goto ringDone;
            }
        }
        static_cast<ui::UIShapeRing*>(shape)->setScale(1.0f);
    ringDone:
        challenge.setDispChild(true, "LAY_ring_v2@04");
        if (m_index == 0 && m_param.m_wait != 0) {
            GfMenuObjUtil::CtrlParam param;
            param.m_time = m_param.m_wait * (1.0f / 30.0f);
            param.m_methods = 1;
            param.m_curve = 1;
            pad_330.push_back(GfMenuObjUtil::startCtrl(challenge.m_handle, param, nullptr));
        } else {
            challenge.setDisp(true);
        }
        if (m_index < m_param.m_buttons.size() && m_param.m_buttons[m_index].m_inputType == 2) {
            ui::UIObjectAcc acc(m_handle, "POL_ring_v2@04");
            acc.setAlpha(0.0f);
        }
    }
    for (unsigned int* it = pad_330.begin(); it != pad_330.end();) {
        if (GfMenuObjUtil::isBusyCtrl(*it)) {
            ++it;
        } else {
            it = pad_330.erase(it);
        }
    }
    if (pad_330.begin() != pad_330.end()) {
        return false;
    }
    const Button& button = m_param.m_buttons[m_index];
    pad_35A = 0;
    switch (button.m_inputType) {
    case 1:
        m_seq.addJob(&GfMenuObjButtonChallenge2::seqMovePush);
        break;
    case 2:
        m_seq.addJob(&GfMenuObjButtonChallenge2::seqMoveMashing);
        break;
    }
    return true;
}

bool GfMenuObjButtonChallenge2::seqSuccess() {
    if (pad_330.empty()) {
        m_param.m_buttons[m_index];
        GfMenuObjUtil::CtrlParam param;
        param.m_time = 0.25f;
        param.m_methods = 2;
        param.m_startFlags = 10;
        pad_330.push_back(GfMenuObjUtil::startCtrl(m_handle, param, "LAY_challenge_v2@04"));
    }
    for (unsigned int* it = pad_330.begin(); it != pad_330.end();) {
        if (GfMenuObjUtil::isBusyCtrl(*it)) {
            ++it;
        } else {
            it = pad_330.erase(it);
        }
    }
    if (pad_330.begin() != pad_330.end()) {
        return false;
    }
    nextChallenge();
    return true;
}

bool GfMenuObjButtonChallenge2::seqFailed() {
    if (pad_330.empty()) {
        m_param.m_buttons[m_index];
        GfMenuObjUtil::CtrlParam param;
        param.m_time = 0.25f;
        param.m_methods = 2;
        param.m_startFlags = 10;
        pad_330.push_back(GfMenuObjUtil::startCtrl(m_handle, param, "LAY_challenge_v2@04"));
    }
    for (unsigned int* it = pad_330.begin(); it != pad_330.end();) {
        if (GfMenuObjUtil::isBusyCtrl(*it)) {
            ++it;
        } else {
            it = pad_330.erase(it);
        }
    }
    if (pad_330.begin() != pad_330.end()) {
        return false;
    }
    nextChallenge();
    return true;
}

bool GfMenuObjButtonChallenge2::seqWaitMashing() {
    if (pad_88 == 0 && m_index < m_param.m_buttons.size() && m_param.m_buttons[m_index].m_inputType == 2) {
        unsigned int wait = m_param.m_buttons[m_index].m_mashingTime;
        {
            ui::UIObjectAcc ring(m_handle, "LAY_ring_v2@04");
            ring.setDisp(false);
        }
        {
            ui::UIObjectAcc eff(m_handle, "IMG_challenge_btn_push_eff@04");
            eff.setDisp(true);
            eff.startAnimation("loop", false);
        }
        {
            ui::UIObjectAcc arw(m_handle, "IMG_challenge_btn_push_arw@04");
            arw.setDisp(true);
            arw.startAnimation("loop", false);
        }
        pad_88 = 1;
        pad_8C = wait;
    }
    if (pad_35A == 0 && pad_8C != 0) {
        pad_8C--;
        return false;
    }
    {
        ui::UIObjectAcc eff(m_handle, "IMG_challenge_btn_push_eff@04");
        eff.setDisp(false);
        eff.stopAnimation();
    }
    {
        ui::UIObjectAcc arw(m_handle, "IMG_challenge_btn_push_arw@04");
        arw.setDisp(false);
        arw.stopAnimation();
    }
    if (pad_35A == 1) {
        for (unsigned int* it = pad_330.begin(); it != pad_330.end(); ++it) {
            GfMenuObjUtil::stopCtrl(*it);
        }
        pad_330.clear();
        m_seq.addJob(&GfMenuObjButtonChallenge2::seqSuccess);
    } else {
        m_seq.addJob(&GfMenuObjButtonChallenge2::seqFailed);
    }
    pad_88 = 0;
    return true;
}

bool GfMenuObjButtonChallenge2::seqWaitRestartV2() {
    if (!pad_4A0) {
        return false;
    }
    setupV2(m_param);
    m_seq.addJob(&GfMenuObjButtonChallenge2::seqRunningV2);
    pad_4A0 = false;
    return true;
}

bool GfMenuObjButtonChallenge2::seqResultWait() {
    if (m_resultWait != 0) {
        m_resultWait--;
        return false;
    }
    if (pad_330.empty()) {
        ui::UIObjectAcc text(m_handle, "LAY_result_text");
        if (text.isDisp()) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_zoom";
            param.m_motion = "fade_out";
            param.m_setDefault = true;
            param.m_startFlags = 10;
            pad_330.push_back(GfMenuObjUtil::startCtrl(text.m_handle, param, nullptr));
        }
    }
    for (unsigned int* it = pad_330.begin(); it != pad_330.end();) {
        if (GfMenuObjUtil::isBusyCtrl(*it)) {
            ++it;
        } else {
            it = pad_330.erase(it);
        }
    }
    if (pad_330.begin() != pad_330.end()) {
        return false;
    }
    ui::UIObjectAcc result(m_handle, "LAY_result");
    result.setDisp(false);
    return true;
}

bool GfMenuObjButtonChallenge2::seqWaitMashingV2() {
    if (m_index < m_param.m_buttons.size()) {
        pad_490++;
        if (GfMenuManager::isBattleState(8)) {
            GfMenuReference::fn_71003673F0(1.0f - static_cast<float>(pad_498) / static_cast<float>(pad_490));
        }
        if (pad_490 < pad_498) {
            return false;
        }
        m_index++;
    }
    ui::UIObjectAcc main(m_handle, "LAY_challenge_v2");
    mm::mtl::FixStr<32> name;
    ui::EventData event;
    event.m_type = 0x104;
    for (unsigned int i = 0; i < m_param.m_buttons.size(); i++) {
        name.format("LAY_challenge_v2@%02d", i + 1);
        GfMenuObject::sendEvent(main.searchChild(name.m_str), event, 0.0f);
    }
    if (!m_resultSent) {
        unsigned int handle = GfMenuObject::getAttachedObject(0x4B);
        unsigned int score = m_score;
        if (pad_90 != 0) {
            score = m_score / (pad_94 + 1);
        }
        GfMenuObject::addResultCallContext(handle, 2, score);
        m_resultSent = true;
    }
    return true;
}

}  // namespace gf
