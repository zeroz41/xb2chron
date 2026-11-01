#include "classes/gf/GfMenuObjChainAttack.h"
#include "classes/gf/GfMenuObjArtsPalette.h"
#include "classes/gf/GfMenuObjBladeChange.h"
#include "classes/gf/GfMenuObjChainAttack/ExtendListener.h"
#include "classes/gf/GfMenuObjChainAttack/FullBurstListener.h"
#include "classes/gf/GfMenuObjChainAttack/StatusListener.h"
#include "classes/gf/GfMenuObjChainAttack.h"
#include "classes/gf/GfMenuObjChainAttack/ExtendListener.h"
#include "classes/gf/GfMenuObjChainAttack/ResultListener.h"
#include "classes/gf/GfMenuObjChainAttack/StartListener.h"
#include "classes/gf/GfMenuObjChainAttack/StartListener.h"
#include "classes/gf/GfMenuObjArtsPalette.h"
#include "classes/gf/GfMenuObjBladeChange.h"
#include "classes/gf/GfMenuObjChainCount/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuBattleAdapter.h"
#include "classes/gf/GfMenuGfObjAdapter.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfObjPropertyEnemy.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

#include <string.h>

namespace gf {

GfMenuObjChainAttack::GfMenuObjChainAttack(unsigned int handle)
    : GfMenuObject(handle), m_resLevel(), m_ovkStage(0) {}

GfMenuObjChainAttack::~GfMenuObjChainAttack() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjChainAttack::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (acc.m_object != nullptr) {
        GfMenuObject::attachExternalCall(0x54, acc.m_handle);
        {
            ui::UIObjectAcc start(acc.m_handle, "LAY_start");
#line 92
            StartListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) StartListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(start.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        {
            ui::UIObjectAcc status(acc.m_handle, "LAY_status");
#line 101
            StatusListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) StatusListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(status.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
            GfMenuBattleAdapter::create(status.searchChild("TXT_status_damage_num"), 0x10);
            GfMenuBattleAdapter::create(status.searchChild("TXT_status_damage_num_b"), 0x10);
            GfMenuObject::addNumberEventCondition(status.m_handle, "TXT_status_damage_num", 3, 0);
            GfMenuBattleAdapter* overkill = GfMenuBattleAdapter::create(status.searchChild("TXT_status_ovk_num"), 0x11);
            if (overkill != nullptr) {
                overkill->setNumberInterpolateMode(0.2f);
            }
            GfMenuObject::addNumberEventCondition(status.m_handle, "TXT_status_ovk_num", 4, 0);
            {
                mm::mtl::FixStr<32> name;
                for (int i = 0; i < 8; i++) {
                    name.format("IMG_status_elem_icon@%02d", i + 1);
                    GfMenuGfObjAdapter* adapter =
                        GfMenuGfObjAdapter::createFromTargetEnemy(status.searchChild(name.m_str), 0x1E, true);
                    if (adapter != nullptr) {
                        adapter->m_index = i;
                        GfMenuObject::addNumberEventCondition(status.m_handle, name.m_str, 2, i);
                        name.format("IMG_status_elem_base_dummy@%02d", i + 1);
                        adapter->m_rowHandle = status.searchChild(name.m_str);
                    }
                    name.format("IMG_status_elem_icon_eff@%02d", i + 1);
                    adapter = GfMenuGfObjAdapter::createFromTargetEnemy(status.searchChild(name.m_str), 0x1E, true);
                    if (adapter != nullptr) {
                        adapter->m_index = i;
                    }
                    name.format("LAY_status_elem_target@%02d", i + 1);
                    adapter = GfMenuGfObjAdapter::createFromTargetEnemy(status.searchChild(name.m_str), 0x1C, true);
                    if (adapter != nullptr) {
                        adapter->m_index = i;
                    }
                    GfMenuObject::addDispEventCondition(status.m_handle, name.m_str, 1, i, false);
                    name.format("TXT_status_elem_burst@%02d", i + 1);
                    adapter = GfMenuGfObjAdapter::createFromTargetEnemy(status.searchChild(name.m_str), 0x1D, true);
                    if (adapter != nullptr) {
                        adapter->m_index = i;
                    }
                    GfMenuObject::addDispEventCondition(status.m_handle, name.m_str, 0, i, false);
                }
            }
            {
                GfMenuObjUtil::FitOption option;
                option.m_keepScaleY = true;
                GfMenuObjUtil::createFitPlugin(status.searchChild("IMG_status_elem_base"),
                                               status.searchChild("LAY_status_elem_base"), 20, 0, option);
            }
            {
                ui::UIObjectAcc bar(status.m_handle, "IMG_status_gauge_bar");
                GfMenuBattleAdapter* gauge = GfMenuBattleAdapter::create(bar.m_handle, 0xD);
                if (gauge != nullptr) {
                    gauge->setNumberInterpolateMode(0.2f);
                }
                bar.setExtType(1);
                GfMenuObject::addNumberEventCondition(status.m_handle, "IMG_status_gauge_bar", 5, 0, 1.0f);
            }
        }
        {
            ui::UIObjectAcc result(acc.m_handle, "LAY_result");
#line 189
            ResultListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ResultListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(result.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
            GfMenuBattleAdapter::create(result.searchChild("TXT_result_total_damage_num"), 0x13);
            GfMenuBattleAdapter::create(result.searchChild("TXT_result_burst_num"), 0x14);
        }
        {
            ui::UIObjectAcc fullBurst(acc.m_handle, "LAY_full_burst");
#line 203
            FullBurstListener* listener =
                new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) FullBurstListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(fullBurst.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        {
            ui::UIObjectAcc extend(acc.m_handle, "LAY_extend");
#line 213
            ExtendListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ExtendListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(extend.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        {
            ui::UIObjectAcc overkillStart(acc.m_handle, "LAY_ovk_start");
#line 221
            GfMenuObjChainCount::MainListener* listener =
                new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuObjChainCount::MainListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(overkillStart.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        GfMenuObject::initialize();
    }
}

void GfMenuObjChainAttack::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjChainAttack::update() {
    GfMenuObject::update();
}

bool GfMenuObjChainAttack::isEnableSelect(unsigned int id, int select) {
    ui::UIObjectAcc acc(id);
    bool enable;
    if (strcmp(acc.getName(), "LAY_turn_sel") != 0) {
        enable = true;
    } else {
        enable = GfMenuReference::getReferenceNumber(select) == 0;
    }
    return enable;
}

void GfMenuObjChainAttack::openStart(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr && GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc start(acc.searchChild("LAY_start"));
        ui::EventData event;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(start.m_handle, event, 0.0f);
        GfMenuObject::startCallContext(context, 0x54, start.m_handle);
    }
}

void GfMenuObjChainAttack::openStatus(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc status(acc.searchChild("LAY_status"));
        ui::EventData event;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(status.m_handle, event, 0.0f);
        GfMenuObjArtsPalette::startChainAttack();
        GfMenuObjBladeChange::startChainAttack(context);
    }
}

void GfMenuObjChainAttack::closeStatus() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc status(acc.searchChild("LAY_status"));
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(status.m_handle, event, 0.0f);
        GfMenuObjArtsPalette::exitChainAttack();
        GfMenuObjBladeChange::exitChainAttack();
    }
}

void GfMenuObjChainAttack::openResult(const ResultParam& param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc result(acc.searchChild("LAY_result"));
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0Short = param.pad_0;
        event.m_param1 = param.pad_4;
        GfMenuObject::sendEvent(result.m_handle, event, 0.0f);
    }
}

void GfMenuObjChainAttack::closeResult() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc result(acc.searchChild("LAY_result"));
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(result.m_handle, event, 0.0f);
    }
}

