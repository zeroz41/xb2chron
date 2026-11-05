#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuObjCharSelect/MainListener.h"
#include "classes/gf/GfMenuObjCharSelect/CharListener.h"
#include "classes/gf/GfMenuObjCharSelect/SubMenuListener.h"
#include "classes/gf/GfMenuObjCharSelect/DetailListener.h"
#include "mm/Rect.h"
#include "classes/gf/GfMenuObjCharSelect/DetailListener.h"
#include "classes/gf/GfMenuObjCharSelect/StatusListener.h"
#include "classes/gf/GfMenuObjCharSelect/CharDrListener.h"
#include "classes/gf/GfMenuObjCharSelect/CharBlMoveListener.h"
#include "classes/gf/GfMenuObjCharSelect/CharDrMoveListener.h"
#include "classes/gf/GfMenuObjCharSelect/CharDrSoloListener.h"
#include "ui/EventData.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/SCOM_NIA_BLADE.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjPartyStatus.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/DataParamAcc.h"
#include "mm/mtl/FixStr.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/Delegate.h"
#include "classes/gf/GfMenuObjCharSelectIra.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/SCOM_ADD_IDEA.h"
#include "ml/MTRand.h"

namespace gf {

namespace {
// an event of that type with that first parameter, requested of the handle's object at once (inline: its event sits
// above the callers' locals; the name is not the original's)
inline void requestEvent(unsigned int handle, unsigned short type, int param) {
    ui::EventData event;
    event.m_type = type;
    event.m_param0 = param;
    ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}
// a fade-in control of preset 6's time on the handle's object (inline: its parameter sits above the callers' locals,
// as GfMenuObjOpeningTelop::ctrlFadeIn's does; the name is not the original's)
inline int startFadeIn(unsigned int handle, int eventId) {
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 1;
    param.m_time = GfMenuObjUtil::getPresetCtrlTime(6);
    param.m_curve = 1;
    param.m_eventId = eventId;
    return GfMenuObjUtil::startCtrl(handle, param, nullptr);
}


// whether the named child of the object is still streaming (inline: every caller's check shares one stack slot with
// the other checks; the name is not the original's)
inline bool isChildStreaming(ui::UIObjectAcc& acc, const char* name) {
    ui::UIObjectAcc child(acc.searchChild(name));
    return child.isStreaming();
}

// the character select's busy flags. Two file statics the compiler merges into one object (GlobalMerge: the
// constructor clears both with one halfword store through the merged object's address)
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAA1D8); 1.0.0's getCharBusy reads it.
bool s_charBusy;
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAA1D8 + 1); 1.0.0's getSelectBusy reads it
bool s_selectBusy;
// the character layouts seqStreamWaitSelect fades in: the driver, then the three blades
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B60FD0)
const char* s_charLayouts[] = {"LAY_char_dr", "LAY_char_bl@01", "LAY_char_bl@02", "LAY_char_bl@03"};
// the image layouts setCharPosScale shows the character in: the driver's, then the three blades
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B60FF0); used: kept out of GlobalMerge
// (the original keeps it apart from s_charLayouts)
__attribute__((used)) const char* s_charImages[] = {"dr_img", "bl_img01", "bl_img02", "bl_img03"};

// a layout table's entry (the name is not the original's). The original's s_charLayouts (and lbl_7100B60FF0) are
// writable data (.data): clang 3.9 makes a static table constant unless its address is passed on before inlining, so
// their users handed the table to an inline helper like this one (gf_bdat_rsc's _gfbrs::getSlot).
template <unsigned long N>
inline const char* getLayoutName(const char* (&table)[N], unsigned int index) {
    return table[index];
}
}  // namespace

GfMenuObjCharSelect::GfMenuObjCharSelect(unsigned int handle)
    : GfMenuObject(handle), m_driverList(nullptr), m_unusedList(nullptr), m_driverNum(0), m_driverNum2(0), pad_428(0),
      m_seq(this), pad_6C0(false), pad_6D8(0), pad_6E8(-1), pad_740(true), pad_741(false), pad_742(0), pad_744(0),
      pad_748(0xFF), pad_768(false), m_itemList(nullptr), m_subContext(nullptr), m_voice(nullptr) {
    m_subMenuPos.assign(-1);
    for (int i = 0; i < 3; i++) {
        m_bladeLists[i] = nullptr;
    }
    m_context = GfMenuCallContext::create();
    pad_760 = -1;
    pad_758.m_first = -1;
    pad_758.m_second = -1;
    pad_750.m_first = -1;
    pad_750.m_second = -1;
    s_charBusy = false;
    s_selectBusy = false;
    m_itemList = GfMenuItemList::create();
    m_subContext = GfMenuCallContext::create();
}

