#include "classes/gf/GfMenuObjMiniGame.h"
#include "classes/gf/GfMenuObjMinimap2.h"
#include "classes/gf/GfMenuObjMinimap2/MainListener.h"
#include "classes/gf/GfMenuObjMinimap2/MapListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuMapInfo.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/minigame/tora/MinigameUpdatableObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIStreamManager.h"
#include "gf/GfMenuFlag.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Pnt.h"
#include "mm/Vec2.h"
#include "mm/mtl/FixStr.h"
#include "mtl/MemManager.h"
#include "ui/EventData.h"

namespace gf {

namespace {
// Proposed names, not the original's: the symbols leave them unnamed (lbl_7100B63780, lbl_71009C2AF0). What
// initialize docks each of the nine "IMG_map_image@%02d" segments to, and at which side.
const char* const s_segmentDockTargets[9] = {
    "IMG_map_image_center", "IMG_map_image_center", "IMG_map_image_center",
    "IMG_map_image_center", "IMG_map_image_center", "IMG_map_image_center",
    "IMG_map_image_center", "IMG_map_image_center", "IMG_map_image_center",
};
const unsigned int s_segmentDockSides[9] = {4, 2, 6, 0, 8, 1, 5, 3, 7};
}  // namespace

GfMenuObjMiniGame::GfMenuObjMiniGame(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjMiniGame::~GfMenuObjMiniGame() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjMiniGame::initialize() {
    ui::UIObjectAcc* acc =
        new (getAllocator(ALLOCATOR(0))->getMemHandle(), nullptr, 0, 4, false) ui::UIObjectAcc(m_handle, "SCR_minigame");
    m_minigame = minigame::tora::factory::create(acc);
    GfMenuObject::initialize();
}

void GfMenuObjMiniGame::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjMiniGame::update() {
    if (m_minigame != nullptr && m_minigame->isTerminate()) {
        GfMenuObject::closeFSLayer(m_handle, true, true);
        m_minigame = nullptr;
    }
    GfMenuObject::update();
}

GfMenuObjMinimap2::GfMenuObjMinimap2(unsigned int handle)
    : GfMenuObject(handle), m_mapCreated(false), m_zoomMode(0), m_scale(1.0f) {}

GfMenuObjMinimap2::~GfMenuObjMinimap2() {}

void GfMenuObjMinimap2::open() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x80);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x21;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjMinimap2::close() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x80);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjMinimap2::enable() {
    GfMenuFlag::set1(0x1F, 0);
}

void GfMenuObjMinimap2::disable() {
    GfMenuFlag::set1(0x1F, 1);
}

void GfMenuObjMinimap2::changeMap() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x80));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x100;
        GfMenuObject::sendEvent(acc.searchChild("LAY_map"), event, 0.0f);
    }
}

void GfMenuObjMinimap2::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
#line 134
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::attachExternalCall(0x80, acc.m_handle);
#line 140
    MapListener* mapListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MapListener(this);
    mapListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.searchChild("LAY_map"), mapListener);
    if (mapListener != nullptr) {
        mapListener->release();
    }
    {
    ui::UIObjectAcc center(acc.m_handle, "IMG_map_image_center");
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < 9; i++) {
        name.format("IMG_map_image@%02d", i + 1);
        GfMenuObjUtil::createDockPlugin(acc.searchChild(name.m_str), acc.searchChild(s_segmentDockTargets[i]),
                                        s_segmentDockSides[i], mm::Pnt<short>(0, 0), 0);
    }
    GfMenuObjUtil::createDockPlugin(acc.searchChild("IMG_map_arrow"), center.m_handle, 8, mm::Pnt<short>(0, 0), 0);
    GfMenuObjUtil::createDockPlugin(acc.searchChild("IMG_map_camera"), center.m_handle, 8, mm::Pnt<short>(0, 0), 0);
    GfMenuObjUtil::setDockPos(center.m_handle, acc.searchChild("IMG_map_frame"), 0, true);
    }
    GfMenuObject::initialize();
}

void GfMenuObjMinimap2::finalize() {
    GfMenuObject::finalize();
}

bool GfMenuObjMinimap2::refreshMapPosition() {
    ui::UIObjectAcc acc(m_handle, "LAY_map_image");
    mm::Pnt<short> offs;
    if (!GfMenuMapInfo::getMapSegImageOffs(offs)) {
        return false;
    }
    offs.x = -offs.x;
    offs.y = -offs.y;
    mm::Pnt<short> center;
    acc.getDisplayOffsCenter(center);
    if (m_zoomMode == 1 || m_zoomMode == 2) {
        offs.x = offs.x * m_scale;
        offs.y = m_scale * offs.y;
    }
    acc.setPosCenter(mm::Pnt<short>(offs.x + center.x, offs.y + center.y));
    return true;
}

void GfMenuObjMinimap2::createIconTable(ui::UIObjectAcc& acc, mm::mtl::FixedVector<unsigned int, 256>& table) {
    ui::UIObjectAcc layout(acc.searchChild("LAY_icon"));
    ui::UIObjectAcc mask(acc.searchChild("IMG_map_mask"));
    for (int i = 0; i < 256; i++) {
        unsigned int handle = layout.duplicateChild("IMG_icon");
        ui::UIObjectAcc icon(handle);
        if (icon.m_object != nullptr) {
            icon.setDisp(false);
            icon.setSuspend(true);
            icon.setIgnoreSize(true);
            icon.setMaskObject(mask.m_handle);
            table.push_back(handle);
        }
    }
}

void GfMenuObjMinimap2::fn_7100444B88(ui::UIObjectAcc& acc, mm::mtl::FixedVector<unsigned int, 256>& table) {
    ui::UIObjectAcc layout(acc.searchChild("LAY_icon2"));
    ui::UIObjectAcc mask(acc.searchChild("IMG_map_mask"));
    if (layout.m_object != nullptr) {
        for (int i = 0; i < 256; i++) {
            unsigned int handle = layout.duplicateChild("IMG_icon2");
            ui::UIObjectAcc icon(handle);
            if (icon.m_object != nullptr) {
                icon.setDisp(false);
                icon.setSuspend(true);
                icon.setIgnoreSize(true);
                icon.setMaskObject(mask.m_handle);
                table.push_back(handle);
            }
        }
    }
}


void GfMenuObjMinimap2::MapListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 0x100: {
        mm::mtl::FixStr<32> name;
        mm::mtl::FixStr<64> image;
        if (GfMenuObjUtil::fn_710048FD30(3)) {
            for (unsigned int i = 0; i < 9; i++) {
                name.format("IMG_map_image@%02d", i + 1);
                if (GfMenuMapInfo::getMapSegImageName(i % 3, i / 3, image)) {
                    ui::UIStreamManager::get()->fn_710068A034(name, acc.searchChild("LAY_map_image"), image.m_str, 0);
                }
            }
            m_owner->update();
        } else {
            for (unsigned int i = 0; i < 9; i++) {
                name.format("IMG_map_image@%02d", i + 1);
                if (GfMenuMapInfo::getMapSegImageName(i % 3, i / 3, image)) {
                    ui::UIStreamManager::get()->createImage(name, acc.searchChild("LAY_map_image"), image.m_str, 0);
                }
            }
        }
        m_owner->m_mapCreated = true;
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}
}  // namespace gf
