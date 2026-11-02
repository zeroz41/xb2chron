#include "gf/GfDataDriver.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataParty.h"
#include "gf/GfMenuTypes.h"
#include "classes/gf/TUnk_B61178.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfReqManager.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"
#include "mm/Vec2.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

namespace {
// a fade-in control of half preset 6's time on the handle's object (inline: its parameter sits above the callers'
// locals, as gf_menu_obj_char_select's startFadeIn's does; the name is not the original's)
inline int startHalfFadeIn(unsigned int handle, int eventId) {
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 1;
    param.m_time = GfMenuObjUtil::getPresetCtrlTime(6) * 0.5f;
    param.m_eventId = eventId;
    return GfMenuObjUtil::startCtrl(handle, param, nullptr);
}
}  // namespace

int TUnk_B61178::s_state;

TUnk_B61178::TUnk_B61178(unsigned int handle)
    : GfMenuObject(handle), m_driverList(nullptr), m_selectList(nullptr), m_driver(0), m_partyId(0), m_seq(this),
      m_seq2(this), pad_578(0), pad_57C(0), m_selectList2(nullptr), m_unusedList(nullptr), m_driverList2(nullptr),
      m_shownDriver(0), pad_5C4(0), m_req(-1), pad_61C(false) {
    m_driverList = GfMenuDriverList::create();
    m_driverList2 = GfMenuDriverList::create();
    {
        ui::UIListInfoBase::SetupParam param;
        m_driverList2->setup(getAllocator(ALLOCATOR(0)), param);
    }
    m_driverList2->clear();
    {
        ui::UISelectObjList::CreateParam create;
        create.m_allocator = getAllocator(ALLOCATOR(0));
        m_selectList = ui::UISelectObjList::create(create);
    }
    {
        ui::UISelectObjList::CreateParam create;
        create.m_allocator = getAllocator(ALLOCATOR(0));
        m_selectList2 = ui::UISelectObjList::create(create);
    }
}

TUnk_B61178::~TUnk_B61178() {
    if (m_unusedList != nullptr) {
        m_unusedList->release();
        m_unusedList = nullptr;
    }
    if (m_selectList2 != nullptr) {
        m_selectList2->release();
        m_selectList2 = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
    if (m_driverList2 != nullptr) {
        m_driverList2->release();
        m_driverList2 = nullptr;
    }
    if (m_driverList != nullptr) {
        m_driverList->release();
        m_driverList = nullptr;
    }
    s_state = 0;
}

void TUnk_B61178::fn_71003D1670() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x61));
    if (acc.m_object != nullptr) {
        GfMenuObject::sendOpenEvent(acc.searchChild("LAY_move"), 0, 0.0f);
    }
}

void TUnk_B61178::fn_71003D16C8() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x61));
    if (acc.m_object != nullptr) {
        GfMenuObject::sendCloseEvent(acc.searchChild("LAY_move"), 0, 0.0f);
    }
}

int TUnk_B61178::fn_71003D1720() {
    return s_state;
}

void TUnk_B61178::fn_71003D1730(unsigned int handle, unsigned short subLayer) {
    GfMenuTypes::Param param;
    param.m_halves.m_type = 1;
    GfMenuFullScreen::registLayerParam(0x12D, param);
    GfMenuObject::changeFSSubLayer(handle, subLayer, 0x12D, true);
}

bool TUnk_B61178::fn_71003D242C() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < pad_578; i++) {
        if (i < pad_578 - 1) {
            for (unsigned int j = 0; j < 3; j++) {
                name.format("IMG_char_img@%02d%02d", j + 1, i + 1);
                if (ui::UIObjectAcc(acc.m_handle, name.m_str).isStreaming()) {
                    return false;
                }
            }
        } else {
            name.format("IMG_char_img@%02d", i + 1);
            if (ui::UIObjectAcc(acc.m_handle, name.m_str).isStreaming()) {
                return false;
            }
        }
    }
    return true;
}

bool TUnk_B61178::fn_71003D2558() {
    ui::UIObjectAcc acc(m_handle, "LAY_char");
    GfMenuObject::sendOpenEvent(acc.m_handle, 0, 0.0f);
    return true;
}

void TUnk_B61178::finalize() {
    GfMenuObject::finalize();
}

void TUnk_B61178::update() {
    m_seq.update();
    m_seq2.update();
    unsigned int driver = 0;
    if (s_state == 1) {
        driver = GfMenuReference::getReferenceDriverID(0);
    } else if (s_state == 2) {
        driver = GfDataBlade::fn_7100236518(GfMenuReference::getReferenceBladeID(0));
    }
    if (driver != 0 && m_shownDriver != driver) {
        ui::UIObjectAcc acc(m_handle, "LAY_move");
        ui::EventData event;
        event.m_type = 0x101;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        m_shownDriver = driver;
        fn_71003D273C(driver);
    }
    GfMenuObject::update();
}

