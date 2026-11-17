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
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
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

void GfMenuObjBladeBook::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    mm::mtl::FixStr<32> name;
    {
#line 266
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    m_bladeList = GfMenuBladeList::create();
    {
        GfMenuBladeList::BladeBookSetup setup;
        setup.m_pageRowSize = 3;
        setup.m_pageColumnSize = 5;
        m_bladeList->clear();
        m_bladeList->setupFromBook(setup);
    }
    GfMenuReference::setReferenceBladeID(0, 0);
    {
        ui::UIObjectAcc select(acc.m_handle, "LAY_select");
        {
#line 293
            ListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(select.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        GfMenuObject::setFSInputObject(0, select.m_handle);
        GfMenuObject::sendOpenEvent(select.m_handle, 0, 0.0f);
    }
    GfMenuAdapterManager::beginAddAfter();
    {
        ui::UIObjectAcc list(acc.m_handle, "LAY_list_bl");
        {
            mm::mtl::IAllocator* allocator = getAllocator(ALLOCATOR(0));
            ui::UISelectObjList::CreateParam create;
            create.m_allocator = allocator;
            m_selectList = ui::UISelectObjList::create(create);
        }
        m_selectList->pickupObject(list.m_handle, "LAY_list_bl@%02d", 1);
        {
            ui::UICtrlCursorSelect::CursorSetting setting;
            setting.setType(0);
            setting.m_dockType = 0;
            setting.m_waitAnim = "loop";
            m_cursor = ui::UICtrlCursorSelect::create(list.searchChild("IMG_list_bl_cursor"), setting, m_selectList);
        }
        for (unsigned int i = 0; i < m_selectList->getSize(); i++) {
            name.format("IMG_list_bl_face@%02d", i + 1);
            GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.m_str), 3, m_bladeList, i, false);
            name.format("IMG_list_bl_info_elem@%02d", i + 1);
            GfMenuCharDataAdapter* adapter =
                GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.m_str), 0x2A, m_bladeList, i, false);
            if (adapter != nullptr) {
                name.format("LAY_list_bl_info_elem@%02d", i + 1);
                adapter->m_rowHandle = list.searchChild(name.m_str);
            }
            name.format("IMG_list_bl_info_wpn@%02d", i + 1);
            adapter = GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.m_str), 0x29, m_bladeList, i, false);
            if (adapter != nullptr) {
                name.format("LAY_list_bl_info_wpn@%02d", i + 1);
                adapter->m_rowHandle = list.searchChild(name.m_str);
            }
        }
        GfMenuObjUtil::createVScrollBarPlugin(list.searchChild("IMG_list_bl_scroll_bar"), m_bladeList,
                                              "IMG_list_bl_scroll_bar_base", true);
    }
    GfMenuAdapterManager::endAddAfter();
    {
        ui::UIObjectAcc layout(acc.m_handle, "LAY_bl_img");
        ui::UIObjectAcc image(layout.m_handle, "IMG_bl_img");
        GfMenuCharDataAdapter::createFromReferenceBlade(image.m_handle, 0x36, 0, false);
        image.setAlpha(0.0f);
        image.setStreamImage2nd();
        GfMenuObject::addNumberEventCondition(acc.searchChild("LAY_select"), "IMG_bl_img", 0, 0);
    }
    GfMenuAdapterManager::beginAddAfter();
    {
        ui::UIObjectAcc layout(acc.m_handle, "LAY_bl_name");
        GfMenuCharDataAdapter::createFromReferenceBlade(layout.searchChild("TXT_status_bl_index_name"), 2, 0, false);
        GfMenuCharDataAdapter::createFromReferenceBlade(layout.searchChild("IMG_status_bl_index_wpn_icon"), 0x29, 0, false);
        GfMenuCharDataAdapter::createFromReferenceBlade(layout.searchChild("IMG_status_bl_index_elm_icon"), 0x2A, 0, false);
    }
    GfMenuAdapterManager::endAddAfter();
    {
        ui::UIObjectAcc preview(acc.m_handle, "LAY_preview");
        GfMenuCharDataAdapter::createFromReferenceBlade(preview.searchChild("TXT_preview_name"), 2, 0, false);
        GfMenuCharDataAdapter::createFromReferenceBlade(preview.searchChild("IMG_prev_bl_img"), 0x36, 0, false);
        GfMenuCharDataAdapter::createFromReferenceBlade(preview.searchChild("TXT_preview_cv_name"), 0x56, 0, false);
        GfMenuCharDataAdapter::createFromReferenceBlade(preview.searchChild("TXT_preview_ilust_name"), 0x57, 0, false);
        {
#line 406
            PreviewListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) PreviewListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(preview.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        GfMenuObject::setFSInputObject(1, preview.m_handle);
        {
            ui::UIObjectAcc image(preview.searchChild("IMG_prev_bl_img"));
            image.getPosCenter(m_previewCenter);
            image.getScale(m_baseScale);
            m_previewScale = m_baseScale.x;
        }
    }
    GfMenuObject::initialize();
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

void GfMenuObjBladeBook::PreviewListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(1);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 9, true);
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, false);
        }
        break;
    case 8: {
        int action = event.m_param1;
        switch (action) {
        case 2: {
            GfMenuObjBladeBook* owner = m_owner;
            if (owner->m_voice != nullptr) {
                GfGameVoice::playStop(owner->m_voice);
                owner->m_voice = nullptr;
            }
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            {
                ui::UIObjectAcc main(m_owner->m_handle, "LAY_main");
                ui::EventData close;
                close.m_type = 0x101;
                GfMenuObject::sendEvent(main.m_handle, close, 0.0f);
            }
            GfMenuObjUtil::playSECommonCancel();
            break;
        }
        case 9: {
            int step = m_owner->m_zoomStep + 1;
            if (step >= 5u) {
                GfMenuObjUtil::playSECommon(2);
                step = 4;
            } else {
                GfMenuObjUtil::playSE(0x37);
            }
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 9, step + 1 < 5u);
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, step > 0);
            if (m_owner->m_zoomStep != step) {
                m_owner->setPreviewScale(step);
                m_owner->m_zoomStep = step;
            }
            break;
        }
        case 10: {
            int step;
            if (m_owner->m_zoomStep <= 0) {
                GfMenuObjUtil::playSECommon(2);
                step = 0;
            } else {
                step = m_owner->m_zoomStep - 1;
                GfMenuObjUtil::playSE(0x38);
            }
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 9, step + 1 < 5u);
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, step > 0);
            if (m_owner->m_zoomStep != step) {
                m_owner->setPreviewScale(step);
                m_owner->m_zoomStep = step;
            }
            break;
        }
        case 0xB:
        case 0xC:
        case 0xD: {
            unsigned int index = action - 0xB;
            const char* voice = GfDataBlade::getMenuVoiceName(GfMenuReference::getReferenceBladeID(0), index);
            if (voice != nullptr && *voice != '\0') {
                GfMenuObjBladeBook* owner = m_owner;
                if (owner->m_voice != nullptr) {
                    GfGameVoice::playStop(owner->m_voice);
                    owner->m_voice = nullptr;
                }
                owner->m_voice = GfGameVoice::playVoice(voice);
            }
            break;
        }
        }
        break;
    }
    case 10: {
        float scale = m_owner->m_previewScale;
        ui::UIObjectAcc image(acc.m_handle, "IMG_prev_bl_img");
        short y = event.m_paramShort[1];
        short x = event.m_paramShort[0];
        m_owner->m_pointerPos.x = m_owner->m_scrollRect.x + m_owner->m_scrollRect.w / 2 - x;
        m_owner->m_pointerPos.y = m_owner->m_scrollRect.y + m_owner->m_scrollRect.h / 2 - y;
        image.setPosCenter(mm::Pnt<short>(m_owner->m_previewCenter.x - m_owner->m_pointerPos.x,
                                          m_owner->m_previewCenter.y - m_owner->m_pointerPos.y));
        image.setScale(mm::Vec2(scale, scale));
        break;
    }
    case 0x21: {
        m_owner->m_pointerPos = mm::Pnt<short>(0, 0);
        m_owner->m_zoomStep = 0;
        {
            ui::UIObjectAcc image(acc.searchChild("IMG_prev_bl_img"));
            image.setScale(m_owner->m_baseScale);
            image.setPosCenter(m_owner->m_previewCenter);
            m_owner->m_previewScale = m_owner->m_baseScale.x;
            GfMenuObjBladeBook* owner = m_owner;
            owner->getScreenOverSize(image.m_handle, owner->m_baseScale.y, owner->m_scrollRect.w, owner->m_scrollRect.h);
            m_owner->m_scrollRect.x = m_owner->m_previewCenter.x - m_owner->m_scrollRect.w / 2;
            m_owner->m_scrollRect.y = m_owner->m_previewCenter.y - m_owner->m_scrollRect.h / 2;
        }
        {
            ui::UIObjectAcc image(acc.m_handle, "IMG_prev_bl_img");
            m_owner->setPreviewScale(0);
            image.setPosCenter(mm::Pnt<short>(m_owner->m_previewCenter.x - m_owner->m_pointerPos.x,
                                              m_owner->m_previewCenter.y - m_owner->m_pointerPos.y));
        }
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 1, 0);
        break;
    }
    case 0x22:
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
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

