#include "gf/SDataPouch.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuPouchAdapter.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfMenuObjSort.h"
#include "classes/gf/GfMenuObjPouch2.h"
#include "classes/gf/GfMenuObjPouch2/MainListener.h"
#include "classes/gf/GfMenuObjPouch2/SlotListener.h"
#include "classes/gf/GfMenuObjPouch2/ItemListListener.h"
#include "classes/gf/GfMenuObjPouch2/FilterListener2.h"
#include "classes/gf/GfMenuObjPouch2/PartyInfoListener.h"
#include "classes/gf/GfMenuObjPouch2/ResultListener.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameVoice.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataItem.h"
#include "classes/gf/GfMenuBladeList.h"
#include "gf/GfMenuItemUtil.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuObjSort.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfPouchUtil.h"
#include "gf/SDataPouch.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"
#include "mm/mtl/Delegate.h"

namespace gf {

namespace {
// 1.0.0's GfMenuObjPouch2::setFadeIn/setFadeOut (0x71004B613C, 0x71004B6244; out of line there, 3.0.1 inlines
// them with type 0): the common fade of that type (0 the preset, 1 from the left, 2 from the right), heard by the
// handle's object. File statics here: the names are 1.0.0's, the placement is not.
inline int setFadeIn(unsigned int handle, unsigned int type) {
    int ctrl = -1;
    switch (type) {
    case 0: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
        break;
    }
    case 1: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l_early";
        param.m_eventId = 1;
        ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
        break;
    }
    case 2: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_r_early";
        param.m_eventId = 1;
        ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
        break;
    }
    }
    GfMenuObject::hookCtrlEvent(handle, ctrl);
    return ctrl;
}

inline int setFadeOut(unsigned int handle, unsigned int type) {
    int ctrl = -1;
    switch (type) {
    case 0: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_eventId = 2;
        ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
        break;
    }
    case 1: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_l_early";
        param.m_startFlags = 10;
        param.m_eventId = 2;
        ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
        break;
    }
    case 2: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_r_early";
        param.m_startFlags = 10;
        param.m_eventId = 2;
        ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
        break;
    }
    }
    GfMenuObject::hookCtrlEvent(handle, ctrl);
    return ctrl;
}
// Proposed names, not the original's: the symbols leave them unnamed (lbl_71009C39E4, lbl_71009C3A18). The stock
// filters' item kinds (getIconNumber's id for item type 10; filter 0 is all items) and, with the expansion, the
// filters shown in their place.
const unsigned int s_filterItemKinds[13] = {0, 0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};
const unsigned int s_filterExpansionKinds[10] = {0, 1, 2, 3, 4, 5, 8, 9, 0xB, 0xC};

// Proposed names, not the original's: the symbols leave them unnamed (lbl_7100B641E8, lbl_7100B64208). procFavFlag's
// images of each FAVORITE: the flash effect and the heart animation (read through getFavImage so they stay in .data).
__attribute__((used)) const char* s_favEffectImages[4] = {"IMG_chr_fvicon01eff@%02d", "IMG_chr_fvicon02eff@%02d",
                                                         "IMG_chr_fviconit01eff@%02d", "IMG_chr_fviconit02eff@%02d"};
__attribute__((used)) const char* s_favAnimImages[4] = {"IMG_chr_fvicon01anm@%02d", "IMG_chr_fvicon02anm@%02d",
                                                       "IMG_chr_fviconit01anm@%02d", "IMG_chr_fviconit02anm@%02d"};
inline const char* getFavImage(const char** table, unsigned int favorite) {
    return table[favorite];
}
}  // namespace

GfMenuObjPouch2::GfMenuObjPouch2(unsigned int handle)
    : GfMenuObject(handle), m_slotItems(nullptr), m_slotCursor(nullptr), m_number(), m_items(nullptr),
      m_select(nullptr), m_context(nullptr), m_filter(0), m_prevFilter(0), m_fvStock(0), m_subContext(nullptr),
      m_favBefore(), m_favAfter(), m_seq(this), m_slotActive(false), m_voice(nullptr), m_sort(0),
      m_blades(nullptr), pad_3E8(false) {}

