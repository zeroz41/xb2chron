#include "classes/gf/GfMenuObjSaveLoad2.h"
#include "classes/gf/GfMenuObjSaveLoad2/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjFade.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuSoundManager.h"
#include "classes/gf/GfReqManager.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectNumberPlugin.h"
#include "classes/ui/UIObjectTextPlugin.h"
#include "classes/ui/UIObjectTimePlugin.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfDataBlade.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "gf/GfReqCommand.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"
#include "gf/GfDataUtil.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameSave.h"
#include "classes/tl/TitleMain.h"
#include "gf/GfDataMap.h"
#include "gf/GfGameUtilSaveData.h"
#include "gf/GfMenuBdat.h"
#include "gf/SaveMenuInfo.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

GfMenuObjSaveLoad2::GfMenuObjSaveLoad2(unsigned int handle)
    : GfMenuObject(handle), m_context(nullptr), m_seq(this), m_saveReq(-1), m_mode(0), m_selectList(nullptr),
      m_yearPlugin(nullptr), m_timePlugin(nullptr), m_progressPlugin(nullptr), m_gameTimePlugin(nullptr),
      m_areaPlugin(nullptr), m_drivers(nullptr), m_blades(nullptr), m_numbers(), m_confirm(0) {
    for (int i = 0; i < 3; i++) {
        m_numbers[i] = nullptr;
    }
}

GfMenuObjSaveLoad2::~GfMenuObjSaveLoad2() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
    if (m_yearPlugin != nullptr) {
        m_yearPlugin->release();
        m_yearPlugin = nullptr;
    }
    if (m_timePlugin != nullptr) {
        m_timePlugin->release();
        m_timePlugin = nullptr;
    }
    if (m_progressPlugin != nullptr) {
        m_progressPlugin->release();
        m_progressPlugin = nullptr;
    }
    if (m_gameTimePlugin != nullptr) {
        m_gameTimePlugin->release();
        m_gameTimePlugin = nullptr;
    }
    if (m_areaPlugin != nullptr) {
        m_areaPlugin->release();
        m_areaPlugin = nullptr;
    }
    if (m_drivers != nullptr) {
        m_drivers->release();
        m_drivers = nullptr;
    }
    if (m_blades != nullptr) {
        m_blades->release();
        m_blades = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        m_numbers[i] = nullptr;
    }
}

void GfMenuObjSaveLoad2::registOpenParam(const OpenParam& param) {
    GfMenuTypes::Param layer;
    layer.m_halves.m_type = param.m_mode;
    GfMenuFullScreen::registLayerParam(GfMenuObject::getMenuLayerID(0x35), layer);
}

void GfMenuObjSaveLoad2::initialize() {
    {
        GfMenuTypes::Param layer;
        if (GfMenuObject::getFSLayerParam(m_fsLayer, layer)) {
            m_mode = layer.m_halves.m_type;
            GfMenuObject::removeFSLayerParam(m_fsLayer);
        }
    }
    ui::UIObjectAcc acc(m_handle);
    unsigned int main = acc.searchChild("LAY_main");
#line 168
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::attachExternalCall(0x75, main);
    m_context = GfMenuCallContext::create();
    {
        ui::UISelectObjList::CreateParam param;
        param.m_allocator = getAllocator(ALLOCATOR(0));
        m_selectList = ui::UISelectObjList::create(param);
    }
    m_drivers = GfMenuDriverList::create();
    GfMenuDriverList::PartySetup party;
    party.m_skipUnused = false;
    party.m_convertDriver = false;
    party.m_selectFlag = false;
    party.m_type = 0;
    m_drivers->setupFromParty(party);
    m_blades = GfMenuBladeList::create();
    {
        GfMenuBladeList::TeamSetup team;
        team.m_type = 1;
        team.m_team = 0;
        team.m_keepEmpty = true;
        m_blades->setupFromTeam(team);
    }
    for (int i = 0; i < 3; i++) {
        m_numbers[i] = GfMenuReferenceNumber::create();
        m_numbers[i]->m_value = 1;
    }
    acc.setDispChild(GfMenuManager::isClearCheck(), "IMG_clear_mark");
    GfMenuObject::initialize();
}

