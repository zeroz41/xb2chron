#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObjLvupSelect.h"
#include "classes/gf/GfMenuObjLvupMain.h"
#include "classes/gf/GfMenuObjLvupMain/MainListener.h"
#include "classes/gf/GfMenuObjLvupMain/MenuListener.h"
#include "classes/gf/GfMenuObjLvupMain/SelectListener.h"
#include "classes/gf/GfMenuObjLvupMain.h"
#include "classes/gf/GfMenuObjLvupMain/MainListener.h"
#include "classes/gf/GfMenuObjLvupMain/MenuListener.h"
#include "classes/gf/GfMenuObjLvupMain/SelectListener.h"
#include "classes/gf/GfMenuObjLvupSelect.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjFade.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuSoundManager.h"
#include "classes/gf/GfSound.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfDataDriver.h"
#include "gf/GfMenuFlag.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjLvupMain::GfMenuObjLvupMain(unsigned int handle)
    : GfMenuObject(handle), m_modeList(nullptr), m_drivers(nullptr), m_driverObjs(nullptr), m_cursor(nullptr),
      m_mode(0xFF), m_seq(this), m_textOpened(false), pad_2E4(0), m_textContext(nullptr), m_selectContext(nullptr),
      m_levelUp(false), m_jingle() {
    m_textContext = GfMenuCallContext::create();
    m_selectContext = GfMenuCallContext::create();
}

GfMenuObjLvupMain::~GfMenuObjLvupMain() {
    if (m_textContext != nullptr) {
        m_textContext->release();
        m_textContext = nullptr;
    }
    if (m_selectContext != nullptr) {
        m_selectContext->release();
        m_selectContext = nullptr;
    }
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_driverObjs != nullptr) {
        m_driverObjs->release();
        m_driverObjs = nullptr;
    }
    if (m_drivers != nullptr) {
        m_drivers->release();
        m_drivers = nullptr;
    }
    if (m_modeList != nullptr) {
        m_modeList->release();
        m_modeList = nullptr;
    }
}

