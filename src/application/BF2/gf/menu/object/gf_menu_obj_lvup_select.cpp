#include "classes/gf/GfMenuObjLvupSelect.h"
#include "classes/gf/GfMenuObjLvupSelect/DrImgListener.h"
#include "classes/gf/GfMenuObjLvupSelect/MainListener.h"
#include "classes/gf/GfMenuObjLvupSelect/SelectListener.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataParty.h"
#include "gf/GfGameUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjLvupSelect::GfMenuObjLvupSelect(unsigned int handle)
    : GfMenuObject(handle), m_seq(this), m_confirmOpen(false), m_levelDown(false), m_levelNumber(), m_bonusExp(),
      m_callContext(nullptr) {
    m_levelNumber = GfMenuReferenceNumber::create();
    m_bonusExp = GfMenuReferenceNumber::create();
    m_callContext = GfMenuCallContext::create();
}

GfMenuObjLvupSelect::~GfMenuObjLvupSelect() {
    if (m_callContext != nullptr) {
        m_callContext->release();
        m_callContext = nullptr;
    }
    m_bonusExp = nullptr;
    m_levelNumber = nullptr;
}

void GfMenuObjLvupSelect::openLevelSelect(GfMenuCallContext* context, unsigned int driver) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x57));
    if (acc.m_object != nullptr && GfMenuObjUtil::checkCCStart(context)) {
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0 = 0;
        event.m_param1 = driver;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        GfMenuObject::startCallContext(context, 0x57, acc.m_handle);
    }
}

void GfMenuObjLvupSelect::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
#line 119
    MainListener* mainListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, mainListener);
    if (mainListener != nullptr) {
        mainListener->release();
    }
    GfMenuObject::attachExternalCall(0x57, acc.m_handle);
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuAdapterManager::beginAddAfter();
    }
    {
        ui::UIObjectAcc select(acc.m_handle, "LAY_lvup_sellect");
        int count = select.countChild("LAY_lvslc_lvset@%02d", 1);
        int offset = -(count / 2);
        mm::mtl::FixStr<32> name;
        for (int i = 0; i < count; i++) {
            name.format("TXT_lvslc_lvnum@%02d", i + 1);
            GfMenuReferenceAdapter* adapter =
                GfMenuReferenceAdapter::create(select.searchChild(name.m_str), m_levelNumber, true);
            if (adapter != nullptr) {
                adapter->m_offset = offset;
                offset++;
                name.format("LAY_lvslc_lvset@%02d", i + 1);
                adapter->m_rowHandle = select.searchChild(name.m_str);
            }
        }
#line 156
        SelectListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SelectListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(select.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc image(acc.m_handle, "LAY_dr_img");
        GfMenuCharDataAdapter::createFromReferenceDriver(image.searchChild("IMG_dr_img"), 0x1C, 0, false);
#line 167
        DrImgListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) DrImgListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(image.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc bonus(acc.m_handle, "LAY_bonus_exp");
        GfMenuReferenceAdapter::create(bonus.searchChild("TXT_bonus_exp_num"), m_bonusExp, false);
        m_bonusExp->m_value = 0;
        m_bonusExp->m_min = 0;
        m_bonusExp->m_max = 999999999;
    }
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuAdapterManager::endAddAfter();
    }
    GfMenuObject::initialize();
}

void GfMenuObjLvupSelect::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjLvupSelect::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjLvupSelect::updateBonusExp() {
    unsigned int driver = GfMenuReference::getReferenceDriverID(0);
    if (driver != 0) {
        DataParamAcc acc(3, driver, static_cast<GimmickType>(0));
        if (acc.isValid()) {
            unsigned int exp = acc.getExp();
            unsigned int level = acc.getLevel(false);
            unsigned int virtualLevel = GfMenuReference::getDriverVirtualLevel();
            unsigned int battleExp = acc.getBattleExp();
            if (virtualLevel > level) {
                unsigned int count = virtualLevel - level;
                for (unsigned int i = 0; i < count; i++) {
                    level++;
                    exp = exp - GfDataBlade::fn_71002326F0(level) + battleExp;
                    battleExp = 0;
                }
            } else {
                unsigned int count = level - virtualLevel;
                for (unsigned int i = 0; i < count; i++) {
                    exp += GfDataBlade::fn_71002326F0(level);
                    level--;
                }
            }
            m_bonusOver = exp > 999999999;
            m_bonusExp->m_value = exp < 1000000000 ? exp : 999999999;
        }
    }
}

