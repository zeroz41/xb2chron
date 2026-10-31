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
#include "ui/EventData.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"

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
      pad_2F61(false), m_context(nullptr), pad_2F70(false), m_gmkBdat(nullptr), pad_2F80(0), m_iconFilter(0),
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

unsigned int GfMenuObjWorldMap::getFloor() {
    if (!m_zoneList->m_groupMode) {
        return m_zoneList->getContents(m_zoneList->getIndex(false)).m_mapId;
    }
    unsigned short pointId = m_pointList->getContents(m_pointList->getIndex(false)).m_mapId;
    return static_cast<unsigned short>(Bdat::getVal(m_gmkBdat, "menuMapImage", pointId));
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