void GfMenuObjLvupMain::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    mm::mtl::FixStr<32> name;
#line 107
    MainListener* mainListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.searchChild("LAY_contents"), mainListener);
    if (mainListener != nullptr) {
        mainListener->release();
    }
    m_drivers = GfMenuDriverList::create();
    {
        ui::UIObjectAcc mode(acc.m_handle, "LAY_mode_menu");
        ui::UISelectObjList::CreateParam param;
        param.m_allocator = getAllocator(ALLOCATOR(0));
        m_modeList = ui::UISelectObjList::create(param);
        m_modeList->pickupObject(mode.m_handle, "LAY_mode_sltag@%02d", 1);
#line 124
        MenuListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MenuListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(mode.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc set(acc.m_handle, "LAY_lv_driverset");
        {
            ui::UISelectObjList::CreateParam param;
            param.m_allocator = getAllocator(ALLOCATOR(0));
            m_driverObjs = ui::UISelectObjList::create(param);
        }
        m_driverObjs->pickupObject(set.m_handle, "LAY_lv_drinfo@%02d", 1);
        m_driverObjs->getSize();
        {
            GfMenuDriverList::PartySetup setup;
            setup.m_skipUnused = false;
            setup.m_convertDriver = false;
            setup.m_selectFlag = false;
            setup.m_type = 2;
            setup.m_param.m_pageRowSize = m_driverObjs->getSize();
            m_drivers->setupFromParty(setup);
        }
        if (GfMenuObjUtil::fn_710048FD30(3)) {
            for (unsigned int i = 0; i < static_cast<unsigned int>(m_drivers->getSize()); i++) {
                MenuDriverInfo& info = m_drivers->getContents(i);
                info.m_driver = GfDataDriver::fn_71002417DC(info.m_driver);
            }
        }
        {
            ui::UICtrlCursorSelect::CursorSetting setting;
            setting.setType(0);
            setting.m_dockType = 0;
            m_cursor = ui::UICtrlCursorSelect::create(set.searchChild("IMG_lv_drcursor"), setting, m_driverObjs);
        }
        for (unsigned int i = 0; i < static_cast<unsigned int>(m_driverObjs->getSize()); i++) {
            if (!GfMenuObjUtil::fn_710048FD30(3)) {
                name.format("TXT_lv_drname@%02d", i + 1);
                GfMenuCharDataAdapter* adapter =
                    GfMenuCharDataAdapter::createFromDriverList(set.searchChild(name.m_str), 2, m_drivers, i, false);
                if (adapter != nullptr) {
                    name.format("LAY_lv_drinfo@%02d", i + 1);
                    adapter->m_rowHandle = set.searchChild(name.m_str);
                }
            } else {
                name.format("TXT_lv_drname2@%02d", i + 1);
                GfMenuCharDataAdapter* adapter =
                    GfMenuCharDataAdapter::createFromDriverList(set.searchChild(name.m_str), 0x6D, m_drivers, i, false);
                if (adapter != nullptr) {
                    name.format("LAY_lv_drinfo@%02d", i + 1);
                    adapter->m_rowHandle = set.searchChild(name.m_str);
                }
                name.format("TXT_lv_drname2_sw@%02d", i + 1);
                GfMenuCharDataAdapter::createFromDriverList(set.searchChild(name.m_str), 0x6D, m_drivers, i, false);
            }
            name.format("IMG_lv_drimage@%02d", i + 1);
            GfMenuCharDataAdapter::createFromDriverList(set.searchChild(name.m_str), 3, m_drivers, i, false);
            name.format("TXT_lv_lvnum_num@%02d", i + 1);
            GfMenuCharDataAdapter::createFromDriverList(set.searchChild(name.m_str), 1, m_drivers, i, true);
            name.format("TXT_lv_lvupeff_num@%02d", i + 1);
            GfMenuCharDataAdapter::createFromDriverList(set.searchChild(name.m_str), 1, m_drivers, i, true);
            name.format("TXT_lv_nowexp_num@%02d", i + 1);
            GfMenuCharDataAdapter::createFromDriverList(set.searchChild(name.m_str), 0x13, m_drivers, i, true);
            name.format("TXT_lv_nexp_num@%02d", i + 1);
            GfMenuCharDataAdapter::createFromDriverList(set.searchChild(name.m_str), 0x14, m_drivers, i, true);
            name.format("TXT_lv_bexp_num@%02d", i + 1);
            GfMenuCharDataAdapter::createFromDriverList(set.searchChild(name.m_str), 0x15, m_drivers, i, true);
            name.format("IMG_lv_exp_gauge_exp@%02d", i + 1);
            {
                ui::UIObjectAcc gauge(set.m_handle, name.m_str);
                GfMenuCharDataAdapter::createFromDriverList(gauge.m_handle, 0x16, m_drivers, i, true);
                gauge.setExtType(1);
            }
            name.format("IMG_lv_exp_gauge_bexp@%02d", i + 1);
            {
                ui::UIObjectAcc gauge(set.m_handle, name.m_str);
                GfMenuCharDataAdapter::createFromDriverList(set.searchChild(name.m_str), 0x17, m_drivers, i, true);
                gauge.setExtType(1);
            }
        }
#line 244
        SelectListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SelectListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(set.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::setFSInputObject(1, set.m_handle);
    }
    GfMenuObject::initialize();
}

void GfMenuObjLvupMain::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjLvupMain::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjLvupMain::refreshLevelUpInfo() {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_drivers->getSize()); i++) {
        unsigned int driver = m_drivers->getContents(i).m_driver;
        ui::UIObjectAcc row(m_driverObjs->getObject(i));
        bool enable = GfDataDriver::isEnableLevelUp(driver);
        name.format("LAY_lv_lvup_enable@%02d", i + 1);
        row.setDispChild(enable, name.m_str);
        name.format("IMG_lv_lvup_enable@%02d", i + 1);
        ui::UIObjectAcc image(row.m_handle, name.m_str);
        image.startAnimation("loop", false);
    }
}

