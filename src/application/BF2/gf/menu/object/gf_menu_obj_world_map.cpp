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
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"

namespace gf {

bool GfMenuObjWorldMap::fn_7100495A98(unsigned int id) {
    return GfGameFlag::getLocal(1, id + 51161) == 1;
}

GfMenuObjWorldMap::GfMenuObjWorldMap(unsigned int handle)
    : GfMenuObject(handle), m_mapList(nullptr), m_mapSelectList(nullptr), pad_38(true), m_zoneList(nullptr),
      m_zoneSelectList(nullptr), m_seq(this), m_list2E0(nullptr), m_mapScale(1.0f), m_pointList(nullptr),
      m_pointSelectList(nullptr), pad_318(0), m_zoneMapList1(nullptr), m_zoneMapList2(nullptr), m_fieldSkillList(nullptr), pad_698(false),
      pad_69C(false), pad_6BC(0), m_iconSelectList(nullptr), m_iconTables(), pad_2F18(0), pad_2F60(false),
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

}  // namespace gf
