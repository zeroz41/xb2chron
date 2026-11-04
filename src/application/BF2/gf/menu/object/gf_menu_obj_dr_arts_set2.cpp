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
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReference.h"
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
    pad_2B8 = false;
    pad_2B9 = false;
    pad_2B4 = 0;
    m_blades = GfMenuBladeList::create();
    m_items = GfMenuItemList::create();
    s_extraWpnType = GfGameManager::isClearGame() && !GfMenuObjUtil::isValidExpansion(3) &&
                     GfMenuObjUtil::isValidExpansion(1) && fn_71003E91EC();
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
    if (!GfMenuObjUtil::isValidExpansion(3)) {
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
    if (!GfMenuObjUtil::isValidExpansion(3)) {
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

inline int GfMenuObjDrArtsSet2::checkArtsLvUp(unsigned int driver, unsigned int wpnType, unsigned int arts,
                                              unsigned int level) {
    if (arts == 0 || GfDataDriverArts::getLevelMax(arts) <= level) {
        return 4;
    }
    return GfDataDriverArts::getNeedLevelupWp(driver, arts) > GfDataDriverArts::getWp(driver, wpnType, 0) ? 5 : 0;
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

int GfMenuObjDrArtsSet2::checkArtsLvUp(unsigned int driver, unsigned int wpnType, GfMenuArtsList* arts,
                                       unsigned int index) {
    unsigned int artsId = (index < arts->m_list.size() ? arts->m_list[index] : arts->m_dummy).m_artsId;
    unsigned int level = (index < arts->m_list.size() ? arts->m_list[index] : arts->m_dummy).m_level;
    if (GfMenuObjUtil::isValidExpansion(3) && pad_2BA) {
        int size = arts->getSize();
        if (artsId == 0 || size - 1 == index) {
            return 4;
        }
    } else if (artsId == 0) {
        return 4;
    }
    return checkArtsLvUp(driver, wpnType, artsId, level);
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
        if (!GfMenuObjUtil::isValidExpansion(3)) {
            m_seq.addJob(&GfMenuObjDrArtsSet2::seqReturnWeaponSelect);
        } else {
            m_seq.addJob(&GfMenuObjDrArtsSet2::seqReturnArtsSelect);
        }
    } else {
        m_items->setIndex(result.m_id);
        m_seq.addJob(&GfMenuObjDrArtsSet2::seqConfirmItem);
    }
    m_seqStep = false;
    return true;
}

void GfMenuObjDrArtsSet2::refreshLvUpWpn(ui::UIObjectAcc& acc, unsigned int driver,
                                         const mm::mtl::FixedVector<unsigned int, 50>& wpnTypes) {
    for (unsigned int i = 0; i < wpnTypes.size();) {
        mm::mtl::FixedArray<unsigned int, 4> arts;
        unsigned int count = GfMenuObjUtil::getEnableArts(arts, driver, wpnTypes[i], 0, false);
        bool lvUp = false;
        mm::mtl::FixStr<32> name;
        for (unsigned int j = 0; j < count; j++) {
            unsigned int artsId = arts[j];
            unsigned int level = GfDataDriverArts::getArtsLevel(driver, artsId);
            if (checkArtsLvUp(driver, wpnTypes[i], artsId, level) == 0) {
                lvUp = true;
                break;
            }
        }
        i++;
        name.format("IMG_wpn_lvup@%02d", i);
        acc.setDispChild(lvUp, name.m_str);
        if (s_extraWpnType) {
            ui::UIObjectAcc wpn2(acc.searchSibiling("LAY_wpn2"));
            name.format("IMG_wpn2_lvup@%02d", i);
            wpn2.setDispChild(lvUp, name.m_str);
        }
    }
}

void GfMenuObjDrArtsSet2::refreshLvCap(ui::UIObjectAcc& acc, unsigned int driver, unsigned int wpnType,
                                       GfMenuArtsList* arts, unsigned int index) {
    mm::mtl::FixStr<32> name;
    unsigned int artsId = (index < arts->m_list.size() ? arts->m_list[index] : arts->m_dummy).m_artsId;
    unsigned int level = (index < arts->m_list.size() ? arts->m_list[index] : arts->m_dummy).m_level;
    for (unsigned int i = 1; i <= 4; i++) {
        name.format("IMG_arts_lv_cap_base@%02d", i);
        ui::UIObjectAcc base(acc.m_handle, name.m_str);
        bool lvUp = false;
        if (i > level) {
            base.setImageIndex(2);
        } else if (level == i && checkArtsLvUp(driver, wpnType, arts, index) == 0) {
            base.setImageIndex(1);
            lvUp = true;
        } else {
            base.setImageIndex(0);
        }
        name.format("TXT_arts_lv_cap_num@%02d", i);
        if (lvUp) {
            GfMenuObjUtil::setColMulandAdd(acc.searchChild(name.m_str), "txt_column");
        } else {
            GfMenuObjUtil::setColDefault(acc.searchChild(name.m_str));
        }
    }
}

void GfMenuObjDrArtsSet2::updateArtsInputIra() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return;
    }
    ui::UIObjectAcc acc(m_handle, "LAY_arts");
    int select = pad_12C;
    bool listTop = m_arts->getIndex(false) < 3;
    bool idle = select == -1;
    float alpha = select != -1 ? 0.5f : 1.0f;
    GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 12, listTop & idle);
    bool hasItems = m_items->getSize() != 0;
    GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 9, hasItems & idle);
    GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, idle);
    GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 11, idle);
    ui::UIObjectAcc(acc.m_handle, "LAY_list_index_btn").setAlpha(alpha);
    GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 1, !pad_2BA);
    GfMenuObjOperationInfo::changeText(acc.m_handle, 2, select != -1);
}