void GfMenuObjChainAttack::openFullBurst(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr && GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc burst(acc.searchChild("LAY_full_burst"));
        ui::EventData event;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(burst.m_handle, event, 0.0f);
        GfMenuObject::startCallContext(context, 0x54, burst.m_handle);
    }
}

void GfMenuObjChainAttack::openRoundExtend() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc extend(acc.searchChild("LAY_extend"));
        ui::EventData event;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(extend.m_handle, event, 0.0f);
    }
}

void GfMenuObjChainAttack::closeRoundExtend() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc extend(acc.searchChild("LAY_extend"));
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(extend.m_handle, event, 0.0f);
    }
}

void GfMenuObjChainAttack::changeCharacter(unsigned int character) {
    GfMenuObjUtil::playSE(0x34);
}

void GfMenuObjChainAttack::fn_71003BF974(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    ui::UIObjectAcc start(acc.searchChild("LAY_ovk_start"));
    ui::EventData event;
    event.m_type = 0x21;
    GfMenuObject::sendEvent(start.m_handle, event, 0.0f);
    if (context != nullptr && GfMenuObjUtil::checkCCStart(context)) {
        GfMenuObject::startCallContext(context, 0x54, start.m_handle);
    }
}

void GfMenuObjChainAttack::StartListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::termCallContext(acc.m_handle);
        }
        break;
    case 0x21: {
        ui::UIObjectAcc base(acc.m_handle, "IMG_start_base");
        base.startAnimationFromID(1, false);
        GfMenuObject::hookAnimationEvent(acc.m_handle, base.m_handle, 0);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_r";
        param.m_setDefault = true;
        param.m_startFlags = 8;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, "TXT_start_caption");
        GfMenuObjUtil::playSE(0x33);
        acc.setDisp(true);
        break;
    }
    case 0xC: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_l";
        param.m_setDefault = true;
        param.m_startFlags = 10;
        param.m_eventId = 1;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        break;
    }
    }
}