GfMenuObjCharSelect::~GfMenuObjCharSelect() {
    if (m_subContext != nullptr) {
        m_subContext->release();
        m_subContext = nullptr;
    }
    if (m_itemList != nullptr) {
        m_itemList->release();
        m_itemList = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_driverList != nullptr) {
        m_driverList->release();
        m_driverList = nullptr;
    }
    if (m_unusedList != nullptr) {
        m_unusedList->release();
        m_unusedList = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        if (m_bladeLists[i] != nullptr) {
            m_bladeLists[i]->release();
            m_bladeLists[i] = nullptr;
        }
    }
}

void GfMenuObjCharSelect::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjCharSelect::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjCharSelect::setPartyData(mm::mtl::FixedArray<DriverData, 5>& drivers, GfMenuDriverList* list) {
    for (unsigned int i = 0; i < 5; i++) {
        unsigned int driver = list->getContents(i).m_driver;
        drivers[i].m_driver = driver;
        DataParamAcc acc(3, driver, GimmickType(0));
        if (acc.isValid()) {
            drivers[i].m_blades[0] = 0;
            drivers[i].m_blades[1] = 0;
            drivers[i].m_blades[2] = 0;
            mm::mtl::FixedVector<unsigned short, 422> blades;
            GfMenuBladeList::getBladeFromDriver(driver, blades, true);
            unsigned int j = 0;
            for (unsigned short* it = blades.begin(); it != blades.end(); ++it) {
                drivers[i].m_blades[j] = *it;
                j++;
            }
        }
    }
}

bool GfMenuObjCharSelect::seqStreamWaitStatDr() {
    s_charBusy = true;
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc img(acc.searchChild("IMG_char_dr_move_img"));
    if (img.isStreaming()) {
        return false;
    }
    ui::UIObjectAcc move(acc.searchChild("LAY_char_dr_move"));
    GfMenuObject::hookCtrlEvent(move.m_handle, startFadeIn(move.m_handle, 1));
    return true;
}

unsigned int GfMenuObjCharSelect::setCharPosScale(unsigned int kind, unsigned int id, unsigned int slot, bool solo) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x61));
    unsigned int handle = 0;
    if (acc.m_object != nullptr && slot < 5) {
        const char* layout;
        const char* image;
        if (slot == 4) {
            layout = kind == 0 ? "LAY_char_dr_move" : "LAY_char_bl_move";
            image = "character";
        } else {
            image = getLayoutName(s_charImages, slot);
            layout = solo ? "LAY_char_dr_solo" : getLayoutName(s_charLayouts, slot);
        }
        GfMenuObjUtil::ImageParam param;
        GfMenuObjUtil::getImageParam(kind, id, param, slot);
        ui::UIObjectAcc chr(acc.searchChild(layout));
        if (solo) {
            chr.setLayout(chr.m_handle, "dr_img_solo");
            mm::Vec2 scale(param.m_scale, param.m_scale);
            chr.setScale(scale);
        } else {
            chr.setLayout(chr.m_handle, image);
            {
                mm::Vec2 scale(param.m_scale, param.m_scale);
                chr.setScale(scale);
            }
            mm::Pnt<short> pos;
            chr.getPosCenter(pos);
            pos.x += param.m_x;
            pos.y += param.m_y;
            chr.setPosCenter(pos);
        }
        handle = chr.m_handle;
    }
    return handle;
}

bool GfMenuObjCharSelect::seqStreamWaitStatBl() {
    s_charBusy = true;
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc img(acc.searchChild("IMG_char_bl_move_img"));
    if (img.isStreaming()) {
        return false;
    }
    ui::UIObjectAcc move(acc.searchChild("LAY_char_bl_move"));
    GfMenuObject::hookCtrlEvent(move.m_handle, startFadeIn(move.m_handle, 1));
    return true;
}

