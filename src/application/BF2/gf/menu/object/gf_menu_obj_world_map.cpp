#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfGmkLocatorAtlas.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/GfMenuLocation.h"
#include "classes/gf/GfMenuObjWorldMap.h"
#include "classes/gf/GfMenuObjWorldMap.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuFieldSkillList.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuMapInfo.h"
#include "gf/GfDataMap.h"
#include "classes/gf/GfMenuLocation.h"
#include "classes/gf/GfMenuZoneMapList.h"
#include "classes/gf/GfMenuZoneMapAdapter.h"
#include "classes/gf/GfMenuWorldMapAdapter.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/ui/UIStreamManager.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjWorldMap/MainListener.h"
#include "classes/gf/GfMenuObjWorldMap/WorldListener.h"
#include "classes/gf/GfMenuObjWorldMap/IconFilterListener.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/ui/UIManager.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"
#include "gf/GfMenuFlag.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "mm/mtl/Vector.h"

namespace gf {

bool GfMenuObjWorldMap::fn_7100495A98(unsigned int id) {
    return GfGameFlag::getLocal(1, id + 51161) == 1;
}

// the world map's icon layouts, in m_iconFilter's bit order (the symbols name it)
const char* nd_lay_icon_node_tbl[10] = {
    "LAY_icon_mapjump", "LAY_icon_area",     "LAY_icon_collect", "LAY_icon_kizuna",      "LAY_icon_salvage",
    "LAY_icon_shop",    "LAY_icon_scenario", "LAY_icon_quest",   "LAY_icon_field_skill", "LAY_icon_player",
};

namespace {
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B65150; its second array is lbl_7100B65158).
// The maps the map select lists: with add-on menu layer 3, then without it. One object: the code reaches the second
// array as the first's address + 8.
struct SelectMaps {
    unsigned int layer3[2];
    unsigned int normal[15];
};
SelectMaps sSelectMaps = {{52, 53}, {3, 4, 5, 6, 9, 10, 11, 12, 13, 14, 15, 16, 18, 20, 21}};
}  // namespace

GfMenuObjWorldMap::GfMenuObjWorldMap(unsigned int handle)
    : GfMenuObject(handle), m_mapList(nullptr), m_mapSelectList(nullptr), pad_38(true), m_zoneList(nullptr),
      m_zoneSelectList(nullptr), m_seq(this), m_list2E0(nullptr), m_mapScale(1.0f), m_pointList(nullptr),
      m_pointSelectList(nullptr), pad_318(0), m_zoneMapList1(nullptr), m_zoneMapList2(nullptr), m_fieldSkillList(nullptr), m_floorLoaded(false),
      m_floorImage(), m_iconSelectList(nullptr), m_iconTables(), pad_2F18(0), pad_2F60(false),
      pad_2F61(false), m_context(nullptr), pad_2F70(false), m_gmkBdat(nullptr), m_floor(0), m_iconFilter(0),
      m_iconFilterList(nullptr), m_iconFilterCursor(nullptr), pad_2FD0(0), pad_2FD4(false) {
    m_jumpInfos.setAllocator(getAllocator(ALLOCATOR(0)));
}