void GfMenuObjChainAttack::StatusListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        m_state = 0;
        m_ovkShown = 0;
        acc.setDisp(false);
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            m_state = 1;
            GfMenuObject::termCallContext(acc.m_handle);
        } else if (event.m_param0 == 2) {
            ui::UIObjectAcc text(acc.m_handle, "LAY_status_ovk_text");
            if (GfMenuObjUtil::getCtrlID(text.m_handle) != -1) {
                GfMenuObjUtil::stopCtrl(GfMenuObjUtil::getCtrlID(text.m_handle));
            }
        }
        break;
    case 0x21: {
        {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_l";
            param.m_time = GfMenuObjUtil::getParamMenu()->m_chainAttackWait;
            param.m_eventId = 1;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        }
        if (GfMenuManager::getTargetObjHandle() != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            GfObjAcc obj(GfMenuManager::getTargetObjHandle());
            if (obj.m_obj == nullptr) {
                break;
            }
            GfObjProperty* property = GfObjUtil::getProperty(GfMenuManager::getTargetObjHandle());
            if (property == nullptr) {
                break;
            }
            GfObjPropertyEnemy* enemy = property->getEnemy();
            if (enemy == nullptr) {
                break;
            }
            for (int i = 0; i < 9; i++) {
                m_owner->m_resLevel[i] = enemy->m_resAttrs[i].m_level;
            }
            mm::Rect<short> center;
            mm::Rect<short> range;
            acc.getLayoutRect("elem2_center", center);
            acc.getLayoutRect("elem2_center_range", range);
            GfMenuObjUtil::placeObjectH(acc.m_handle, "LAY_status_elem@%02d", enemy->m_resAttrList.size(),
                                        mm::Pnt<short>(center.x + center.w / 2, center.y + center.h / 2),
                                        range.x - center.x);
            GfMenuObjUtil::placeObjectH(acc.m_handle, "IMG_status_elem_base_dummy@%02d", enemy->m_resAttrList.size(),
                                        mm::Pnt<short>(center.x + center.w / 2, center.y + center.h / 2),
                                        range.x - center.x);
            acc.setDispChild(static_cast<unsigned int>(enemy->m_resAttrList.size()) != 0, "IMG_status_elem_base");
        }
        for (int& level : m_owner->m_resLevel) {
            level = 3;
        }
        m_owner->m_ovkStage = 0;
        m_ovkShown = 0;
        acc.setDispChild(false, "LAY_status_ovk");
        break;
    }
    case 0x22: {
        {
            mm::mtl::FixStr<32> name;
            for (int i = 1; i < 9; i++) {
                name.format("IMG_status_elem_target@%02d", i);
                ui::UIObjectAcc(acc.m_handle, name.m_str).stopAnimation();
                name.format("IMG_status_elem_burst@%02d", i);
                ui::UIObjectAcc(acc.m_handle, name.m_str).stopAnimation();
            }
            ui::UIObjectAcc bar(acc.m_handle, "IMG_status_gauge_bar");
            int ctrl = GfMenuObjUtil::getCtrlID(bar.m_handle);
            if (ctrl != -1) {
                GfMenuObjUtil::stopCtrl(ctrl);
            }
        }
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_l";
        param.m_startFlags = 10;
        param.m_eventId = 2;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        m_state = 0;
        break;
    }
    case 0xD: {
        // the condition's event and the element's index; m_param1 picks the update and m_param3 is its value (the
        // names are not the original's)
        int type = event.m_param0;
        unsigned int index = event.m_param2;
        switch (event.m_param1) {
        case 0: {
            mm::mtl::FixStr<32> name;
            name.format("TXT_status_elem_burst@%02d", index + 1);
            if (type == 5) {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "cmn_fade_emotion";
                param.m_motion = "fade_in";
                param.m_setDefault = true;
                GfMenuObjUtil::startCtrl(acc.m_handle, param, name.m_str);
            } else {
                acc.setDispChild(false, name.m_str);
            }
            break;
        }
        case 1: {
            mm::mtl::FixStr<32> name;
            name.format("IMG_status_elem_icon_eff@%02d", index + 1);
            int ctrl = GfMenuObjUtil::getCtrlID(acc.searchChild(name.m_str));
            if (ctrl != -1) {
                GfMenuObjUtil::stopCtrl(ctrl);
            }
            if (type == 5) {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x40002;
                param.m_scale = 0.3f;
                param.m_reserve = true;
                param.m_curve = 1;
                param.m_time = 1.0f;
                param.m_startFlags = 8;
                GfMenuObjUtil::startCtrl(acc.m_handle, param, name.m_str);
            } else {
                acc.setDispChild(false, name.m_str);
            }
            break;
        }
        case 2: {
            int value = event.m_param3;
            if (m_state != 0 && GfMenuManager::getTargetObjHandle() != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                GfObjAcc obj(GfMenuManager::getTargetObjHandle());
                if (obj.m_obj != nullptr) {
                    GfObjProperty* property = GfObjUtil::getProperty(GfMenuManager::getTargetObjHandle());
                    if (property != nullptr) {
                        GfObjPropertyEnemy* enemy = property->getEnemy();
                        if (type == 4 && enemy != nullptr && enemy->m_resAttrList.size() > index) {
                            unsigned int element = enemy->m_resAttrList[index];
                            if (element != 0) {
                                int level = element * 4 - (value + 1);
                                if (level < 0) {
                                    level = 0;
                                }
                                int down = m_owner->m_resLevel[element] - level;
                                if (down >= 1) {
                                    mm::mtl::FixStr<32> name;
                                    name.format("IMG_status_elem_eff@%02d", index + 1);
                                    if (down == 1) {
                                        ui::UIObjectAcc(acc.m_handle, name.m_str).startAnimation("damage_a", false);
                                    } else {
                                        ui::UIObjectAcc(acc.m_handle, name.m_str).startAnimation("damage_b", false);
                                    }
                                    name.format("LAY_status_elem@%02d", index + 1);
                                    GfMenuObjUtil::CtrlParam param;
                                    param.m_methods = 0x10000000;
                                    param.m_motionLib = "cmn_damage";
                                    param.m_motion = "fadein";
                                    param.m_setDefault = true;
                                    param.m_startFlags = 8;
                                    GfMenuObjUtil::startCtrl(acc.m_handle, param, name.m_str);
                                    m_owner->m_resLevel[element] = level;
                                }
                            }
                        }
                    }
                }
            }
            break;
        }
        case 3: {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_l";
            param.m_setDefault = true;
            param.m_startFlags = 8;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, "TXT_status_damage_num");
            param = GfMenuObjUtil::CtrlParam();
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_levelup_text_fadein_blur";
            param.m_motion = "fade_in";
            param.m_setDefault = true;
            param.m_startFlags = 8;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_status_damage_num_eff");
            break;
        }
        case 4: {
            static const int thresholds[6] = {400, 500, 600, 700, 800, 900};
            // the flag is read before the value: the original tests it first
            bool shown = m_ovkShown != 0;
            int value = event.m_param3;
            if (!shown && value >= 1 && m_owner->m_ovkStage == 0) {
                ui::UIObjectAcc ovk(acc.m_handle, "LAY_status_ovk");
                ui::UIObjectAcc text(acc.m_handle, "LAY_status_ovk_text");
                ovk.setDisp(true);
                text.setAddColor("black");
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x40000000;
                param.m_bright = 1.0f;
                param.m_time = 0.5f;
                param.m_curve = 4;
                param.m_setDefault = true;
                param.m_reserve = true;
                GfMenuObjUtil::startCtrl(ovk.m_handle, param, "LAY_status_ovk_text");
                m_ovkShown = 1;
            }
            unsigned int stage = m_owner->m_ovkStage;
            if (stage < 6 && value >= thresholds[stage]) {
                m_owner->m_ovkStage = stage + 1;
                ui::UIObjectAcc eff(acc.m_handle, "IMG_status_ovk_eff");
                eff.startAnimation("start", false);
            }
            break;
        }
        case 5:
            if (type == 1) {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x40000000;
                param.m_time = 1.0f;
                param.m_reserve = true;
                param.m_curve = 4;
                param.m_startFlags = 8;
                param.m_bright = 1.0f;
                GfMenuObjUtil::startCtrl(acc.searchChild("IMG_status_gauge_bar"), param, nullptr);
                GfMenuObjUtil::playSE(0x26);
            } else {
                ui::UIObjectAcc bar(acc.m_handle, "IMG_status_gauge_bar");
                int ctrl = GfMenuObjUtil::getCtrlID(bar.m_handle);
                if (ctrl != -1) {
                    GfMenuObjUtil::stopCtrl(ctrl);
                }
            }
            break;
        }
        break;
    }
    }
}