bool GfMenuObjCharSelect::seqConfSpecial() {
    ui::UIObjectAcc acc(m_handle, "LAY_char");
    if (!pad_6C0) {
        if (pad_748 == 3 && GfMenuObjUtil::isBladeLastOneInSlot(0x3F3, nullptr)) {
            GfMenuManager::openCommonWindow(0xDF);
            m_seq.addJob(&GfMenuObjCharSelect::seqConfSpecialWaitError);
            return true;
        }
        const unsigned int windows[] = {0xB9, 0xBA, 0xBB, 0xBC};
        GfMenuManager::openCommonWindow(windows[pad_748]);
        pad_6C0 = true;
        return false;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    unsigned short result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
        switch (pad_748) {
        case 0:
            m_seq.addJob(&GfMenuObjCharSelect::seqSpHomuraToHikari);
            break;
        case 1:
            m_seq.addJob(&GfMenuObjCharSelect::seqSpHikariToHomura);
            break;
        case 2:
            m_seq.addJob(&GfMenuObjCharSelect::seqSpNiaChangeBl);
            break;
        case 3:
            m_seq.addJob(&GfMenuObjCharSelect::seqSpNiaChangeDr);
            break;
        default:
            m_seq.addJob(&GfMenuObjCharSelect::seqReturn);
            return true;
        }
        m_seq.addWait(2);
        m_seq.addJob(&GfMenuObjCharSelect::seqSpUpdateParty);
        m_seq.addJob(&GfMenuObjCharSelect::seqReturnChange);
        return true;
    }
    m_seq.addJob(&GfMenuObjCharSelect::seqReturn);
    return true;
}

bool GfMenuObjCharSelect::seqConfSpecialSelect() {
    if (!pad_6C0) {
        if (pad_748 != 4) {
            return true;
        }
        m_subContext->reset();
        GfMenuObjCommonText::openSelectItem(m_subContext, m_itemList, 2);
        pad_6C0 = true;
    }
    if (!m_subContext->isTerm()) {
        return false;
    }
    int index = -1;
    if (!m_subContext->m_results.empty()) {
        GfMenuCallContext::GfMenuResult result;
        m_subContext->popResult(result);
        index = result.m_id;
    }
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
    if (index != -1) {
        m_itemList->setIndex(index);
        m_seq.addJob(&GfMenuObjCharSelect::seqConfirmItem);
        pad_6C0 = false;
        return true;
    }
    m_seq.addJob(&GfMenuObjCharSelect::seqReturn);
    pad_6C0 = false;
    return true;
}

void GfMenuObjCharSelect::refreshCharSelect(unsigned int driver) {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    m_driverList->getIndex(false);
    unsigned int index = 0;
    for (unsigned int i = 0; i < m_driverList->getSize(); i++) {
        if (m_driverList->getContents(i).m_driver == driver) {
            index = i;
            break;
        }
    }
    m_driverList->setIndex(index);
    unsigned int selected = m_driverList->getContents(m_driverList->getIndex(false)).m_driver;
    adjustBladeList(m_drivers, m_blades, m_bladeLists, selected);
    const char* charLayouts[] = {"LAY_char_bl@01", "LAY_char_bl@02", "LAY_char_bl@03"};
    const char* statusLayouts[] = {"LAY_status_bl@01", "LAY_status_bl@02", "LAY_status_bl@03"};
    int num = 0;
    for (int i = 0; i < 3; i++) {
        unsigned int blade = m_drivers[index].m_blades[i];
        ui::UIObjectAcc chr(acc.searchChild(charLayouts[i]));
        ui::UIObjectAcc status(acc.searchChild(statusLayouts[i]));
        if (GfMenuObjUtil::isValidBlade(blade)) {
            chr.setDisp(true);
            status.setDisp(true);
            num++;
        } else {
            chr.setDisp(false);
            status.setDisp(false);
        }
    }
    requestEvent(acc.searchChild("LAY_char"), 0x101, num);
    ui::UIObjectAcc icon(acc.searchChild("LAY_status_dr"), "IMG_status_dr_icon");
    if (GfDataParty::isPartyBattleMember(selected)) {
        icon.setImageIndex(GfDataParty::getDriverPartyID(selected));
        icon.setDisp(true);
    } else {
        icon.setDisp(false);
    }
    GfMenuReference::setReferenceDriverID(0, selected);
    setDriverPos(acc, m_drivers, selected);
}

