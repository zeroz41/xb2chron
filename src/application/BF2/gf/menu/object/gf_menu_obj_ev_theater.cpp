#include "classes/gf/GfMenuObjEvTheater.h"
#include "classes/gf/GfMenuObjEvTheater/HeaderListener.h"
#include "classes/gf/GfMenuObjEvTheater/TopListener.h"
#include "classes/gf/GfMenuObjEvTheater/SubListener.h"
#include "classes/gf/GfMenuObjEvTheater/ItemSettingListener.h"
#include "classes/gf/GfMenuObjEvTheater/PreviewListener.h"
#include "classes/gf/GfMenuMsgList.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "fw/LangUtil.h"
#include "gf/SDataOption.h"
#include "mm/Math.h"
#include "ui/UIStr.h"
#include "ui/EventData.h"
#include "mm/mtl/Vector.h"
#include "classes/tl/TitleMain.h"
#include "gf/SDataSaveIra.h"
#include "classes/ui/UICtrlCursorSelect.h"

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009C10C4). updateTimezone's timezone images.
// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009C10B8). updateInfo's "cap_id" rows; getDefaultLevel reads bdat 0x104's levels at the same rows.
static const int s_capRows[3] = {1, 2, 9};
static const unsigned int s_timezoneImages[3] = {0, 2, 3};
// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009C10D0). updateCommonElem's element icons.
static const int s_elementIcons[7] = {0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA6};

// a 0..255 volume on a level scale of 0..max, rounded (0xFF: max); getDefaultLevel and convOptionDataToLevelList (the name is not
// the original's)
static unsigned char volumeToLevel(unsigned char volume, unsigned char max) {
    if (volume == 0xFF) {
        return max;
    }
    float step = 255.0f / static_cast<unsigned int>(max);
    float level = static_cast<unsigned int>(volume) / step;
    return static_cast<int>(level + (level > 0.0f ? 0.5f : -0.5f));
}

GfMenuObjEvTheater::GfMenuObjEvTheater(unsigned int handle)
    : GfMenuObject(handle), m_title(1), m_msgList(nullptr), m_subObjList(nullptr), m_selectIdList(nullptr),
      m_selectObjList(nullptr), m_settingIdList(nullptr), m_settingObjList(nullptr), m_game(nullptr), pad_168(0),
      m_timezone(0), pad_170(0), pad_174(0), m_faceIcon(0), m_timezoneLocked(false), m_timezoneFromList(false),
      pad_18C(0), pad_190(0), pad_194(false), m_callContext(nullptr), m_levelObjList(nullptr), m_cursor(nullptr),
      m_capBdat(nullptr), m_capHandle(0), m_levelHandle(0), m_volumeLevel(0), m_volumeBase(0), m_seq(this),
      m_previewTime(0.0f) {
    m_game = &mm::mtl::PtrSingleton<tl::TitleMain>::sys()->getSaveBuffer()->m_game;
    m_msgList = GfMenuMsgList::create();
    m_selectIdList = GfMenuIDList::create();
    m_settingIdList = GfMenuIDList::create();
    {
        ui::UIListInfoBase::SetupParam param;
        param.m_pageRowSize = 3;
        m_settingIdList->setup(getAllocator(ALLOCATOR(0)), param);
    }
    m_number = GfMenuReferenceNumber::create();
    m_callContext = GfMenuCallContext::create();
}

GfMenuObjEvTheater::~GfMenuObjEvTheater() {
    m_number = nullptr;
    if (m_callContext != nullptr) {
        m_callContext->release();
        m_callContext = nullptr;
    }
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_levelObjList != nullptr) {
        m_levelObjList->release();
        m_levelObjList = nullptr;
    }
    if (m_subObjList != nullptr) {
        m_subObjList->release();
        m_subObjList = nullptr;
    }
    if (m_msgList != nullptr) {
        m_msgList->release();
        m_msgList = nullptr;
    }
    if (m_settingIdList != nullptr) {
        m_settingIdList->release();
        m_settingIdList = nullptr;
    }
    if (m_settingObjList != nullptr) {
        m_settingObjList->release();
        m_settingObjList = nullptr;
    }
    if (m_selectObjList != nullptr) {
        m_selectObjList->release();
        m_selectObjList = nullptr;
    }
    if (m_selectIdList != nullptr) {
        m_selectIdList->release();
        m_selectIdList = nullptr;
    }
}

