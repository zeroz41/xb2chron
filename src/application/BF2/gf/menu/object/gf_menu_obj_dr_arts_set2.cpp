#include "gf/GfDataDriver.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjDrArtsSet2.h"
#include "classes/gf/GfMenuObjDrArtsSet2/MainListener.h"
#include "classes/gf/GfMenuObjDrArtsSet2/WpnTypeListener.h"
#include "classes/gf/GfMenuObjDrArtsSet2/ArtsListListener.h"
#include "classes/gf/GfMenuObjDrArtsSet2/LevelupListener.h"
#include "classes/gf/GfMenuObjDrArtsSet2.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuArtsAdapter.h"
#include "classes/gf/GfMenuArtsList.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuDiffAdapter.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuObjCharSelectIra.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuWeaponTypeAdapter.h"
#include "classes/gf/GfMenuObjDrArtsSet2/ArtsListListener.h"
#include "classes/gf/GfMenuObjDrArtsSet2/LevelupListener.h"
#include "classes/gf/GfMenuObjDrArtsSet2/MainListener.h"
#include "classes/gf/GfMenuObjDrArtsSet2/WpnTypeListener.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataDriverArts.h"
#include "gf/GfEquipUtil.h"
#include "btl/Utility.h"
#include "gf/GfItemUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedArray.h"
#include "ui/EventData.h"
#include "mm/mtl/FixedVector.h"
#include <algorithm>

namespace gf {

unsigned int GfMenuObjDrArtsSet2::s_RefDriverIndex;
bool GfMenuObjDrArtsSet2::s_EnableWpn2;

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
    s_EnableWpn2 = GfGameManager::isClearGame() && !GfMenuObjUtil::isValidExpansion(3) &&
                     GfMenuObjUtil::isValidExpansion(1) && isActiveBCHWpn();
    s_RefDriverIndex = 0;
}