GfMenuObjPouch2::~GfMenuObjPouch2() {
    if (m_slotItems != nullptr) {
        m_slotItems->release();
        m_slotItems = nullptr;
    }
    if (m_slotCursor != nullptr) {
        m_slotCursor->release();
        m_slotCursor = nullptr;
    }
    if (m_items != nullptr) {
        m_items->release();
        m_items = nullptr;
    }
    if (m_select != nullptr) {
        m_select->release();
        m_select = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_subContext != nullptr) {
        m_subContext->release();
        m_subContext = nullptr;
    }
    if (m_blades != nullptr) {
        m_blades->release();
        m_blades = nullptr;
    }
    m_number = nullptr;
}

void GfMenuObjPouch2::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int main = acc.searchChild("LAY_main");
#line 221
    MainListener* mainListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main, mainListener);
    if (mainListener != nullptr) {
        mainListener->release();
    }
    GfMenuObject::attachExternalCall(0x70, main);
    unsigned int slot = acc.searchChild("LAY_eqp_fevitem");
#line 227
    SlotListener* slotListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SlotListener(this);
    slotListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(slot, slotListener);
    if (slotListener != nullptr) {
        slotListener->release();
    }
    unsigned int stock = acc.searchChild("LAY_fvstock_fevitem");
#line 231
    ItemListListener* itemListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ItemListListener(this);
    itemListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(stock, itemListener);
    if (itemListener != nullptr) {
        itemListener->release();
    }
    unsigned int filter = acc.searchChild("LAY_stock_filter2");
#line 245
    FilterListener2* filterListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) FilterListener2(this);
    filterListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(filter, filterListener);
    if (filterListener != nullptr) {
        filterListener->release();
    }
    unsigned int party = acc.searchChild("LAY_chr_fevinfo");
#line 249
    PartyInfoListener* partyListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) PartyInfoListener(this);
    partyListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(party, partyListener);
    if (partyListener != nullptr) {
        partyListener->release();
    }
    unsigned int result = acc.searchChild("LAY_result");
#line 253
    ResultListener* resultListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ResultListener(this);
    resultListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(result, resultListener);
    if (resultListener != nullptr) {
        resultListener->release();
    }
    m_slotItems = GfMenuItemList::create();
    ui::UIListInfoBase::SetupParam setup;
    setup.m_pageRowSize = 3;
    m_slotItems->setup(getAllocator(ALLOCATOR(0)), setup);
    ui::UISelectObjList::CreateParam create;
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_select = ui::UISelectObjList::create(create);
    m_items = GfMenuItemList::create();
    m_number = GfMenuReferenceNumber::create();
    m_context = GfMenuCallContext::create();
    m_subContext = GfMenuCallContext::create();
    m_blades = GfMenuBladeList::create();
    ui::UIObjectAcc slotAcc(acc.searchChild("LAY_eqp_fevitem"));
    GfMenuObject::disableInput(slotAcc.m_handle);
    ui::UIObjectAcc stockAcc(acc.searchChild("LAY_fvstock_fevitem"));
    GfMenuObject::disableInput(stockAcc.m_handle);
    GfMenuObject::initialize();
}

void GfMenuObjPouch2::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjPouch2::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjPouch2::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        setFadeIn(handle, 0);
        break;
    case 3:
        if (event.m_param0 == 2) {
            acc.setDisp(false);
            acc.setTerm();
            GfMenuObjCharSelect::returnSubMenu();
            GfMenuObject::returnFSSubLayer(handle, 2);
        }
        break;
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        setFadeOut(handle, 0);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjPouch2::seqFavOpen() {
    m_favVoice = false;
    m_favIndex = 0;
    m_favKind = 0;
    return true;
}