void GfMenuObjDrArtsSet2::refreshArtsNeedWP(ui::UIObjectAcc& acc, GfMenuArtsList* arts, unsigned int driver,
                                            unsigned int wpnType) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < 4;) {
        bool lvUp = i < arts->getSize() && checkArtsLvUp(driver, wpnType, arts, i) == 0;
        unsigned int index = i;
        i++;
        name.format("TXT_arts_tag_wp_num@%02d", i);
        ui::UIObjectAcc text(acc.m_handle, name.m_str);
        if (lvUp) {
            text.loadDefColor();
            text.setBorderWeight(-0.5f);
        } else {
            GfMenuObjUtil::setColMulandAdd(text.m_handle, "txt_warning");
            text.setBorderWeight(2.0f);
        }
        if (GfMenuObjUtil::isValidExpansion(3) && pad_2B9 && index == arts->getSize() - 1) {
            bool disp = pad_2B4 != 0;
            name.format("LAY_arts_tag_wp@%02d", i);
            acc.setDispChild(disp, name.m_str);
            name.format("LAY_arts_lv@%02d", i);
            acc.setDispChild(disp, name.m_str);
        }
    }
}

void GfMenuObjDrArtsSet2::updateArtsSwapSelectIra(int index, bool close) {
    ui::UIObjectAcc acc(m_handle, "LAY_arts");
    unsigned int driver = GfMenuReference::getReferenceDriverID(s_wpnTypeIndex);
    mm::mtl::FixedArray<unsigned int, 4> arts;
    unsigned int count = GfMenuObjUtil::getEnableArts(arts, driver, m_number->m_value, pad_2B4, pad_2B9);
    if (count <= 3) {
        count = 3;
    }
    if (close) {
        if (pad_2B4 != 0 || pad_2B9) {
            GfMenuObject::setupInputSelection(acc.m_handle, index, count - 1);
        }
        GfMenuObjMainMenu2::closeCharChange();
    } else {
        GfMenuObject::setupInputSelection(acc.m_handle, index, count);
        if (pad_2B8) {
            GfMenuObjMainMenu2::openCharChange(acc.m_handle, 1, false);
        } else {
            GfMenuObjMainMenu2::openCharChange(acc.m_handle, 0, false);
        }
    }
}

void GfMenuObjDrArtsSet2::refreshParam(ui::UIObjectAcc& acc, unsigned int driver, unsigned int wpnType,
                                       GfMenuArtsList* arts, unsigned int index) {
    int lvUp = checkArtsLvUp(driver, wpnType, arts, index);
    if (lvUp == 4) {
        acc.setDispChild(true, "LAY_param_num_max@01");
        acc.setDispChild(true, "LAY_param_num_max@02");
        return;
    }
    acc.setDispChild(true, "LAY_param_num_diff@01");
    acc.setDispChild(true, "LAY_param_num_diff@02");
    if (lvUp == 0) {
        GfMenuObjUtil::setColMulandAdd(acc.searchChild("TXT_param_num_r@01"), "txt_lvup");
        GfMenuObjUtil::setColMulandAdd(acc.searchChild("TXT_param_num_r@02"), "txt_lvup");
    } else {
        GfMenuObjUtil::setColDefault(acc.searchChild("TXT_param_num_r@01"));
        GfMenuObjUtil::setColDefault(acc.searchChild("TXT_param_num_r@02"));
    }
    acc.setDispChild(false, "LAY_param_num_max@01");
    acc.setDispChild(false, "LAY_param_num_max@02");
}

void GfMenuObjDrArtsSet2::LevelupListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        acc.setDisp(false);
    } else if (event.m_type == 3) {
        sendEvent(owner.searchChild("LAY_arts"), 0x102, 0);
        acc.setDisp(false);
    } else if (event.m_type == 0x21) {
        acc.setDisp(true);
        {
            ui::UIObjectAcc img(acc.m_handle, "IMG_lvup_eff");
            img.startAnimation("fade_in", false);
        }
        ui::UIObjectAcc text(acc.m_handle, "TXT_lvup_eff_blur");
        ui::UIObjectAcc blur(acc.m_handle, "TXT_lvup_eff_blur");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_levelup_text_fadein";
        param.m_motion = "fade_in";
        param.m_startFlags = 10;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, "TXT_lvup_eff");
        param.m_motionLib = "cmn_levelup_text_fadein_blur";
        int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "TXT_lvup_eff_blur");
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
    } else {
        UIObjectListener::reciveEvent(event, handle);
    }
}

bool GfMenuObjDrArtsSet2::seqReturnArtsSelect() {
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
