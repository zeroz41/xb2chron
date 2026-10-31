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
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuBladeList.h"
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

void GfMenuObjPouch2::getFilterText(unsigned int filter, ui::UIStr& text) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        ui::UIStr str(GfDataBdat::getFP(0x11D), GfMenuObjUtil::getMsgIDFromList(0x14D, filter + 1));
        text.copy(str);
    } else {
        ui::UIStr str(GfDataBdat::getFP(0x11D), GfMenuObjUtil::getMsgIDFromList(0x14C, filter + 1));
        text.copy(str);
    }
}

}  // namespace gf