void GfMenuObjPouch2::setupSlot(ui::UIObjectAcc& acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < 3; i++) {
        name.format("IMG_eqpouch_slicon@%02d", i + 1);
        GfMenuItemAdapter::createFromPouchReferenceDriver(acc.searchChild(name.m_str), 2, i, 0, false);
        name.format("TXT_eqpouch_efftime@%02d", i + 1);
        ui::UIObjectAcc time(acc.searchChild(name.m_str));
        GfMenuPouchAdapter* adapter =
            GfMenuPouchAdapter::createFromReferenceDriver(acc.searchChild(name.m_str), 0, i, 0, false);
        name.format("IMG_eqpouch_efftime_bg@%02d", i + 1);
        ui::UIObjectAcc bg(acc.searchChild(name.m_str));
        if (adapter != nullptr) {
            adapter->m_rowHandle = bg.m_handle;
        }
        GfMenuObjUtil::FitOption option;
        GfMenuObjUtil::createFitPlugin(bg.m_handle, time.m_handle, 8, 8, option);
        name.format("TXT_eqpouch_name@%02d", i + 1);
        GfMenuItemAdapter::createFromPouchReferenceDriver(acc.searchChild(name.m_str), 0, i, 0, false);
    }
}

void GfMenuObjPouch2::updateSlotList(GfMenuItemList* items) {
    unsigned int driver = GfMenuReference::getReferenceDriverID(0);
    items->clear();
    for (unsigned int i = 0; i < 3; i++) {
        SDataPouch& pouch = GfPouchUtil::getPouch(driver, i);
        if (pouch.m_open) {
            MenuItemInfo info;
            info.m_type = 10;
            info.m_id = pouch.itemId;
            info.m_count = info.m_id != 0;
            items->addContents(info);
        }
    }
}

void GfMenuObjPouch2::refreshSlot(ui::UIObjectAcc& acc, unsigned int index) {
    unsigned int driver = GfMenuReference::getReferenceDriverID(0);
    unsigned int count = GfPouchUtil::getOpenCount(driver);
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < 3; i++) {
        SDataPouch& pouch = GfPouchUtil::getPouch(driver, i);
        if (i < count) {
            mm::mtl::FixStr<32> slot;
            slot.format("IMG_eqpouch_slbase@%02d", i + 1);
            ui::UIObjectAcc base(acc.searchChild(slot.m_str));
            base.startAnimation(pouch.itemId == 0 ? "porch1_idle" : "porch_full", false);
            slot.format("TXT_eqpouch_no@%02d", i + 1);
            ui::UIObjectAcc no(acc.searchChild(slot.m_str));
            no.setDisp(pouch.itemId == 0);
        }
    }
    SDataPouch& current = GfPouchUtil::getPouch(driver, index);
    ui::UIObjectAcc cursor(acc.searchChild("IMG_slotcursor"));
    cursor.setImageIndex(current.itemId != 0);
    for (unsigned int i = 0; i < 3; i++) {
        name.format("LAY_eqpouch_slot@%02d", i + 1);
        ui::UIObjectAcc slot(acc.searchChild(name.m_str));
        if (i < count) {
            slot.setDisp(true);
        } else {
            slot.setDisp(false);
        }
    }
    ui::UISelectObjList::CreateParam param;
    param.m_allocator = getAllocator(ALLOCATOR(0));
    ui::UISelectObjList* list = ui::UISelectObjList::create(param);
    for (unsigned int i = 0; i < count;) {
        mm::mtl::FixStr<32> slot;
        slot.format("LAY_eqpouch_slot@%02d", ++i);
        unsigned int handle = acc.searchChild(slot.m_str);
        list->addContents(handle);
    }
    mm::Rect<short> rect;
    acc.getLayoutRect("fev_slot02", rect);
    mm::Rect<short> range;
    acc.getLayoutRect("fev_slot03", range);
    GfMenuObjUtil::placeObjectH(list, mm::Pnt<short>(rect.x + rect.w / 2, rect.y + rect.h / 2), range.x - rect.x - 1);
    if (list != nullptr) {
        list->release();
    }
}