bool isActiveBCHWpn() {
    if (!GfMenuObjUtil::isValidExpansion(1)) {
        return false;
    }
    mm::mtl::FixedVector<unsigned int, 50> types;
    GfDataDriver::getEquipWpnType(types, 1);
    for (mm::mtl::FixedVector<unsigned int, 50>::iterator it = types.begin(); it != types.end();) {
        mm::mtl::FixedArray<unsigned int, 4> arts;
        GfMenuObjUtil::getEnableArts(arts, 1, *it, PTPOS(0), false);
        int i;
        for (i = 0; i < 4; i++) {
            if (GfDataDriverArts::getArtsLevel(1, arts[i]) != 0) {
                break;
            }
        }
        if (*it == 17) {
            if (GfMenuObjUtil::isValidBlade(GfDataDriver::getBlade(1, -1))) {
                it = types.erase(it);
            } else {
                ++it;
            }
        } else if (i == 4) {
            it = types.erase(it);
        } else {
            ++it;
        }
    }
    return std::find(types.begin(), types.end(), 33u) != types.end();
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

namespace {
// Inferred name, not the original's: the original inlines it (its control parameters sit above the listener's UI
// accessor in the frame, where an inlined callee's local goes): the common fade out to the left, ending with event 2.
inline void startFadeOut(unsigned int handle) {
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = "fade_out_l_early";
    param.m_eventId = 2;
    param.m_setDefault = true;
    param.m_startFlags = 10;
    GfMenuObjUtil::startCtrl(handle, param, nullptr);
}
}  // namespace

void GfMenuObjDrArtsSet2::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObjMainMenu2::setSubIndexText(6);
        if (GfMenuObjUtil::isValidExpansion(3)) {
            s_RefDriverIndex = GfMenuObjCharSelectIra::getSubMenuMode() == 2;
            unsigned int driver = GfMenuReference::getReferenceDriverID(s_RefDriverIndex);
            m_owner->m_wpnTypes.clear();
            GfDataDriver::getEquipWpnType(m_owner->m_wpnTypes, driver);
            m_owner->m_number->setValue(m_owner->m_wpnTypes[0]);
            GfMenuObject::sendOpenEvent(acc.searchChild("LAY_arts"), 1, 0.0f);
            m_owner->pad_2B8 = !GfDataDriver::isIraFront(driver);
            m_owner->pad_2B9 = btl::Utility::IsSatisfyCondition(0x10);
            ui::UIObjectAcc line(acc.m_handle, "IMG_arts_list_line@01");
            if (m_owner->pad_2B8) {
                line.startAnimation("blade", false);
            } else {
                line.startAnimation("driver", false);
            }
            acc.setDispChild(!m_owner->pad_2B8, "IMG_arts_bg");
            acc.setDispChild(!m_owner->pad_2B8, "IMG_arts_detail_a_base");
            acc.setDispChild(!m_owner->pad_2B8, "IMG_arts_detail_b_base");
            acc.setDispChild(m_owner->pad_2B8, "IMG_arts_bg_bl");
            acc.setDispChild(m_owner->pad_2B8, "IMG_arts_detail_a_base_bl");
            acc.setDispChild(m_owner->pad_2B8, "IMG_arts_detail_b_base_bl");
            if (m_owner->pad_2B8) {
                {
                    ui::UIObjectAcc index(acc.m_handle, "TXT_param_a_txt_index@01");
                    index.setMulColor("tgt_cursor_lv03");
                    index.setAddColor("bl_thema01_dark");
                }
                {
                    ui::UIObjectAcc line1(acc.m_handle, "IMG_param_a_txt_line@01");
                    ui::UIObjectAcc line2(acc.m_handle, "IMG_arts_detail_a_tal_line@01");
                    ui::UIObjectAcc line3(acc.m_handle, "IMG_arts_detail_a_tal_line@02");
                    line1.setAddColor("bl_thema01_dark");
                    line2.setAddColor("bl_thema01_dark");
                    line3.setAddColor("bl_thema01_dark");
                }
                {
                    ui::UIObjectAcc base(acc.m_handle, "IMG_arts_detail_a_base_line");
                    base.setAddColor("bl_thema01_light");
                }
                ui::UIObjectAcc index1(acc.m_handle, "TXT_arts_detail_a_tal_index@01");
                ui::UIObjectAcc index2(acc.m_handle, "TXT_arts_detail_a_tal_index@02");
                index1.setMulColor("tgt_cursor_lv03");
                index1.setAddColor("bl_thema01_dark");
                index2.setMulColor("tgt_cursor_lv03");
                index2.setAddColor("bl_thema01_dark");
            }
        } else {
            GfMenuObject::sendOpenEvent(acc.searchChild("LAY_wpn"), 1, 0.0f);
        }
        // falls through: the open shows the layout too
    case 0x21:
        acc.setDisp(true);
        break;
    case 3:
        if (event.m_param0 == 2) {
            acc.setDisp(false);
            acc.setTerm();
            GfMenuObjCharSelect::returnSubMenu();
            GfMenuObject::returnFSSubLayer(m_owner);
        }
        break;
    case 0x22:
        startFadeOut(acc.m_handle);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjDrArtsSet2::setupWpnType(ui::UIObjectAcc& acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number,
                                       GfMenuArtsList* arts, GfMenuBladeList* blades) {
    GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild("TXT_wpn_wp_name"), 0, s_RefDriverIndex,
                                                              number, 0, false);
    GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild("TXT_wpn_wp_num"), 2, s_RefDriverIndex,
                                                              number, 0, true);
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 4; i++) {
        name.format("TXT_wpn_arts_name@%02d", i + 1);
        GfMenuArtsAdapter* adapter =
            GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.m_str), 0, arts, i, s_RefDriverIndex, false);
        if (adapter != nullptr) {
            name.format("LAY_wpn_arts@%02d", i + 1);
            adapter->m_rowHandle = acc.searchChild(name.m_str);
        }
        name.format("TXT_wpn_arts_lv@%02d", i + 1);
        GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.m_str), 8, arts, i, s_RefDriverIndex, false);
    }
    for (int i = 0; i < 3; i++) {
        name.format("IMG_wpn_blade_face@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 3, blades, i, false);
    }
    if (s_EnableWpn2) {
        ui::UIObjectAcc wpn2(acc.searchSibiling("LAY_wpn2"));
        GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(wpn2.searchChild("TXT_wpn2_wp_name"), 0,
                                                                  s_RefDriverIndex, number, 0, false);
        GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(wpn2.searchChild("TXT_wpn2_wp_num"), 2,
                                                                  s_RefDriverIndex, number, 0, true);
        mm::mtl::FixStr<32> name2;
        for (int i = 0; i < 4; i++) {
            name2.format("TXT_wpn2_arts_name@%02d", i + 1);
            GfMenuArtsAdapter* adapter = GfMenuArtsAdapter::createFromListReferenceDriver(
                wpn2.searchChild(name2.m_str), 0, arts, i, s_RefDriverIndex, false);
            if (adapter != nullptr) {
                name2.format("LAY_wpn2_arts@%02d", i + 1);
                adapter->m_rowHandle = wpn2.searchChild(name2.m_str);
            }
            name2.format("TXT_wpn2_arts_lv@%02d", i + 1);
            GfMenuArtsAdapter::createFromListReferenceDriver(wpn2.searchChild(name2.m_str), 8, arts, i,
                                                             s_RefDriverIndex, false);
        }
        for (int i = 0; i < 3; i++) {
            name2.format("IMG_wpn2_blade_face@%02d", i + 1);
            GfMenuCharDataAdapter::createFromBladeList(wpn2.searchChild(name2.m_str), 3, blades, i, false);
        }
    }
}