bool GfMenuObjCharSelect::seqStreamWaitSelectBefore() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int bladeNum = getEquipBladeNum(GfMenuReference::getReferenceDriverID(0), m_drivers);
    {
        ui::UIObjectAcc chr(acc.searchChild(bladeNum == 0 ? "LAY_char_dr_solo" : "LAY_char_dr"));
        int ctrl = GfMenuObjUtil::getCtrlID(chr.m_handle);
        if (ctrl != -1) {
            GfMenuObjUtil::stopCtrl(ctrl);
        }
    }
    {
        ui::UIObjectAcc chr(acc.searchChild("LAY_char_bl@01"));
        int ctrl = GfMenuObjUtil::getCtrlID(chr.m_handle);
        if (ctrl != -1) {
            GfMenuObjUtil::stopCtrl(ctrl);
        }
    }
    {
        ui::UIObjectAcc chr(acc.searchChild("LAY_char_bl@02"));
        int ctrl = GfMenuObjUtil::getCtrlID(chr.m_handle);
        if (ctrl != -1) {
            GfMenuObjUtil::stopCtrl(ctrl);
        }
    }
    {
        ui::UIObjectAcc chr(acc.searchChild("LAY_char_bl@03"));
        int ctrl = GfMenuObjUtil::getCtrlID(chr.m_handle);
        if (ctrl != -1) {
            GfMenuObjUtil::stopCtrl(ctrl);
        }
    }
    return true;
}

bool GfMenuObjCharSelect::seqStreamWaitSelect() {
    s_selectBusy = true;
    ui::UIObjectAcc acc(m_handle);
    unsigned int bladeNum = getEquipBladeNum(GfMenuReference::getReferenceDriverID(0), m_drivers);
    if (isChildStreaming(acc, bladeNum == 0 ? "IMG_char_dr_img_solo" : "IMG_char_dr_img")) {
        return false;
    }
    if (isChildStreaming(acc, "IMG_char_bl_img@01")) {
        return false;
    }
    if (isChildStreaming(acc, "IMG_char_bl_img@02")) {
        return false;
    }
    if (isChildStreaming(acc, "IMG_char_bl_img@03")) {
        return false;
    }
    for (int i = 0; i < 4; i++) {
        ui::UIObjectAcc chr(acc.searchChild(i == 0 && bladeNum == 0 ? "LAY_char_dr_solo" : getLayoutName(s_charLayouts, i)));
        GfMenuObject::hookCtrlEvent(chr.m_handle, startFadeIn(chr.m_handle, 1));
    }
    return true;
}

bool GfMenuObjCharSelect::seqWaitSelect() {
    if (s_selectBusy) {
        return false;
    }
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc chr(acc.searchChild("LAY_char"));
    if (!pad_741) {
        GfMenuObjMainMenu2::openCharChange(chr.m_handle, 3, false);
    }
    GfMenuObject::enableInput(chr.m_handle);
    GfMenuObjMainMenu2::setSystemKeyEnable(true);
    GfMenuObjOperationInfo::add(chr.m_handle, 0, 0, 0);
    GfMenuObjOperationInfo::changeText(chr.m_handle, 9, !GfMenuObjUtil::getMenuCondition(0x23));
    updateSpecialOperation();
    return true;
}

void GfMenuObjCharSelect::adjustBladeList(mm::mtl::FixedArray<DriverData, 5>& drivers,
                                          mm::mtl::FixedVector<unsigned short, 422>& blades,
                                          mm::mtl::FixedArray<GfMenuBladeList*, 3>& lists, unsigned int driver) {
    for (int i = 0; i < 5; i++) {
        if (drivers[i].m_driver == driver) {
            for (int j = 0; j < 3; j++) {
                unsigned int blade = drivers[i].m_blades[j];
                lists[j]->clear();
                if (blade != 0 && GfMenuObjUtil::isValidBlade(blade)) {
                    MenuBladeInfo info;
                    info.m_blade = blade;
                    info.m_creator = driver;
                    lists[j]->addContents(info);
                    lists[j]->setIndex(0);
                }
            }
            return;
        }
    }
}