bool GfMenuObjEvTheater::attach(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x19));
    if (acc.m_object != nullptr) {
        GfMenuObject::startCallContext(context, 0x19, acc.m_handle);
        return true;
    }
    return false;
}

void GfMenuObjEvTheater::fadeout(GfMenuCallContext* context) {
    if (GfMenuObjUtil::checkCCNext(context, 0x19)) {
        ui::EventData event;
        event.m_type = 0x101;
        GfMenuObject::sendEvent(context->m_handle, event, 0.0f);
    }
}

void GfMenuObjEvTheater::fadein(GfMenuCallContext* context) {
    if (GfMenuObjUtil::checkCCNext(context, 0x19)) {
        ui::EventData event;
        event.m_type = 0x102;
        GfMenuObject::sendEvent(context->m_handle, event, 0.0f);
    }
}

void GfMenuObjEvTheater::dispOffScreen(bool flag) {}

void GfMenuObjEvTheater::finalize() {
    GfMenuManager::setTheaterNonTelop(false);
    GfMenuObject::finalize();
}

void GfMenuObjEvTheater::update() {
    m_seq.update();
    GfMenuObject::update();
}

bool GfMenuObjEvTheater::updateTimezone(unsigned int value) {
    if (m_timezoneLocked) {
        return false;
    }
    ui::UIObjectAcc acc(m_handle, "IMG_select_set_ev_timezone");
    if (m_timezone != 0) {
        acc.setImageIndex(s_timezoneImages[m_timezone - 1]);
    } else {
        acc.setImageIndex(s_timezoneImages[value]);
        m_timezoneFromList = false;
    }
    return true;
}

bool GfMenuObjEvTheater::updateWeather(unsigned int index) {
    if (index < m_weathers.size()) {
        ui::UIObjectAcc weather(m_handle, "IMG_select_set_ev_weather");
        weather.setImageIndex(
            GfMenuBdat::getIconImageIndex(GfMenuBdat::getIconIDFromWeatherType(m_weathers[index].m_weather)));
        if (m_weathers[index].m_timezone == 0) {
            m_timezoneLocked = false;
        } else {
            updateTimezone(m_weathers[index].m_timezone);
            m_settings[0].m_value = m_weathers[index].m_timezone;
            m_timezoneLocked = true;
        }
        ui::UIObjectAcc input(m_handle, "LAY_select_set_ev_input@01");
        input.setMulColor(m_timezoneLocked ? "gray" : "white");
        input.setAlpha(m_timezoneLocked ? 0.5f : 1.0f);
    }
    return true;
}

bool GfMenuObjEvTheater::updateHomuraHikari(unsigned int value) {
    ui::UIObjectAcc acc(m_handle, "IMG_select_set_ev_face");
    acc.setImageIndex(GfMenuBdat::getIconImageIndex(value != 0 ? 0xD0 : 0xCF));
    return true;
}

bool GfMenuObjEvTheater::updateCommonElem(unsigned int value) {
    ui::UIObjectAcc acc(m_handle, "IMG_select_set_bl_elem");
    acc.setImageIndex(GfMenuBdat::getIconImageIndex(s_elementIcons[value]));
    return true;
}

bool GfMenuObjEvTheater::updateCommonParts(unsigned int value) {
    ui::UIObjectAcc acc(m_handle, "IMG_select_set_bl_face");
    unsigned int icon = m_faceIcon;
    if (icon == 0x10E) {
        unsigned int next = value + 1;
        icon += next > 3 ? 0 : next;
    } else {
        icon += value;
    }
    acc.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
    return true;
}

bool GfMenuObjEvTheater::updateCommonVoice(unsigned int value) {
    m_number->m_value = value;
    return true;
}

void GfMenuObjEvTheater::refreshSelctList() {
    unsigned int selected = m_selectIdList->getIndex(true);
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < m_selectObjList->getSize(); i++) {
        name.format("IMG_select_frame@%02d", i + 1);
        ui::UIObjectAcc frame(m_selectObjList->getObject(i), name.m_str);
        frame.startAnimation(selected == i ? "select" : "non", false);
    }
}