void TUnk_B61178::fn_71003D273C(unsigned int driver) {
    if (GfDataDriver::fn_7100237A94(driver)) {
        GfMenuReference::setReferenceDriverID(0, driver);
        GfMenuReference::setReferenceDriverID(1, driver);
        GfMenuReference::setReferenceBladeID(0, 0);
    } else {
        GfMenuReference::setReferenceDriverID(0, GfDataDriver::fn_71002417DC(driver));
        GfMenuReference::setReferenceDriverID(1, driver);
        GfMenuReference::setReferenceBladeID(0, GfDataBlade::fn_7100237B70(driver, -1));
    }
}

void TUnk_B61178::fn_71003D2EA4() {
    m_ids.clear();
    if (m_driverList->getSize() == 3) {
        if (GfDataDriver::fn_7100237A94(m_driverList->getContents(0).m_driver)) {
            m_ids.push_back(0);
            m_ids.push_back(1);
            m_ids.push_back(2);
        } else {
            m_ids.push_back(0);
            m_ids.push_back(2);
            m_ids.push_back(1);
        }
    } else if (m_driverList->getSize() == 2) {
        m_ids.push_back(0);
        m_ids.push_back(1);
    } else if (m_driverList->getSize() == 1) {
        m_ids.push_back(0);
    }
}

void TUnk_B61178::fn_71003D3C34(int index) {
    ui::UIObjectAcc acc(m_handle, "LAY_sub_menu");
    unsigned char* bdat;
    unsigned int title;
    unsigned int info;
    if (s_state == 1) {
        bdat = GfDataBdat::getFP(0x182);
        title = acc.searchChild("TXT_index_dr");
        info = acc.searchChild("TXT_sub_menu_info_dr");
    } else {
        bdat = GfDataBdat::getFP(0x184);
        title = acc.searchChild("TXT_index_bl");
        info = acc.searchChild("TXT_sub_menu_info_bl");
    }
    if (index < m_list580.size()) {
        int row = m_list580[index];
        unsigned int msgId;
        unsigned char* file;
        GfMenuObject::getMenuText((unsigned short)Bdat::getVal(bdat, "layer", row), file, msgId);
        ui::UIObjectAcc(title).setText(ui::UIStr(file, msgId));
        GfMenuObject::getMenuDesc((unsigned short)Bdat::getVal(bdat, "layer", row), file, msgId);
        ui::UIObjectAcc(info).setText(ui::UIStr(file, msgId));
    }
}

void TUnk_B61178::fn_71003D3DCC(unsigned int driver) {
    ui::UIObjectAcc move(m_handle, "LAY_move");
    ui::UIObjectAcc image(m_handle, "IMG_char_move_img");
    mm::Vec2 scale;
    m_driverList2->clear();
    MenuDriverInfo info;
    info.m_driver = driver;
    m_driverList2->addContents(info);
    move.setLayout(image.m_handle, "character");
    image.getScale(scale);
    GfMenuObjUtil::ImageParam param;
    param.m_x = 0;
    param.m_y = 0;
    param.m_scale = 1.0f;
    GfMenuObjUtil::getImageParam(0, driver, param, 4);
    scale.x *= param.m_scale;
    scale.y *= param.m_scale;
    image.setScale(scale);
    GfMenuObjUtil::addPos(image.m_handle, param.m_x, param.m_y);
}

void TUnk_B61178::fn_71003D3EC0(unsigned int driver) {
    if (GfDataDriver::isActivateUnuse(driver)) {
        mm::mtl::FixedVector<unsigned short, 32> drivers;
        GfDataDriver::fn_71002416B4(drivers, driver);
        for (unsigned int i = 0; i < drivers.size(); i++) {
            if (!GfDataDriver::isActivateUnuse(*drivers.at(i))) {
                driver = drivers[i];
                break;
            }
        }
    }
    m_driver = driver;
    m_partyId = GfDataParty::getDriverPartyID(driver);
}

void TUnk_B61178::fn_71003D3F94(unsigned int blade) {
    unsigned int driver = GfDataBlade::fn_7100236518(blade);
    unsigned int listDriver = GfDataDriver::fn_71002418CC(driver, 0);
    if (m_driver != listDriver) {
        fn_71003D3EC0(listDriver);
        fn_71003D27B8(m_driver, false);
    }
    for (unsigned int i = 0; i < m_driverList->getSize(); i++) {
        if (m_driverList->getContents(i).m_driver == driver) {
            m_driverList->setIndex(i);
        }
    }
}

bool TUnk_B61178::fn_71003D4568() {
    if (m_req == -1) {
        return true;
    }
    return GfReqManager::isValid(m_req);
}