void GfMenuObjPouch2::updateItemList(GfMenuItemList* items, ui::UISelectObjList* select, unsigned int filter,
                                     unsigned int sort) {
    items->clear();
    GfMenuItemList::ItemBoxSetup setup;
    setup.m_type = 10;
    setup.m_setup.m_pageRowSize = 8;
    setup.m_setup.m_pageScroll = true;
    setup.pad_28 = 0;
    setup.pad_29 = 0;
    GfMenuItemList::FiltertInfo info;
    if (filter != 0) {
        info.m_flags = 8;
        info.m_favoriteKey = s_filterItemKinds[filter];
        setup.m_filter = &info;
    }
    items->setupFromBox(setup);
    items->sort(GfMenuObjSort::getSortID(0x10, sort), false);
    items->setIndex(0);
}

void GfMenuObjPouch2::setupItemList(ui::UIObjectAcc& acc, GfMenuItemList* items) {
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 8; i++) {
        name.format("IMG_fvstock_iticon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 2, items, i, false);
        name.format("TXT_fvstock_itname@%02d", i + 1);
        GfMenuItemAdapter* adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0, items, i, false);
        name.format("LAY_fvstock_listtag@%02d", i + 1);
        if (adapter != nullptr) {
            adapter->m_rowHandle = acc.searchChild(name.m_str);
        }
        name.format("IMG_fvstock_reaicon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 7, items, i, false);
        name.format("TXT_fvstock_stcknum@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 3, items, i, false);
        name.format("IMG_fvstock_tagsellct@%02d", i + 1);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
    }
    name.format("TXT_fvstock_info_eff@%02d", 1);
    GfMenuItemAdapter* adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0xE, items, -1, false);
    if (adapter != nullptr) {
        adapter->m_subIndex = 0;
    }
    name.format("TXT_fvstock_info_eff@%02d", 2);
    adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0xE, items, -1, false);
    if (adapter != nullptr) {
        adapter->m_subIndex = 1;
    }
    name.format("TXT_fvstock_info_eff@%02d", 3);
    adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0xE, items, -1, false);
    if (adapter != nullptr) {
        adapter->m_subIndex = 2;
    }
    GfMenuItemAdapter::createFromList(acc.searchChild("TXT_fvstock_info_time_num"), 0xD, items, -1, false);
}

void GfMenuObjPouch2::refreshItemList(ui::UIObjectAcc& acc, GfMenuItemList* items, ui::UISelectObjList* select,
                                      unsigned int index) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < static_cast<unsigned int>(select->getSize());) {
        bool selected = items->getContents(items->getPageIndex(i)).m_id == index;
        if (!(i < static_cast<unsigned int>(items->getSize()))) {
            selected = false;
        }
        i++;
        name.format("IMG_fvstock_tagsellct@%02d", i);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, selected);
        name.format("TXT_fvstock_itname@%02d", i);
        ui::UIObjectAcc text(acc.searchChild(name.m_str));
        GfMenuObjUtil::setColMulandAdd(text.m_handle, "txt_normal2");
        name.format("IMG_fvstock_eqicon@%02d", i);
        ui::UIObjectAcc icon(acc.searchChild(name.m_str));
        icon.setDisp(false);
    }
}

void GfMenuObjPouch2::setFavFlag(unsigned int driver, unsigned int chr, mm::mtl::FixedArray<FavoriteFlag, 4>& flags,
                                 const GfMenuBladeList* blades) {
    flags[0].m_id = driver;
    flags[0].m_chr = chr;
    flags[0].m_stat[0] = GfMenuObjUtil::getFavoriteStat(3, driver, FAVORITE(0));
    flags[0].m_stat[1] = GfMenuObjUtil::getFavoriteStat(3, driver, FAVORITE(1));
    flags[0].m_stat[2] = GfMenuObjUtil::getFavoriteStat(3, driver, FAVORITE(2));
    flags[0].m_stat[3] = GfMenuObjUtil::getFavoriteStat(3, driver, FAVORITE(3));
    DataParamAcc param(3, driver, GimmickType(0));
    for (unsigned int i = 0; i < 3; i++) {
        if (i < static_cast<unsigned int>(blades->getSize())) {
            unsigned int blade = blades->getContents(i).m_blade;
            flags[i + 1].m_id = blade;
            flags[i + 1].m_chr = chr;
            if (blade != 0) {
                flags[i + 1].m_stat[0] = GfMenuObjUtil::getFavoriteStat(4, blade, FAVORITE(0));
                flags[i + 1].m_stat[1] = GfMenuObjUtil::getFavoriteStat(4, blade, FAVORITE(1));
                flags[i + 1].m_stat[2] = GfMenuObjUtil::getFavoriteStat(4, blade, FAVORITE(2));
                flags[i + 1].m_stat[3] = GfMenuObjUtil::getFavoriteStat(4, blade, FAVORITE(3));
            }
        } else {
            flags[i + 1].m_id = 0;
            flags[i + 1].m_chr = chr;
        }
    }
}