void GfMenuObjEvTheater::TopListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    case 0x21: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_setDefault = true;
        param.m_eventId = 1;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        unsigned int selected = 0;
        for (unsigned int i = 0; i < m_owner->m_topItems.size(); i++) {
            if (m_owner->m_topItems[i] == static_cast<unsigned int>(m_owner->m_title)) {
                selected = i;
                break;
            }
        }
        GfMenuObject::resetInputSelection(acc.m_handle);
        GfMenuObject::setupInputSelection(acc.m_handle, selected, m_owner->m_topItems.size());
        break;
    }
    case 0x22: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_l";
        param.m_startFlags = 10;
        param.m_eventId = 2;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        break;
    }
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(0);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        }
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            mm::mtl::FixStr<32> name;
            if (prev != -1) {
                unsigned int item = m_owner->m_topItems[prev];
                name.format("IMG_top_item_base@%02d", item);
                ui::UIObjectAcc base(acc.m_handle, name.m_str);
                base.startAnimation("non", false);
                name.format("TXT_top_item_sel@%02d", item);
                acc.setDispChild(false, name.m_str);
                name.format("TXT_top_item_def@%02d", item);
                acc.setDispChild(true, name.m_str);
            }
            {
                unsigned int item = m_owner->m_topItems[index];
                name.format("IMG_top_item_base@%02d", item);
                ui::UIObjectAcc base(acc.m_handle, name.m_str);
                base.startAnimation("select", false);
                name.format("TXT_top_item_sel@%02d", item);
                acc.setDispChild(true, name.m_str);
                name.format("TXT_top_item_def@%02d", item);
                acc.setDispChild(false, name.m_str);
            }
            m_owner->m_title = m_owner->m_topItems[index];
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 8:
        if (event.m_param1 == 1) {
            GfMenuObjEvTheater* owner = m_owner;
            unsigned int title = owner->m_title;
            if (title == 1 || title == 2 || title == 4) {
                owner->updateSubMsgList(title);
                GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_sub"), 0, 0.0f);
            } else {
                owner->getEvthIDList(owner->m_selectIdList, title, 0);
                GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_select"), 0, 0.0f);
            }
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObjUtil::playSECommonDecide();
        } else if (event.m_param1 == 2) {
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObject::closeFSLayer(acc.m_handle, true, true);
            GfMenuObjUtil::playSECommonCancel();
        }
        break;
    }
}

void GfMenuObjEvTheater::SubListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            m_owner->m_msgList->setIndex(index);
            m_owner->refreshSubList();
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 0x22: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_l";
        param.m_startFlags = 10;
        param.m_eventId = 2;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        GfMenuObject::disableFSInput();
        break;
    }
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::resetInputSelection(acc.m_handle);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_msgList);
            GfMenuObject::enableFSInput(1);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        }
        break;
    case 8:
        if (event.m_param1 == 1) {
            if (m_owner->m_title == 4) {
                GfMenuMsgList* list = m_owner->m_msgList;
                unsigned short id = list->getContents(list->getIndex(false)).m_id;
                GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_preview"), id, 0.0f);
            } else {
                GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_select"), 0, 0.0f);
            }
            GfMenuObjUtil::playSECommonDecide();
        } else if (event.m_param1 == 2) {
            GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_header"), 0, 0.0f);
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_top"), 0, 0.0f);
            GfMenuObjUtil::playSECommonCancel();
        } else {
            break;
        }
        GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
        GfMenuObject::disableFSInput();
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        break;
    case 0x21: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_setDefault = true;
        param.m_eventId = 1;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        m_owner->refreshSubList();
        unsigned int count = m_owner->m_msgList->getSize();
        unsigned int rows = m_owner->m_subObjList->getSize();
        acc.setDispChild(count > rows, "LAY_sub_arrow");
        GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_header"), 0, 0.0f);
        break;
    }
    }
}