void GfMenuObjChainAttack::ResultListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_state = 0;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 0xB:
        GfMenuObjChainAttack::closeResult();
        break;
    case 0xC:
        // the open event's time, kept in hundredths in the state field until the open finishes
        GfMenuObject::registTimer(acc.m_handle, 0, m_state / 100.0f, false);
        break;
    case 0x21:
        if (m_state == 0) {
            float time = event.m_param1Float;
            ui::UIObjectAcc bg(acc.m_handle, "IMG_result_info_bg");
            bg.startAnimationFromID(1, false);
            GfMenuObject::hookAnimationEvent(acc.m_handle, bg.m_handle, 0);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_r";
            param.m_setDefault = true;
            param.m_startFlags = 8;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_result_info");
            acc.setDisp(true);
            m_state = time * 100.0f;
            GfMenuObjUtil::playJingle(0xE);
            m_state = 1;
        }
        break;
    case 0x22:
        if (m_state == 1) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 2;
            param.m_time = 0.25f;
            param.m_startFlags = 10;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            GfMenuObject::releaseTimer(acc.m_handle);
            m_state = 0;
        }
        break;
    }
}

void GfMenuObjChainAttack::FullBurstListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            acc.setDisp(false);
        }
        break;
    case 0x21: {
        ui::UIObjectAcc base(acc.m_handle, "IMG_full_burst_base");
        base.startAnimation("fadein", false);
        GfMenuObject::hookAnimationEvent(acc.m_handle, base.m_handle, 0);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "mnu065_fb_base";
        param.m_motion = "fadein";
        param.m_setDefault = true;
        param.m_startFlags = 10;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, "TXT_full_burst");
        param = GfMenuObjUtil::CtrlParam();
        param.m_methods = 0x10000000;
        param.m_motionLib = "mnu065_fb_base_hilight";
        param.m_motion = "fadein";
        param.m_setDefault = true;
        param.m_startFlags = 10;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, "TXT_full_burst_eff");
        {
            ui::UIObjectAcc bg(acc.m_handle, "IMG_full_burst_bg");
            bg.setAlpha(0.0f);
            param = GfMenuObjUtil::CtrlParam();
            param.m_methods = 1;
            param.m_time = GfMenuObjUtil::getCtrlMotionTime("mnu065_fb_base", "fadein") * 0.5f;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, "IMG_full_burst_bg");
        }
        acc.setDisp(true);
        break;
    }
    case 0xC: {
        GfMenuObject::termCallContext(acc.m_handle);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = 0.2f;
        param.m_startFlags = 10;
        param.m_eventId = 1;
        int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "IMG_full_burst_bg");
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        break;
    }
    }
}