bool GfMenuObjCharSelect::getCharBusy() {
    return s_charBusy;
}

void GfMenuObjCharSelect::CharDrListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(m_owner->m_handle);
    switch (event.m_type) {
    case 1:
        break;
    case 3:
        if (event.m_param0 == 0) {
            break;
        }
        if (event.m_param0 == 1) {
            s_selectBusy = false;
            GfMenuObject::enableInput(acc.searchChild("LAY_char"));
        }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjCharSelect::CharDrSoloListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(m_owner->m_handle);
    switch (event.m_type) {
    case 1:
        break;
    case 3:
        if (event.m_param0 == 0) {
            break;
        }
        if (event.m_param0 == 1) {
            s_selectBusy = false;
            GfMenuObject::enableInput(acc.searchChild("LAY_char"));
        }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjCharSelect::CharBlMoveListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    switch (event.m_type) {
    case 1:
        break;
    case 3:
        if (event.m_param0 == 0) {
            break;
        }
        if (event.m_param0 == 1) {
            s_charBusy = false;
        }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjCharSelect::CharDrMoveListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    switch (event.m_type) {
    case 1:
        break;
    case 3:
        if (event.m_param0 == 0) {
            break;
        }
        if (event.m_param0 == 1) {
            s_charBusy = false;
        }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjCharSelect::seqStreamWaitStatDrBefore() {
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc move(acc.searchChild("LAY_char_dr_move"));
    int ctrl = GfMenuObjUtil::getCtrlID(move.m_handle);
    if (ctrl != -1) {
        GfMenuObjUtil::stopCtrl(ctrl);
    }
    return true;
}

bool GfMenuObjCharSelect::seqStreamWaitStatBlBefore() {
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc move(acc.searchChild("LAY_char_bl_move"));
    int ctrl = GfMenuObjUtil::getCtrlID(move.m_handle);
    if (ctrl != -1) {
        GfMenuObjUtil::stopCtrl(ctrl);
    }
    return true;
}

bool GfMenuObjCharSelect::seqConfSpecialWaitError() {
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    m_seq.addJob(&GfMenuObjCharSelect::seqReturn);
    pad_6C0 = false;
    return true;
}

bool GfMenuObjCharSelect::seqSpHomuraToHikari() {
    GfGameUtil::changeHikariCurrent(true);
    return true;
}

bool GfMenuObjCharSelect::seqSpHikariToHomura() {
    GfGameUtil::changeHikariCurrent(false);
    return true;
}

bool GfMenuObjCharSelect::seqSpNiaChangeBl() {
    SCOM_NIA_BLADE::create(true);
    unsigned int num = 0;
    for (unsigned int i = 0; i < 3; i++) {
        if (GfGameParty::getDriverBdatId(i, static_cast<PTPOS>(0)) != 0) {
            num++;
        }
    }
    for (unsigned int i = 0; i < num; i++) {
        if (m_driverList->getContents(i).m_driver == 2) {
            unsigned short member = 0;
            switch (i) {
            case 0:
                member = num;
                break;
            case 1:
                member = num;
                break;
            case 2:
                member = 3;
                break;
            }
            GfMenuObjPartyStatus::memberChange(member, 0);
            return true;
        }
    }
    return true;
}

bool GfMenuObjCharSelect::seqSpNiaChangeDr() {
    SCOM_NIA_BLADE::create(false);
    return true;
}

bool GfMenuObjCharSelect::seqReturn() {
    ui::UIObjectAcc acc(m_handle, "LAY_char");
    requestEvent(acc.m_handle, 0x107, 0);
    return true;
}

bool GfMenuObjCharSelect::seqSpUpdateParty() {
    unsigned int driver = m_driverList->getContents(m_driverList->getIndex(false)).m_driver;
    GfMenuDriverList::PartySetup setup;
    setup.m_skipUnused = false;
    setup.m_convertDriver = false;
    setup.m_selectFlag = false;
    setup.m_type = 2;
    m_driverList->setupFromParty(setup);
    m_driverList->setIndex(0);
    for (unsigned int i = 0; i < m_driverList->getSize(); i++) {
        if (m_driverList->getContents(i).m_driver == driver) {
            m_driverList->setIndex(i);
            break;
        }
    }
    setPartyData(m_drivers, m_driverList);
    return true;
}

bool GfMenuObjCharSelect::seqReturnChange() {
    ui::UIObjectAcc acc(m_handle, "LAY_char");
    requestEvent(acc.m_handle, 0x107, 1);
    return true;
}

void GfMenuObjCharSelect::returnSubMenu() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x61);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x104;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjCharSelect::execCharPosScale(unsigned int param) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x61);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            requestEvent(handle, 0x109, param);
        }
    }
}