void GfMenuObjLvupSelect::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 0x21: {
        unsigned int driver = event.m_param1;
        GfMenuReference::setReferenceDriverID(0, driver);
        GfMenuReference::setDriverVirtualLevel(GfDataDriver::getLevel(driver));
        m_owner->updateBonusExp();
        GfMenuObject::sendOpenEvent(acc.searchChild("LAY_lvup_sellect"), 0, 0.0f);
        GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_dr_img"), 0, 0.0f);
        break;
    }
    case 0x22:
        GfMenuObject::termCallContext(acc.m_handle);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjLvupSelect::SelectListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::setFSInputObject(4, acc.m_handle);
        acc.setDisp(false);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(4);
        } else if (event.m_param0 == 2) {
            GfMenuReference::resetDriverVirtual();
        }
        break;
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            int prev = event.m_param1;
            unsigned int driver = GfMenuReference::getReferenceDriverID(0);
            unsigned int first = GfGameManager::isClearGame() ? 1 : GfDataDriver::getLevel(driver) + 1;
            int& level = m_owner->m_levelNumber->m_value;
            level = first + index;
            GfMenuReference::setDriverVirtualLevel(level);
            acc.setDispChild(!m_owner->m_levelNumber->isMin(), "IMG_lvslc_arrow@01");
            acc.setDispChild(!m_owner->m_levelNumber->isMax(), "IMG_lvslc_arrow@02");
            m_owner->updateBonusExp();
            if (prev != -1 && index != prev) {
                GfMenuObjUtil::playSECommonCursor();
            }
        }
        break;
    }
    case 8:
        if (event.m_param1 == 1) {
            int index = event.m_param0;
            unsigned int driver = GfMenuReference::getReferenceDriverID(0);
            unsigned int first = GfGameManager::isClearGame() ? 1 : GfDataDriver::getLevel(driver) + 1;
            if (first + index == GfDataDriver::getLevel(driver)) {
                GfMenuObjUtil::playSECommon(2);
            } else {
                m_owner->m_level = first + index;
                m_owner->m_levelDown = m_owner->m_level < GfDataDriver::getLevel(driver);
                m_owner->m_confirmOpen = false;
                m_owner->m_seq.addJob(&GfMenuObjLvupSelect::seqConfirmLevelUp);
                GfMenuObject::disableFSInput();
            }
        } else if (event.m_param1 == 2) {
            GfMenuObject::addResultCallContext(acc.getParentHandle(), 2, 0);
            GfMenuObject::sendCloseEvent(acc.getParentHandle(), 0, 0.0f);
            GfMenuObjUtil::playSECommonCancel();
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            GfMenuObject::disableFSInput();
        }
        break;
    case 0x21: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        unsigned int driver = GfMenuReference::getReferenceDriverID(0);
        unsigned int first = GfGameManager::isClearGame() ? 1 : GfDataDriver::getLevel(driver) + 1;
        unsigned int last;
        unsigned int value;
        GfDataDriver::fn_7100245794(&last, &value, driver);
        if (last < first) {
            last = first;
        }
        int selected = GfGameManager::isClearGame() ? GfDataDriver::getLevel(driver) - 1 : 0;
        GfMenuObject::resetInputSelection(acc.m_handle);
        GfMenuObject::setupInputSelection(acc.m_handle, selected, last - first + 1);
        m_owner->m_levelNumber->m_value = first;
        m_owner->m_levelNumber->m_min = first;
        int& max = m_owner->m_levelNumber->m_max;
        max = last;
        if (GfMenuObjUtil::fn_710048FD30(3)) {
            GfMenuObjCmnStatus::fn_71003D7620(true);
        }
        GfMenuObjCmnStatus::openDrStatus(1, 0);
        break;
    }
    case 0x22: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_eventId = 2;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_dr_img"), 0, 0.0f);
        GfMenuObjCmnStatus::closeDrStatus();
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjLvupSelect::seqConfirmLevelUp() {
    if (!m_confirmOpen) {
        if (GfGameManager::isClearGame()) {
            GfMenuManager::openCommonWindow(0x104);
        } else {
            GfMenuManager::openCommonWindow(0xA7);
        }
        m_confirmOpen = true;
        return false;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    unsigned short result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
        if (GfGameManager::isClearGame() && m_bonusOver) {
            m_seq.addJob(&GfMenuObjLvupSelect::fn_710042E8EC);
        } else {
            m_seq.addJob(&GfMenuObjLvupSelect::seqExecLevelUp);
        }
    } else {
        GfMenuObject::enableFSInput(4);
    }
    m_confirmOpen = false;
    return true;
}