bool GfMenuObjLvupMain::seqExecLevelUp() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    unsigned int number = m_drivers->getIndex(true) + 1;
    mm::mtl::FixStr<32> name;
    name.format("IMG_lv_lvup_eff@%02d", number);
    ui::UIObjectAcc effect(main.m_handle, name.m_str);
    effect.startAnimation("fade_in", false);
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "mnu061_levelup";
    param.m_motion = "fade_in";
    param.m_setDefault = true;
    param.m_startFlags = 10;
    name.format("TXT_lv_lvup_text@%02d", number);
    ui::UIObjectAcc text(main.m_handle, name.m_str);
    GfMenuObjUtil::startCtrl(text.m_handle, param, nullptr);
    param.m_methods = 0x10000000;
    param.m_motionLib = "mnu061_levelup_shadow";
    param.m_motion = "fade_in";
    param.m_setDefault = true;
    param.m_startFlags = 10;
    name.format("IMG_lv_lvup_text_bg@%02d", number);
    ui::UIObjectAcc textBg(main.m_handle, name.m_str);
    GfMenuObjUtil::startCtrl(textBg.m_handle, param, nullptr);
    GfMenuObjUtil::playJingle(5);
    return true;
}

bool GfMenuObjLvupMain::seqEndLevelUp() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    unsigned int index = m_drivers->getIndex(true);
    mm::mtl::FixStr<32> name;
    name.format("IMG_lv_lvup_eff@%02d", index + 1);
    ui::UIObjectAcc effect(main.m_handle, name.m_str);
    if (effect.isPlayingAnimation()) {
        return false;
    }
    GfMenuObject::sendOpenEvent(main.searchChild("LAY_lv_driverset"), 0, 0.0f);
    refreshLevelUpInfo();
    return true;
}

void GfMenuObjLvupMain::MenuListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_modeList);
        acc.setDisp(false);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(0);
        }
        break;
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            int prev = event.m_param1;
            mm::mtl::FixStr<32> name;
            if (prev != -1) {
                name.format("IMG_mode_slbase@%02d", prev + 1);
                ui::UIObjectAcc base(m_owner->m_modeList->getObject(prev), name.m_str);
                base.setImageIndex(0);
            }
            name.format("IMG_mode_slbase@%02d", index + 1);
            ui::UIObjectAcc base(m_owner->m_modeList->getObject(index), name.m_str);
            base.setImageIndex(1);
            m_owner->m_modeList->setIndex(index);
        }
        break;
    }
    case 8: {
        int mode = event.m_param0;
        if (event.m_param1 == 1) {
            if (mode == 3) {
                GfMenuObject::closeFSLayer(acc.m_handle, true, true);
                m_owner->m_mode = 3;
            } else if (mode == 1 || mode == 2) {
                GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_lv_driverset"), 0, 0.0f);
                m_owner->m_drivers->setIndex(0);
                m_owner->m_mode = mode;
                GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
                GfMenuObject::disableFSInput();
            } else {
                m_owner->m_mode = mode;
            }
        }
        break;
    }
    case 0x21: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    case 0x22: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_eventId = 2;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjLvupMain::seqClose() {
    float time = 1.0f / GfInfo::m_fSecPerFrame * 2.0f;
    GfMenuSoundManager::fadeOutFieldBgm(2.0f);
    ui::UIObjectAcc acc(m_handle);
    unsigned int frames = static_cast<unsigned int>(time);
    GfMenuObjFade::StartParam param;
    param.channel = 2;
    param.color = mm::Col4(0.0f, 0.0f, 0.0f, 1.0f);
    param.time = frames;
    GfMenuObjFade::start(param);
    m_seq.addWait(frames);
    m_seq.addJob(&GfMenuObjLvupMain::seqClose2);
    return true;
}

}  // namespace gf
