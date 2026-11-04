#include "classes/gf/GfMenuFieldSkill.h"
#include "classes/gf/GfMenuObjFieldIcon.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObjFieldSkill.h"
#include "classes/gf/GfMenuObjFieldSkill/InputListener.h"
#include "classes/gf/GfMenuObjFieldSkill/MainListener.h"
#include "classes/gf/GfMenuObjFieldSkill/BladeListener.h"
#include "classes/gf/GfMenuObjFieldSkill/BaseListener.h"
#include "classes/gf/GfMenuObjFieldSkill/SkillInfoListener.h"
#include "classes/gf/GfMenuObjFieldSkill/ResultListener.h"
#include "classes/gf/GfMenuObjFieldSkill/TotalListener.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuReferenceFs.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/GfMenuObjFieldIcon.h"
#include "classes/gf/GfMenuObjFieldSkill.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuFieldSkillList.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuPosAdapter.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuFieldSkillAdapter.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/ui/UIEventManager.h"
#include "mm/Pnt.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"

namespace gf {

GfMenuObjFieldIcon::GfMenuObjFieldIcon(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjFieldIcon::~GfMenuObjFieldIcon() {
    ;  // a statement the build compiles away (an empty body skips the table store)
}

void GfMenuObjFieldIcon::open(GfMenuCallContext* context, const OpenParam& param) {
    if (context == nullptr || param.m_icon == 0) {
        return;
    }
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0x78));
    if (GfMenuObjUtil::checkCCStart(context) && root.m_object != nullptr) {
        ui::UIObjectAcc icon(root.duplicateChild("LAY_icon"));
        if (icon.m_object != nullptr) {
            unsigned int image = GfMenuBdat::getIconImageIndex(param.m_icon);
            ui::UIObjectAcc(icon.m_handle, "IMG_icon").setImageIndex(image);
            icon.setDisp(true);
            mm::Vec3 pos(param.m_pos);
            pos.x = pos.x + param.m_offset.x;
            pos.y = pos.y + param.m_offset.y;
            pos.z = pos.z + param.m_offset.z;
            GfMenuPosAdapter::createFixedPoint(icon.m_handle, pos, false);
            GfMenuObject::startCallContext(context, 0x78, icon.m_handle);
        }
    }
}

void GfMenuObjFieldIcon::close(GfMenuCallContext* context) {
    if (GfMenuObjUtil::checkCCNext(context, 0x78)) {
        ui::UIObjectAcc icon(context->m_handle);
        if (icon.m_object != nullptr) {
            icon.setTerm();
        }
    }
}

void GfMenuObjFieldIcon::disp(GfMenuCallContext* context, bool disp) {
    if (GfMenuObjUtil::checkCCNext(context, 0x78)) {
        ui::UIObjectAcc icon(context->m_handle);
        if (icon.m_object != nullptr) {
            icon.setDispChild(disp, "IMG_icon");
        }
    }
}

void GfMenuObjFieldIcon::dispAll(bool disp) {
    ui::UIObjectAcc(GfMenuObject::getAttachedObject(0x78)).setDisp(disp);
}

void GfMenuObjFieldIcon::initialize() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    if (main.m_object != nullptr) {
        GfMenuObject::attachExternalCall(0x78, main.m_handle);
        GfMenuObject::initialize();
    }
}

void GfMenuObjFieldIcon::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjFieldIcon::update() {
    GfMenuObject::update();
}

namespace {
// BaseListener's animations per its m_type: in, in (skill), repeat, out (proposed name, not the original's: the
// symbols leave it unnamed, lbl_7100B623C0)
const char* s_baseAnims[5][4] = {
    {"treasure_in", "treasure_in_skill", "treasure_repeat", "treasure_out"},
    {"non_one_in", nullptr, nullptr, "non_one_out"},
    {"non_two_in", nullptr, nullptr, "non_two_out"},
    {"obj_one_in", "obj_one_in_skill", "obj_one_repeat", "obj_one_out"},
    {"obj_two_in", "obj_two_in_skill", "obj_two_repeat", "obj_two_out"},
};
}  // namespace