void GfMenuObjDrArtsSet2::refreshArtsList(ui::UIObjectAcc& acc, GfMenuArtsList* arts, unsigned int driver,
                                          unsigned int wpnType, GfMenuBladeList* blades) {
    mm::mtl::FixedArray<unsigned int, 4> enable;
    GfMenuObjUtil::getEnableArts(enable, driver, wpnType, static_cast<PTPOS>(pad_2B4), pad_2B9);
    arts->clear();
    for (int i = 0; i < 4; i++) {
        MenuArtsInfo info = {enable[i], 0};
        info.m_level = GfDataDriverArts::getArtsLevel(driver, enable[i]);
        arts->addContents(info);
    }
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        mm::mtl::FixStr<32> name;
        for (unsigned int i = 0; i < blades->getSize(); i++) {
            name.format("IMG_wpn_blade_face@%02d", i + 1);
            ui::UIObjectAcc face(acc.m_handle, name.m_str);
            unsigned int blade = (i < blades->m_list.size() ? blades->m_list[i] : blades->m_dummy).m_blade;
            if (GfDataBlade::getBladeWpnType(blade) == wpnType) {
                face.setMulColor("white");
            } else {
                face.setMulColor("gray");
            }
        }
        if (s_EnableWpn2) {
            ui::UIObjectAcc wpn2(acc.searchSibiling("LAY_wpn2"));
            for (unsigned int i = 0; i < blades->getSize(); i++) {
                name.format("IMG_wpn2_blade_face@%02d", i + 1);
                ui::UIObjectAcc face(wpn2.m_handle, name.m_str);
                unsigned int blade = (i < blades->m_list.size() ? blades->m_list[i] : blades->m_dummy).m_blade;
                if (GfDataBlade::getBladeWpnType(blade) == wpnType) {
                    face.setMulColor("white");
                } else {
                    face.setMulColor("gray");
                }
            }
        }
    }
}

inline int GfMenuObjDrArtsSet2::checkArtsLvUp(unsigned int driver, unsigned int wpnType, unsigned int arts,
                                              unsigned int level) {
    if (arts == 0 || GfDataDriverArts::getLevelMax(arts) <= level) {
        return 4;
    }
    return GfDataDriverArts::getNeedLevelupWp(driver, arts) >
                   GfDataDriverArts::getWp(driver, wpnType, static_cast<PTPOS>(0))
               ? 5
               : 0;
}

void GfMenuObjDrArtsSet2::refreshLvUp(ui::UIObjectAcc& acc, unsigned int driver, unsigned int wpnType,
                                      GfMenuArtsList* arts) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < 4;) {
        bool lvUp = i < arts->getSize() && checkArtsLvUp(driver, wpnType, arts, i) == 0;
        i++;
        name.format("LAY_wpn_arts_lv_up@%02d", i);
        acc.setDispChild(lvUp, name.m_str);
        if (s_EnableWpn2) {
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

void GfMenuObjDrArtsSet2::setupWpnTypeIcon(ui::UIObjectAcc& acc, mm::mtl::FixedVector<unsigned int, 50>& wpnTypes,
                                           GfMenuBladeList* blades) {
    unsigned int driver = GfMenuReference::getReferenceDriverID(s_RefDriverIndex);
    mm::mtl::FixedVector<unsigned int, 50> bladeTypes;
    for (unsigned int i = 0; i < blades->getSize(); i++) {
        unsigned int blade = (i < blades->m_list.size() ? blades->m_list[i] : blades->m_dummy).m_blade;
        bladeTypes.push_back(GfDataBlade::getBladeWpnType(blade));
    }
    wpnTypes.clear();
    GfDataDriver::getEquipWpnType(wpnTypes, driver);
    for (mm::mtl::FixedVector<unsigned int, 50>::iterator it = wpnTypes.begin(); it != wpnTypes.end();) {
        mm::mtl::FixedArray<unsigned int, 4> arts;
        GfMenuObjUtil::getEnableArts(arts, driver, *it, PTPOS(0), false);
        int i;
        for (i = 0; i < 4; i++) {
            if (GfDataDriverArts::getArtsLevel(driver, arts[i]) != 0) {
                break;
            }
        }
        if (*it == 17) {
            if (GfMenuObjUtil::isValidBlade(GfDataDriver::getBlade(driver, -1))) {
                it = wpnTypes.erase(it);
            } else {
                ++it;
            }
        } else if (i == 4) {
            it = wpnTypes.erase(it);
        } else {
            ++it;
        }
    }
    // each driver's own weapon type goes first
    unsigned int type = 0;
    switch (driver) {
    case 1:
        for (mm::mtl::FixedVector<unsigned int, 50>::iterator it = wpnTypes.begin(); it != wpnTypes.end(); ++it) {
            if (*it == 1) {
                wpnTypes.erase(it);
                type = 1;
                break;
            }
        }
        break;
    case 2:
        for (mm::mtl::FixedVector<unsigned int, 50>::iterator it = wpnTypes.begin(); it != wpnTypes.end(); ++it) {
            if (*it == 3) {
                wpnTypes.erase(it);
                type = 3;
                break;
            }
        }
        break;
    case 3:
        for (mm::mtl::FixedVector<unsigned int, 50>::iterator it = wpnTypes.begin(); it != wpnTypes.end(); ++it) {
            if (*it == 8) {
                wpnTypes.erase(it);
                type = 8;
                break;
            }
        }
        break;
    case 5:
        for (mm::mtl::FixedVector<unsigned int, 50>::iterator it = wpnTypes.begin(); it != wpnTypes.end(); ++it) {
            if (*it == 9) {
                wpnTypes.erase(it);
                type = 9;
                break;
            }
        }
        break;
    case 6:
        for (mm::mtl::FixedVector<unsigned int, 50>::iterator it = wpnTypes.begin(); it != wpnTypes.end(); ++it) {
            if (*it == 7) {
                wpnTypes.erase(it);
                type = 7;
                break;
            }
        }
        break;
    }
    if (type != 0) {
        wpnTypes.insert(wpnTypes.begin(), type);
    }
    ui::UIObjectAcc bladeLay(acc.m_handle, "LAY_wpn_blade");
    bladeLay.setDisp(true);
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < 21; i++) {
        name.format("IMG_wpn_icon@%02d", i + 1);
        ui::UIObjectAcc icon(acc.searchChild(name.m_str));
        if (icon.m_object != nullptr) {
            name.format("IMG_wpn_lvup@%02d", i + 1);
            ui::UIObjectAcc lvup(acc.searchChild(name.m_str));
            unsigned int type = i < wpnTypes.size() ? wpnTypes[i] : 0;
            if (type != 0) {
                if (type == 0x21) {
                    type = 0x1B;
                } else if (type == 0x22) {
                    type = 0x1C;
                } else if (type == 0x24) {
                    type = 0x1D;
                } else if (type == 0x23) {
                    type = 0x1E;
                }
                icon.setImageIndex(type - 1);
                icon.setDisp(true);
                const unsigned int& wpnType = wpnTypes[i];
                if (std::find(bladeTypes.begin(), bladeTypes.end(), wpnType) != bladeTypes.end()) {
                    icon.setMulColor("white");
                } else if (wpnTypes[i] == 0x11) {
                    icon.setMulColor("white");
                    bladeLay.setDisp(false);
                } else {
                    icon.setMulColor("dr_thema01_light");
                }
            } else {
                icon.setDisp(false);
            }
            lvup.setDisp(icon.isDisp());
        }
    }
    if (s_EnableWpn2) {
        ui::UIObjectAcc wpn2(acc.searchSibiling("LAY_wpn2"));
        setupWpnTypeIcon2(wpn2, wpnTypes, blades);
    }
}

void GfMenuObjDrArtsSet2::refreshLvUpWpn(ui::UIObjectAcc& acc, unsigned int driver,
                                         const mm::mtl::FixedVector<unsigned int, 50>& wpnTypes) {
    for (unsigned int i = 0; i < wpnTypes.size();) {
        mm::mtl::FixedArray<unsigned int, 4> arts;
        unsigned int count = GfMenuObjUtil::getEnableArts(arts, driver, wpnTypes[i], static_cast<PTPOS>(0), false);
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
        if (s_EnableWpn2) {
            ui::UIObjectAcc wpn2(acc.searchSibiling("LAY_wpn2"));
            name.format("IMG_wpn2_lvup@%02d", i);
            wpn2.setDispChild(lvUp, name.m_str);
        }
    }
}

void GfMenuObjDrArtsSet2::setupArtsList(ui::UIObjectAcc& acc, GfMenuArtsList* arts,
                                        mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number,
                                        mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number2) {
    mm::mtl::FixStr<32> name;
    unsigned int driver = s_RefDriverIndex;
    GfMenuAdapterManager::beginAddAfter();
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild("TXT_list_index"), 0,
                                                                  s_RefDriverIndex, number, 0, false);
        GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild("IMG_arts_wpn_icon"), 1,
                                                                  s_RefDriverIndex, number, 0, false);
    }
    GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild("TXT_arts_wp_num"), 2, s_RefDriverIndex,
                                                              number, 0, true);
    for (int i = 0; i < 4; i++) {
        name.format("TXT_arts_name@%02d", i + 1);
        GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.m_str), 0, arts, i, driver, false);
        name.format("IMG_arts_icon_type@%02d", i + 1);
        GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.m_str), 2, arts, i, driver, false);
        name.format("IMG_arts_icon_enhance@%02d", i + 1);
        GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.m_str), 3, arts, i, driver, false);
        name.format("IMG_arts_icon_react@%02d", i + 1);
        GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.m_str), 4, arts, i, driver, false);
        name.format("IMG_arts_icon_range@%02d", i + 1);
        GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.m_str), 5, arts, i, driver, false);
        name.format("TXT_arts_tag_wp_num@%02d", i + 1);
        GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.m_str), 6, arts, i, driver, false);
        name.format("TXT_arts_tag_wp_max@%02d", i + 1);
        GfMenuArtsAdapter* wpMax =
            GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.m_str), 0x14, arts, i, driver, false);
        wpMax->m_releaseIndex = 1;
        name.format("TXT_arts_lv@%02d", i + 1);
        GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.m_str), 8, arts, i, driver, false);
    }
    GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_a_txt@01"), 10, arts,
                                                                   number2, driver, false);
    GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_b_txt@01"), 10, arts,
                                                                   number2, driver, false);
    GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_a_txt@02"), 11, arts,
                                                                   number2, driver, false);
    GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_b_txt@02"), 11, arts,
                                                                   number2, driver, false);
    GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_a_txt@03"), 12, arts,
                                                                   number2, driver, false);
    GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_b_txt@03"), 12, arts,
                                                                   number2, driver, false);
    GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_a_num_index@01"), 0x15,
                                                                   arts, number2, driver, false);
    GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_b_num_index@01"), 0x15,
                                                                   arts, number2, driver, false);
    GfMenuArtsAdapter* numA1 = GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(
        acc.searchChild("TXT_param_a_num@01"), 13, arts, number2, driver, false);
    GfMenuArtsAdapter* numB1 = GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(
        acc.searchChild("TXT_param_b_num@01"), 17, arts, number2, driver, false);
    GfMenuDiffAdapter::create(acc.searchChild("TXT_param_b_num@01"), numA1, numB1, 1, true);
    GfMenuArtsAdapter* numA2 = GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(
        acc.searchChild("TXT_param_a_num@02"), 14, arts, number2, driver, false);
    GfMenuArtsAdapter* numB2 = GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(
        acc.searchChild("TXT_param_b_num@02"), 18, arts, number2, driver, false);
    GfMenuDiffAdapter::create(acc.searchChild("TXT_param_b_num@02"), numB2, numA2, 1, true);
    GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_arts_detail_a_enhance"), 15,
                                                                   arts, number2, driver, false);
    GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_arts_detail_b_enhance"), 19,
                                                                   arts, number2, driver, false);
    if (GfMenuObjUtil::isValidExpansion(3)) {
        GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_arts_icon_talent"), 0x6E,
                                                         s_RefDriverIndex, false);
        GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_arts_detail_a_tal_info@01"),
                                                                       0x17, arts, number2, driver, false);
        GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_arts_detail_a_tal_info@02"),
                                                                       0x16, arts, number2, driver, false);
    }
    GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjDrArtsSet2::refreshArtsSelect(ui::UIObjectAcc& acc, int index, int prev) {
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 4; i++) {
        name.format("IMG_arts_icon_tag_base@%02d", i + 1);
        ui::UIObjectAcc tagBase(acc.searchChild(name.m_str));
        name.format("IMG_arts_icon_base@%02d", i + 1);
        ui::UIObjectAcc iconBase(acc.searchChild(name.m_str));
        name.format("TXT_arts_name@%02d", i + 1);
        ui::UIObjectAcc text(acc.searchChild(name.m_str));
        if (GfMenuObjUtil::isValidExpansion(3)) {
            name.format("IMG_arts_icon_tag_base@%02d", i + 1);
            ui::UIObjectAcc iconTag(acc.searchChild(name.m_str));
            name.format("IMG_arts_tag_base@%02d", i + 1);
            ui::UIObjectAcc artsTag(acc.searchChild(name.m_str));
            if (prev == i) {
                if (pad_2B8) {
                    tagBase.startAnimation("blade_hold", false);
                    artsTag.startAnimation("blade_hold", false);
                } else {
                    tagBase.startAnimation("driver_hold", false);
                    artsTag.startAnimation("driver_hold", false);
                }
                iconTag.startAnimation("normal_hold", false);
                GfMenuObjUtil::setColMulandAdd(text.m_handle, "txt_column");
            } else {
                if (index == i) {
                    if (pad_2B8) {
                        tagBase.startAnimation("blade_select", false);
                        artsTag.startAnimation("blade_select", false);
                    } else {
                        tagBase.startAnimation("driver_select", false);
                        artsTag.startAnimation("driver_select", false);
                    }
                    iconTag.startAnimation("normal_select", false);
                } else {
                    if (pad_2B8) {
                        tagBase.startAnimation("blade", false);
                        artsTag.startAnimation("blade", false);
                    } else {
                        tagBase.startAnimation("driver", false);
                        artsTag.startAnimation("driver", false);
                    }
                    iconTag.startAnimation("normal", false);
                }
                text.loadDefColor();
            }
        } else {
            if (prev == i) {
                tagBase.setAddColor("sys_hold");
                iconBase.setMulColor("black");
                iconBase.setAddColor("sys_hold");
                GfMenuObjUtil::setColMulandAdd(text.m_handle, "txt_column");
            } else {
                if (index == i) {
                    tagBase.setAddColor("sys_select");
                    iconBase.setMulColor("black");
                    iconBase.setAddColor("sys_select");
                } else {
                    tagBase.loadDefColor();
                    iconBase.loadDefColor();
                }
                text.loadDefColor();
            }
        }
    }
    if (GfMenuObjUtil::isValidExpansion(3)) {
        acc.setDispChild(pad_2B4 == 0, "TXT_arts_sp_index_talent");
        acc.setDispChild(pad_2B4 == 0, "LAY_arts_icon_talent");
        acc.setDispChild(pad_2B4 != 0, "TXT_arts_sp_index_switch");
        acc.setDispChild(pad_2B4 != 0, "IMG_arts_icon_switch");
        {
            ui::UIObjectAcc listIndex(acc.m_handle, "IMG_list_index");
            listIndex.startAnimation(pad_2B4 == 0 ? "attacker" : "supporter", false);
        }
        {
            ui::UIObjectAcc atk(acc.m_handle, "TXT_list_index_atk");
            ui::UIObjectAcc sup(acc.m_handle, "TXT_list_index_sup");
            atk.setAlpha(pad_2B4 == 0 ? 1.0f : 0.5f);
            sup.setAlpha(pad_2B4 != 0 ? 1.0f : 0.5f);
        }
        bool line = false;
        if (pad_2B4 == 0) {
            line = pad_2B9;
        }
        line |= pad_2B4 == 1;
        acc.setDispChild(line, "IMG_arts_list_line@01");
        acc.setDispChild(line, "LAY_arts@04");
        acc.setDispChild(line, "LAY_arts_sp_index");
        bool talent = pad_2B4 == 0 && pad_2B9 && m_arts->getSize() - 1 == index;
        acc.setDispChild(!talent, "LAY_arts_detail_a_normal");
        acc.setDispChild(talent, "LAY_arts_detail_a_talent");
        pad_2BA = talent;
        bool num = pad_2B4 != 1 || m_arts->getSize() - 1 != index;
        acc.setDispChild(num, "TXT_param_a_num_index@02");
        acc.setDispChild(num, "TXT_param_b_num_index@02");
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
    unsigned int driver = GfMenuReference::getReferenceDriverID(s_RefDriverIndex);
    mm::mtl::FixedArray<unsigned int, 4> arts;
    unsigned int count =
        GfMenuObjUtil::getEnableArts(arts, driver, m_number->m_value, static_cast<PTPOS>(pad_2B4), pad_2B9);
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

void GfMenuObjDrArtsSet2::setupWpnTypeIcon2(ui::UIObjectAcc& acc, mm::mtl::FixedVector<unsigned int, 50>& wpnTypes,
                                            GfMenuBladeList* blades) {
    mm::mtl::FixedVector<unsigned int, 50> bladeTypes;
    for (unsigned int i = 0; i < blades->getSize(); i++) {
        unsigned int blade = (i < blades->m_list.size() ? blades->m_list[i] : blades->m_dummy).m_blade;
        bladeTypes.push_back(GfDataBlade::getBladeWpnType(blade));
    }
    ui::UIObjectAcc bladeLay(acc.m_handle, "LAY_wpn2_blade");
    bladeLay.setDisp(true);
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < 28; i++) {
        name.format("IMG_wpn2_icon@%02d", i + 1);
        ui::UIObjectAcc icon(acc.searchChild(name.m_str));
        if (icon.m_object != nullptr) {
            name.format("IMG_wpn2_lvup@%02d", i + 1);
            ui::UIObjectAcc lvup(acc.searchChild(name.m_str));
            unsigned int type = i < wpnTypes.size() ? wpnTypes[i] : 0;
            if (type != 0) {
                if (type == 0x21) {
                    type = 0x1B;
                } else if (type == 0x22) {
                    type = 0x1C;
                } else if (type == 0x24) {
                    type = 0x1D;
                } else if (type == 0x23) {
                    type = 0x1E;
                }
                icon.setImageIndex(type - 1);
                icon.setDisp(true);
                const unsigned int& wpnType = wpnTypes[i];
                if (std::find(bladeTypes.begin(), bladeTypes.end(), wpnType) != bladeTypes.end()) {
                    icon.setMulColor("white");
                } else if (wpnTypes[i] == 0x11) {
                    icon.setMulColor("white");
                    bladeLay.setDisp(false);
                } else {
                    icon.setMulColor("dr_thema01_light");
                }
            } else {
                icon.setDisp(false);
            }
            lvup.setDisp(icon.isDisp());
        }
    }
}

