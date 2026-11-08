#include "classes/gf/GfMenuObjEnemyStatus.h"
#include "classes/gf/GfMenuObjEnemyStatus/MainListener.h"
#include "classes/gf/GfMenuObjEnemyStatus/ElemListener.h"
#include "classes/gf/GfMenuObjEnemyStatus.h"
#include "classes/gf/GfMenuObjEnemyStatus/MainListener.h"
#include "classes/gf/GfMenuObjEnemyStatus/ElemListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuGfObjAdapter.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObjPropertyEnemy.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"
#include "mm/mtl/FixStr.h"
#include "mm/Rect.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjEnemyStatus::GfMenuObjEnemyStatus(unsigned int handle)
    : GfMenuObject(handle), m_target(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_adapters(), m_suspendCtrl(-1),
      m_seq(this) {}

GfMenuObjEnemyStatus::~GfMenuObjEnemyStatus() {}

void GfMenuObjEnemyStatus::initialize() {
    // hands an adapter to m_adapters, while there is room (update passes each new target on to them)
    auto add = [this](TUnk_B5C118* adapter) {
        if (adapter != nullptr && m_adapters.m_list.size() != m_adapters.m_list.capacity()) {
            m_adapters.m_list.push_back(adapter);
        }
    };
    GF_OBJ_HANDLE* none = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    ui::UIObjectAcc root(m_handle);
    GfMenuObject::attachExternalCall(0x14, m_handle);
    unsigned int main = root.searchChild("LAY_main");
    bool exists = ui::UIObjectAcc(main).m_object != nullptr;
    if (exists) {
        GfMenuObject::attachExternalCall(0x10, main);
        GfMenuObject::attachExternalCall(0x15, main);
#line 106
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(main, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc bg(root.searchChild("IMG_bg"));
        GfMenuGfObjAdapter* bgAdapter = GfMenuGfObjAdapter::create(bg.m_handle, 0x20, none, true);
        if (bgAdapter != nullptr) {
            add(bgAdapter);
        }
    }
    {
        ui::UIObjectAcc gauge(root.searchChild("IMG_hpgauge"));
        if (gauge.m_object != nullptr) {
            GfMenuGfObjAdapter* hp = GfMenuGfObjAdapter::create(gauge.m_handle, 0, none, true);
            if (hp != nullptr) {
                hp->setNumberInterpolateMode(0.25f);
                add(hp);
            }
            add(GfMenuGfObjAdapter::create(gauge.m_handle, 1, none, true));
            gauge.setExtType(1);
        }
    }
    add(GfMenuGfObjAdapter::create(root.searchChild("IMG_acticon"), 0xB, none, true));
    {
        ui::UIObjectAcc link(root.searchChild("IMG_linkicon"));
        if (link.m_object != nullptr) {
            add(GfMenuGfObjAdapter::create(link.m_handle, 0xC, none, true));
            link.setImageIndex(1);
        }
    }
    add(GfMenuGfObjAdapter::create(root.searchChild("TXT_lv"), 7, none, true));
    add(GfMenuCharDataAdapter::createFromGfObj(root.searchChild("TXT_name"), 2, none, false));
    GfMenuGfObjAdapter* arts = GfMenuGfObjAdapter::create(root.searchChild("LAY_arts_name"), 9, none, true);
    if (arts != nullptr) {
        add(arts);
    }
    GfMenuObject::addNumberEventCondition(main, "LAY_arts_name", 5, 0);
    {
        ui::UIObjectAcc elem(root.m_handle, "LAY_elem2");
#line 182
        ElemListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ElemListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(elem.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        add(GfMenuGfObjAdapter::create(elem.m_handle, 0x14, none, true));
        GfMenuObject::addDispEventCondition(elem.m_handle, nullptr, 1, 0, false);
        add(GfMenuGfObjAdapter::create(elem.searchChild("TXT_elem_eff"), 0xA, none, true));
        add(GfMenuGfObjAdapter::create(elem.searchChild("IMG_elem_lv_icon"), 0x15, none, true));
        add(GfMenuGfObjAdapter::create(elem.searchChild("IMG_elem_lv_icon_base"), 0x15, none, true));
        {
            ui::UIObjectAcc time(elem.m_handle, "IMG_elem_time");
            add(GfMenuGfObjAdapter::create(time.m_handle, 0x13, none, true));
            add(GfMenuGfObjAdapter::create(time.m_handle, 0x16, none, true));
            time.setExtType(2);
        }
        {
            ui::UIObjectAcc suspend(elem.m_handle, "IMG_elem_time_suspend");
            add(GfMenuGfObjAdapter::create(suspend.m_handle, 0x13, none, true));
            suspend.setExtType(2);
            add(GfMenuGfObjAdapter::create(elem.searchChild("LAY_elem_time_suspend"), 0x18, none, true));
            GfMenuObject::addDispEventCondition(elem.m_handle, "LAY_elem_time_suspend", 2, 0, false);
        }
        {
            ui::UIObjectAcc debuff(root.m_handle, "LAY_debuff");
            debuff.setDisp(false);
        }
    }
    add(GfMenuGfObjAdapter::create(root.searchChild("IMG_infoicon"), 4, none, true));
    add(GfMenuGfObjAdapter::create(root.searchChild("IMG_reaction_icon"), 0xE, none, true));
    add(GfMenuGfObjAdapter::create(root.searchChild("IMG_reaction_icon_eff"), 0xE, none, true));
    GfMenuObject::addNumberEventCondition(main, "IMG_reaction_icon", 3, 0);
    GfMenuObject::addDispEventCondition(main, "IMG_reaction_icon", 3, 0, false);
    add(GfMenuGfObjAdapter::create(root.searchChild("TXT_reaction"), 0xF, none, true));
    add(GfMenuGfObjAdapter::create(root.searchChild("IMG_reaction_gauge"), 0x10, none, true));
    ui::UIObjectAcc(root.searchChild("IMG_reaction_gauge")).setExtType(1);
    {
        ui::UIObjectAcc suspend(root.m_handle, "IMG_reaction_time_suspend");
        add(GfMenuGfObjAdapter::create(suspend.m_handle, 0x10, none, true));
        suspend.setExtType(1);
        add(GfMenuGfObjAdapter::create(root.searchChild("LAY_reaction_time_suspend"), 0x11, none, true));
        GfMenuObject::addDispEventCondition(main, "LAY_reaction_time_suspend", 4, 0, false);
    }
    GfMenuObjUtil::createFollowDispPlugin(root.searchChild("LAY_reaction"), root.searchChild("IMG_reaction_icon"));
    {
        ui::UIObjectAcc state(root.m_handle, "LAY_state");
        GfMenuGfObjAdapter* weak =
            GfMenuGfObjAdapter::create(root.searchChild("IMG_state_weak_elem_icon"), 0x19, none, true);
        weak->m_rowHandle = root.searchChild("LAY_state_weak_elem");
        add(weak);
        if (state.searchChild("LAY_state_angry") != 0) {
            GfMenuGfObjAdapter* angry =
                GfMenuGfObjAdapter::create(root.searchChild("IMG_state_angry_icon"), 0x22, none, true);
            angry->m_rowHandle = root.searchChild("LAY_state_angry");
            add(angry);
        }
        if (GfMenuObjUtil::isValidExpansion(1) || GfMenuObjUtil::isValidExpansion(3)) {
            if (state.searchChild("LAY_state_awake") != 0) {
                GfMenuGfObjAdapter* awake =
                    GfMenuGfObjAdapter::create(root.searchChild("IMG_state_awake"), 0x23, none, true);
                awake->m_rowHandle = root.searchChild("LAY_state_awake");
                add(awake);
            }
            GfMenuObject::addDispEventCondition(main, "IMG_state_awake", 7, 0, false);
        }
    }
    {
        ui::UIObjectAcc combo(root.m_handle, "LAY_combo_debuff");
        GfMenuGfObjAdapter* debuff = GfMenuGfObjAdapter::create(combo.m_handle, 0x1F, none, true);
        if (debuff != nullptr) {
            add(debuff);
        }
        combo.setDisp(false);
        GfMenuObject::addNumberEventCondition(main, "LAY_combo_debuff", 6, 0);
    }
    ui::UIObjectAcc elem(m_handle, "LAY_elem");
    if (elem.m_object != nullptr) {
        elem.setDisp(false);
    }
    GfMenuObject::initialize();
}

void GfMenuObjEnemyStatus::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjEnemyStatus::update() {
    GF_OBJ_HANDLE* target = GfMenuManager::getTargetObjHandle();
    if (m_target != target) {
        for (unsigned int i = 0; i < m_adapters.m_list.size(); i++) {
            m_adapters.m_list[i]->changeGfObj(target);
        }
        {
            ui::UIObjectAcc acc(m_handle, "LAY_main");
            GfObjAcc obj(m_target);
            ui::EventData event;
            event.m_type = 0x10A;
            event.m_param0 = m_target == reinterpret_cast<GF_OBJ_HANDLE*>(-1) ? true : obj.getType() != 5;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
        m_target = target;
    }
    m_seq.update();
    if (GfMenuObjUtil::isValidExpansion(1)) {
        bool battle = GfMenuManager::isBattleState(8);
        ui::UIObjectAcc acc(m_handle, "LAY_arts_name");
        acc.setAlpha(battle ? 0.0f : 1.0f);
    }
    GfMenuObject::update();
}

void GfMenuObjEnemyStatus::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 0x100:
        acc.setDisp(true);
        break;
    case 0x101:
        acc.setDisp(false);
        break;
    case 0x103: {
        ui::UIObjectAcc elem(acc.searchDuplicatedChild("IMG_elem", event.m_paramShort[0]));
        if (elem.m_object != nullptr) {
            acc.setLayout(elem.m_handle, "elem_start");
            GfMenuObjEnemyStatus::fn_71003F98A4(acc.m_handle, elem.m_handle, event.m_paramShort[1]);
            elem.setImageIndex(event.m_paramShort[2]);
        }
        break;
    }
    case 0x104: {
        ui::UIObjectAcc elem(acc.searchDuplicatedChild("IMG_elem", event.m_paramShort[0]));
        if (elem.m_object != nullptr) {
            GfMenuObjUtil::CtrlParam param;
            param.m_time = 0.5f;
            param.m_methods = 0x42;
            param.m_curve = 1;
            param.m_startFlags = 1;
            param.m_distance = 0x20;
            GfMenuObjUtil::startCtrl(elem.m_handle, param, nullptr);
            GfMenuObject::termCallContext(elem.m_handle);
        }
        break;
    }
    case 0x105: {
        ui::UIObjectAcc elem(acc.searchDuplicatedChild("IMG_elem", event.m_paramShort[0]));
        if (elem.m_object != nullptr) {
            GfMenuObjEnemyStatus::fn_71003F98A4(acc.m_handle, elem.m_handle, event.m_paramShort[1]);
        }
        break;
    }
    case 0x10A:
        if (event.m_param0 == 1) {
            ui::UIObjectAcc eff(acc.m_handle, "IMG_lv_name_eff");
            eff.startAnimation("start", false);
        }
        break;
    case 1: {
        ui::UIObjectAcc arts(acc.m_handle, "LAY_arts_name");
        arts.setDisp(false);
        m_state.m_open = 0;
        m_state.m_labelCtrl = -1;
        m_state.m_pulseCtrl = -1;
        acc.setDisp(false);
        break;
    }
    case 3:
        if (event.m_param0 == 1) {
            ui::UIObjectAcc eff(acc.m_handle, "IMG_reaction_icon_eff");
            eff.setAlpha(1.0f);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "pulse";
            param.m_motion = "pulse";
            param.m_reserve = true;
            param.m_slot = m_state.m_pulseCtrl;
            param.m_setDefault = true;
            param.m_startFlags = 4;
            m_state.m_pulseCtrl = GfMenuObjUtil::startCtrl(eff.m_handle, param, nullptr);
        }
        break;
    case 0xC:
        if (m_state.m_open != 1) {
            ui::UIObjectAcc arts(acc.m_handle, "LAY_arts_name");
            arts.setDisp(false);
        }
        break;
    case 0xD: {
        int value = event.m_param0;
        int kind = event.m_param1;
        int param3 = event.m_param3;
        switch (kind) {
        case 4: {
            ui::UIObjectAcc suspend(acc.m_handle, "LAY_reaction_time_suspend");
            if (value == 5) {
                suspend.setDisp(true);
                suspend.setAlpha(0.0f);
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 4;
                param.m_time = 0.5f;
                param.m_alpha = 1.0f;
                param.m_reserve = true;
                param.m_curve = 3;
                GfMenuObjUtil::startCtrl(suspend.m_handle, param, nullptr);
            } else {
                int ctrl = GfMenuObjUtil::getCtrlID(suspend.m_handle);
                if (ctrl != -1) {
                    GfMenuObjUtil::stopCtrl(ctrl);
                    suspend.setDisp(false);
                }
            }
            break;
        }
        case 5: {
            ui::UIObjectAcc arts(acc.m_handle, "LAY_arts_name");
            if (param3 == 0) {
                if (m_state.m_open == 1) {
                    {
                        ui::UIObjectAcc text(acc.m_handle, "TXT_artsname");
                        text.setDisp(false);
                    }
                    {
                        ui::UIObjectAcc base(acc.m_handle, "IMG_arts_base");
                        base.startAnimation("out", false);
                        GfMenuObject::hookAnimationEvent(acc.m_handle, base.m_handle, 0);
                    }
                    m_state.m_open = 0;
                }
            } else {
                ui::UIStr name;
                GfObjProperty* property = GfObjUtil::getProperty(m_owner->m_target);
                if (property != nullptr) {
                    GfObjPropertyEnemy* enemy = property->getEnemy();
                    if (enemy != nullptr && enemy->m_artsNameId != 0 && enemy->m_artsNameBdat != nullptr) {
                        name.setupMstxt(enemy->m_artsNameBdat, enemy->m_artsNameId);
                    }
                }
                if (name.isValid()) {
                    arts.setDisp(true);
                    m_state.m_open = 1;
                    {
                        ui::UIObjectAcc text(acc.m_handle, "TXT_artsname");
                        text.setText(name);
                        text.setDisp(true);
                        GfMenuObjUtil::CtrlParam param;
                        param.m_methods = 0x10000000;
                        param.m_motionLib = "cmn_fade_emotion";
                        param.m_motion = "fade_in_select";
                        param.m_setDefault = true;
                        GfMenuObjUtil::startCtrl(text.m_handle, param, nullptr);
                    }
                    {
                        ui::UIObjectAcc base(acc.m_handle, "IMG_arts_base");
                        base.startAnimation("in", false);
                    }
                } else {
                    arts.setDisp(false);
                }
            }
            break;
        }
        case 6: {
            ui::UIObjectAcc combo(acc.m_handle, "LAY_combo_debuff");
            if (param3 == 0) {
                if (combo.isDisp()) {
                    GfMenuObjUtil::CtrlParam param;
                    param.m_methods = 2;
                    param.m_time = 0.2f;
                    param.m_startFlags = 10;
                    GfMenuObjUtil::startCtrl(combo.m_handle, param, nullptr);
                }
            } else {
                ui::UIObjectAcc text(combo.m_handle, "TXT_combo_debuff");
                unsigned char id = Bdat::getVal(Bdat::getFP("BTL_ElementalEffect"), "Name", param3);
                if (id != 0) {
                    {
                        ui::UIStr str(Bdat::getFP("btl_elementaleffect_ms"), id);
                        text.setText(str);
                    }
                    ui::UIObjectAcc eff(combo.m_handle, "IMG_combo_debuff_eff");
                    eff.startAnimation("fade_in", false);
                }
                combo.setDisp(true);
                combo.setAlpha(1.0f);
            }
            break;
        }
        case 3:
            if (acc.isDisp()) {
                {
                    ui::UIObjectAcc reaction(acc.m_handle, "LAY_reaction");
                    reaction.setAddColor("white");
                    GfMenuObjUtil::CtrlParam param;
                    param.m_methods = 0x4000000;
                    param.m_time = 0.5f;
                    param.m_color = GfMenuObjUtil::getPresetColor("black");
                    GfMenuObjUtil::startCtrl(reaction.m_handle, param, nullptr);
                }
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "fadein";
                param.m_motion = "label";
                param.m_eventId = 1;
                param.m_slot = m_state.m_labelCtrl;
                param.m_setDefault = true;
                param.m_startFlags = 4;
                int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "IMG_reaction_icon");
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
                m_state.m_labelCtrl = ctrl;
                if (m_state.m_pulseCtrl != -1) {
                    ui::UIObjectAcc(acc.m_handle, "IMG_reaction_icon_eff").setAlpha(0.0f);
                    GfMenuObjUtil::suspendCtrl(m_state.m_pulseCtrl);
                }
                if (value == 4 || value == 5) {
                    GfMenuObjUtil::playSE(0x2E);
                }
            }
            break;
        default:
            if ((GfMenuObjUtil::isValidExpansion(1) || GfMenuObjUtil::isValidExpansion(3)) && kind == 7) {
                ui::UIObjectAcc awake(acc.m_handle, "IMG_state_awake");
                m_owner->m_seq.clear();
                if (value == 5) {
                    m_owner->m_seq.addAnimJob(awake.m_handle, "start");
                    m_owner->m_seq.addAnimJob(awake.m_handle, "loop");
                } else {
                    awake.stopAnimation();
                }
            }
            break;
        }
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjEnemyStatus::fn_71003F98A4(unsigned int layout, unsigned int handle, int index) {
    ui::UIObjectAcc acc(layout);
    ui::UIObjectAcc obj(handle);
    if (acc.m_object != nullptr && obj.m_object != nullptr) {
        mm::mtl::FixStr<16> name;
        name.format("elem_%02d", index);
        mm::Rect<short> rect;
        if (acc.getLayoutRect(name.m_str, rect)) {
            GfMenuObjUtil::CtrlParam param;
            param.m_time = 0.25f;
            param.m_methods = 0x80;
            param.m_curve = 1;
            param.m_pos[0] = rect.x;
            param.m_pos[1] = rect.y;
            GfMenuObjUtil::startCtrl(obj.m_handle, param, nullptr);
        }
    }
}

void GfMenuObjEnemyStatus::ElemListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 0xD: {
            int value = event.m_param0;
            if (event.m_param1 == 1) {
                if (value == 5) {
                    acc.setAddColor("white");
                    GfMenuObjUtil::CtrlParam param;
                    param.m_methods = 0x4000000;
                    param.m_time = 0.5f;
                    param.m_color = GfMenuObjUtil::getPresetColor("black");
                    GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
                }
            } else if (event.m_param1 == 2) {
                ui::UIObjectAcc suspend(acc.m_handle, "LAY_elem_time_suspend");
                if (value == 5) {
                    suspend.setDisp(true);
                    suspend.setAlpha(0.0f);
                    GfMenuObjUtil::CtrlParam param;
                    param.m_methods = 4;
                    param.m_time = 0.5f;
                    param.m_alpha = 1.0f;
                    param.m_reserve = true;
                    param.m_curve = 3;
                    m_owner->m_suspendCtrl = GfMenuObjUtil::startCtrl(suspend.m_handle, param, nullptr);
                } else if (m_owner->m_suspendCtrl != -1) {
                    GfMenuObjUtil::stopCtrl(m_owner->m_suspendCtrl);
                    m_owner->m_suspendCtrl = -1;
                    suspend.setDisp(false);
                }
            }
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjEnemyStatus::open(const OpenParam& param) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x10);
    bool exists = ui::UIObjectAcc(handle).m_object != nullptr;
    if (exists) {
        bool term = ui::UIObjectAcc(handle).isTerm();
        if (!term) {
            ui::EventData event;
            event.m_type = 0x100;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjEnemyStatus::close() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x10);
    bool exists = ui::UIObjectAcc(handle).m_object != nullptr;
    if (exists) {
        bool term = ui::UIObjectAcc(handle).isTerm();
        if (!term) {
            ui::EventData event;
            event.m_type = 0x101;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjEnemyStatus::disp(bool disp) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x14));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        acc.setDisp(disp);
    }
}

}  // namespace gf
