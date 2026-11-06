#include "classes/gf/GfMenuObjBladeBook.h"
#include "classes/gf/GfMenuObjBladeBook/MainListener.h"
#include "classes/gf/GfMenuObjBladeBook/ListListener.h"
#include "classes/gf/GfMenuObjBladeBook/PreviewListener.h"
#include "classes/gf/GfMenuObjBladeBook.h"
#include "classes/gf/GfMenuObjBladeBook/MainListener.h"
#include "classes/gf/GfMenuObjBladeBook/ListListener.h"
#include "classes/gf/GfMenuObjBladeBook/PreviewListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "mm/Rect.h"
#include "ui/EventData.h"
#include "ui/UIUtil.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataEvent.h"
#include "gf/GfDataUtil.h"

namespace gf {

GfMenuObjBladeBook::GfMenuObjBladeBook(unsigned int handle)
    : GfMenuObject(handle), m_bladeList(nullptr), m_selectList(nullptr), m_cursor(nullptr), m_seq(this),
      m_unknownFlag(false), m_voice(nullptr), m_pointerPos(0, 0), m_baseScale(0.0f, 0.0f) {}

GfMenuObjBladeBook::~GfMenuObjBladeBook() {
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
    if (m_bladeList != nullptr) {
        m_bladeList->release();
        m_bladeList = nullptr;
    }
}

void GfMenuObjBladeBook::finalize() {
    if (m_voice != nullptr) {
        GfGameVoice::playStop(m_voice);
        m_voice = nullptr;
    }
    GfMenuObject::finalize();
}

void GfMenuObjBladeBook::update() {
    m_seq.update();
    if (m_voice != nullptr && GfGameVoice::getResult(m_voice) > 2) {
        m_voice = nullptr;
    }
    GfMenuObject::update();
}

void GfMenuObjBladeBook::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        GfMenuObjMainMenu2::setSubIndexText(0x1B);
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    case 2: {
        GfMenuObjMainMenu2::dispGuide(true);
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_startFlag1 = true;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    case 0x100:
        GfMenuObjMainMenu2::dispGuide(false);
        GfMenuObject::sendCloseEvent(acc.searchChild("LAY_select"), 0, 0.0f);
        GfMenuObject::sendOpenEvent(acc.searchChild("LAY_preview"), 0, 0.0f);
        break;
    case 0x101:
        GfMenuObjMainMenu2::dispGuide(true);
        GfMenuObject::sendOpenEvent(acc.searchChild("LAY_select"), 1, 0.0f);
        GfMenuObject::sendCloseEvent(acc.searchChild("LAY_preview"), 0, 0.0f);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjBladeBook::ListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(0);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        }
        break;
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            int last = event.m_param1;
            m_owner->m_bladeList->setIndex(index);
            m_owner->m_selectList->setIndex(m_owner->m_bladeList->getIndex(true));
            GfMenuBladeList* list = m_owner->m_bladeList;
            unsigned int blade = list->getContents(list->getIndex(false)).m_blade;
            bool different = GfMenuObjUtil::isBladeDifferentImage(blade, GfMenuReference::getReferenceBladeID(0));
            GfMenuReference::setReferenceBladeID(0, blade);
            if (different) {
                ui::UIObjectAcc image(acc.m_handle, "IMG_bl_img");
                int ctrl = GfMenuObjUtil::getCtrlID(image.m_handle);
                if (ctrl != -1) {
                    GfMenuObjUtil::stopCtrl(ctrl);
                }
                image.setAlpha(0.0f);
            }
            m_owner->refreshBladeList();
            if (last != -1 && index != last) {
                GfMenuObjUtil::playSECommonCursor();
            }
            acc.setDispChild(!isUnuseBlade(blade), "LAY_bl_name");
        }
        break;
    }
    case 8:
        if (event.m_param1 == 1) {
            GfMenuBladeList* list = m_owner->m_bladeList;
            if (!isUnuseBlade(list->getContents(list->getIndex(false)).m_blade)) {
                GfMenuObject::disableInput(acc.m_handle);
                GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
                {
                    ui::UIObjectAcc main(m_owner->m_handle, "LAY_main");
                    ui::EventData open;
                    open.m_type = 0x100;
                    GfMenuObject::sendEvent(main.m_handle, open, 0.0f);
                }
                GfMenuObjUtil::playSECommonDecide();
            } else {
                GfMenuObjUtil::playSECommon(2);
            }
        } else if (event.m_param1 == 2) {
            GfMenuObject::returnFSSubLayer(m_owner);
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObjUtil::playSECommonCancel();
        }
        break;
    case 0xD:
        if (event.m_param0 == 4 && event.m_param1 == 0 && GfMenuReference::getReferenceBladeID(0) != 0) {
            m_owner->m_seq.clear();
            m_owner->m_seq.addJob(&GfMenuObjBladeBook::seqOpenImage);
        }
        break;
    case 0x21:
        if (event.m_param0 == 1) {
            GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 1, 0);
        } else {
            GfMenuObject::resetInputSelection(acc.m_handle);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_bladeList);
            GfMenuObject::setupPadLineSelection(acc.m_handle, 5);
            GfMenuObject::enableFSInput(0);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        }
        GfMenuObjOperationInfo::setGuideText(0x21, 0);
        GfMenuObjOperationInfo::changeText(handle, 0x12, false);
        m_owner->m_cursor->setDisp(true);
        m_owner->refreshBladeList();
        break;
    case 0x22:
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjBladeBook::refreshBladeList() {
    ui::UIObjectAcc acc(m_handle, "LAY_list_bl");
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < m_bladeList->getPageSize();) {
        GfMenuBladeList* list = m_bladeList;
        unsigned int blade = list->getContents(list->getPageIndex(i)).m_blade;
        bool unuse = isUnuseBlade(blade);
        i++;
        name.format("IMG_list_bl_face@%02d", i);
        {
            ui::UIObjectAcc face(acc.m_handle, name.m_str);
            face.setAlpha(unuse ? 0.0f : 1.0f);
        }
        name.format("IMG_list_bl_secret@%02d", i);
        {
            ui::UIObjectAcc secret(acc.m_handle, name.m_str);
            secret.setDisp(unuse && blade != 0);
        }
    }
}