bool GfMenuObjDrArtsSet2::seqConfirmItem() {
    if (!m_seqStep) {
        unsigned int item = m_items->getContents(m_items->getIndex(false)).m_id;
        if (item - 0x633D < 3) {
            unsigned int text = item - 0x6267;
            m_context->reset();
            GfMenuObjCommonText::open(m_context, text, 0);
        }
        m_seqStep = true;
    }
    if (!m_context->isTerm()) {
        return false;
    }
    if (!m_context->m_results.empty()) {
        bool yes;
        {
            GfMenuCallContext::GfMenuResult result;
            m_context->popResult(result);
            yes = result.m_value == 0 && result.m_id == 0;
        }
        if (yes) {
            unsigned int driver = GfMenuReference::getReferenceDriverID(s_RefDriverIndex);
            unsigned int wpnType = m_number->m_value;
            GfEquipUtil::execWpUpItem(driver, m_items->getContents(m_items->getIndex(false)).m_id, wpnType);
            MenuItemInfo info = m_items->getContents(m_items->getIndex(false));
            info.m_count = 1;
            m_items->decItem(info, false);
        }
    }
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        m_seq.addJob(&GfMenuObjDrArtsSet2::seqReturnWeaponSelect);
    } else {
        m_seq.addJob(&GfMenuObjDrArtsSet2::seqReturnArtsSelect);
    }
    m_seqStep = false;
    return true;
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