void GfMenuObjCharSelect::dispOnChar(unsigned int blade) {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        GfMenuObjCharSelectIra::dispOnChar(blade);
        return;
    }
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x61));
    if (acc.m_object != nullptr) {
        dispOnCopyChar(acc, blade);
    }
}

void GfMenuObjCharSelect::dispOffChar(unsigned int blade) {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        GfMenuObjCharSelectIra::dispOffChar(blade);
        return;
    }
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x61));
    if (acc.m_object != nullptr) {
        dispOffCopyChar(acc, blade);
    }
}

void GfMenuObjCharSelect::openBladeCustomize(unsigned int handle, unsigned int blade, unsigned short layerGroup) {
    GfMenuTypes::Param param;
    param.m_halves.m_type = 1;
    param.m_value = blade;
    GfMenuFullScreen::registLayerParam(0x27, param);
    GfMenuObject::changeFSSubLayer(handle, layerGroup, 0x27, true);
}

bool GfMenuObjCharSelect::attach(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x61));
    if (acc.m_object != nullptr) {
        GfMenuObject::startCallContext(context, 0x61, acc.m_handle);
        return true;
    }
    return false;
}
}  // namespace gf

template bool gf::GfMenuSequence<gf::GfMenuObjCharSelect, 8>::wait();

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjCharSelect, 8>>(const mm::mtl::Delegate<bool()>*);