bool GfMenuObjPouch2::seqFavLoop() {
    ui::UIObjectAcc acc(m_handle);
    if (m_voice != nullptr && GfMenuObjUtil::isVoiceSkip()) {
        GfGameVoice::playStop(m_voice);
        m_voice = nullptr;
        return true;
    }
    if (m_favVoice) {
        switch (GfGameVoice::getResult(m_voice)) {
        case CV_RESULT(1):
        case CV_RESULT(2):
            break;
        default:
            m_favVoice = false;
            break;
        }
        return false;
    }
    for (; m_favIndex < 4; m_favIndex++) {
        for (; m_favKind < 4; m_favKind++) {
            if (m_favBefore[m_favIndex].m_stat[m_favKind] != m_favAfter[m_favIndex].m_stat[m_favKind] &&
                m_favAfter[m_favIndex].m_stat[m_favKind] == 0) {
                m_voice = procFavFlag(acc, m_favAfter[m_favIndex], m_favIndex, m_favKind);
                m_favVoice = true;
                m_favKind++;
                return false;
            }
            unsigned int favorite = m_favIndex == 0
                                        ? GfDataDriver::getFavorite(m_favAfter[m_favIndex].m_id, FAVORITE(m_favKind))
                                        : GfDataBlade::getFavorite(m_favAfter[m_favIndex].m_id, FAVORITE(m_favKind));
            if (m_favKind < 2) {
                if (favorite == GfDataItem::getCategory(m_favAfter[m_favIndex].m_chr)) {
                    m_voice = SCOM_FIELD_VOICE::createFavorite(m_favAfter[m_favIndex].m_id, FAVORITE(m_favKind));
                    m_favVoice = true;
                    m_favKind++;
                    return false;
                }
            } else if (favorite == m_favAfter[m_favIndex].m_chr) {
                m_voice = SCOM_FIELD_VOICE::createFavorite(m_favAfter[m_favIndex].m_id, FAVORITE(m_favKind));
                m_favVoice = true;
                m_favKind++;
                return false;
            }
        }
        m_favKind = 0;
    }
    return true;
}

bool GfMenuObjPouch2::seqFavClose() {
    ui::UIObjectAcc acc(m_handle);
    sendEvent(acc.searchChild("LAY_fvstock_fevitem"), 0x22, 0);
    sendEvent(acc.searchChild("LAY_stock_filter2"), 0x22, 0);
    sendEvent(acc.searchChild("LAY_chr_fevinfo"), 0x102, 0);
    sendEvent(acc.searchChild("LAY_eqp_fevitem"), 0x101, 1);
    m_favIndex = 0;
    m_favKind = 0;
    return true;
}

