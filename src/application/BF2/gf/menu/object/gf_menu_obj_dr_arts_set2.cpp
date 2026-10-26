#include "gf/GfDataDriver.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjDrArtsSet2.h"
#include "classes/gf/GfMenuObjDrArtsSet2/MainListener.h"
#include "classes/gf/GfMenuObjDrArtsSet2/WpnTypeListener.h"
#include "classes/gf/GfMenuObjDrArtsSet2/ArtsListListener.h"
#include "classes/gf/GfMenuObjDrArtsSet2/LevelupListener.h"
#include "classes/gf/GfMenuObjDrArtsSet2.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuArtsList.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjDrArtsSet2/ArtsListListener.h"
#include "classes/gf/GfMenuObjDrArtsSet2/LevelupListener.h"
#include "classes/gf/GfMenuObjDrArtsSet2/MainListener.h"
#include "classes/gf/GfMenuObjDrArtsSet2/WpnTypeListener.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataDriverArts.h"
#include "gf/GfItemUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedArray.h"
#include "ui/EventData.h"

namespace gf {

unsigned int GfMenuObjDrArtsSet2::s_wpnTypeIndex;
bool GfMenuObjDrArtsSet2::s_extraWpnType;

GfMenuObjDrArtsSet2::GfMenuObjDrArtsSet2(unsigned int handle)
    : GfMenuObject(handle), m_wpnTypes(), m_number(), m_number2(), m_object(nullptr), m_context(nullptr),
      m_context2(nullptr), pad_128(-1), pad_12C(-1), m_arts(nullptr), pad_138(false), m_blades(nullptr),
      m_items(nullptr), m_seq(this), m_seqStep(false) {
    pad_2BA = false;
    pad_2B8 = 0;
    pad_2B4 = 0;
    m_blades = GfMenuBladeList::create();
    m_items = GfMenuItemList::create();
    s_extraWpnType = GfGameManager::isClearGame() && !GfMenuObjUtil::fn_710048FD30(3) &&
                     GfMenuObjUtil::fn_710048FD30(1) && fn_71003E91EC();
    s_wpnTypeIndex = 0;
}

GfMenuObjDrArtsSet2::~GfMenuObjDrArtsSet2() {
    m_number = nullptr;
    m_number2 = nullptr;
    if (m_items != nullptr) {
        m_items->release();
        m_items = nullptr;
    }
    if (m_blades != nullptr) {
        m_blades->release();
        m_blades = nullptr;
    }
    if (m_object != nullptr) {
        m_object->release();
        m_object = nullptr;
    }
    if (m_context2 != nullptr) {
        m_context2->release();
        m_context2 = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_arts != nullptr) {
        m_arts->release();
        m_arts = nullptr;
    }
}

void GfMenuObjDrArtsSet2::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int handle = acc.searchChild("LAY_main");
    {
#line 240
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::attachExternalCall(0x65, handle);
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        handle = acc.searchChild("LAY_wpn");
#line 249
        WpnTypeListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) WpnTypeListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_arts");
    {
#line 254
        ArtsListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ArtsListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_lvup_eff");
    {
#line 258
        LevelupListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) LevelupListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    m_number = GfMenuReferenceNumber::create();
    m_number->m_value = 0;
    m_number2 = GfMenuReferenceNumber::create();
    m_number2->m_value = 0;
    m_context = GfMenuCallContext::create();
    m_context2 = GfMenuCallContext::create();
    m_arts = GfMenuArtsList::create();
    ui::UIListInfoBase::SetupParam artsParam;
    artsParam.m_pageRowSize = 4;
    m_arts->setup(getAllocator(ALLOCATOR(0)), artsParam);
    {
        ui::UIListInfoBase::SetupParam param;
        param.m_pageRowSize = 3;
        m_items->setup(getAllocator(ALLOCATOR(0)), param);
    }
    for (unsigned int id = 0x633D; id < 0x6340; id++) {
        GfItem item = GfItemUtil::getInfo(id);
        if (item.m_count != 0) {
            MenuItemInfo info;
            info.m_id = id;
            info.m_type = GfItemUtil::getType(id);
            info.m_count = item.m_count;
            m_items->addItem(info, false);
        }
    }
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuObject::disableInput(acc.searchChild("LAY_wpn"));
    }
    GfMenuObject::disableInput(acc.searchChild("LAY_arts"));
    GfMenuObject::initialize();
}

void GfMenuObjDrArtsSet2::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjDrArtsSet2::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjDrArtsSet2::refreshLvUp(ui::UIObjectAcc& acc, unsigned int driver, unsigned int wpnType,
                                      GfMenuArtsList* arts) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < 4;) {
        bool lvUp = i < arts->getSize() && checkArtsLvUp(driver, wpnType, arts, i) == 0;
        i++;
        name.format("LAY_wpn_arts_lv_up@%02d", i);
        acc.setDispChild(lvUp, name.m_str);
        if (s_extraWpnType) {
            ui::UIObjectAcc wpn2(acc.searchSibiling("LAY_wpn2"));
            name.format("LAY_wpn2_arts_lv_up@%02d", i);
            wpn2.setDispChild(lvUp, name.m_str);
        }
    }
}

bool GfMenuObjDrArtsSet2::seqSelectItem() {
    if (!m_seqStep) {
        m_context->reset();
        GfMenuObjCommonText::openSelectItem(m_context, m_items, 1);
        m_seqStep = true;
    }
    if (!m_context->isTerm()) {
        return false;
    }
    GfMenuCallContext::GfMenuResult result;
    if (m_context->m_results.empty() || (m_context->popResult(result), result.m_id == -1)) {
        if (!GfMenuObjUtil::fn_710048FD30(3)) {
            m_seq.addJob(&GfMenuObjDrArtsSet2::seqReturnWeaponSelect);
        } else {
            m_seq.addJob(&GfMenuObjDrArtsSet2::fn_71003F03D8);
        }
    } else {
        m_items->setIndex(result.m_id);
        m_seq.addJob(&GfMenuObjDrArtsSet2::seqConfirmItem);
    }
    m_seqStep = false;
    return true;
}

bool GfMenuObjDrArtsSet2::fn_71003F03D8() {
    ui::UIObjectAcc acc(m_handle, "LAY_arts");
    sendEvent(acc.m_handle, 0x101, 0);
    return true;
}

bool GfMenuObjDrArtsSet2::seqReturnWeaponSelect() {
    ui::UIObjectAcc acc(m_handle, "LAY_wpn");
    sendEvent(acc.m_handle, 0x101, 0);
    return true;
}

}  // namespace gf