namespace gf {

void GfMenuObjCharSelect::dispOffCopyChar(ui::UIObjectAcc& acc, unsigned int blade) {
    GfMenuObjUtil::CtrlParam param;
    if (blade != 0) {
        unsigned int move = acc.searchChild("LAY_char_bl_move");
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "warp_r";
        param.m_setDefault = true;
        param.m_startFlags = 10;
        GfMenuObjUtil::startCtrl(move, param, nullptr);
        GfMenuObjCmnStatus::closeBlStatus();
    } else {
        unsigned int move = acc.searchChild("LAY_char_dr_move");
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "warp_r";
        param.m_setDefault = true;
        param.m_startFlags = 10;
        GfMenuObjUtil::startCtrl(move, param, nullptr);
        GfMenuObjCmnStatus::closeDrStatus();
    }
}

int GfMenuObjCharSelect::refreshDriver(ui::UIObjectAcc acc, unsigned int driver) {
    setPartyData(m_drivers, m_driverList);
    adjustBladeList(m_drivers, m_blades, m_bladeLists, driver);
    for (unsigned int i = 0; i < m_driverList->getSize(); i++) {
        if (m_driverList->getContents(i).m_driver == driver) {
            m_driverList->setIndex(i);
            break;
        }
    }
    unsigned int index = m_driverList->getIndex(false);
    const char* charLayouts[] = {"LAY_char_bl@01", "LAY_char_bl@02", "LAY_char_bl@03"};
    const char* statusLayouts[] = {"LAY_status_bl@01", "LAY_status_bl@02", "LAY_status_bl@03"};
    int num = 0;
    for (int i = 0; i < 3; i++) {
        unsigned int blade = m_drivers[index].m_blades[i];
        ui::UIObjectAcc chr(acc.searchChild(charLayouts[i]));
        ui::UIObjectAcc status(acc.searchChild(statusLayouts[i]));
        if (GfMenuObjUtil::isValidBlade(blade)) {
            chr.setDisp(true);
            status.setDisp(true);
            num++;
        } else {
            chr.setDisp(false);
            status.setDisp(false);
        }
    }
    return num;
}

void GfMenuObjCharSelect::dispOnCopyChar(ui::UIObjectAcc& acc, unsigned int blade) {
    GfMenuObjUtil::CtrlParam param;
    if (blade != 0) {
        unsigned int move = acc.searchChild("LAY_char_bl_move");
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_r";
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(move, param, nullptr);
        GfMenuObjCmnStatus::openBlStatus(1, -1);
    } else {
        unsigned int move = acc.searchChild("LAY_char_dr_move");
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_r";
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(move, param, nullptr);
        GfMenuObjCmnStatus::openDrStatus(1, -1);
    }
}

void GfMenuObjCharSelect::DetailListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        m_detailMode = 0;
        break;
    case 0x21: {
        int mode = event.m_param0;
        acc.setDisp(true);
        GfMenuObjMainMenu2::setSubIndexText(mode != 0 ? 19 : 18);
        GfMenuObject::enableInput(acc.m_handle);
        m_detailMode = mode;
        break;
    }
    case 8:
        if (event.m_param1 == 2) {
            GfMenuObjMainMenu2::setSubIndexText(m_detailMode != 0 ? 3 : 2);
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

unsigned int GfMenuObjCharSelect::getEquipBladeNum(unsigned int driver, const mm::mtl::FixedArray<DriverData, 5>& drivers) {
    unsigned int num = 0;
    for (int i = 0; i < 5; i++) {
        if (drivers[i].m_driver == driver) {
            for (int j = 0; j < 3; j++) {
                if (GfMenuObjUtil::isValidBlade(drivers[i].m_blades[j])) {
                    num++;
                }
            }
        }
    }
    return num;
}

void GfMenuObjCharSelect::setCharOffset(ui::UIObjectAcc& acc, const mm::mtl::FixedArray<DriverData, 5>& drivers,
                                        unsigned int driver) {
    for (int i = 0; i < 5; i++) {
        if (drivers[i].m_driver == driver) {
            setCharPosScale(0, driver, 0, getEquipBladeNum(driver, drivers) == 0);
            for (int j = 0; j < 3; j++) {
                unsigned int blade = drivers[i].m_blades[j];
                if (GfMenuObjUtil::isValidBlade(blade)) {
                    setCharPosScale(1, blade, j + 1, false);
                }
            }
        }
    }
}

unsigned int GfMenuObjCharSelect::setDriverPos(ui::UIObjectAcc& acc, mm::mtl::FixedArray<DriverData, 5>& drivers,
                                               unsigned int driver) {
    unsigned int bladeNum = getEquipBladeNum(driver, drivers);
    ui::UIObjectAcc status(acc.searchChild("LAY_status_dr"));
    ui::UIObjectAcc dr(acc.searchChild("LAY_char_dr"));
    ui::UIObjectAcc solo(acc.searchChild("LAY_char_dr_solo"));
    if (bladeNum != 0) {
        dr.setDisp(true);
        solo.setDisp(false);
        acc.setLayout(status.m_handle, "driver_index_layout_normal");
    } else {
        dr.setDisp(false);
        solo.setDisp(true);
        acc.setLayout(status.m_handle, "driver_index_layout_solo");
    }
    return bladeNum;
}

void GfMenuObjCharSelect::StatusListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    ui::UIObjectAcc owner(m_owner->m_handle);
    switch (event.m_type) {
    case 1:
        break;
    case 0x105:
        acc.getPos(m_owner->m_statusPos);
        switch (event.m_param0) {
        case 0x1D:
        case 0x20: {
            const char* name = event.m_param0 == 0x1D ? "drindex_atst" : "drindex_acs";
            ui::UIObjectAcc main(owner.searchChild("LAY_main"));
            mm::Rect<short> rect;
            main.getLayoutRect(name, rect);
            mm::Pnt<short> pos;
            pos.x = rect.x;
            pos.y = rect.y;
            acc.setPos(pos);
            break;
        }
        case 0x1E: {
            ui::UIObjectAcc main(owner.searchChild("LAY_main"));
            mm::Rect<short> rect;
            main.getLayoutRect("drindex_atst", rect);
            mm::Pnt<short> pos;
            pos.x = -(m_owner->m_statusPos.x + rect.w);
            pos.y = rect.y;
            acc.setPos(pos);
            break;
        }
        }
        break;
    case 0x106:
        acc.setPos(m_owner->m_statusPos);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf
