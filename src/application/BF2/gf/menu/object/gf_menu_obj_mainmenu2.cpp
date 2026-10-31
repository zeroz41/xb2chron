#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/SelectionChecker.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjMainMenu2/ChrChangeListener.h"
#include "classes/gf/GfMenuObjMainMenu2/CloseListener.h"
#include "classes/gf/GfMenuObjMainMenu2/ContentsListener.h"
#include "classes/gf/GfMenuObjMainMenu2/IndexListener.h"
#include "classes/gf/GfMenuObjMainMenu2/MainListener.h"
#include "classes/gf/TUnk_B5F9E8.h"
#include "classes/gf/TUnk_B625A0.h"
#include "classes/gf/GfMenuGameAdapter.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UISelectObjList.h"
#include "mm/Rect.h"
#include "mm/Pnt.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuSoundManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "gf/GfPartySelect.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuObjPopup.h"
#include "gf/GfMenuBdat.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/DataParamAcc.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

unsigned int GfMenuObjMainMenu2::s_openMenuID;
bool GfMenuObjMainMenu2::s_worldMapOpen;
bool GfMenuObjMainMenu2::s_cancelEnable;
bool GfMenuObjMainMenu2::s_closeKeyLocked;
bool GfMenuObjMainMenu2::s_charMenuOpen;
unsigned char GfMenuObjMainMenu2::s_bgOpen;
unsigned int GfMenuObjMainMenu2::s_index;
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB890). initialize stores how many
// contents ids it collected (m_contentsIds' size); setupMainMenu and the contents listener read it.
static unsigned int s_contentsCount;

GfMenuObjMainMenu2::GfMenuObjMainMenu2(unsigned int handle)
    : GfMenuObject(handle), m_cursor(nullptr), m_context(nullptr), pad_38(0), m_contentsIndex(-1), pad_40(-1), m_menuId(0),
      m_driverList(nullptr), m_bladeList(nullptr), m_checker(nullptr), pad_88(0), pad_8C(false), m_seq(this),
      m_jobStarted(false) {
    m_driverList = GfMenuDriverList::create();
    m_bladeList = GfMenuBladeList::create();
    m_checker = new (getAllocator(ALLOCATOR(0)), __FILE__, 210, 8) SelectionChecker;
    s_openMenuID = 0;
    s_charMenuOpen = false;
    s_bgOpen = 0;
}

GfMenuObjMainMenu2::~GfMenuObjMainMenu2() {
    if (m_bladeList != nullptr) {
        m_bladeList->release();
        m_bladeList = nullptr;
    }
    if (m_driverList != nullptr) {
        m_driverList->release();
        m_driverList = nullptr;
    }
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_checker != nullptr) {
        delete m_checker;
        m_checker = nullptr;
    }
    s_openMenuID = 0;
    s_bgOpen = 0;
}

void GfMenuObjMainMenu2::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned char* bdat = GfDataBdat::getFP(GfMenuObjUtil::fn_710048FD30(3) ? 0x180 : 0x17F);
    m_contentsIds.clear();
    for (unsigned int i = 0; i < (unsigned int)Bdat::getIdCount(bdat); i++) {
        if (GfMenuObjUtil::fn_710048FD30(3)) {
            if (7 == Bdat::getIdTop(bdat) + i || Bdat::getIdTop(bdat) + i == 8) {
                continue;
            }
        } else {
            if (Bdat::getIdTop(bdat) + i == 8 && !TUnk_B5F9E8::fn_71003828CC()) {
                continue;
            }
            if (Bdat::getIdTop(bdat) + i == 9 && TUnk_B5F9E8::fn_71003828CC()) {
                continue;
            }
        }
        m_contentsIds.push_back(Bdat::getIdTop(bdat) + i);
    }
    s_contentsCount = m_contentsIds.size();
    unsigned int main = acc.searchChild("LAY_main");
#line 276
    MainListener* mainListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main, mainListener);
    if (mainListener != nullptr) {
        mainListener->release();
    }
    GfMenuObject::attachExternalCall(0x5F, main);
    unsigned int contents = acc.searchChild("LAY_contents");
    ContentsListener* contentsListener =
#line 282
        new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ContentsListener(this);
    contentsListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(contents, contentsListener);
    if (contentsListener != nullptr) {
        contentsListener->release();
    }
    unsigned int index = acc.searchChild("LAY_index");
#line 286
    IndexListener* indexListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) IndexListener(this);
    indexListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(index, indexListener);
    if (indexListener != nullptr) {
        indexListener->release();
    }
    unsigned int close = acc.searchChild("LAY_close");
#line 291
    CloseListener* closeListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) CloseListener(this);
    closeListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(close, closeListener);
    if (closeListener != nullptr) {
        closeListener->release();
    }
    unsigned int chrChange = acc.searchChild("LAY_chr_change");
    ChrChangeListener* chrListener =
#line 299
        new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ChrChangeListener(this);
    chrListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(chrChange, chrListener);
    if (chrListener != nullptr) {
        chrListener->release();
    }
    m_context = GfMenuCallContext::create();
    acc.setDispChild(GfMenuManager::isClearCheck(), "IMG_clear_mark");
    s_worldMapOpen = false;
    GfMenuObject::initialize();
}

void GfMenuObjMainMenu2::initChrChangeDr(ui::UIObjectAcc& acc, GfMenuDriverList* list) {
    ui::UIObjectAcc change(acc.searchChild("LAY_chr_change"));
    mm::mtl::FixStr<32> name;
    unsigned int count = change.countChild("LAY_chr_change_dr@%02d", 1);
    mm::mtl::FixedVector<unsigned short, 32> drivers;
    GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE(0), 0);
    unsigned int party = drivers.size();
    for (unsigned int i = 0; i < count; i++) {
        name.format("IMG_chr_change_dr_icon@%02d", i + 1);
        GfMenuCharDataAdapter* adapter =
            GfMenuCharDataAdapter::createFromDriverList(change.searchChild(name.m_str), 3, list, i, false);
        if (adapter != nullptr) {
            name.format("LAY_chr_change_dr@%02d", i + 1);
            adapter->m_rowHandle = change.searchChild(name.m_str);
        }
        name.format("IMG_chr_change_no@%02d", i + 1);
        ui::UIObjectAcc number(change.searchChild(name.m_str));
        if (i < party) {
            number.setImageIndex(i);
            number.setDisp(true);
        } else {
            number.setDisp(false);
        }
    }
}

void GfMenuObjMainMenu2::initChrChangeBl(ui::UIObjectAcc& acc, GfMenuBladeList* list) {
    ui::UIObjectAcc change(acc.searchChild("LAY_chr_change"));
    mm::mtl::FixStr<32> name;
    unsigned int count = change.countChild("LAY_chr_change_bl@%02d", 1);
    for (unsigned int i = 0; i < count; i++) {
        name.format("IMG_chr_change_bl_icon@%02d", i + 1);
        GfMenuCharDataAdapter* adapter =
            GfMenuCharDataAdapter::createFromBladeList(change.searchChild(name.m_str), 3, list, i, false);
        if (adapter != nullptr) {
            name.format("LAY_chr_change_bl@%02d", i + 1);
            adapter->m_rowHandle = change.searchChild(name.m_str);
        }
    }
}

void GfMenuObjMainMenu2::finalize() {
    GfMenuSoundManager::fadeInFieldBgm(1.0f);
    GfMenuObject::finalize();
}

void GfMenuObjMainMenu2::update() {
    if (m_menuId != 0x28) {
        s_openMenuID = m_menuId;
    }
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjMainMenu2::setupMainMenu(ui::UIObjectAcc& acc, const mm::mtl::FixedVector<unsigned int, 8>& ids) {
    mm::mtl::FixStr<32> name;
    mm::mtl::FixStr<32> layout;
    for (unsigned int i = 0; i < s_contentsCount; i++) {
        unsigned int no = i + 1;
        name.format("TXT_contents_item@%02d", no);
        unsigned int item = acc.searchChild(name.m_str);
        if (item == 0) {
            continue;
        }
        setContentsText(item, ids[i] - 1);
        if (GfMenuObjUtil::fn_710048FD30(3)) {
            if (ids.size() == 7) {
                name.format("IMG_contents_item_bg@%02d", no);
                layout.format("mnu075_menu_anim_%02d", no);
                acc.setLayout(acc.searchChild(name.m_str), layout.m_str);
                name.format("TXT_contents_item@%02d", no);
                layout.format("text%02d", no);
                acc.setLayout(acc.searchChild(name.m_str), layout.m_str);
                name.format("LAY_contents_item@%02d", no);
                acc.setDispChild(true, name.m_str);
            }
        } else {
            if (ids.size() == 8) {
                name.format("IMG_contents_item_bg@%02d", no);
                layout.format("mnu075_menu_anim_pres%02d", no);
                acc.setLayout(acc.searchChild(name.m_str), layout.m_str);
                name.format("TXT_contents_item@%02d", no);
                layout.format("text_pres%02d", no);
                acc.setLayout(acc.searchChild(name.m_str), layout.m_str);
                name.format("LAY_contents_item@%02d", no);
                acc.setDispChild(true, name.m_str);
            }
        }
        GfMenuObjUtil::setColMulandAdd(item, "txt_main_title");
    }
    GfMenuGameAdapter::create(acc.searchChild("TXT_info_time"), 0, true);
    GfMenuGameAdapter::create(acc.searchChild("TXT_info_money"), 1, true);
    if (GfMenuManager::fn_710035A6BC()) {
        acc.setDispChild(TUnk_B625A0::fn_710040BF88(true), "LAY_gift_icon");
    }
    ui::UIObjectAcc bg(acc.searchChild("IMG_contents_bg"));
    bg.startAnimation("loop", false);
}

bool GfMenuObjMainMenu2::seqExecTerm() {
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc main(acc.searchChild("LAY_main"));
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        if (m_jobStarted) {
            m_jobStarted = false;
        } else if (!GfGameManager::isEvent(false) && !GfGameManager::isTalking()) {
            if (!s_charMenuOpen ||
                (GfDataBlade::fn_7100231884() != 0x2B38 && GfDataBlade::fn_7100231884() != 0x2B74)) {
                GfMenuObjPopup::continuePickup(0x14);
            }
        }
        GfMenuReference::fn_7100368380(6, false);
    } else {
        if (m_jobStarted) {
            m_jobStarted = false;
        } else {
            GfMenuObjPopup::continuePickup(0x14);
        }
    }
    main.setTerm();
    return true;
}

void GfMenuObjMainMenu2::setDispGold(bool disp) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x5F);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            GfMenuObjUtil::setChildDisp(handle, "LAY_info_money", disp);
            GfMenuObjUtil::setChildDisp(handle, "LAY_info_time", disp);
            GfMenuObjUtil::setChildDisp(handle, "LAY_clear_mark", disp);
        }
    }
}

void GfMenuObjMainMenu2::setCloseKeyEnable(bool enable) {
    if (GfMenuObjUtil::fn_710048FD30(3) && s_closeKeyLocked) {
        return;
    }
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        GfMenuObject::setInputActionEnable(acc.searchChild("LAY_close"), 3, enable);
    }
}

void GfMenuObjMainMenu2::setSystemKeyEnable(bool enable) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x106;
        event.m_param0 = enable;
        ui::UIManager::sys()->requestObjectEvent(acc.m_handle, event, 0.0f);
        s_cancelEnable = enable;
    }
}

void GfMenuObjMainMenu2::IndexListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        acc.searchChild("TXT_index");
        GfMenuObjUtil::setChildDisp(acc.m_handle, "LAY_index", false);
        acc.searchChild("TXT_index_shadow");
        GfMenuObjUtil::setChildDisp(acc.m_handle, "LAY_index", false);
        ui::UIObjectAcc icon(acc.searchChild("IMG_index_icon"));
        icon.setImageIndex(0);
        acc.setDisp(true);
    } else if (event.m_type == 0x102) {
        unsigned int index = event.m_param0;
        ui::UIObjectAcc title(acc.searchChild("LAY_title"));
        if (index != 0) {
            setContentsSubText(acc.searchChild("TXT_index"), index, acc.m_handle);
            setContentsSubText(acc.searchChild("TXT_index_shadow"), index, acc.m_handle);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 1;
            param.m_curve = 1;
            param.m_time = 0.3f;
            GfMenuObjUtil::startCtrl(title.m_handle, param, nullptr);
            title.setDisp(true);
        } else {
            title.setDisp(false);
        }
        if (GfMenuObjUtil::fn_710048FD30(3)) {
            s_index = index;
        }
    } else if (event.m_type == 0x101) {
        int index = event.m_param0;
        unsigned char* fp = GfDataBdat::getFP(GfMenuObjUtil::fn_710048FD30(3) ? 0x180 : 0x17F);
        unsigned int id = m_owner->m_contentsIds[index];
        unsigned int text = (unsigned short)Bdat::getVal(fp, "subTitle", id);
        if (handle != 0) {
            ui::EventData sub;
            sub.m_type = 0x102;
            sub.m_param0 = text;
            ui::UIManager::sys()->requestObjectEvent(handle, sub, 0.0f);
        }
        unsigned int image = (unsigned short)Bdat::getVal(fp, "titleIcon", id);
        ui::UIObjectAcc icon(acc.searchChild("IMG_index_icon"));
        icon.setImageIndex(image);
    } else {
        UIObjectListener::reciveEvent(event, handle);
    }
}