void GfMenuObjEvTheater::HeaderListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        m_shown = 0;
        break;
    case 0x21:
        if (m_shown == 0) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_r";
            param.m_setDefault = true;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_header_body");
            {
                ui::UIObjectAcc base(acc.m_handle, "IMG_header_base");
                base.startAnimation("fade_in", false);
                base.setDisp(true);
            }
            unsigned int count = acc.countChild("TXT_header_title@%02d", 1);
            mm::mtl::FixStr<32> name;
            for (unsigned int i = 0; i < count; i++) {
                name.format("TXT_header_title@%02d", i + 1);
                acc.setDispChild(i + 1 == m_owner->m_title, name.m_str);
            }
            acc.setDispChild(false, "LAY_header_item");
            acc.setDispChild(false, "LAY_header_input");
            m_shown = 1;
        }
        break;
    case 0x22:
        if (m_shown == 1) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_r";
            param.m_startFlags = 10;
            param.m_eventId = 2;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_header_body");
            {
                ui::UIObjectAcc base(acc.m_handle, "IMG_header_base");
                base.startAnimation("fade_out", false);
            }
            m_shown = 0;
        }
        break;
    case 0x103: {
        ui::UIObjectAcc text(acc.m_handle, "TXT_header_item");
        ui::UIStr str;
        m_owner->m_msgList->getMsg(-1, str, false);
        text.setText(str);
        acc.setDispChild(true, "LAY_header_item");
        acc.setDispChild(false, "LAY_header_input");
        unsigned int count = acc.countChild("TXT_header_input@%02d", 1);
        mm::mtl::FixStr<32> name;
        for (unsigned int i = 0; i < count; i++) {
            name.format("TXT_header_input@%02d", i + 1);
            acc.setDispChild(i + 1 == m_owner->m_title, name.m_str);
        }
        break;
    }
    case 0x104:
        acc.setDispChild(false, "LAY_header_item");
        acc.setDispChild(false, "LAY_header_input");
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjEvTheater::convOptionDataToLevelList(unsigned int category, const SDataOption& option) {
    m_levels.clear();
    getDefaultLevel(category, m_levels);
    unsigned int top = Bdat::getIdTop(GfDataBdat::getFP(0x104));
    m_levels[1 - top].m_level = option.m_soundUi.m_eventSubtitle ? 1 : 2;
    unsigned char volume = option.m_soundUi.m_volume[1];
    m_levels[2 - top].m_level = volumeToLevel(volume, m_levels[2 - top].m_max);
    if (GfMenuManager::isEnableVoiceChange()) {
        m_levels[3 - top].m_level = option.m_soundUi.m_byte1E ? 2 : 1;
    } else if (3 - top < m_levels.size()) {
        m_levels[3 - top].m_level = 0;
    }
}

void GfMenuObjEvTheater::updateInfo(unsigned int index) {
    ui::UIObjectAcc acc(m_capHandle);
    if (acc.m_object != nullptr) {
        unsigned char* messages = GfDataBdat::getFP(0x136);
        ui::UIStr text(messages, static_cast<unsigned short>(
                                     Bdat::getVal(m_capBdat, "cap_id", s_capRows[index])));
        acc.setText(text);
    }
}

void GfMenuObjEvTheater::refreshLevel(unsigned int) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < m_levels.size(); i++) {
        if (m_levels[i].m_max == 2) {
            name.format("TXT_%s_item_param_on@%02d", "snd", i + 1);
            ui::UIObjectAcc on(m_handle, name.m_str);
            name.format("TXT_%s_item_param_off@%02d", "snd", i + 1);
            ui::UIObjectAcc off(m_handle, name.m_str);
            on.setDisp(m_levels[i].m_level == 1);
            off.setDisp(m_levels[i].m_level == 2);
        } else {
            name.format("IMG_%s_item_param_base@%02d", "snd", i + 1);
            ui::UIObjectAcc base(m_handle, name.m_str);
            name.format("IMG_%s_item_param_point@%02d", "snd", i + 1);
            ui::UIObjectAcc point(m_handle, name.m_str);
            if (base.m_object != nullptr && point.m_object != nullptr) {
                float ratio = static_cast<float>(m_levels[i].m_level - 1) / static_cast<float>(m_levels[i].m_max - 1);
                GfMenuObjUtil::placeObjectHRatio(base.m_handle, point.m_handle, mm::clamp(ratio, 0.0f, 1.0f), -4);
            }
        }
    }
}