void GfMenuObjSaveLoad2::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjSaveLoad2::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjSaveLoad2::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        m_owner->setupSave(acc, m_owner->m_numbers);
        m_owner->refreshSave(acc, 0);
        if (m_owner->m_mode != 0) {
            GfMenuObjOperationInfo::open(handle, 0, 0, 0);
            GfMenuObjOperationInfo::setGuideText(0x23, 2);
            GfMenuSoundManager::fadeOutFieldBgm(0.5f);
        } else {
            GfMenuObjOperationInfo::add(handle, 0, 0, 0);
            GfMenuObjMainMenu2::setSubIndexText(0x15);
            GfMenuObjOperationInfo::setGuideText(0x23, 0);
        }
        GfMenuObjSaveLoad2::setFadeIn(handle, 2);
        break;
    case 3:
        if (event.m_param0 == 2) {
            GfMenuObject::returnFSSubLayer(m_owner);
        }
        break;
    case 8: {
        unsigned int input = event.m_param1;
        GfMenuObjUtil::playSECommonFromInput(input);
        switch (static_cast<unsigned short>(input)) {
        case 1:
            GfMenuObjCommonText::open(m_owner->m_context, 0x9D, 0);
            m_owner->m_confirm = 0;
            GfMenuObject::setCallContextEventHandler(m_owner->m_context, handle);
            GfMenuObject::disableInput(handle);
            break;
        case 2:
            if (m_owner->m_mode == 0) {
                GfMenuObjSaveLoad2::sendEvent(handle, 0x22, 0);
                break;
            }
            GfMenuObjCommonText::open(m_owner->m_context, 0xE3, 0);
            m_owner->m_confirm = 1;
            GfMenuObject::setCallContextEventHandler(m_owner->m_context, handle);
            GfMenuObject::disableInput(handle);
            break;
        }
        break;
    }
    case 0x22:
        if (m_owner->m_mode != 0) {
            GfMenuObjOperationInfo::close();
            GfMenuSoundManager::fadeInFieldBgm(1.0f);
        } else {
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            GfMenuObjMainMenu2::setCloseKeyEnable(false);
        }
        GfMenuObjSaveLoad2::setFadeOut(handle, 2);
        break;
    case 0x41: {
        unsigned int id = event.m_param0;
        GfMenuCallContext* context = m_owner->m_context;
        if (context != nullptr && context->m_id == id) {
            if (event.m_paramShort[4] != 0) {
                GfMenuObject::enableInput(handle);
            } else if (m_owner->m_confirm == 0) {
                bool close = GfDataUtil::getScenarioFlag() > 10042;
                if (GfMenuObjUtil::isValidExpansion(3)) {
                    close = GfDataUtil::getScenarioFlag() > 11125;
                }
                m_owner->m_seq.clear();
                m_owner->m_seq.addJob(&GfMenuObjSaveLoad2::seqSave);
                if (!close) {
                    m_owner->m_seq.addJob(&GfMenuObjSaveLoad2::seqSaveWait);
                } else {
                    m_owner->m_seq.addJob(&GfMenuObjSaveLoad2::seqSaveWaitToClose);
                }
            } else if (m_owner->m_confirm == 1) {
                GfMenuObjSaveLoad2::sendEvent(handle, 0x22, 0);
            }
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjSaveLoad2::setupSave(ui::UIObjectAcc& acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber>* numbers) {
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 3; i++) {
        name.format("TXT_char_name@%02d", i + 1);
        GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.m_str), 2, m_drivers, i, false);
        name.format("TXT_lv_num@%02d", i + 1);
        GfMenuReferenceAdapter::create(acc.searchChild(name.m_str), numbers[i], false);
    }
    m_yearPlugin = ui::UIObjectTimePlugin::create(acc.searchChild("TXT_year_num"), 1);
    m_timePlugin = ui::UIObjectTimePlugin::create(acc.searchChild("TXT_time_num"), 6);
    m_progressPlugin = ui::UIObjectNumberPlugin::create(acc.searchChild("TXT_progress"));
    m_gameTimePlugin = ui::UIObjectTimePlugin::create(acc.searchChild("TXT_game_time"), 7);
    m_areaPlugin = ui::UIObjectTextPlugin::create(acc.searchChild("TXT_area"));
}

void GfMenuObjSaveLoad2::refreshSave(ui::UIObjectAcc& acc, unsigned int refresh) {
    SaveMenuInfo info;
    SDataGame* game = &GfGameSave::getGameSaveData()->m_game;
    tl::TitleMain* title = mm::mtl::PtrSingleton<tl::TitleMain>::sys();
    if (title != nullptr && title->getSaveBuffer()->m_system.m_version == 0x3A15B) {
        game = &title->getSaveBuffer()->m_game;
    }
    GfGameUtilSaveData::getSaveDataMenuInfo(info);
    bool disp;
    if (refresh == 0 && info.m_newGame) {
        info.m_drivers[0].m_driver = 0;
        info.m_drivers[1].m_driver = 0;
        info.m_drivers[2].m_driver = 0;
        ui::UIObjectAcc dr3(acc.searchChild("LAY_dr3"));
        ui::UIObjectAcc dr2(acc.searchChild("LAY_dr2"));
        ui::UIObjectAcc dr0(acc.searchChild("LAY_dr0"));
        dr3.setDisp(true);
        dr2.setDisp(false);
        dr0.setDisp(true);
        disp = false;
    } else {
        disp = true;
    }
    mm::mtl::FixStr<32> name;
    unsigned int handle = acc.m_handle;
    GfMenuObjUtil::setChildDisp(handle, "LAY_time_data", disp);
    GfMenuObjUtil::setChildDisp(handle, "LAY_progress_data", disp);
    GfMenuObjUtil::setChildDisp(handle, "LAY_game_time_data", disp);
    GfMenuObjUtil::setChildDisp(handle, "LAY_area_data", disp);
    m_drivers->clear();
    m_blades->clear();
    if (GfMenuObjUtil::isValidExpansion(3)) {
        for (int i = 0; i < 3; i++) {
            SaveMenuInfo::IraDriver& row = info.m_iraDrivers[i];
            MenuDriverInfo driver;
            driver.m_driver = row.m_driver;
            m_drivers->addContents(driver);
            name.format("IMG_driver@%02d", i + 1);
            {
                ui::UIObjectAcc img(handle, name.m_str);
                img.setImageIndex(GfMenuBdat::getIconImageIndex(GfMenuObjUtil::getFaceIconID(*game, 3, driver.m_driver)));
            }
            unsigned short blade1 = row.m_blade1;
            bool has1;
            {
                name.format("IMG_blade%d@%02d", 1, i + 1);
                ui::UIObjectAcc img1(handle, name.m_str);
                name.format("IMG_blade%d@%02d", 3, i + 1);
                ui::UIObjectAcc img3(handle, name.m_str);
                if (blade1 != 0) {
                    unsigned int icon = GfMenuObjUtil::getFaceIconID(*game, 3, blade1);
                    img1.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
                    img1.setDisp(true);
                    has1 = true;
                    img3.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
                    img3.setDisp(false);
                } else {
                    img1.setDisp(false);
                    img3.setDisp(false);
                    has1 = false;
                }
            }
            unsigned short blade2 = row.m_blade2;
            bool has2;
            {
                name.format("IMG_blade%d@%02d", 2, i + 1);
                ui::UIObjectAcc img2(handle, name.m_str);
                if (blade2 != 0) {
                    img2.setImageIndex(GfMenuBdat::getIconImageIndex(GfMenuObjUtil::getFaceIconID(*game, 3, blade2)));
                    has2 = true;
                    img2.setDisp(true);
                } else {
                    img2.setDisp(false);
                    has2 = false;
                }
            }
            {
                name.format("IMG_driver@%02d", i + 1);
                ui::UIObjectAcc img(handle, name.m_str);
                if (has1 || has2) {
                    acc.setLayout(img.m_handle, "sv_icondr");
                } else {
                    acc.setLayout(img.m_handle, "sv_icon_solo");
                }
            }
            name.format("IMG_char_bg@%02d", i + 1);
            ui::UIObjectAcc bg(handle, name.m_str);
            if (has1 && !has2) {
                name.format("IMG_blade%d@%02d", 1, i + 1);
                ui::UIObjectAcc img1(handle, name.m_str);
                name.format("IMG_blade%d@%02d", 3, i + 1);
                ui::UIObjectAcc img3(handle, name.m_str);
                img1.setDisp(false);
                img3.setDisp(true);
                bg.startAnimationFromIndex(1, false);
            } else if (!has1 && !has2) {
                bg.startAnimationFromIndex(3, false);
            } else {
                bg.startAnimationFromIndex(2, false);
            }
        }
    } else {
        for (unsigned int i = 0; i < 3; i++) {
            SaveMenuInfo::Driver& row = info.m_drivers[i];
            MenuDriverInfo driver;
            driver.m_driver = row.m_driver;
            m_drivers->addContents(driver);
            name.format("IMG_driver@%02d", i + 1);
            {
                ui::UIObjectAcc img(handle, name.m_str);
                img.setImageIndex(GfMenuBdat::getIconImageIndex(GfMenuObjUtil::getFaceIconID(*game, 3, driver.m_driver)));
            }
            short top = row.m_bladeTop;
            unsigned int max = GfMenuObjUtil::getBladeSlotMax(*game);
            unsigned int slot = 0;
            for (; slot < max; slot++) {
                unsigned short id = row.m_blades[(top + slot) % max];
                MenuBladeInfo blade;
                blade.m_blade = id;
                m_blades->addContents(blade);
                name.format("IMG_blade%d@%02d", slot + 1, i + 1);
                ui::UIObjectAcc img(handle, name.m_str);
                if (id == 1113 || id == 1114 || !GfMenuObjUtil::isValidBlade(id)) {
                    img.setDisp(false);
                } else {
                    img.setImageIndex(GfMenuBdat::getIconImageIndex(GfMenuObjUtil::getFaceIconID(*game, 4, blade.m_blade)));
                    img.setDisp(true);
                }
            }
            for (; slot < 3; slot++) {
                MenuBladeInfo blade;
                m_blades->addContents(blade);
                name.format("IMG_blade%d@%02d", slot + 1, i + 1);
                ui::UIObjectAcc img(handle, name.m_str);
                img.setDisp(false);
            }
        }
    }
    m_yearPlugin->setYear(info.m_saveTime.year);
    m_yearPlugin->setMonth(info.m_saveTime.month);
    m_yearPlugin->setDay(info.m_saveTime.day);
    m_timePlugin->setHour(info.m_saveTime.hour);
    m_timePlugin->setMin(info.m_saveTime.minute);
    m_progressPlugin->setNumber(info.m_progress);
    if (info.m_playTime.hour > 999) {
        info.m_playTime.hour = 999;
        info.m_playTime.min = 59;
        info.m_playTime.sec = 59;
    }
    m_gameTimePlugin->setElapseHour(info.m_playTime.hour);
    m_gameTimePlugin->setMin(info.m_playTime.min);
    m_gameTimePlugin->setSec(info.m_playTime.sec);
    unsigned int mapId = GfDataMap::getMapID(info.m_mapJump);
    if (mapId != 0) {
        if (info.m_scenario == 9038) {
            mapId = 20;
        }
        unsigned int nameId = (unsigned short)Bdat::getVal(GfDataBdat::getFP(0x5D), "nameID", mapId);
        unsigned char* texts = GfDataBdat::getFP(0x1B4);
        m_areaPlugin->setText(ui::UIStr(texts, nameId));
    }
    unsigned int count = 0;
    if (GfMenuObjUtil::isValidExpansion(3)) {
        for (int i = 0; i < 3; i++) {
            if (info.m_iraDrivers[i].m_driver != 0) {
                m_numbers[i]->setValue(info.m_iraDrivers[i].m_level);
                count++;
            }
        }
    } else {
        for (int i = 0; i < 3; i++) {
            if (info.m_drivers[i].m_driver != 0) {
                m_numbers[i]->setValue(info.m_drivers[i].m_level);
                count++;
            }
        }
    }
    m_selectList->clear();
    for (unsigned int i = 0; i < 3; i++) {
        mm::mtl::FixStr<32> child;
        child.format("LAY_char@%02d", i + 1);
        if (count > i) {
            m_selectList->addContents(acc.searchChild(child.m_str));
            GfMenuObjUtil::setChildDisp(acc.m_handle, child.m_str, true);
        } else {
            GfMenuObjUtil::setChildDisp(acc.m_handle, child.m_str, false);
        }
    }
    ui::UIObjectAcc dr3(acc.searchChild("LAY_dr3"));
    ui::UIObjectAcc dr2(acc.searchChild("LAY_dr2"));
    ui::UIObjectAcc dr0(acc.searchChild("LAY_dr0"));
    switch (count) {
    case 1:
        dr3.setDisp(false);
        dr2.setDisp(false);
        dr0.setDisp(false);
        break;
    case 2:
        dr3.setDisp(false);
        dr2.setDisp(true);
        dr0.setDisp(false);
        break;
    case 3:
        dr3.setDisp(true);
        dr2.setDisp(false);
        dr0.setDisp(false);
        break;
    }
    mm::Rect<short> grp2;
    acc.getLayoutRect("sv_icon_grp02", grp2);
    mm::Rect<short> grp1;
    acc.getLayoutRect("sv_icon_grp01", grp1);
    unsigned int width = grp2.x - grp1.x - 1;
    mm::Pnt<short> center(grp2.x + grp2.w / 2, grp2.y + grp2.h / 2);
    GfMenuObjUtil::placeObjectH(m_selectList, center, width);
}