void GfMenuObjMainMenu2::setContentsSubText(unsigned int handle, unsigned int index, unsigned int owner) {
    bool disp = false;
    if (index != 0) {
        ui::UIObjectAcc acc(handle);
        unsigned int name = (unsigned short)Bdat::getVal(GfDataBdat::getFP(0x148), "name", index);
        acc.setText(ui::UIStr(GfDataBdat::getFP(0x119), name));
        disp = true;
    }
    GfMenuObjUtil::setChildDisp(owner, "LAY_index", disp);
}

void GfMenuObjMainMenu2::closeCharChange() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc change(acc.searchChild("LAY_chr_change"));
        ui::EventData event;
        event.m_type = 0x22;
        ui::UIManager::sys()->requestObjectEvent(change.m_handle, event, 0.0f);
    }
}

void GfMenuObjMainMenu2::fn_71004323A8(ui::UIObjectAcc& acc, GfMenuDriverList* list) {
    ui::UIObjectAcc change(acc.m_handle, "LAY_chr_change_dr");
    mm::mtl::FixStr<32> name;
    unsigned int party;
    {
        mm::mtl::FixedVector<unsigned short, 32> drivers;
        GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE(0), 0);
        party = drivers.size();
    }
    for (unsigned int i = 0; i < list->getSize(); i++) {
        name.format("IMG_chr_change_dr_cursor@%02d", i + 1);
        ui::UIObjectAcc cursor(change.m_handle, name.m_str);
        name.format("IMG_chr_change_no@%02d", i + 1);
        ui::UIObjectAcc number(change.m_handle, name.m_str);
        if (i < party) {
            if (GfMenuObjUtil::fn_710048FD30(3)) {
                unsigned int driver = list->getContents(i).m_driver;
                if (GfDataDriver::isActivateUnuse(driver)) {
                    number.setImageIndex(i);
                } else {
                    number.setImageIndex(GfGameParty::getPartyId(3, driver));
                }
            } else {
                number.setImageIndex(i);
            }
            number.setDisp(true);
        } else {
            number.setDisp(false);
        }
        if (i == list->getIndex(false)) {
            cursor.setDisp(true);
            cursor.startAnimation("loop", false);
        } else {
            cursor.stopAnimation();
            cursor.setDisp(false);
        }
    }
}

void GfMenuObjMainMenu2::refreshCharChangeBl(ui::UIObjectAcc& acc, GfMenuBladeList* list) {
    ui::UIObjectAcc change(acc.m_handle, "LAY_chr_change_bl");
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < list->getPageSize(); i++) {
        name.format("IMG_chr_change_bl_cursor@%02d", i + 1);
        ui::UIObjectAcc cursor(change.m_handle, name.m_str);
        if (i == list->getIndex(true)) {
            cursor.setDisp(true);
            cursor.startAnimation("loop", false);
        } else {
            cursor.stopAnimation();
            cursor.setDisp(false);
        }
    }
    ui::UIObjectAcc left(change.m_handle, "IMG_chr_change_bl_icon_l");
    left.setDisp(false);
    unsigned int first = list->getPageIndex(0);
    if (first != 0) {
        DataParamAcc blade(4, list->getContents(first - 1).m_blade, GimmickType(0));
        int icon = GfMenuObjUtil::getFaceIconID(blade);
        if (icon != 0) {
            left.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
            left.setDisp(true);
        }
    }
    ui::UIObjectAcc right(change.m_handle, "IMG_chr_change_bl_icon_r");
    right.setDisp(false);
    unsigned int count = list->getPageSize();
    if (count != 0) {
        unsigned int last = list->getPageIndex(count - 1);
        if (last < list->getSize() - 1U) {
            DataParamAcc blade(4, list->getContents(last + 1).m_blade, GimmickType(0));
            int icon = GfMenuObjUtil::getFaceIconID(blade);
            if (icon != 0) {
                right.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
                right.setDisp(true);
            }
        }
    }
}

