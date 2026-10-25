#include "classes/gf/GfMenuFieldSkill.h"
#include "classes/gf/GfMenuObjFieldIcon.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObjFieldSkill.h"
#include "classes/gf/GfMenuObjFieldIcon.h"
#include "classes/gf/GfMenuObjFieldSkill.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuPosAdapter.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Vec3.h"
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

void GfMenuObjFieldSkill::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjFieldSkill::update() {
    if (m_voice != nullptr) {
        if (GfMenuObjUtil::fn_710048FD30(3) && GfMenuObjUtil::fn_7100492C88()) {
            GfGameVoice::playStop(m_voice);
            m_voice = nullptr;
            return;
        }
        if (GfGameVoice::getResult(m_voice) >= 3) {
            m_voice = nullptr;
        }
    }
    if (!m_seq.empty() && (*m_seq.begin())()) {
        m_seq.erase(m_seq.begin());
    }
    GfMenuObject::update();
}

bool GfMenuObjFieldSkill::seqWaitVoice() {
    if (m_voice != nullptr) {
        return false;
    }
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObject::termCallContext(main.m_handle);
    return true;
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

}  // namespace gf
