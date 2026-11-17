#include "gf/GfDataDriver.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataParty.h"
#include "gf/GfMenuTypes.h"
#include "classes/gf/GfMenuObjCharSelectIra.h"
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
#include "mm/Rect.h"
#include "mm/Pnt.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"
#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfReqCommand.h"
#include "gf/GfReqParam.h"

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
// a fade-out control of half preset 6's time on the handle's object (CharMoveListener::reciveEvent's event 0x101;
// inline, as startHalfFadeIn; the name is not the original's)
inline int startHalfFadeOut(unsigned int handle, int eventId) {
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 2;
    param.m_time = GfMenuObjUtil::getPresetCtrlTime(6) * 0.5f;
    param.m_eventId = eventId;
    return GfMenuObjUtil::startCtrl(handle, param, nullptr);
}
// the LAY_char layouts of a row's three image slots (driver, front and back blade): applyImageParam fits each
// IMG_char_img@ image to one. Proposed name, not the original's (lbl_7100B611C0)
const char* const sCharFrames[] = {"character_dr", "character_bl_front", "character_bl_back"};
}  // namespace

int GfMenuObjCharSelectIra::s_SubMenuMode;

GfMenuObjCharSelectIra::GfMenuObjCharSelectIra(unsigned int handle)
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

GfMenuObjCharSelectIra::~GfMenuObjCharSelectIra() {
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
    s_SubMenuMode = 0;
}

void GfMenuObjCharSelectIra::dispOnChar(unsigned int) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x61));
    if (acc.m_object != nullptr) {
        GfMenuObject::sendOpenEvent(acc.searchChild("LAY_move"), 0, 0.0f);
    }
}

void GfMenuObjCharSelectIra::dispOffChar(unsigned int) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x61));
    if (acc.m_object != nullptr) {
        GfMenuObject::sendCloseEvent(acc.searchChild("LAY_move"), 0, 0.0f);
    }
}

int GfMenuObjCharSelectIra::getSubMenuMode() {
    return s_SubMenuMode;
}

void GfMenuObjCharSelectIra::openFromBattleBefore(unsigned int handle, unsigned short subLayer) {
    GfMenuTypes::Param param;
    param.m_halves.m_type = 1;
    GfMenuFullScreen::registLayerParam(0x12D, param);
    GfMenuObject::changeFSSubLayer(handle, subLayer, 0x12D, true);
}