void GfMenuObjMainMenu2::openChrChange2Sub(ui::UIObjectAcc& acc, ChrChangeParam& param) {
    mm::Rect<short> icon1;
    acc.getLayoutRect("chr_icon_1", icon1);
    mm::Rect<short> icon2;
    acc.getLayoutRect("chr_icon_2", icon2);
    if (param.m_listKind == 0) {
        unsigned int count = param.m_driverList->getSize();
        GfMenuObjUtil::placeObjectHLeft(acc.m_handle, "LAY_chr_change_dr@%02d", count,
                                        mm::Pnt<short>(icon1.x + icon1.w / 2, icon1.y + icon1.h / 2),
                                        icon2.x - icon1.x);
    } else {
        unsigned int count = param.m_bladeList->getSize();
        if (count > 5) {
            count = 5;
        }
        GfMenuObjUtil::placeObjectHLeft(acc.m_handle, "LAY_chr_change_bl@%02d", count,
                                        mm::Pnt<short>(icon1.x + icon1.w / 2, icon1.y + icon1.h / 2),
                                        icon2.x - icon1.x);
    }
}

void GfMenuObjMainMenu2::inputChrChangeSub(ui::UIObjectAcc& acc, ChrChangeParam& param, int index) {
    switch (param.m_listKind) {
    case 1:
    case 2: {
        if (index == -1) {
            return;
        }
        param.m_bladeList->setIndex(index);
        refreshCharChangeBl(acc, param.m_bladeList);
        if (GfMenuReference::getReferenceBladeID(0) ==
            param.m_bladeList->getContents(param.m_bladeList->getIndex(false)).m_blade) {
            return;
        }
        ui::EventData event;
        event.m_type = 0x140;
        event.m_param0 = param.m_bladeList->getContents(param.m_bladeList->getIndex(false)).m_blade;
        event.m_param1 = index;
        GfMenuObject::sendEvent(param.m_target, event, 0.0f);
        break;
    }
    case 0: {
        if (index == -1) {
            return;
        }
        param.m_driverList->setIndex(index);
        fn_71004323A8(acc, param.m_driverList);
        if (GfMenuReference::getReferenceDriverID(0) ==
            param.m_driverList->getContents(param.m_driverList->getIndex(false)).m_driver) {
            return;
        }
        ui::EventData event;
        event.m_type = 0x140;
        event.m_param0 = param.m_driverList->getContents(param.m_driverList->getIndex(false)).m_driver;
        event.m_param1 = index;
        GfMenuObject::sendEvent(param.m_target, event, 0.0f);
        break;
    }
    }
}

void GfMenuObjMainMenu2::closeChrChangeSub(ui::UIObjectAcc& acc, ChrChangeParam& param) {
    unsigned int list;
    if (param.m_listKind == 0) {
        list = acc.searchChild("LAY_chr_change_dr");
    } else {
        list = acc.searchChild("LAY_chr_change_bl");
    }
    GfMenuObjUtil::CtrlParam ctrl;
    ctrl.m_methods = 0x10000000;
    ctrl.m_motionLib = "cmn_fade_motion_lr";
    ctrl.m_motion = "fade_out_r";
    ctrl.m_setDefault = true;
    ctrl.m_startFlags = 10;
    ctrl.m_eventId = 2;
    int slot = GfMenuObjUtil::startCtrl(list, ctrl, nullptr);
    GfMenuObjUtil::startCtrl(acc.searchChild("LAY_chr_change_input"), ctrl, nullptr);
    ctrl = GfMenuObjUtil::CtrlParam();
    ctrl.m_methods = 2;
    ctrl.m_time = 0.2f;
    GfMenuObjUtil::startCtrl(acc.searchChild("IMG_chr_change_base"), ctrl, nullptr);
    GfMenuObject::hookCtrlEvent(acc.m_handle, slot);
    GfMenuObject::disableInput(acc.m_handle);
}

bool GfMenuObjMainMenu2::isOpenCharMenu() {
    if (GfMenuObjUtil::fn_710048FD30(3) && s_charMenuOpen) {
        return true;
    }
    return s_openMenuID == 0x27 || s_openMenuID == 0x12D;
}