GfMenuObjFieldSkill::GfMenuObjFieldSkill(unsigned int handle)
    : GfMenuObject(handle), m_skillList(nullptr), pad_5C(0), pad_5D(0), m_seq(this) {
    for (int i = 0; i < 2; i++) {
        m_skillLevels[i] = GfMenuReferenceNumber::create();
    }
    for (int i = 0; i < 2; i++) {
        m_skillGauges[i] = GfMenuReferenceNumber::create();
    }
    m_skillRef = GfMenuReferenceFs::create();
}

GfMenuObjFieldSkill::~GfMenuObjFieldSkill() {
    m_skillRef = nullptr;
    m_skillGauges[0] = nullptr;
    m_skillGauges[1] = nullptr;
    m_skillLevels[0] = nullptr;
    m_skillLevels[1] = nullptr;
    if (m_skillList != nullptr) {
        m_skillList->release();
        m_skillList = nullptr;
    }
}

void GfMenuObjFieldSkill::initialize() {
    ui::UIObjectAcc acc(m_handle);
    {
        ui::UIObjectAcc main(acc.m_handle, "LAY_main");
        GfMenuObject::attachExternalCall(0x31, main.m_handle);
        GfMenuObject::attachExternalCall(0x33, main.m_handle);
        GfMenuObject::attachExternalCall(0x34, main.m_handle);
        GfMenuObject::attachExternalCall(0x35, main.m_handle);
        GfMenuObject::attachExternalCall(0x36, main.m_handle);
#line 125
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(main.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc request(acc.m_handle, "LAY_request");
        mm::mtl::FixStr<32> name;
        GfMenuObject::attachExternalCall(0x37, request.m_handle);
#line 138
        TotalListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TotalListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(request.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        {
            ui::UIListInfoBase::SetupParam param;
            m_skillList = GfMenuFieldSkillList::create();
            param.m_pageRowSize = 2;
            m_skillList->setup(getAllocator(ALLOCATOR(0)), param);
        }
        for (int i = 0; i < 2; i++) {
            name.format("TXT_request_skill_name@%02d", i + 1);
            GfMenuFieldSkillAdapter* skill =
                GfMenuFieldSkillAdapter::createFromList(request.searchChild(name.m_str), 0, m_skillList, i);
            if (skill != nullptr) {
                name.format("LAY_request_skill@%02d", i + 1);
                skill->m_rowHandle = request.searchChild(name.m_str);
            }
            name.format("TXT_request_skill_lv_num@%02d", i + 1);
            GfMenuReferenceAdapter* level =
                GfMenuReferenceAdapter::create(request.searchChild(name.m_str), m_skillLevels[i], true);
            if (level != nullptr) {
                level->setNumberInterpolateMode(0.15f);
            }
            name.format("IMG_requestskill_gauge@%02d", i + 1);
            ui::UIObjectAcc gauge(request.m_handle, name.m_str);
            if (gauge.m_object != nullptr) {
                GfMenuReferenceAdapter* number = GfMenuReferenceAdapter::create(gauge.m_handle, m_skillGauges[i], true);
                if (number != nullptr) {
                    number->setNumberInterpolateMode(0.15f);
                }
                gauge.setExtType(1);
                GfMenuObject::addNumberEventCondition(request.m_handle, name.m_str, 1, i, 1.0f);
            }
        }
    }
    {
        ui::UIObjectAcc blade(acc.m_handle, "LAY_blade");
        GfMenuCharDataAdapter::createFromReferenceBlade(blade.searchChild("IMG_blade_shadow"), 0x36, 5, false);
        GfMenuCharDataAdapter::createFromReferenceBlade(blade.searchChild("IMG_blade"), 0x36, 5, false);
#line 203
        BladeListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) BladeListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(blade.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc base(acc.m_handle, "LAY_base");
#line 213
        BaseListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) BaseListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(base.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc info(acc.m_handle, "LAY_blade_info");
        GfMenuCharDataAdapter::createFromReferenceBlade(info.searchChild("TXT_blade_info_name"), 2, 5, false);
        GfMenuFieldSkillAdapter::createFromReference(info.searchChild("TXT_blade_info_skill_name"), 0, m_skillRef);
        GfMenuFieldSkillAdapter::createFromReference(info.searchChild("TXT_blade_info_skill_lv_num"), 1, m_skillRef);
#line 232
        SkillInfoListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SkillInfoListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(info.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc result(acc.m_handle, "LAY_result");
        GfMenuObjUtil::createDockPlugin(acc.searchChild("TXT_result_success_text"),
                                        acc.searchChild("TXT_result_success_name"), 1, mm::Pnt<short>(8, 0), 0);
        GfMenuObjUtil::createDockPlugin(acc.searchChild("TXT_result_success_eff_text"),
                                        acc.searchChild("TXT_result_success_eff_name"), 1, mm::Pnt<short>(8, 0), 0);
#line 250
        ResultListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ResultListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(result.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc input(acc.m_handle, "LAY_input");
        GfMenuObject::attachExternalCall(0x32, input.m_handle);
#line 262
        InputListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) InputListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(input.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::initialize();
}

void GfMenuObjFieldSkill::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjFieldSkill::update() {
    if (m_voice != nullptr) {
        if (GfMenuObjUtil::isValidExpansion(3) && GfMenuObjUtil::isVoiceSkip()) {
            GfGameVoice::playStop(m_voice);
            m_voice = nullptr;
            return;
        }
        if (GfGameVoice::getResult(m_voice) >= 3) {
            m_voice = nullptr;
        }
    }
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjFieldSkill::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 8:
        if (event.m_param1 == 1) {
            GfMenuObject::addResultCallContext(acc.m_handle, 2, 0);
            GfMenuObject::disableInput(acc.m_handle);
        }
        break;
    case 0x22:
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObject::sendCloseEvent(acc.searchChild("LAY_blade"), 0, 0.0f);
        GfMenuObject::sendCloseEvent(acc.searchChild("LAY_base"), 0, 0.0f);
        GfMenuObject::sendCloseEvent(acc.searchChild("LAY_request"), 0, 0.0f);
        GfMenuObject::sendCloseEvent(acc.searchChild("LAY_blade_info"), 0, 0.0f);
        GfMenuObject::sendCloseEvent(acc.searchChild("LAY_blade_result"), 0, 0.0f);
        GfMenuObject::sendCloseEvent(acc.searchChild("LAY_input"), 0, 0.0f);
        m_owner->m_mainHandle = acc.m_handle;
        break;
    case 0x10B:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
        } else {
            GfMenuObject::disableInput(acc.m_handle);
        }
        break;
    case 0x10D:
        m_owner->m_seq.clear();
        m_owner->m_seq.addJob(&GfMenuObjFieldSkill::seqWaitVoice);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjFieldSkill::seqWaitVoice() {
    if (m_voice != nullptr) {
        return false;
    }
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObject::termCallContext(main.m_handle);
    return true;
}

void GfMenuObjFieldSkill::SkillInfoListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_state = 0;
        m_open = Open();
        break;
    case 3:
        if (event.m_param0 == 3) {
            acc.setDisp(true);
            m_owner->m_skillRef->m_fs = m_owner->m_skill;
            {
                MenuFieldSkill skill;
                m_owner->m_skillRef->getFs(skill);
                m_owner->m_voice = SCOM_FIELD_VOICE::createFieldSkillStart(m_open.m_blade, skill.m_id);
            }
            {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "cmn_fade_motion_lr";
                param.m_motion = "fade_in_l";
                param.m_eventId = 2;
                param.m_startFlags = 8;
                GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            }
            GfMenuObject::addResultCallContext(acc.m_handle, 1, 0);
            GfMenuReference::setReferenceBladeID(5, m_open.m_blade);
            m_owner->m_mainHandle = acc.m_handle;
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_base"), 1, 0.0f);
            GfMenuObjUtil::playSE(0x10);
        }
        break;
    case 0x21: {
        MenuFieldSkill skill;
        skill.m_id = event.m_paramShort[0];
        skill.m_lv = event.m_paramShort[1];
        m_open.m_blade = event.m_param1;
        m_owner->m_skill = skill;
        GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_blade"), 0, 0.0f);
        if (m_state == 0) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_l";
            param.m_eventId = 1;
            param.m_startFlags = 8;
            int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_blade_info_name");
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            acc.setDispChild(false, "LAY_blade_info_skill");
            m_owner->m_mainHandle = acc.m_handle;
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_base"), 0, 0.0f);
            m_state = 1;
            m_open.m_waitSkill = 1;
            GfMenuReference::setReferenceBladeID(5, m_open.m_blade);
        } else {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_r";
            param.m_eventId = 3;
            param.m_startFlags = 10;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        }
        acc.setDisp(true);
        break;
    }
    case 0x22:
        if (m_state == 1) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_l";
            param.m_eventId = 2;
            param.m_startFlags = 10;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_blade"), 0, 0.0f);
            m_state = 0;
        }
        break;
    case 0x10D:
        if (m_open.m_waitSkill == 1) {
            acc.setDispChild(true, "LAY_blade_info_skill");
            m_owner->m_skillRef->m_fs = m_owner->m_skill;
            {
                MenuFieldSkill skill;
                m_owner->m_skillRef->getFs(skill);
                m_owner->m_voice = SCOM_FIELD_VOICE::createFieldSkillStart(m_open.m_blade, skill.m_id);
            }
            {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "cmn_fade_motion_lr";
                param.m_motion = "fade_in_l";
                param.m_eventId = 2;
                param.m_startFlags = 8;
                int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_blade_info_skill");
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            }
            m_owner->m_mainHandle = acc.m_handle;
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_base"), 1, 0.0f);
            GfMenuObject::addResultCallContext(acc.m_handle, 1, 0);
            m_open.m_waitSkill = 0;
            GfMenuObjUtil::playSE(0x10);
        } else {
            GfMenuObject::termCallContext(acc.m_handle);
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjFieldSkill::BladeListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_state = 0;
        break;
    case 3:
        if (event.m_param0 == 1) {
            acc.setDisp(true);
            GfMenuObjFieldSkill::applyImageParam(acc.m_handle);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_l";
            param.m_startFlags = 8;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        } else if (event.m_param0 == 2) {
            ui::UIObjectAcc blade(acc.m_handle, "IMG_blade");
            ui::UIObjectAcc shadow(acc.m_handle, "IMG_blade_shadow");
            blade.setImageIndex(0);
            shadow.setImageIndex(0);
        }
        break;
    case 0x21:
        acc.setDisp(true);
        if (m_state == 0) {
            GfMenuObjFieldSkill::applyImageParam(acc.m_handle);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_l";
            param.m_startFlags = 8;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_state = 1;
        } else {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_eventId = 1;
            param.m_motion = "fade_out_r";
            param.m_startFlags = 10;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        }
        break;
    case 0x22:
        if (m_state == 1) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_l";
            param.m_startFlags = 10;
            param.m_eventId = 2;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_state = 0;
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjFieldSkill::applyImageParam(unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc blade(acc.m_handle, "IMG_blade");
        ui::UIObjectAcc shadow(acc.m_handle, "IMG_blade_shadow");
        unsigned int id = GfMenuReference::getReferenceBladeID(5);
        acc.setLayout(blade.m_handle, "character");
        acc.setLayout(shadow.m_handle, "character");
        GfMenuObjUtil::ImageParam imageParam;
        if (GfMenuObjUtil::getImageParam(1, id, imageParam, 1)) {
            mm::Vec2 scale;
            blade.getScale(scale);
            scale.x = imageParam.m_scale * scale.x;
            scale.y = imageParam.m_scale * scale.y;
            blade.setScale(scale);
            GfMenuObjUtil::addPos(blade.m_handle, imageParam.m_x, imageParam.m_y);
            shadow.getScale(scale);
            scale.x = imageParam.m_scale * scale.x;
            scale.y = imageParam.m_scale * scale.y;
            shadow.setScale(scale);
            GfMenuObjUtil::addPos(shadow.m_handle, imageParam.m_x + 10, imageParam.m_y + 10);
        }
    }
}

void GfMenuObjFieldSkill::BaseListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    ui::UIObjectAcc shadowLayout(acc.searchSibiling("LAY_shadow"));
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_type = 0;
        m_shown = 0;
        break;
    case 0xC: {
        unsigned int main = m_owner->m_mainHandle;
        if (main != 0) {
            ui::EventData close;
            close.m_type = 0x10D;
            GfMenuObject::sendEvent(main, close, 0.0f);
        }
        break;
    }
    case 0x21: {
        ui::UIObjectAcc base(acc.m_handle, "IMG_base");
        ui::UIObjectAcc shadow(shadowLayout.m_handle, "IMG_shadow");
        int mode = event.m_param0;
        acc.setDisp(true);
        shadow.setDisp(true);
        unsigned int type = 0;
        if (m_owner->pad_5C) {
            if (m_owner->pad_5D) {
                shadow.setDisp(false);
                type = m_owner->m_skillList->getSize() == 1 ? 1 : 2;
            } else {
                type = m_owner->m_skillList->getSize() == 1 ? 3 : 4;
            }
        }
        m_type = type;
        if (mode == 0) {
            if (m_owner->pad_5C) {
                GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_request"), 0, 0.0f);
            }
            base.startAnimation(s_baseAnims[m_type][0], false);
            shadow.startAnimation(s_baseAnims[m_type][0], false);
        } else if (mode == 1) {
            if (m_shown == 0) {
                if (type - 1UL > 1) {
                    base.startAnimation(s_baseAnims[m_type][1], false);
                    shadow.startAnimation(s_baseAnims[m_type][1], false);
                }
                m_shown = 1;
            } else if (type - 1UL > 1) {
                base.startAnimation(s_baseAnims[m_type][2], false);
                shadow.startAnimation(s_baseAnims[m_type][2], false);
            }
        }
        GfMenuObject::hookAnimationEvent(acc.m_handle, base.m_handle, 0);
        break;
    }
    case 0x22: {
        ui::UIObjectAcc base(acc.m_handle, "IMG_base");
        ui::UIObjectAcc shadow(shadowLayout.m_handle, "IMG_shadow");
        base.startAnimation(s_baseAnims[m_type][3], false);
        shadow.startAnimation(s_baseAnims[m_type][3], false);
        GfMenuObject::hookAnimationEvent(acc.m_handle, base.m_handle, 0);
        break;
    }
    case 0x10A: {
        ui::UIObjectAcc base(acc.m_handle, "IMG_base");
        if (m_type == 3) {
            base.startAnimation("obj_one_special", false);
        } else if (m_type == 4) {
            base.startAnimation("obj_two_special", false);
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjFieldSkill::ResultListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_state = 0;
        m_result = 0;
        break;
    case 3:
        if (event.m_param0 == 2) {
            acc.setDisp(true);
            GfMenuObject::termCallContext(acc.m_handle);
        }
        break;
    case 0x21:
        if (m_state == 0) {
            int result = event.m_param0;
            acc.setDisp(true);
            if (result == 0) {
                int text = event.m_param1;
                ui::UIObjectAcc name(acc.m_handle, "TXT_result_success_name");
                ui::UIObjectAcc effName(acc.m_handle, "TXT_result_success_eff_name");
                if (text == -1) {
                    name.setAlpha(0.0f);
                    effName.setAlpha(0.0f);
                } else {
                    name.setText(GfMenuObject::getString(text));
                    name.setAlpha(1.0f);
                    effName.setText(GfMenuObject::getString(text));
                    effName.setAlpha(1.0f);
                    GfMenuObject::releaseString(text);
                }
                acc.setDispChild(true, "LAY_result_success");
                acc.setDispChild(true, "LAY_result_success_eff");
                acc.setDispChild(false, "LAY_result_failed");
                {
                    GfMenuObjUtil::CtrlParam param;
                    param.m_methods = 0x10000000;
                    param.m_motionLib = "cmn_fade_motion_zoom";
                    param.m_motion = "fade_out";
                    param.m_startFlags = 10;
                    GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_result_success_eff");
                }
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "cmn_fade_emotion";
                param.m_motion = "fade_in_select";
                param.m_startFlags = 8;
                int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_result_success");
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
                ui::EventData special;
                special.m_type = 0x10A;
                m_owner->m_mainHandle = acc.m_handle;
                GfMenuObject::sendEvent(acc.searchSibiling("LAY_base"), special, 0.0f);
                if (event.m_param2 != 0) {
                    SCOM_FIELD_VOICE::createFieldSkillClear(event.m_param2);
                }
                GfMenuObjUtil::playJingle(0x13);
                GfMenuObjUtil::playVibration(static_cast<fw::VibrationID>(3), 1.0f);
            } else {
                acc.setDispChild(false, "LAY_result_success");
                acc.setDispChild(false, "LAY_result_success_eff");
                acc.setDispChild(true, "LAY_result_failed");
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "cmn_fade_motion_lr";
                param.m_motion = "fade_in_r";
                param.m_startFlags = 8;
                int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_result_failed");
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
                if (event.m_param2 != 0) {
                    SCOM_FIELD_VOICE::createFieldSkillMiss(event.m_param2);
                }
                GfMenuObjUtil::playVibration(static_cast<fw::VibrationID>(8), 1.0f);
            }
            m_state = 1;
            m_result = result;
            acc.setDisp(true);
        }
        break;
    case 0x22:
        if (m_state == 1) {
            if (m_result != 0) {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "cmn_fade_motion_lr";
                param.m_motion = "fade_out_l";
                param.m_startFlags = 10;
                param.m_eventId = 2;
                int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_result_failed");
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            } else {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "cmn_fade_emotion";
                param.m_motion = "fade_out";
                param.m_startFlags = 10;
                param.m_eventId = 2;
                int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_result_success");
                GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            }
            m_state = 0;
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjFieldSkill::TotalListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_state = 0;
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::addResultCallContext(acc.m_handle, 1, 0);
        } else if (event.m_param0 == 2) {
            m_owner->pad_5C = 0;
        }
        break;
    case 0x21:
        if (m_state == 0) {
            acc.setDisp(true);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_r";
            param.m_startFlags = 8;
            param.m_eventId = 1;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_state = 1;
        }
        break;
    case 0x22:
        if (m_state == 1) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_r";
            param.m_startFlags = 10;
            param.m_eventId = 2;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_state = 0;
        }
        break;
    case 0xD:
        if (event.m_param1 == 1) {
            int row = event.m_param2 + 1;
            int on = event.m_param0;
            mm::mtl::FixStr<32> name;
            name.format("IMG_requestskill_clear@%02d", row);
            ui::UIObjectAcc clear(acc.m_handle, name.m_str);
            name.format("TXT_request_skill_name@%02d", row);
            ui::UIObjectAcc skillName(acc.m_handle, name.m_str);
            name.format("TXT_request_skill_lv_num@%02d", row);
            ui::UIObjectAcc level(acc.m_handle, name.m_str);
            if (on == 1) {
                GfMenuObjUtil::setColMulandAdd(skillName.m_handle, "txt_highlight");
                skillName.setBorderWeight(1.0f);
                level.setBorderWeight(1.0f);
                clear.startAnimation("start", false);
                clear.setDisp(true);
            } else {
                skillName.loadDefColor();
                skillName.setBorderWeight(-0.5f);
                level.setBorderWeight(-0.5f);
                clear.stopAnimation();
                clear.setDisp(false);
            }
        }
        break;
    case 0x100: {
        unsigned short gmkName = event.m_param0Short;
        unsigned short noSkills = event.m_paramShort[7];
        {
            ui::UIObjectAcc text(acc.m_handle, "TXT_requset_gmkname");
            text.setDisp(gmkName != 0xffff);
            if (gmkName != 0xffff) {
                GfMenuObject::setText(text.m_handle, gmkName);
            }
        }
        m_owner->m_skillList->clear();
        for (int i = 0; i < 2; i++) {
            unsigned short skill = event.m_paramShort[i * 2 + 1];
            if (skill == 0) {
                m_owner->m_skillLevels[i]->m_value = 0;
                m_owner->m_skillGauges[i]->m_value = 0;
            } else {
                unsigned short lv = event.m_paramShort[i * 2 + 2];
                MenuFieldSkill fs;
                fs.m_id = skill;
                fs.m_lv = lv;
                m_owner->m_skillList->addFieldSkill(fs);
                m_owner->m_skillLevels[i]->m_value = lv;
                m_owner->m_skillLevels[i]->m_max = lv;
                m_owner->m_skillGauges[i]->m_value = 0;
                m_owner->m_skillGauges[i]->m_max = 100;
            }
        }
        if (noSkills == 1) {
            m_owner->m_mainHandle = acc.m_handle;
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_base"), 0, 0.0f);
            GfMenuObject::sendOpenEvent(acc.m_handle, 0, 0.0f);
        } else {
            GfMenuObject::addResultCallContext(acc.m_handle, 1, 0);
        }
        m_owner->pad_5D = noSkills == 1;
        m_owner->pad_5C = 1;
        break;
    }
    case 0x101:
        GfMenuObject::termCallContext(acc.m_handle);
        break;
    case 0x102: {
        unsigned short slot = event.m_paramShort[0];
        unsigned short add = event.m_paramShort[1];
        unsigned short done = m_owner->m_skillLevels[slot]->m_max - m_owner->m_skillLevels[slot]->m_value;
        m_owner->m_skillLevels[slot]->setValue(m_owner->m_skillLevels[slot]->m_max - (add + done));
        if (m_owner->m_skillLevels[slot]->m_value < 0) {
            m_owner->m_skillLevels[slot]->m_value = 0;
        }
        m_owner->m_skillGauges[slot]->m_value =
            (1.0f - (float)m_owner->m_skillLevels[slot]->m_value / (float)m_owner->m_skillLevels[slot]->m_max) * 100.0f;
        GfMenuObjUtil::playVibration(static_cast<fw::VibrationID>(2), 1.0f);
        break;
    }
    case 0x103:
        break;
    case 0x10C: {
        unsigned short slot = event.m_param0Short;
        if (slot >= 1 && slot <= 2) {
            (*(m_owner->m_skillLevels + (slot - 1)))->setValue(m_owner->m_skillLevels[slot - 1]->m_max);
            m_owner->m_skillGauges[slot - 1]->m_value = 0;
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjFieldSkill::InputListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 8:
        if (event.m_param1 == 1) {
            GfMenuObject::addResultCallContext(acc.m_handle, 2, 0);
            GfMenuObject::disableInput(acc.m_handle);
        }
        break;
    case 0x22:
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObject::termCallContext(acc.m_handle);
        break;
    case 0x10B:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
        } else {
            GfMenuObject::disableInput(acc.m_handle);
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjFieldSkill::close(GfMenuCallContext* context) {
    if (GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc main(GfMenuObject::getAttachedObject(0x31));
        if (main.m_object != nullptr && !main.isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            GfMenuObject::sendEvent(main.m_handle, event, 0.0f);
            GfMenuObject::startCallContext(context, 0x31, main.m_handle);
        }
    }
}

void GfMenuObjFieldSkill::attachSkip(GfMenuCallContext* context) {
    if (GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc skip(GfMenuObject::getAttachedObject(0x32));
        if (skip.m_object != nullptr && !skip.isTerm()) {
            GfMenuObject::startCallContext(context, 0x32, skip.m_handle);
        }
    }
}

void GfMenuObjFieldSkill::setSkipInput(GfMenuCallContext* context, bool enable) {
    if (GfMenuObjUtil::checkCCNext(context, 0x32)) {
        ui::UIObjectAcc skip(GfMenuObject::getAttachedObject(0x32));
        if (skip.m_object != nullptr && !skip.isTerm()) {
            ui::EventData event(0x10b);
            event.m_param0 = enable;
            GfMenuObject::sendEvent(skip.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjFieldSkill::openSkillInfo(GfMenuCallContext* context, unsigned char slot, const OpenSkillInfoParam& param) {
    if (GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc main(GfMenuObject::getAttachedObject(0x33));
        if (main.m_object != nullptr && !main.isTerm()) {
            ui::UIObjectAcc info(main.searchChild("LAY_blade_info"));
            if (info.m_object != nullptr) {
                ui::EventData event;
                event.m_type = 0x21;
                event.m_paramShort[0] = param.m_skill;
                event.m_paramShort[1] = param.m_level;
                event.m_param1 = param.m_blade;
                GfMenuObject::sendEvent(info.m_handle, event, 0.0f);
                GfMenuObject::startCallContext(context, 0x33, info.m_handle);
            }
        }
    }
}

void GfMenuObjFieldSkill::openResult(GfMenuCallContext* context, const OpenResultParam& param) {
    if (GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc main(GfMenuObject::getAttachedObject(0x35));
        if (main.m_object != nullptr && !main.isTerm()) {
            ui::UIObjectAcc result(main.searchChild("LAY_result"));
            ui::EventData event(0);
            int text = !param.m_unk0 && param.m_unk8 != nullptr && param.m_unk10 != 0
                           ? GfMenuObject::registString(ui::UIStr(param.m_unk8, param.m_unk10))
                           : -1;
            event.m_type = 0x21;
            event.m_param0 = param.m_unk0;
            event.m_param1 = text;
            event.m_param2 = param.m_unk14;
            GfMenuObject::sendEvent(result.m_handle, event, 0.0f);
            GfMenuObject::startCallContext(context, 0x35, result.m_handle);
        }
    }
}

void GfMenuObjFieldSkill::closeResult(GfMenuCallContext* context) {
    if (GfMenuObjUtil::checkCCNext(context, 0x35)) {
        ui::EventData event;
        event.m_type = 0x22;
        ui::UIManager::get()->requestObjectEvent(context->m_handle, event, 0.0f);
        GfMenuObject::nextCallContext(context, 0x36);
    }
}

void GfMenuObjFieldSkill::openTotalInfo(GfMenuCallContext* context, const OpenTotalParam& param) {
    ui::UIObjectAcc total(GfMenuObject::getAttachedObject(0x37));
    if (total.m_object == nullptr) {
        return;
    }
    bool term = total.isTerm();
    if (context == nullptr || term || context->isActive()) {
        return;
    }
    ui::UIStr text;  // unused: the original constructs and destroys it
    ui::EventData event;
    event.m_type = 0x100;
    if (param.m_unk0 != nullptr && param.m_unk8 != 0) {
        event.m_param0Short = GfMenuObject::registString(ui::UIStr(param.m_unk0, param.m_unk8));
    } else {
        event.m_param0Short = 0xffff;
    }
    event.m_paramShort[7] = param.m_noSkills;
    unsigned int count = 0;
    for (const GfMenuFieldSkill::SkillLevel* it = param.m_levels.begin(); it != param.m_levels.end(); ++it) {
        if (it->m_skill != 0) {
            event.m_paramShort[count * 2 + 1] = it->m_skill;
            event.m_paramShort[count * 2 + 2] = it->m_level;
            count++;
        }
    }
    ui::UIManager::get()->requestObjectEvent(total.m_handle, event, 0.0f);
    GfMenuObject::startCallContext(context, 0x37, total.m_handle);
}

void GfMenuObjFieldSkill::closeTotalInfo(GfMenuCallContext* context) {
    if (context != nullptr && context->m_objectId == 0x37) {
        ui::EventData event;
        event.m_type = 0x101;
        ui::UIManager::get()->requestObjectEvent(context->m_handle, event, 0.0f);
        GfMenuObject::nextCallContext(context, 0x38);
    }
}

void GfMenuObjFieldSkill::addTotalSkillLevel(unsigned char slot, unsigned char level) {
    ui::UIObjectAcc total(GfMenuObject::getAttachedObject(0x37));
    if (total.m_object != nullptr && !total.isTerm()) {
        ui::EventData event(0x102);
        event.m_paramShort[0] = slot;
        event.m_paramShort[1] = level;
        ui::UIManager::get()->requestObjectEvent(total.m_handle, event, 0.0f);
    }
}

void GfMenuObjFieldSkill::setCurrentTotalSkill(unsigned char slot) {
    ui::UIObjectAcc total(GfMenuObject::getAttachedObject(0x37));
    if (total.m_object != nullptr && !total.isTerm()) {
        ui::EventData event;
        event.m_type = 0x103;
        event.m_param0Short = slot;
        ui::UIManager::get()->requestObjectEvent(total.m_handle, event, 0.0f);
    }
}

void GfMenuObjFieldSkill::undoTotalSkillLevel(unsigned char slot) {
    ui::UIObjectAcc total(GfMenuObject::getAttachedObject(0x37));
    if (total.m_object != nullptr && !total.isTerm()) {
        ui::EventData event;
        event.m_type = 0x10c;
        event.m_param0Short = slot;
        ui::UIManager::get()->requestObjectEvent(total.m_handle, event, 0.0f);
    }
}

void GfMenuReferenceFs::getFs(MenuFieldSkill& fs) const {
    fs = m_fs;
}

}  // namespace gf