bool TUnk_B61178::fn_71003D4580() {
    unsigned int driver = m_driverList->getContents(m_driverList->getIndex(false)).m_driver;
    fn_71003D27B8(driver, false);
    if (m_ctrl != -1) {
        GfMenuObjUtil::setCtrlDefault(m_ctrl);
        GfMenuObjUtil::releaseCtrl(m_ctrl);
        m_ctrl = -1;
    }
    if (m_ctrl2 != -1) {
        GfMenuObjUtil::setCtrlDefault(m_ctrl2);
        GfMenuObjUtil::releaseCtrl(m_ctrl2);
        m_ctrl = -1;  // the original's code clears m_ctrl here too, not m_ctrl2
    }
    for (unsigned int i = 0; i < m_driverList->getSize(); i++) {
        if (m_driverList->getContents(i).m_driver == driver) {
            m_driverList->setIndex(i);
            break;
        }
    }
    fn_71003D311C(m_ids[m_driverList->getIndex(false)]);
    return true;
}

bool TUnk_B61178::fn_71003D478C() {
    ui::UIObjectAcc acc(m_handle, "LAY_char");
    if (GfMenuObjUtil::getCtrlID(acc.m_handle) == -1) {
        fn_71003D27B8(m_driver, true);
        GfMenuObject::sendOpenEvent(acc.m_handle, 2, 0.0f);
    }
    return true;
}

void TUnk_B61178::fn_71003D4800() {
    unsigned int input = GfMenuObject::getFSInputObject(0);
    GfMenuObjMainMenu2::openCharChange(input, 3, false);
    GfMenuObjMainMenu2::cancelEnableMainMenu(true);
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
    GfMenuObject::enableFSInput(0);
    GfMenuObjOperationInfo::add(input, 0, 0, 0);
    {
        ui::UIObjectAcc acc(m_handle, "LAY_char");
        bool prev = m_driverList->getSize() > 1u;
        bool next = m_driverList->getSize() > 2u;
        GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, prev);
        GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 11, next);
    }
    GfMenuObjOperationInfo::setActionEnable(input, 9, GfMenuObjUtil::getMenuCondition(0x2F) && !pad_61C);
    GfMenuObjOperationInfo::setActionEnable(input, 2, pad_61C);
    if (pad_61C) {
        GfMenuObjMainMenu2::cancelEnableMainMenu(false);
    }
    GfMenuObject::resetInputSelection(input);
    unsigned int index = m_driverList->getIndex(false);
    unsigned int count = m_driverList->getSize();
    GfMenuObject::setupInputSelection(input, m_ids[index], count);
}

void TUnk_B61178::fn_71003D4974() {
    for (unsigned int i = 0; i < m_selectList->getSize(); i++) {
        int ctrl = GfMenuObjUtil::getCtrlID(m_selectList->getObject(i));
        if (ctrl != -1) {
            GfMenuObjUtil::stopCtrl(ctrl);
            ui::UIObjectAcc(m_selectList->getObject(i)).updateLayoutSize();
        }
    }
    for (unsigned int i = 0; i < pad_578; i++) {
        mm::mtl::FixStr<32> name;
        name.format("LAY_char@%02d", i + 1);
        ui::UIObjectAcc acc(m_handle, name.m_str);
        acc.updateLayoutSize();
    }
}

void TUnk_B611D8::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 0x104) {
        if (TUnk_B61178::s_state == 1) {
            TUnk_B61178* owner = m_owner;
            unsigned int driver = GfMenuReference::getReferenceDriverID(0);
            if (owner->m_driver != driver) {
                owner->fn_71003D3EC0(driver);
                owner->fn_71003D27B8(owner->m_driver, false);
            }
        } else if (TUnk_B61178::s_state == 2) {
            unsigned int blade = GfMenuReference::getReferenceBladeID(0);
            m_owner->fn_71003D3F94(GfMenuReference::getReferenceBladeID(0));
            TUnk_B61178::fn_71003D273C(GfDataBlade::fn_7100236518(blade));
        }
        GfMenuObject::sendOpenEvent(acc.searchChild("LAY_sub_menu"), 1, 0.0f);
    } else {
        UIObjectListener::reciveEvent(event, handle);
    }
}

bool TUnk_B61178::fn_71003D5C48() {
    ui::UIObjectAcc acc(m_handle, "LAY_char");
    if (GfMenuObjUtil::getCtrlID(acc.m_handle) == -1) {
        fn_71003D27B8(m_driver, false);
        GfMenuObject::sendOpenEvent(acc.m_handle, 1, 0.0f);
    }
    return true;
}

void TUnk_B61228::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 2:
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 1, 0);
        break;
    case 3:
        if (event.m_param0 == 1) {
            acc.setTerm();
        }
        break;
    case 0x21:
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 0, 0);
        break;
    case 0x22:
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 0, 0);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool TUnk_B61178::fn_71003D6E94() {
    ui::UIObjectAcc acc(m_handle, "IMG_char_move_img");
    return !acc.isStreaming();
}

bool TUnk_B61178::fn_71003D6EE0() {
    ui::UIObjectAcc acc(m_handle, "LAY_move");
    startHalfFadeIn(acc.m_handle, 0);
    return true;
}

}  // namespace gf