GfMenuObjWorldMap::~GfMenuObjWorldMap() {
    if (m_mapList != nullptr) {
        m_mapList->release();
        m_mapList = nullptr;
    }
    if (m_mapSelectList != nullptr) {
        m_mapSelectList->release();
        m_mapSelectList = nullptr;
    }
    if (m_list2E0 != nullptr) {
        m_list2E0->release();
        m_list2E0 = nullptr;
    }
    if (m_zoneList != nullptr) {
        m_zoneList->release();
        m_zoneList = nullptr;
    }
    if (m_zoneSelectList != nullptr) {
        m_zoneSelectList->release();
        m_zoneSelectList = nullptr;
    }
    if (m_list2E0 != nullptr) {
        m_list2E0->release();
        m_list2E0 = nullptr;
    }
    if (m_pointList != nullptr) {
        m_pointList->release();
        m_pointList = nullptr;
    }
    if (m_pointSelectList != nullptr) {
        m_pointSelectList->release();
        m_pointSelectList = nullptr;
    }
    if (m_jumpInfos.size() != 0) {
        m_jumpInfos.clear();
    }
    if (m_fieldSkillList != nullptr) {
        m_fieldSkillList->release();
        m_fieldSkillList = nullptr;
    }
    if (m_zoneMapList2 != nullptr) {
        m_zoneMapList2->release();
        m_zoneMapList2 = nullptr;
    }
    if (m_zoneMapList1 != nullptr) {
        m_zoneMapList1->release();
        m_zoneMapList1 = nullptr;
    }
    if (m_zoneMapList3 != nullptr) {
        m_zoneMapList3->release();
        m_zoneMapList3 = nullptr;
    }
    if (m_iconSelectList != nullptr) {
        m_iconSelectList->release();
        m_iconSelectList = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_iconFilterList != nullptr) {
        m_iconFilterList->release();
        m_iconFilterList = nullptr;
    }
    if (m_iconFilterCursor != nullptr) {
        m_iconFilterCursor->release();
        m_iconFilterCursor = nullptr;
    }
}

void GfMenuObjWorldMap::finalize() {
    if (m_atlasInfo.m_mapId > 0) {
        mm::mtl::PtrSingleton<GfFieldGimmick>::sys()->m_locatorAtlas.create(m_atlasInfo);
    }
    GfMenuObject::finalize();
}

void GfMenuObjWorldMap::update() {
    m_seq.update();
    GfMenuLocation::updateLocator();
    mm::mtl::PtrSingleton<GfFieldGimmick>::sys()->m_locatorAtlas.update(0.0f);
    GfMenuObject::update();
}

bool GfMenuObjWorldMap::isEnterMap(unsigned int mapId) {
    unsigned char* fp = GfDataBdat::getFP(0x179);
    if (!GfMenuObjUtil::fn_710048FD30(1) || !GfMenuObjUtil::fn_7100492CBC()) {
        int top = Bdat::getIdTop(fp);
        for (unsigned int i = 0; i < Bdat::getIdCount(fp); i++) {
            if (static_cast<unsigned short>(Bdat::getVal(fp, "mapId", top + i)) == mapId) {
                unsigned short enter = Bdat::getVal(fp, "enter", top + i);
                if (enter == 0 || GfGameCond::isGameCond(enter)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void GfMenuObjWorldMap::refreshIconFilter() {
    if (m_iconFilterList != nullptr) {
        ui::UIObjectAcc acc(m_handle, "LAY_icon_filter");
        mm::mtl::FixStr<32> name;
        for (unsigned int i = 0; i < 9; i++) {
            if (i >= static_cast<unsigned int>(m_iconFilterList->getSize())) {
                break;
            }
            bool on = (m_iconFilter & (1 << i)) != 0;
            name.format("IMG_icon_filter_on@%02d", i + 1);
            acc.setDispChild(on, name.m_str);
            name.format("IMG_icon_filter_off@%02d", i + 1);
            acc.setDispChild(!on, name.m_str);
        }
    }
}

bool GfMenuObjWorldMap::seqTexDeleteWait() {
    return true;
}

bool GfMenuObjWorldMap::seqTexLoadWait() {
    ui::UIObjectAcc main(ui::UIObjectAcc(m_handle).searchChild("LAY_main"));
    ui::UIObjectAcc floor(main.searchChild("LAY_floor"));
    return !floor.isStreaming();
}

void GfMenuObjWorldMap::fn_710049761C(GfMenuIDList* list) {
    list->clear();
    for (unsigned int i = 0; i < (GfMenuObjUtil::fn_710048FD30(3) ? 2u : 15u); i++) {
        if (chkMapCond((GfMenuObjUtil::fn_710048FD30(3) ? sSelectMaps.layer3 : sSelectMaps.normal)[i], nullptr)) {
            MenuID id = MenuID();
            id.m_id = (GfMenuObjUtil::fn_710048FD30(3) ? sSelectMaps.layer3 : sSelectMaps.normal)[i];
            list->addContents(id);
        }
    }
}

bool GfMenuObjWorldMap::setupZoneList(GfMenuZoneMapList* list) {
    const char* mapName = GfDataMap::getMapResourceNameByMapID(GfMenuReference::getReferenceWorldMapID());
    list->clear();
    unsigned char* fp = GfDataBdat::getFP(0x17B);
    int top = Bdat::getIdTop(fp);
    for (unsigned int i = 0; i < Bdat::getIdCount(fp); i++) {
        unsigned int row = top + i;
        const char* includeMap = reinterpret_cast<const char*>(Bdat::getVal(fp, "include_map", row));
        if (includeMap != nullptr && strcmp(mapName, includeMap) == 0) {
            MenuZoneMapInfo info;
            info.m_mapId = row;
            unsigned short cond = Bdat::getVal(fp, "condition", row);
            if (cond == 0 || !GfGameCond::isGameCond(cond)) {
                unsigned char* gmkFp = m_gmkBdat;
                int gmkTop = Bdat::getIdTop(gmkFp);
                unsigned int gmkCount = Bdat::getIdCount(gmkFp);
                unsigned int floor = GfMenuMapInfo::fn_7100361DC0();
                for (unsigned int j = 0; j < gmkCount; j++) {
                    int gmkRow = gmkTop + j;
                    unsigned short group = Bdat::getVal(gmkFp, "menuGroup", gmkRow);
                    unsigned short jump = Bdat::getVal(gmkFp, "MAPJUMPID", gmkRow);
                    unsigned short image = Bdat::getVal(gmkFp, "menuMapImage", gmkRow);
                    if (jump != 0 && group == info.m_mapId && (image == floor || fn_7100495A98(gmkRow))) {
                        list->addContents(info);
                        break;
                    }
                }
            }
        }
    }
    return list->getSize() != 0;
}

void GfMenuObjWorldMap::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        setFadeIn(handle);
        break;
    case 2: {
        m_owner->m_seq.clear();
        GfMenuObjWorldMap* owner = m_owner;
        if (owner->m_floorLoaded && owner->m_floorImage.m_nLen != 0) {
            ui::UIObjectAcc ownerAcc(owner->m_handle);
            mm::mtl::PtrSingleton<ui::UIStreamManager>::sys()->deleteImage(owner->m_floorImage,
                                                                           ownerAcc.searchChild("LAY_floor"));
            owner->m_floorLoaded = false;
            owner->m_floorImage.clear();
        }
        setFadeOut(handle, true);
        break;
    }
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObjMainMenu2::setCloseKeyEnable(true);
        }
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjWorldMap::WorldListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObjOperationInfo::setGuideText(2, 0);
        if (m_owner->pad_2FD0 == 0) {
            setFadeIn(handle);
        }
        break;
    case 2:
        setFadeOut(handle, true);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(0);
        } else if (event.m_param0 == 2) {
            acc.setDisp(false);
            acc.setTerm();
        }
        break;
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        if (m_owner->pad_38) {
            setFadeOut(handle, event.m_param0 == 1);
        } else {
            ui::EventData ev;
            ev.m_type = 3;
            ev.m_param0 = 2;
            ui::UIManager::get()->requestObjectEvent(handle, ev, 0.0f);
        }
        GfMenuObject::disableInput(acc.searchChild("LAY_worldmap"));
        GfMenuObject::disableInput(acc.searchChild("LAY_map_sellect"));
        break;
    case 0x24: {
        GfMenuObject::disableInput(acc.searchChild("LAY_worldmap"));
        GfMenuObject::disableInput(acc.searchChild("LAY_map_sellect"));
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_out = 1;
        param.m_preset = 6;
        param.m_eventId = 2;
        GfMenuObjUtil::startPresetCtrl(handle, param);
        m_owner->pad_38 = false;
        break;
    }
    default:
        if (event.m_type == 0x102) {
            {
                unsigned int child = acc.searchChild("LAY_worldmap");
                ui::EventData ev;
                ev.m_type = 0x103;
                ev.m_param0 = 0;
                ui::UIManager::get()->requestObjectEvent(child, ev, 0.0f);
            }
            {
                unsigned int child = acc.searchChild("LAY_map_sellect");
                ui::EventData ev;
                ev.m_type = 0x103;
                ev.m_param0 = 0;
                ui::UIManager::get()->requestObjectEvent(child, ev, 0.0f);
            }
            break;
        }
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjWorldMap::refreshMapSelect(ui::UIObjectAcc& acc, GfMenuIDList* list, ui::UISelectObjList* selectList,
                                         int index) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < selectList->getSize(); i++) {
        name.format("IMG_tagbg@%02d", i + 1);
        ui::UIObjectAcc tag(selectList->getObject(i), name.m_str);
        if (index == i) {
            tag.startAnimation("select", false);
        } else {
            tag.startAnimation("normal", false);
        }
    }
    if (index != -1) {
        selectList->setIndex(index);
    }
}

void GfMenuObjWorldMap::fn_710049A6E8(ui::UIObjectAcc& acc, GfMenuZoneMapList* list) {
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 9; i++) {
        name.format("TXT_zonename_@%02d", i + 1);
        GfMenuZoneMapAdapter* adapter = GfMenuZoneMapAdapter::createFromList(acc.searchChild(name.m_str), 0, list, i, true, false);
        name.format("LAY_zonespot@%02d", i + 1);
        if (adapter != nullptr) {
            adapter->m_rowHandle = acc.searchChild(name.m_str);
        }
        name.format("IMG_sonestay_@%02d", i + 1);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
    }
    GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_zone_scroll_bar"), list, "IMG_zone_scroll_bar_base", true);
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        ui::UIObjectAcc bar(acc.m_handle, "LAY_zone_scroll_bar");
        GfMenuObjUtil::createSyncPlugin(acc.searchChild("LAY_zone_focus"), acc.searchChild("LAY_zone_scroll_bar"), 0x10);
        bar.setAlpha(0.0f);
    }
}

void GfMenuObjWorldMap::setupPointSelect(ui::UIObjectAcc& acc, GfMenuZoneMapList* list) {
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 9; i++) {
        name.format("TXT_pointname_@%02d", i + 1);
        GfMenuZoneMapAdapter* adapter = GfMenuZoneMapAdapter::createFromList(acc.searchChild(name.m_str), 1, list, i, true, false);
        name.format("LAY_pointspot@%02d", i + 1);
        if (adapter != nullptr) {
            adapter->m_rowHandle = acc.searchChild(name.m_str);
        }
    }
    GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_point_scroll_bar"), list, "IMG_point_scroll_bar_base", true);
}

void GfMenuObjWorldMap::setupMapSelect(ui::UIObjectAcc& acc, GfMenuIDList* list) {
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 9; i++) {
        name.format("TXT_areaname@%02d", i + 1);
        GfMenuWorldMapAdapter* adapter = GfMenuWorldMapAdapter::createFromList(acc.searchChild(name.m_str), 0, list, i, true, false);
        if (adapter != nullptr) {
            name.format("LAY_area_tag@%02d", i + 1);
            adapter->m_rowHandle = acc.searchChild(name.m_str);
        }
        name.format("IMG_stayicon@%02d", i + 1);
        GfMenuWorldMapAdapter::createFromList(acc.searchChild(name.m_str), 3, list, i, true, false);
    }
    GfMenuWorldMapAdapter::createFromList(acc.searchChild("TXT_areaname_select"), 0, list, -1, true, false);
    GfMenuWorldMapAdapter::createFromList(acc.searchChild("IMG_stayicon_select"), 3, list, -1, true, false);
    acc.setDispChild(false, "LAY_area_tag_select");
    GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_area_scroll_bar"), list, "IMG_area_scroll_bar_base", true);
}

void GfMenuObjWorldMap::refreshPointSelect(ui::UIObjectAcc& acc, GfMenuZoneMapList* list,
                                           ui::UISelectObjList* selectList, unsigned int mapId) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < selectList->getSize(); i++) {
        unsigned int pointMapId = list->getContents(list->getPageIndex(i)).m_mapId;
        name.format("IMG_point_base_@%02d", i + 1);
        ui::UIObjectAcc base(acc.searchChild(name.m_str));
        if (pointMapId == mapId) {
            base.startAnimation("select", false);
        } else {
            base.startAnimation("normal", false);
        }
    }
    refreshPointText(acc, list, selectList);
}

void GfMenuObjWorldMap::refreshPointText(ui::UIObjectAcc& acc, GfMenuZoneMapList* list,
                                         ui::UISelectObjList* selectList) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < selectList->getSize(); i++) {
        list->getContents(list->getPageIndex(i));
        name.format("TXT_pointname_@%02d", i + 1);
        ui::UIObjectAcc text(acc.m_handle, name.m_str);
        if (isEnableJump(list->getContents(list->getPageIndex(i)))) {
            GfMenuObjUtil::setColMulandAdd(text.m_handle, "txt_normal2");
        } else {
            GfMenuObjUtil::setColMulandAdd(text.m_handle, "txt_disable");
        }
    }
}

void GfMenuObjWorldMap::loadTex() {
    if (m_floor != getFloor()) {
        m_floor = getFloor();
        m_seq.clear();
        m_seq.addJob(&GfMenuObjWorldMap::seqTexDelete);
        m_seq.addJob(&GfMenuObjWorldMap::seqTexDeleteWait);
        m_seq.addJob(&GfMenuObjWorldMap::seqTexLoad);
        m_seq.addJob(&GfMenuObjWorldMap::seqTexLoadWait);
        m_seq.addJob(&GfMenuObjWorldMap::seqTexDraw);
        m_seq.addJob(&GfMenuObjWorldMap::seqGimik);
        m_seq.addJob(&GfMenuObjWorldMap::seqNext);
    }
}

bool GfMenuObjWorldMap::isEnableJump(const MenuZoneMapInfo& info) {
    unsigned int mapId = GfMenuReference::getReferenceWorldMapID();
    unsigned char* fp = GfDataBdat::getFP(0x5D);
    unsigned int allOff = static_cast<unsigned short>(Bdat::getVal(fp, "st_allOFF_cndID", mapId));
    unsigned short off = Bdat::getVal(fp, "st_OFF_cndID", mapId);
    if (allOff != 0 && GfGameCond::isGameCondWithMap(allOff, mapId)) {
        return false;
    }
    if (off != 0 && GfGameCond::isGameCondWithMap(off, mapId)) {
        return false;
    }
    if (info.m_disableCondition != 0 && GfGameCond::isGameCondWithMap(info.m_disableCondition, mapId)) {
        return false;
    }
    return fn_7100495A98(info.m_mapId);
}

void GfMenuObjWorldMap::fn_710049D2A4(bool fadeFirst) {
    ui::UIObjectAcc zoneMap(m_handle, "LAY_zonemap");
    for (int i = 0; i < 9; i++) {
        bool on = (m_iconFilter & (1 << i)) != 0;
        ui::UIObjectAcc icon(zoneMap.searchChild(nd_lay_icon_node_tbl[i]));
        if (fadeFirst && i == 0) {
            icon.setAlpha(on ? 1.0f : 0.0f);
            icon.setDisp(true);
        } else {
            icon.setDisp(on);
        }
    }
}

int GfMenuObjWorldMap::getTotalFieldSkillLv(unsigned int fieldSkill) {
    int total = 0;
    for (unsigned short id : m_fieldSkillBlades) {
        DataParamAcc acc(4, id, GimmickType(0));
        for (unsigned int i = 0; i < 3; i++) {
            if (acc.getFieldSkill(i, false) == fieldSkill) {
                total += acc.getFieldSkillLevel(i, false);
                break;
            }
        }
    }
    return total;
}

void GfMenuObjWorldMap::IconFilterListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc ownerAcc(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        GfMenuObject::disableInput(handle);
        break;
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            int prev = event.m_param1;
            m_owner->m_iconFilterList->setIndex(index);
            {
                ui::UIObjectAcc text(acc.m_handle, "TXT_icon_filter_index");
                unsigned short msg =
                    GfMenuObjUtil::getMsgIDFromList(GfMenuObjUtil::fn_710048FD30(3) ? 0x160 : 0x15F, index + 1);
                ui::UIStr str(GfDataBdat::getFP(0xF5), msg);
                text.setText(str);
            }
            bool on = (m_owner->m_iconFilter & (1 << index)) != 0;
            GfMenuObjOperationInfo::changeText(acc.m_handle, 0xB, on);
            if (prev != -1 && index != prev) {
                GfMenuObjUtil::playSECommonTab();
            }
        }
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
    case 8: {
        int index = event.m_param0;
        if (index != -1 && event.m_param1 == 0xB) {
            unsigned int flags = m_owner->m_iconFilter;
            if (flags & (1 << index)) {
                flags &= ~(1 << index);
            } else {
                flags |= 1 << index;
            }
            m_owner->m_iconFilter = flags;
            m_owner->refreshIconFilter();
            m_owner->fn_710049D2A4(true);
            unsigned int on = m_owner->m_iconFilter & (1 << index);
            if (on) {
                GfMenuObjUtil::playSE(0xC);
            } else {
                GfMenuObjUtil::playSE(0xE);
            }
            GfMenuFlag::set1(index + 0x28, on != 0);
            GfMenuObjOperationInfo::changeText(acc.m_handle, 0xB, on != 0);
        }
        break;
    }
    case 0x103:
        m_owner->m_iconFilterList->setIndex(0);
        GfMenuObject::resetInputSelection(acc.m_handle);
        GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_iconFilterList);
        acc.setDisp(true);
        m_owner->m_iconFilterCursor->setDisp(true);
        m_owner->refreshIconFilter();
        GfMenuObject::enableInput(handle);
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    case 0x104:
        acc.setDisp(false);
        m_owner->m_iconFilterCursor->setDisp(false);
        GfMenuObject::disableInput(handle);
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjWorldMap::chkMapCond(unsigned int mapId, mm::Pnt<short>* pos) {
    unsigned char* fp = GfDataBdat::getFP(0x179);
    unsigned char* posFp = GfDataBdat::getFP(0x178);
    int top = Bdat::getIdTop(fp);
    for (unsigned int i = 0; i < Bdat::getIdCount(fp); i++) {
        int row = i + top;
        if (static_cast<unsigned short>(Bdat::getVal(fp, "mapId", row)) == mapId) {
            mm::mtl::FixStr<32> name;
            for (unsigned int j = 0; j < 3; j++) {
                name.format("cond%d", j + 1);
                bool met = GfGameCond::isGameCond(static_cast<unsigned short>(Bdat::getVal(fp, name.m_str, row)));
                if (met) {
                    if (pos != nullptr) {
                        name.format("pos%d", j + 1);
                        unsigned short posId = Bdat::getVal(fp, name.m_str, row);
                        if (posId == 0) {
                            pos->x = 0;
                            pos->y = 0;
                        } else {
                            pos->x = Bdat::getVal(posFp, "posX", posId);
                            pos->y = Bdat::getVal(posFp, "posY", posId);
                        }
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

unsigned int GfMenuObjWorldMap::getFloor() {
    if (!m_zoneList->m_groupMode) {
        return m_zoneList->getContents(m_zoneList->getIndex(false)).m_mapId;
    }
    unsigned short pointId = m_pointList->getContents(m_pointList->getIndex(false)).m_mapId;
    return static_cast<unsigned short>(Bdat::getVal(m_gmkBdat, "menuMapImage", pointId));
}

bool GfMenuObjWorldMap::seqTexLoad() {
    ui::UIObjectAcc main(ui::UIObjectAcc(m_handle).searchChild("LAY_main"));
    GfDataMap::getMapResourceNameByMapID(GfMenuReference::getReferenceWorldMapID());
    unsigned int floor = getFloor();
    unsigned char* fp = GfDataBdat::getFP(0x17A);
    const char* level = reinterpret_cast<const char*>(Bdat::getVal(fp, "level_name", floor));
    unsigned short cond = Bdat::getVal(fp, "condition", floor);
    if (cond != 0 && GfGameCond::isGameCond(cond)) {
        level = reinterpret_cast<const char*>(Bdat::getVal(fp, "level_name2", floor));
    }
    mm::mtl::FixStr<32> file;
    file.format("%s_map", level);
    mm::mtl::FixStr<32> image;
    image.format("%s%d", "IMG_floor", floor);
    mm::mtl::PtrSingleton<ui::UIStreamManager>::sys()->createImage(image, main.searchChild("LAY_floor"), file.m_str, 0);
    m_floorLoaded = true;
    m_floorImage = image;
    main.setDispChild(false, "LAY_frame_cursor");
    return true;
}

void GfMenuObjWorldMap::getFloorAABB(unsigned int mapId, unsigned int floor, mm::Aabb& aabb, mm::Pnt<short>& center) {
    int index = GfMenuMapInfo::getMapInfoIndex(GfDataMap::getMapResourceNameByMapID(mapId));
    if (index != -1) {
        GfMenuMapInfo::MapAreaInfo info;
        const char* name = reinterpret_cast<const char*>(Bdat::getVal(GfDataBdat::getFP(0x17A), "level_name", floor));
        if (GfMenuMapInfo::getMapAreaFromName(index, name, info)) {
            mm::Vec3 min;
            min.x = info.m_minX;
            min.y = info.m_minY;
            min.z = info.m_minZ;
            mm::Vec3 max;
            max.x = info.m_maxX;
            max.y = info.m_maxY;
            max.z = info.m_maxZ;
            aabb.set(min, max);
            center.x = static_cast<short>((min.x + max.x) * 0.5f);
            center.y = static_cast<short>((min.z + max.z) * 0.5f);
        }
    }
}

bool GfMenuObjWorldMap::fn_710049FB94(const gmk::AGmkBase* gmk) {
    unsigned int type = gmk->getGmkType();
    if (type - 3 > 1) {
        return false;
    }
    return Bdat::getValCheckU16(gmk->getBindedBdatFp(), "ShopID", gmk->m_createInfo.m_bdatId) == 0xDE;
}

unsigned int GfMenuObjWorldMap::setupIconTableSub(ui::UIObjectAcc& acc, mm::mtl::FixedVector<unsigned int, 256>& icons,
                                                  unsigned int type, mm::Pnt<short> pos, mm::Vec2 scale) {
    static const unsigned int imageIndex[10] = {1, 3, 4, 5, 6, 7, 8, 9, 10, 0};
    if (icons.size() == 256) {
        return 0;
    }
    const char* node = nd_lay_icon_node_tbl[type];
    ui::UIObjectAcc layIcon(acc.searchChild("LAY_icon"));
    unsigned int handle = ui::UIObjectAcc(layIcon.searchChild("IMG_zoneicon")).duplicate(layIcon.searchChild(node));
    ui::UIObjectAcc icon(handle);
    if (icon.m_object != nullptr) {
        icon.setDisp(true);
        icon.setPosCenter(pos);
        icon.setImageIndex(imageIndex[type]);
        icons.push_back(handle);
    }
    return handle;
}

mm::Col3 GfMenuObjWorldMap::fn_710049FD30(unsigned int id) {
    static const mm::Col3 colors[2] = {mm::Col3(1.0f, 1.0f, 1.0f), mm::Col3(0.78f, 1.0f, 0.0f)};
    if (id >= 2) {
        return colors[0];
    }
    return colors[id];
}
}  // namespace gf

// instantiated for gf::GfMenuObjWorldMap::ZoneSelectListener::reciveEvent, gf::GfMenuObjWorldMap::initialize (not written yet)
template mm::mtl::Vector<gf::MenuZoneMapInfo>::iterator mm::mtl::Vector<gf::MenuZoneMapInfo>::erase(gf::MenuZoneMapInfo*);

namespace gf {

}  // namespace gf