void GfMenuObjEvTheater::getDefaultLevel(unsigned int, mm::mtl::FixedVector<Level, 32>& levels) {
    levels.clear();
    unsigned char* bdat = GfDataBdat::getFP(0x104);
    for (unsigned long i = 0; i < 3; i++) {
        if (i == 2 && !GfMenuManager::isEnableVoiceChange()) {
            break;
        }
        int row = s_capRows[i];
        unsigned char level = Bdat::getVal(bdat, "default_level", row);
        unsigned char max = Bdat::getVal(bdat, "max_level", row);
        if (GfMenuObjUtil::isValidExpansion(3)) {
            if (GfMenuManager::isEnableVoiceChange() && i == 2) {
                if (fw::LangUtil::getLangType() == 0 || fw::LangUtil::getLangType() == 6) {
                    level = 2;
                } else {
                    level = fw::LangUtil::getLangType() == 11 ? 2 : 1;
                }
            }
            if (i == 1) {
                level = volumeToLevel(m_volumeLevel, max);
            }
        }
        Level entry;
        entry.m_level = level;
        entry.m_max = max;
        levels.push_back(entry);
        if (levels.size() == levels.capacity()) {
            break;
        }
    }
}

void GfMenuObjEvTheater::ItemSettingListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 0x21:
        acc.setDisp(true);
        GfMenuObject::enableInput(acc.m_handle);
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 0, 0);
        break;
    case 0x22:
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 0, 0);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjEvTheater::PreviewListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        m_guideOpen = 0;
        break;
    case 0x105:
        GfMenuObjOperationInfo::open(acc.m_handle, 0, 0, 0);
        GfMenuObjOperationInfo::setGuideDisp(false);
        m_guideOpen = 1;
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    case 8:
        if (event.m_param1 == 2) {
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_sub"), 0, 0.0f);
            GfMenuObjUtil::playSECommonCancel();
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            m_owner->m_seq.clear();
            if (m_guideOpen == 1) {
                GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            } else {
                GfMenuObjOperationInfo::open(0, 0, 0, 0);
                GfMenuObjOperationInfo::setGuideDisp(false);
            }
        }
        break;
    case 0x22:
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
            m_owner->m_seq.clear();
            m_owner->m_seq.addWait(60);
            m_owner->m_seq.addJob(&GfMenuObjEvTheater::seqStartInput);
        }
        break;
    case 0x21: {
        unsigned short image = Bdat::getVal(m_owner->m_msgList->m_dataBdat, "image_id", event.m_param0);
        ui::UIObjectAcc preview(acc.m_handle, "IMG_preview");
        preview.setImageIndex(image);
        m_owner->m_seq.clear();
        m_owner->m_seq.addJob(&GfMenuObjEvTheater::seqWaitStreaming);
        GfMenuObjOperationInfo::close();
        m_guideOpen = 0;
        break;
    }
    }
}

bool GfMenuObjEvTheater::seqWaitStreaming() {
    ui::UIObjectAcc image(m_handle, "IMG_preview");
    m_previewTime += GfMenuManager::getUpdateDT();
    if (m_previewTime < 5.0f && image.isStreaming()) {
        return false;
    }
    ui::UIObjectAcc preview(m_handle, "LAY_preview");
    GfMenuObjUtil::setCommonFadeIn(preview.m_handle, 1, 0);
    m_previewTime = 0.0f;
    return true;
}

bool GfMenuObjEvTheater::seqStartInput() {
    ui::UIObjectAcc acc(m_handle, "LAY_preview");
    ui::EventData event;
    event.m_type = 0x105;
    GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    return true;
}
}  // namespace gf

// instantiated for gf::GfMenuObjOption::ItemListListener::reciveEvent, gf::GfMenuObjHitonowa::delNpc, ui::UISelectObjList::delObject (not written yet)
template mm::mtl::Vector<unsigned int>::iterator mm::mtl::Vector<unsigned int>::erase(unsigned int*);

namespace gf {

}  // namespace gf

template bool mm::mtl::Delegate<bool(unsigned int)>::memberFuncInvoker<gf::GfMenuObjEvTheater>(const mm::mtl::Delegate<bool(unsigned int)>*, unsigned int);