bool GfMenuObjSaveLoad2::seqSave() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObject::disableInput(main.m_handle);
    GfMenuObjMainMenu2::setCloseKeyEnable(false);
    m_saveReq = GfReqCommand::reqSave(static_cast<SAVESLOT>(22));
    GfMenuObjFade::dispSaving(true, 0);
    return true;
}

bool GfMenuObjSaveLoad2::seqSaveWait() {
    if (GfReqManager::isValid(m_saveReq)) {
        return false;
    }
    GfMenuObjUtil::playSE(8);
    GfMenuObjFade::dispSaving(false, 0);
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc main(acc.searchChild("LAY_main"));
    refreshSave(main, 1);
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
    ui::UIObjectAcc input(m_handle, "LAY_main");
    GfMenuObject::enableInput(input.m_handle);
    m_saveReq = -1;
    return true;
}

bool GfMenuObjSaveLoad2::seqSaveWaitToClose() {
    if (GfReqManager::isValid(m_saveReq)) {
        return false;
    }
    GfMenuObjUtil::playSE(8);
    GfMenuObjFade::dispSaving(false, 0);
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc main(acc.searchChild("LAY_main"));
    refreshSave(main, 1);
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
    GfMenuObjSaveLoad2::sendEvent(main.m_handle, 0x22, 0);
    m_saveReq = -1;
    return true;
}

}  // namespace gf