bool GfMenuObjPouch2::seqFavPouchIn() {
    ui::UIObjectAcc acc(m_handle);
    int index = m_number->m_value;
    mm::mtl::FixStr<32> name;
    name.format("IMG_eqpouch_slbase@%02d", index + 1);
    ui::UIObjectAcc base(acc.searchChild(name.m_str));
    name.format("IMG_eqpouch_slicon@%02d", index + 1);
    ui::UIObjectAcc icon(acc.searchChild(name.m_str));
    m_slotActive = true;
    switch (m_favIndex) {
    case 0: {
        name.format("TXT_eqpouch_no@%02d", index + 1);
        ui::UIObjectAcc no(acc.searchChild(name.m_str));
        no.setDisp(false);
        if (m_favKind < 5) {
            m_favKind++;
        } else {
            m_favIndex++;
        }
        return false;
    }
    case 1: {
        base.startAnimation("porch1_itemin", false);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "mnu070_item";
        param.m_motion = "item_throw";
        param.m_setDefault = true;
        param.m_startFlags = 8;
        GfMenuObjUtil::startCtrl(icon.m_handle, param, nullptr);
        GfMenuObjUtil::playSE(0x39);
        m_favIndex++;
        return false;
    }
    case 2: {
        if (base.isPlayingAnimation()) {
            return false;
        }
        unsigned int slot = acc.searchChild("LAY_eqp_fevitem");
        GfMenuObjMainMenu2::openCharChange(slot, 0, false);
        ui::UIObjectAcc slotAcc(acc.searchChild("LAY_eqp_fevitem"));
        refreshSlot(slotAcc, m_slotItems->getIndex(false));
        GfMenuObject::enableInput(slot);
        m_slotActive = false;
        m_slotCursor->setAlpha(1.0f);
        m_slotCursor->setDisp(true);
        return true;
    }
    }
    return true;
}

void GfMenuObjPouch2::ResultListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        setupResult(acc);
        acc.setDisp(false);
        GfMenuObject::disableInput(handle);
        break;
    case 8:
        if (event.m_param1 == 0xB || event.m_param1 == 2) {
            sendEvent(handle, 0x102, 0);
            sendEvent(owner.searchChild(m_owner->m_fvStock == 0 ? "LAY_eqp_fevitem" : "LAY_fvstock_fevitem"), 0x101, 0);
            if (m_owner->m_fvStock == 0) {
                GfMenuObjCharSelect::setCharPosScale(0, GfMenuReference::getReferenceDriverID(0), 4, false);
                GfMenuObjCharSelect::dispOnChar(0);
            } else {
                setFadeIn(owner.searchChild("LAY_fvstock_fevitem"), 1);
                setFadeIn(owner.searchChild("LAY_chr_fevinfo"), 2);
            }
            GfMenuObjUtil::playSECommonCloseSubMenu();
        }
        break;
    case 0x101:
        refreshResult(acc, m_owner->m_blades);
        GfMenuObjOperationInfo::setGuideText(0x22, 0);
        GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        setFadeIn(handle, 1);
        GfMenuObject::enableInput(handle);
        break;
    case 0x102:
        GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
        setFadeOut(handle, 1);
        GfMenuObject::disableInput(handle);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjPouch2::setupFilter(ui::UIObjectAcc& acc, unsigned int filter) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < 13; i++) {
        name.format("IMG_ficon@%02d", i + 1);
        ui::UIObjectAcc icon(acc.searchChild(name.m_str));
        if (icon.m_object == nullptr) {
            continue;
        }
        if (i < (GfMenuObjUtil::isValidExpansion(3) ? sizeof(s_filterExpansionKinds) / sizeof(s_filterExpansionKinds[0])
                                                     : sizeof(s_filterItemKinds) / sizeof(s_filterItemKinds[0]))) {
            unsigned int number = 0;
            if (i == 0) {
                number = 14;
            } else {
                unsigned int kind = i;
                if (GfMenuObjUtil::isValidExpansion(3)) {
                    kind = s_filterExpansionKinds[i];
                }
                GfMenuItemUtil::getIconNumber(ItemType::Type(10), s_filterItemKinds[kind], number, false);
            }
            icon.setImageIndex(number);
        } else {
            icon.setDisp(false);
        }
    }
    {
        mm::Rect<short> rect;
        acc.getLayoutRect("all_item", rect);
        mm::Rect<short> range;
        acc.getLayoutRect("all_item_range", range);
        unsigned int count = GfMenuObjUtil::isValidExpansion(3) ? 10 : 13;
        GfMenuObjUtil::placeObjectH(acc.m_handle, "LAY_icon@%02d", count,
                                    mm::Pnt<short>(rect.x + rect.w / 2, rect.y + rect.h / 2), range.x - rect.x);
    }
    ui::UIStr text;
    getFilterText(filter, text);
    ui::UIObjectAcc index(acc.searchChild("TXT_fvstock_index"));
    index.setText(text);
}