void GfMenuObjChainAttack::ExtendListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_state = 0;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        break;
    case 0x21:
        if (m_state == 0) {
            acc.setDisp(true);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_l_early";
            param.m_setDefault = true;
            param.m_eventId = 1;
            param.m_startFlags = 8;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_state = 1;
        }
        break;
    case 0x22:
        if (m_state == 1) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_r_early";
            param.m_setDefault = true;
            param.m_eventId = 2;
            param.m_startFlags = 10;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_state = 0;
        }
        break;
    }
}


void GfMenuObjChainCount::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_state = 0;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 2) {
            GfMenuObject::termCallContext(acc.m_handle);
        }
        break;
    case 0xC:
        GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
        break;
    case 0x21:
        if (m_state == 0) {
            acc.setDisp(true);
            {
                ui::UIObjectAcc base(acc.m_handle, "IMG_ovk_start_base");
                base.startAnimation("start", false);
                GfMenuObject::hookAnimationEvent(acc.m_handle, base.m_handle, 0);
            }
            {
                ui::UIObjectAcc text(acc.m_handle, "TXT_ovk_start");
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "cmn_fade_motion_lr";
                param.m_eventId = 1;
                param.m_motion = "fade_in_l";
                param.m_setDefault = true;
                param.m_startFlags = 8;
                GfMenuObjUtil::startCtrl(text.m_handle, param, nullptr);
            }
            m_state = 1;
        }
        break;
    case 0x22:
        if (m_state == 1) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_l";
            param.m_setDefault = true;
            param.m_eventId = 2;
            param.m_startFlags = 10;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_state = 0;
        } else {
            GfMenuObject::termCallContext(acc.m_handle);
        }
        break;
    }
}

}  // namespace gf