bool GfMenuObjMainMenu2::fn_7100432E2C() {
    return GfMenuObjUtil::fn_710048FD30(3) && s_bgOpen != 0;
}

bool GfMenuObjMainMenu2::fn_7100432E5C() {
    return s_worldMapOpen;
}

unsigned int GfMenuObjMainMenu2::fn_7100432E6C() {
    return GfMenuObjUtil::fn_710048FD30(3) ? s_index : 0;
}

void GfMenuObjMainMenu2::ChrChangeListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        initChrChangeDr(owner, m_owner->m_driverList);
        initChrChangeBl(owner, m_owner->m_bladeList);
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        m_chr.m_state = 0;
        m_chr.m_listKind = -1;
        m_chr.m_subHandle = 0;
        break;
    case 3:
        switch (event.m_param0) {
        case 0:
            return;
        case 1:
            if (m_chr.m_listKind == 1 || m_chr.m_listKind == 2) {
                GfMenuObject::resetInputSelection(acc.m_handle);
                GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_bladeList);
            } else if (m_chr.m_listKind == 0) {
                GfMenuObject::resetInputSelection(acc.m_handle);
                GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_driverList);
            }
            if (m_owner->pad_88 != 0) {
                GfMenuObject::enableInput(acc.m_handle);
            } else {
                GfMenuObject::disableInput(acc.m_handle);
            }
            break;
        case 2:
            GfMenuObject::termCallContext(acc.m_handle);
            acc.setDisp(false);
            break;
        case 3:
            sendEvent(handle, 0x10C, 0);
            break;
        }
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        ChrChangeParam param;
        param.m_listKind = m_chr.m_listKind;
        param.m_target = m_owner->pad_88;
        param.m_driverList = m_owner->m_driverList;
        param.m_bladeList = m_owner->m_bladeList;
        inputChrChangeSub(acc, param, index);
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonTab();
        }
        break;
    }
    case 0x21: {
        int kind = event.m_param0;
        int mode = event.m_param2;
        m_owner->pad_88 = event.m_param1;
        ChrChangeParam param;
        if (kind == 3) {
            kind = 0;
            param.pad_2C = false;
        }
        param.m_listKind = kind;
        param.pad_04 = mode == 1;
        param.m_prevKind = m_chr.m_listKind;
        param.m_isOpen = m_chr.m_state == 1;
        param.m_target = m_owner->pad_88;
        param.m_driverList = m_owner->m_driverList;
        param.m_bladeList = m_owner->m_bladeList;
        param.m_driverId = GfMenuReference::getReferenceDriverID(0);
        param.m_subHandle = m_chr.m_subHandle;
        unsigned int sub = 0;
        if (openChrChangeSub(acc, param, sub)) {
            m_chr.m_state = 1;
            m_chr.m_listKind = kind;
            m_chr.m_subHandle = sub;
        }
        break;
    }
    case 0x22: {
        ChrChangeParam param;
        param.m_listKind = m_chr.m_listKind;
        closeChrChangeSub(acc, param);
        m_chr.m_state = 0;
        break;
    }
    case 0x109:
        m_owner->pad_88 = 0;
        break;
    case 0x10C: {
        ChrChangeParam param;
        param.m_listKind = m_chr.m_listKind;
        param.m_driverList = m_owner->m_driverList;
        param.m_bladeList = m_owner->m_bladeList;
        openChrChange2Sub(acc, param);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

namespace {
// Inferred name, not the original's: 3.0.1 and 1.0.0 both inline it into CloseListener::reciveEvent (no symbol);
// the frame shows an inlined helper (its event sits above the listener's own UI accessors). What it does: sends an
// event of that type to the main menu object attached at 0x5F, when there is one (as setSubLayer, setGuideText and
// execMapJump do with theirs).
inline void sendMainMenuEvent(unsigned short type) {
    ui::UIObjectAcc main(GfMenuObject::getAttachedObject(0x5F));
    if (main.m_object != nullptr) {
        ui::EventData event;
        event.m_type = type;
        ui::UIManager::sys()->requestObjectEvent(main.m_handle, event, 0.0f);
    }
}
}  // namespace

void GfMenuObjMainMenu2::CloseListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(handle);
        s_cancelEnable = false;
        s_closeKeyLocked = false;
        break;
    case 8:
        switch (event.m_param1) {
        case 2:
            if (!s_cancelEnable || GfMenuManager::isSwitchingFullScreen()) {
                break;
            }
            if (m_owner->m_menuId != 0) {
                GfMenuObject::returnFSSubLayer(handle, 1);
                sendMainMenuEvent(0x105);
                GfMenuObjUtil::playSECommonCancel();
                break;
            }
            sendEvent(owner.searchChild("LAY_main"), 0x107, 0);
            GfMenuObject::disableInput(handle);
            break;
        case 3:
            if (GfMenuManager::isSwitchingFullScreen()) {
                break;
            }
            sendEvent(owner.searchChild("LAY_main"), 0x107, 0);
            GfMenuObject::disableInput(handle);
            break;
        }
        break;
    case 0x21:
        GfMenuObject::enableInput(handle);
        s_cancelEnable = true;
        break;
    case 0x10D:
        GfMenuObjOperationInfo::open(handle, 0, 0, 0);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjMainMenu2::getContentsText(unsigned int index, unsigned char*& bdat, unsigned int& text) {
    unsigned char* menu = GfDataBdat::getFP(GfMenuObjUtil::fn_710048FD30(3) ? 0x180 : 0x17F);
    int top = Bdat::getIdTop(menu);
    if (GfMenuObjUtil::getMenuCondition((unsigned short)Bdat::getVal(menu, "useCond", top + index))) {
        bdat = GfDataBdat::getFP(0x117);
        text = (unsigned short)Bdat::getVal(menu, "title", top + index);
    } else {
        bdat = GfDataBdat::getFP(0xF5);
        text = 0x67C;
    }
}

void GfMenuObjMainMenu2::setSubIndexText(unsigned int text) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x5F);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x102;
            event.m_param0 = text;
            ui::UIObjectAcc acc(handle);
            ui::UIManager::sys()->requestObjectEvent(acc.searchChild("LAY_index"), event, 0.0f);
        }
    }
}