void GfMenuObjPouch2::getFilterText(unsigned int filter, ui::UIStr& text) {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIStr str(GfDataBdat::getFP(0x11D), GfMenuObjUtil::getMsgIDFromList(0x14D, filter + 1));
        text.copy(str);
    } else {
        ui::UIStr str(GfDataBdat::getFP(0x11D), GfMenuObjUtil::getMsgIDFromList(0x14C, filter + 1));
        text.copy(str);
    }
}

void GfMenuObjPouch2::setupPartyInfo(ui::UIObjectAcc& acc) {
    GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_chr_fiface@01"), 3, 0, false);
    GfMenuCharDataAdapter* adapter =
        GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_chr_fvicon01@01"), 10, 0, true);
    if (adapter != nullptr) {
        adapter->m_index = 0;
    }
    adapter = GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_chr_fvicon02@01"), 10, 0, true);
    if (adapter != nullptr) {
        adapter->m_index = 1;
    }
    adapter = GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_chr_fviconit@01"), 0xC, 0, true);
    if (adapter != nullptr) {
        adapter->m_index = 0;
    }
    adapter = GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_chr_fvitnameit@01"), 0xB, 0, true);
    if (adapter != nullptr) {
        adapter->m_index = 0;
    }
    adapter = GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_chr_fviconit2@01"), 0xC, 0, true);
    if (adapter != nullptr) {
        adapter->m_index = 1;
    }
    adapter = GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_chr_fvitnameit2@01"), 0xB, 0, true);
    if (adapter != nullptr) {
        adapter->m_index = 1;
    }
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 3; i++) {
        name.format("IMG_chr_fiface@%02d", i + 2);
        adapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.m_str), 3, 0, i, false);
        if (adapter != nullptr) {
            name.format("LAY_chr_fi@%02d", i + 2);
            adapter->m_rowHandle = acc.searchChild(name.m_str);
        }
        name.format("IMG_chr_fvicon01@%02d", i + 2);
        adapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.m_str), 10, 0, i, true);
        if (adapter != nullptr) {
            adapter->m_index = 0;
        }
        name.format("IMG_chr_fvicon02@%02d", i + 2);
        adapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.m_str), 10, 0, i, true);
        if (adapter != nullptr) {
            adapter->m_index = 1;
        }
        name.format("IMG_chr_fviconit@%02d", i + 2);
        adapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.m_str), 0xC, 0, i, true);
        if (adapter != nullptr) {
            adapter->m_index = 0;
        }
        name.format("TXT_chr_fvitnameit@%02d", i + 2);
        adapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.m_str), 0xB, 0, i, true);
        if (adapter != nullptr) {
            adapter->m_index = 0;
        }
        name.format("IMG_chr_fviconit2@%02d", i + 2);
        adapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.m_str), 0xC, 0, i, true);
        if (adapter != nullptr) {
            adapter->m_index = 1;
        }
        name.format("TXT_chr_fvitnameit2@%02d", i + 2);
        adapter = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.m_str), 0xB, 0, i, true);
        if (adapter != nullptr) {
            adapter->m_index = 1;
        }
    }
}

GAME_VOICE_HANDLE* GfMenuObjPouch2::procFavFlag(ui::UIObjectAcc& acc, FavoriteFlag& flag, unsigned int index,
                                                unsigned int favorite) {
    mm::mtl::FixStr<32> name;
    name.format(getFavImage(s_favEffectImages, favorite), index + 1);
    ui::UIObjectAcc effect(acc.searchChild(name.m_str));
    effect.startAnimation("flash", false);
    name.format(getFavImage(s_favAnimImages, favorite), index + 1);
    ui::UIObjectAcc anim(acc.searchChild(name.m_str));
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "mnu070_heart";
    param.m_motion = "fadein_a";
    param.m_eventId = 1;
    GfMenuObjUtil::startCtrl(anim.m_handle, param, nullptr);
    return SCOM_FIELD_VOICE::createFavorite(flag.m_id, FAVORITE(favorite));
}
}  // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjPouch2>(const mm::mtl::Delegate<bool()>*);

namespace gf {

}  // namespace gf