bool isUnuseBlade(unsigned int blade) {
    if (!GfMenuObjUtil::isValidBlade(blade)) {
        return true;
    }
    if (GfDataBlade::isRegularBlade(blade)) {
        if (GfGameManager::isClearGame() && blade != 1007) {
            return false;
        }
        switch (blade) {
        case 1001:
            return GfDataUtil::getScenarioFlag() < 1031;
        case 1002:
            return GfDataUtil::getScenarioFlag() < 3048;
        case 1004:
            return GfDataUtil::getScenarioFlag() < 2010;
        case 1005:
            return GfDataUtil::getScenarioFlag() < 2033;
        case 1006:
            return GfDataUtil::getScenarioFlag() < 4054;
        case 1007:
            return GfGameFlag::getLocal(1, 0x8A03) == 0;
        case 1008:
            return GfDataUtil::getScenarioFlag() < 3013;
        case 1009:
            return GfDataUtil::getScenarioFlag() < 5004;
        case 1010:
            return GfDataUtil::getScenarioFlag() < 5042;
        case 1011:
            return GfDataUtil::getScenarioFlag() < 7040;
        default:
            return true;
        }
    }
    if (!GfDataBlade::isRareBlade(blade)) {
        return true;
    }
    switch (blade) {
    case 1045:
        return GfGameFlag::getLocal(1, 0x8A02) == 0;
    case 1105:
        return GfGameFlag::getLocal(1, 0x8A08) == 0;
    case 1106:
        return GfGameFlag::getLocal(1, 0x8A09) == 0;
    case 1107:
        return GfGameFlag::getLocal(1, 0x8A0A) == 0;
    case 1111:
        return GfGameFlag::getLocal(1, 0x8A10) == 0;
    default:
        break;
    }
    unsigned int event = GfDataBlade::getCreateEvent(blade);
    if (event != 0 && GfDataEvent::isWatchedEventFlag(event)) {
        return false;
    }
    return GfDataBlade::isActivateUnuse(blade);
}

void GfMenuObjBladeBook::getScreenOverSize(unsigned int handle, float scale, short& width, short& height) {
    ui::UIObjectAcc acc(handle);
    mm::Rect<short> rect;
    acc.getRect(rect, 0);
    float w = rect.w * scale;
    width = w + (w > 0.0f ? 0.5f : -0.5f);
    float h = rect.h * scale;
    height = h + (h > 0.0f ? 0.5f : -0.5f);
    width -= ui::UIUtil::getScreenWidth();
    height -= ui::UIUtil::getScreenHeight();
    if (width < 0) {
        width = 0;
    }
    if (height < 0) {
        height = 0;
    }
}

bool GfMenuObjBladeBook::seqOpenImage() {
    ui::UIObjectAcc image(m_handle, "IMG_bl_img");
    if (image.isStreaming()) {
        image.setAlpha(0.0f);
        return false;
    }
    ui::UIObjectAcc acc(m_handle, "LAY_select");
    unsigned int blade = GfMenuReference::getReferenceBladeID(0);
    acc.setLayout(image.m_handle, "bl_img01");
    {
        GfMenuObjUtil::ImageParam imageParam;
        if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
            mm::Vec2 scale;
            image.getScale(scale);
            scale.x = imageParam.m_scale * scale.x;
            scale.y = imageParam.m_scale * scale.y;
            image.setScale(scale);
            GfMenuObjUtil::addPos(image.m_handle, imageParam.m_x, imageParam.m_y);
        }
    }
    image.setAlpha(1.0f);
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = "fade_in_r";
    param.m_startFlags = 8;
    param.m_setDefault = true;
    GfMenuObjUtil::startCtrl(image.m_handle, param, nullptr);
    image.setAlpha(0.0f);
    {
        ui::UIObjectAcc frame(acc.m_handle, "LAY_bl_img");
        if (isUnuseBlade(blade)) {
            frame.setMulColor("black");
            frame.setAddColor("txt_list_index_mul");
        } else {
            frame.setMulColor("white");
            frame.setAddColor("black");
        }
    }
    return true;
}

}  // namespace gf