void GfMenuObjBladeBook::setPreviewScale(unsigned int step) {
    ui::UIObjectAcc image(m_handle, "IMG_prev_bl_img");
    float scale = step >= 4 ? 2.0f : m_baseScale.x + ((2.0f - m_baseScale.x) / 5.0f) * step;
    {
        ui::UIObjectAcc preview(m_handle, "LAY_preview");
        mm::Rect<short> rect;
        getScreenOverSize(image.m_handle, scale, rect.w, rect.h);
        rect.x = m_previewCenter.x - rect.w / 2;
        rect.y = m_previewCenter.y - rect.h / 2;
        ui::UIInputPointer::SelectionSetup setup;
        setup.m_sizeW = 0;
        setup.m_sizeH = 0;
        setup.m_rect = rect;
        float ratio = static_cast<float>(rect.h) / m_scrollRect.h;
        float x = m_pointerPos.x * ratio;
        m_pointerPos.x = x + (x > 0.0f ? 0.5f : -0.5f);
        float y = ratio * m_pointerPos.y;
        short py = y + (y > 0.0f ? 0.5f : -0.5f);
        if (step == 0) {
            py = -(rect.h / 2);
        }
        m_pointerPos.y = py;
        mm::Pnt<short> pos(rect.x + rect.w / 2 - m_pointerPos.x, m_previewCenter.y - m_pointerPos.y);
        GfMenuObject::setupPointerSelection(preview.m_handle, setup);
        GfMenuObject::changePointerPos(preview.m_handle, pos);
        m_scrollRect = rect;
    }
    m_previewScale = scale;
}