bool GfMenuObjCharSelectIra::seqWaitStreaming() {
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

bool GfMenuObjCharSelectIra::seqOpenCharSelectByInit() {
    ui::UIObjectAcc acc(m_handle, "LAY_char");
    GfMenuObject::sendOpenEvent(acc.m_handle, 0, 0.0f);
    return true;
}

void GfMenuObjCharSelectIra::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjCharSelectIra::update() {
    m_seq.update();
    m_seq2.update();
    unsigned int driver = 0;
    if (s_SubMenuMode == 1) {
        driver = GfMenuReference::getReferenceDriverID(0);
    } else if (s_SubMenuMode == 2) {
        driver = GfDataBlade::getIraDriver(GfMenuReference::getReferenceBladeID(0));
    }
    if (driver != 0 && m_shownDriver != driver) {
        ui::UIObjectAcc acc(m_handle, "LAY_move");
        ui::EventData event;
        event.m_type = 0x101;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        m_shownDriver = driver;
        mnu_chr_sel_ira::setReferenceChar(driver);
    }
    GfMenuObject::update();
}

void mnu_chr_sel_ira::setReferenceChar(unsigned int driver) {
    if (GfDataDriver::isIraFront(driver)) {
        GfMenuReference::setReferenceDriverID(0, driver);
        GfMenuReference::setReferenceDriverID(1, driver);
        GfMenuReference::setReferenceBladeID(0, 0);
    } else {
        GfMenuReference::setReferenceDriverID(0, GfDataDriver::getIraFront(driver));
        GfMenuReference::setReferenceDriverID(1, driver);
        GfMenuReference::setReferenceBladeID(0, GfDataDriver::getIraBlade(driver, -1));
    }
}

void GfMenuObjCharSelectIra::updateDriverPosList() {
    m_ids.clear();
    if (m_driverList->getSize() == 3) {
        if (GfDataDriver::isIraFront(m_driverList->getContents(0).m_driver)) {
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

void GfMenuObjCharSelectIra::applyImageParam() {
    ui::UIObjectAcc layout(m_handle, "LAY_char");
    mm::Vec2 scale;
    GfMenuObjUtil::ImageParam param;
    mm::mtl::FixStr<32> imageName;
    mm::mtl::FixStr<32> glowName;
    param.m_x = 0;
    param.m_y = 0;
    param.m_scale = 1.0f;
    for (unsigned int row = 0; row < pad_578; row++) {
        unsigned int size = m_driverList->getSize();
        bool last = row >= pad_578 - 1;
        unsigned int count = last ? 1 : size;
        for (unsigned int i = 0; i < count; i++) {
            if (i < m_driverList->getSize()) {
                unsigned int driver = m_driverList->getContents(i).m_driver;
                unsigned int slot = 0;
                if (count == 3) {
                    if (!GfDataDriver::isIraFront(driver)) {
                        slot = i == 2 ? 2 : 1;
                    }
                } else if (count == 2) {
                    if (row != i) {
                        continue;
                    }
                }
                GfMenuObjUtil::getImageParam(0, driver, param, 0);
                const char* frame;
                if (!last) {
                    frame = sCharFrames[slot];
                    imageName.format("IMG_char_img@%02d%02d", slot + 1, row + 1);
                    glowName.format("IMG_char_glow@%02d%02d", slot + 1, row + 1);
                } else {
                    imageName.format("IMG_char_img@%02d", row + 1);
                    glowName.format("IMG_char_glow@%02d", row + 1);
                    frame = "character_solo";
                }
                ui::UIObjectAcc image(layout.m_handle, imageName.m_str);
                ui::UIObjectAcc glow(layout.m_handle, glowName.m_str);
                mm::Rect<short> frameRect;
                layout.getLayoutRect(frame, frameRect);
                mm::Rect<short> imageRect;
                image.getRect(imageRect, 0);
                scale.x = (float)frameRect.w / (float)imageRect.w;
                scale.y = (float)frameRect.h / (float)imageRect.h;
                scale.x *= param.m_scale;
                scale.y *= param.m_scale;
                image.setScale(scale);
                glow.setScale(scale);
                frameRect.x += param.m_x;
                frameRect.y += param.m_y;
                image.setPosCenter(mm::Pnt<short>(frameRect.x + frameRect.w / 2, frameRect.y + frameRect.h / 2));
                glow.setPosCenter(mm::Pnt<short>(frameRect.x + frameRect.w / 2, frameRect.y + frameRect.h / 2));
            }
        }
    }
}

void GfMenuObjCharSelectIra::refreshSubMenu(int index) {
    ui::UIObjectAcc acc(m_handle, "LAY_sub_menu");
    unsigned char* bdat;
    unsigned int title;
    unsigned int info;
    if (s_SubMenuMode == 1) {
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

void GfMenuObjCharSelectIra::updateDispDriver(unsigned int driver) {
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

void GfMenuObjCharSelectIra::updateTopDriver(unsigned int driver) {
    if (GfDataDriver::isActivateUnuse(driver)) {
        mm::mtl::FixedVector<unsigned short, 32> drivers;
        GfDataDriver::getIraBack(drivers, driver);
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

void GfMenuObjCharSelectIra::changeBlade(unsigned int blade) {
    unsigned int driver = GfDataBlade::getIraDriver(blade);
    unsigned int listDriver = GfDataDriver::getIraFromPos(driver, static_cast<PTPOS>(0));
    if (m_driver != listDriver) {
        updateTopDriver(listDriver);
        updateDriverList(m_driver, false);
    }
    for (unsigned int i = 0; i < m_driverList->getSize(); i++) {
        if (m_driverList->getContents(i).m_driver == driver) {
            m_driverList->setIndex(i);
        }
    }
}

void GfMenuObjCharSelectIra::applyDriverForm(const mm::mtl::FixedVector<unsigned short, 32>& form) {
    RQ_SETUP_PARTY party;
    GfGameParty::getCurrentPartyInfo(party);
    int row = -1;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            if (party.m_iraDrivers[i][j] == m_driver) {
                row = i;
                break;
            }
        }
    }
    for (int j = 0; j < 3; j++) {
        if (j < form.size()) {
            party.m_iraDrivers[row][j] = form[j];
        } else {
            party.m_iraDrivers[row][j] = 0;
        }
    }
    m_req = GfReqCommand::reqChangeParty(party);
    m_seq.clear();
    m_seq.addJob(&GfMenuObjCharSelectIra::seqWaitRequest);
    m_seq.addWait(1);
    m_seq.addJob(&GfMenuObjCharSelectIra::seqChangeDriverList);
    m_seq.addJob(&GfMenuObjCharSelectIra::seqOpenCharSelectByFormChange);
}

bool GfMenuObjCharSelectIra::seqWaitRequest() {
    if (m_req == -1) {
        return true;
    }
    return GfReqManager::isValid(m_req);
}

bool GfMenuObjCharSelectIra::seqChangeDriverList() {
    unsigned int driver = m_driverList->getContents(m_driverList->getIndex(false)).m_driver;
    updateDriverList(driver, false);
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
    refreshCharSelect(m_ids[m_driverList->getIndex(false)]);
    return true;
}

bool GfMenuObjCharSelectIra::seqOpenCharSelectByFormChange() {
    ui::UIObjectAcc acc(m_handle, "LAY_char");
    if (GfMenuObjUtil::getCtrlID(acc.m_handle) == -1) {
        updateDriverList(m_driver, true);
        GfMenuObject::sendOpenEvent(acc.m_handle, 2, 0.0f);
    }
    return true;
}

void GfMenuObjCharSelectIra::startCharSelect() {
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

void GfMenuObjCharSelectIra::resetObjControl() {
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

void GfMenuObjCharSelectIra::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 0x104) {
        if (GfMenuObjCharSelectIra::s_SubMenuMode == 1) {
            GfMenuObjCharSelectIra* owner = m_owner;
            unsigned int driver = GfMenuReference::getReferenceDriverID(0);
            if (owner->m_driver != driver) {
                owner->updateTopDriver(driver);
                owner->updateDriverList(owner->m_driver, false);
            }
        } else if (GfMenuObjCharSelectIra::s_SubMenuMode == 2) {
            unsigned int blade = GfMenuReference::getReferenceBladeID(0);
            m_owner->changeBlade(GfMenuReference::getReferenceBladeID(0));
            mnu_chr_sel_ira::setReferenceChar(GfDataBlade::getIraDriver(blade));
        }
        GfMenuObject::sendOpenEvent(acc.searchChild("LAY_sub_menu"), 1, 0.0f);
    } else {
        UIObjectListener::reciveEvent(event, handle);
    }
}

bool GfMenuObjCharSelectIra::seqOpenCharSelect() {
    ui::UIObjectAcc acc(m_handle, "LAY_char");
    if (GfMenuObjUtil::getCtrlID(acc.m_handle) == -1) {
        updateDriverList(m_driver, false);
        GfMenuObject::sendOpenEvent(acc.m_handle, 1, 0.0f);
    }
    return true;
}

void GfMenuObjCharSelectIra::StatusListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
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

void GfMenuObjCharSelectIra::ParamListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_shown = 0;
        m_refresh = 1;
        break;
    case 2:
        if (m_shown == 1) {
            ui::UIObjectAcc base(acc.searchSibiling("IMG_char_param_base"));
            base.startAnimation("out", false);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_l";
            param.m_startFlags = 10;
            param.m_eventId = 1;
            param.m_setDefault = true;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_shown = 0;
        } else {
            acc.setTerm();
        }
        break;
    case 3:
        if (event.m_param0 == 1) {
            acc.setTerm();
        }
        break;
    case 0x21:
        if (m_shown == 0) {
            ui::UIObjectAcc base(acc.searchSibiling("IMG_char_param_base"));
            base.startAnimation("in", false);
            {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "cmn_fade_motion_lr";
                param.m_eventId = 0;
                param.m_motion = "fade_in_l";
                param.m_setDefault = true;
                GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            }
            m_shown = 1;
            if (m_refresh == 1) {
                ui::UIObjectAcc exp(acc.m_handle, "IMG_char_param_exp");
                GfMenuCharDataAdapter::createFromReferenceDriver(exp.m_handle, 0x16, 0, true);
                m_refresh = 0;
            }
        }
        break;
    case 0x22:
        if (m_shown == 1) {
            ui::UIObjectAcc base(acc.searchSibiling("IMG_char_param_base"));
            base.startAnimation("out", false);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_l";
            param.m_startFlags = 10;
            param.m_eventId = 0;
            param.m_setDefault = true;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_shown = 0;
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjCharSelectIra::CharMoveListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_shown = 0;
        break;
    case 3:
        if (event.m_param0 == 1) {
            m_owner->updateDispDriver(m_owner->m_shownDriver);
            m_owner->m_seq2.clear();
            m_owner->m_seq2.addJob(&GfMenuObjCharSelectIra::seqWaitStreamingDriver);
            m_owner->m_seq2.addJob(&GfMenuObjCharSelectIra::seqOpenDriver);
        } else if (event.m_param0 == 2) {
            m_owner->updateDispDriver(m_owner->m_shownDriver);
        }
        break;
    case 0x21:
        if (m_shown == 0) {
            acc.setDisp(true);
            acc.setAlpha(1.0f);
            m_owner->updateDispDriver(m_owner->m_shownDriver);
            {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "cmn_fade_motion_lr";
                param.m_motion = "fade_in_r";
                param.m_setDefault = true;
                param.m_startFlags = 8;
                GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            }
            if (GfMenuObjCharSelectIra::s_SubMenuMode == 1) {
                GfMenuObjCmnStatus::openDrStatus(1, -1);
            } else if (GfMenuObjCharSelectIra::s_SubMenuMode == 2) {
                GfMenuObjCmnStatus::openBlStatus(1, -1);
            }
            m_shown = 1;
        }
        break;
    case 0x22:
        if (m_shown == 1) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "warp_r";
            param.m_eventId = 2;
            param.m_setDefault = true;
            param.m_startFlags = 10;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            if (GfMenuObjCharSelectIra::s_SubMenuMode == 1) {
                GfMenuObjCmnStatus::closeDrStatus();
            } else if (GfMenuObjCharSelectIra::s_SubMenuMode == 2) {
                GfMenuObjCmnStatus::closeBlStatus();
            }
            m_owner->m_seq2.clear();
            m_shown = 0;
        }
        break;
    case 0x101:
        if (m_shown == 1) {
            startHalfFadeOut(acc.m_handle, 1);
            m_owner->m_seq2.clear();
        } else {
            m_owner->updateDispDriver(m_owner->m_shownDriver);
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjCharSelectIra::seqWaitStreamingDriver() {
    ui::UIObjectAcc acc(m_handle, "IMG_char_move_img");
    return !acc.isStreaming();
}

bool GfMenuObjCharSelectIra::seqOpenDriver() {
    ui::UIObjectAcc acc(m_handle, "LAY_move");
    startHalfFadeIn(acc.m_handle, 0);
    return true;
}

}  // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjCharSelectIra>(const mm::mtl::Delegate<bool()>*);

template bool gf::GfMenuSequence<gf::GfMenuObjCharSelectIra, 8>::wait();

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjCharSelectIra, 8>>(const mm::mtl::Delegate<bool()>*);