void GfMenuObjMainMenu2::cancelEnableMainMenu(bool enable) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x106;
        event.m_param0 = enable;
        ui::UIManager::sys()->requestObjectEvent(acc.m_handle, event, 0.0f);
        s_cancelEnable = enable;
    }
}

void GfMenuObjMainMenu2::fn_71004335FC(bool lock) {
    if (GfMenuObjUtil::fn_710048FD30(3) && s_closeKeyLocked != lock) {
        if (lock) {
            setCloseKeyEnable(false);
        }
        s_closeKeyLocked = lock;
    }
}

void GfMenuObjMainMenu2::openCharChange(unsigned int handle, unsigned int kind, bool flag) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc change(acc.searchChild("LAY_chr_change"));
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0 = kind;
        event.m_param1 = handle;
        event.m_param2 = flag;
        ui::UIManager::sys()->requestObjectEvent(change.m_handle, event, 0.0f);
    }
}

void GfMenuObjMainMenu2::disableCharChange() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc change(acc.searchChild("LAY_chr_change"));
        ui::EventData event;
        event.m_type = 0x109;
        ui::UIManager::sys()->requestObjectEvent(change.m_handle, event, 0.0f);
        GfMenuObject::disableInput(change.m_handle);
    }
}

void GfMenuObjMainMenu2::registOpenParam(const OpenParam& param) {
    GfMenuTypes::Param layer;
    layer.m_menuId = param.m_page;
    GfMenuFullScreen::registLayerParam(GfMenuFullScreen::getScreenLayerID(1), layer);
}

void GfMenuObjMainMenu2::setSubLayer(unsigned int layer) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        sendEvent(acc.m_handle, 0x108, layer);
    }
}

void GfMenuObjMainMenu2::setGuideText(unsigned int text) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        sendEvent(acc.m_handle, 0x10A, text);
    }
}

void GfMenuObjMainMenu2::dispCloseButton() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        sendEvent(acc.searchChild("LAY_close"), 0x10D, 0);
    }
}

void GfMenuObjMainMenu2::execMapJump() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        sendEvent(acc.m_handle, 0x10E, 0);
    }
}

bool SelectionChecker::isEnableSelect(unsigned int id, int select) {
    unsigned char* bdat = GfDataBdat::getFP(GfMenuObjUtil::fn_710048FD30(3) ? 0x180 : 0x17F);
    return GfMenuObjUtil::getMenuCondition(static_cast<unsigned short>(
        Bdat::getVal(bdat, "useCond", Bdat::getIdTop(bdat) + select)));
}

}  // namespace gf