// no 3.0.1 caller (2.0.0's code): the wpn rows show unless the mode is 2, the elem rows only then
void GfMenuObjBladeBook::refreshBladeInfo(ui::UIObjectAcc& acc, unsigned int mode) {
    unsigned int count = acc.countChild("LAY_list_bl_info@%02d", 1);
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < count; i++) {
        name.format("LAY_list_bl_info_wpn@%02d", i + 1);
        acc.setDispChild(mode != 2, name.m_str);
        name.format("LAY_list_bl_info_elem@%02d", i + 1);
        acc.setDispChild(mode == 2, name.m_str);
    }
}

// no 3.0.1 caller (2.0.0's code): darkens the booster image, then waits for it
bool GfMenuObjBladeBook::seqEffReleaseC() {
    ui::UIObjectAcc booster(m_handle, "IMG_bl_img_booster");
    int ctrl = GfMenuObjUtil::getCtrlID(booster.m_handle);
    if (!m_unknownFlag) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x40000000;
        param.m_time = 1.0f;
        param.m_startFlags = 4;
        GfMenuObjUtil::startCtrl(booster.m_handle, param, nullptr);
        m_unknownFlag = true;
        return false;
    }
    if (GfMenuObjUtil::isBusyCtrl(ctrl)) {
        return false;
    }
    m_unknownFlag = false;
    return true;
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