void GfMenuObjLvupSelect::DrImgListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
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
        param.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjLvupSelect::fn_710042E8EC() {
    if (!m_confirmOpen) {
        GfMenuManager::openCommonWindow(0x102);
        m_confirmOpen = true;
        return false;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    unsigned short result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
        m_seq.addJob(&GfMenuObjLvupSelect::seqExecLevelUp);
    } else {
        GfMenuObject::enableFSInput(4);
    }
    m_confirmOpen = false;
    return true;
}

bool GfMenuObjLvupSelect::seqExecLevelUp() {
    ui::UIObjectAcc effect(m_handle, "IMG_lv_lvupeff@01");
    if (!m_confirmOpen) {
        effect.startAnimation("start", false);
        effect.setDisp(true);
        ui::UIObjectAcc number(m_handle, "LAY_lv_lvupeff_num@01");
        number.setDisp(true);
        {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x22;
            param.m_time = 1.0f;
            param.m_distance = 0x20;
            param.m_startFlags = 10;
            GfMenuObjUtil::startCtrl(number.m_handle, param, nullptr);
        }
        if (!GfMenuObjUtil::fn_710048FD30(3)) {
            if (m_levelDown) {
                GfGameUtil::fn_71002DB338(GfMenuReference::getReferenceDriverID(0), m_level);
            } else {
                GfGameUtil::execLevelUp(GfMenuReference::getReferenceDriverID(0), m_level);
            }
        } else {
            unsigned int driver = GfMenuReference::getReferenceDriverID(0);
            if (GfDataDriver::isActivateUnuse(driver)) {
                mm::mtl::FixedVector<unsigned short, 32> drivers;
                GfDataDriver::fn_71002416B4(drivers, driver);
                for (unsigned int i = 0; i < drivers.size(); i++) {
                    if (!GfDataDriver::isActivateUnuse(drivers[i])) {
                        driver = drivers[i];
                        break;
                    }
                }
            }
            unsigned int partyDriver = GfDataParty::getDriver(GfDataParty::getDriverPartyID(driver), 0);
            if (m_levelDown) {
                GfGameUtil::fn_71002DB338(partyDriver, m_level);
            } else {
                GfGameUtil::execLevelUp(partyDriver, m_level);
            }
        }
        m_confirmOpen = true;
        return false;
    }
    if (effect.isPlayingAnimation()) {
        return false;
    }
    effect.setDisp(false);
    ui::UIObjectAcc(m_handle, "LAY_lv_lvupeff_num@01").setDisp(false);
    {
        ui::UIObjectAcc select(m_handle, "LAY_lvup_sellect");
        GfMenuObject::sendCloseEvent(select.m_handle, 0, 0.0f);
    }
    {
        ui::UIObjectAcc main(m_handle, "LAY_main");
        GfMenuObject::sendCloseEvent(main.m_handle, 0, 0.0f);
    }
    {
        ui::UIObjectAcc main(m_handle, "LAY_main");
        GfMenuObject::addResultCallContext(main.m_handle, m_levelDown, 0);
    }
    return true;
}

}  // namespace gf
