#include "ui/EventData.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/gf/GfMenuObjMainMenu2BG.h"
#include "classes/gf/GfMenuObjMainMenu2BG/MainListener.h"
#include "classes/gf/GfInfo.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Rect.h"
#include "mm/Pnt.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjWorldMap.h"
#include "classes/ui/UIEventManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

int GfMenuObjMainMenu2BG::s_ThemaIndex = -1;

GfMenuObjMainMenu2BG::GfMenuObjMainMenu2BG(unsigned int handle)
    : GfMenuObject(handle), m_resultHandle(0), m_list(nullptr), m_bgList(nullptr) {}

GfMenuObjMainMenu2BG::~GfMenuObjMainMenu2BG() {
    if (m_bgList != nullptr) {
        m_bgList->release();
        m_bgList = nullptr;
    }
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

void GfMenuObjMainMenu2BG::initialize() {
    // the names of the tables' types and fields are not the original's
    struct BgFormat {
        const char* m_layFormat;  // the backgrounds' layouts
        const char* m_imgFormat;  // their images
    };
    struct BgImage {
        const char* m_name;
        unsigned int m_mapId;  // GfMenuObjWorldMap::chkMapCond's map, 0 for always shown
    };
    ui::UIObjectAcc acc(m_handle);
    {
        unsigned int main = acc.searchChild("LAY_main");
#line 122
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(main, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::attachExternalCall(0x60, main);
    }
    GfMenuObject::initialize();
    if (GfMenuObjUtil::isValidExpansion(3)) {
        if (!GfMenuObjMainMenu2::isOpenHitonowaDirect()) {
            // the layout and image name formats of the two background sets (lbl_7100B63130; the names are not the
            // original's)
            static const BgFormat s_bgFormats[] = {
                {"LAY_bg2@%02d", "IMG_bg2@%02d"},
                {"LAY_bg3@%02d", "IMG_bg3@%02d"},
            };
            bool cond = GfMenuObjUtil::getMenuCondition(0x39);
            {
                mm::mtl::IAllocator* allocator = getAllocator(ALLOCATOR(0));
                ui::UISelectObjList::CreateParam create;
                create.m_allocator = allocator;
                m_list = ui::UISelectObjList::create(create);
            }
            m_list->pickupObject(acc.m_handle, s_bgFormats[cond].m_layFormat, 1);
            ui::UISelectObjList::CreateParam create;
            mm::mtl::FixStr<32> name;
            create.m_allocator = getAllocator(ALLOCATOR(0));
            m_bgList = ui::UISelectObjList::create(create);
            m_positions.clear();
            const char* imgFormat = s_bgFormats[cond].m_imgFormat;
            for (unsigned int i = 0; i < m_list->getSize(); i++) {
                name.format(imgFormat, i + 1);
                ui::UIObjectAcc img(acc.m_handle, name.m_str);
                m_bgList->addObject(img.m_handle);
                img.setImageIndex(i + 1);
                BgPos bg;
                bg.m_flip = cond && i == 0;
                name.format(s_bgFormats[cond].m_layFormat, i + 1);
                {
                    ui::UIObjectAcc lay(acc.m_handle, name.m_str);
                    mm::Pnt<short> pos;
                    lay.getPos(pos);
                    bg.m_x = pos.x;
                }
                m_positions.push_back(bg);
            }
            acc.setDispChild(!cond, "LAY_bg2");
            acc.setDispChild(cond, "LAY_bg3");
        }
    } else {
        {
            mm::mtl::IAllocator* allocator = getAllocator(ALLOCATOR(0));
            ui::UISelectObjList::CreateParam create;
            create.m_allocator = allocator;
            m_list = ui::UISelectObjList::create(create);
            m_list->pickupObject(acc.searchChild("LAY_bg2"), "LAY_bg2@%02d", 1);
        }
        // the background images and the map each one is shown for, 0 for always (lbl_7100B63150; the names are
        // not the original's)
        static const BgImage s_bgImages[] = {
            {"IMG_bg_far", 0},       {"IMG_bg_symbol@01", 0},  {"IMG_bg_symbol@02", 14}, {"IMG_bg_symbol@03", 12},
            {"IMG_bg_symbol@04", 12}, {"IMG_bg_symbol@06", 9},  {"IMG_bg_symbol@07", 10}, {"IMG_bg_cloud@12", 0},
            {"IMG_bg_symbol@08", 13}, {"IMG_bg_symbol@09", 6},  {"IMG_bg_symbol@10", 3},  {"IMG_bg_symbol@11", 0},
            {"IMG_bg_cloud@11", 0},
        };
        mm::mtl::IAllocator* allocator = getAllocator(ALLOCATOR(0));
        ui::UISelectObjList::CreateParam create;
        create.m_allocator = allocator;
        m_bgList = ui::UISelectObjList::create(create);
        for (unsigned int i = 0; i < sizeof(s_bgImages) / sizeof(s_bgImages[0]); i++) {
            m_bgList->addObject(acc.searchChild(s_bgImages[i].m_name));
        }
        int thema;
        if (GfFieldTime* time = GfFieldTime::get()) {
            int hour = time->getHour();
            if (hour >= 5 && hour < 15) {
                thema = 1;
            } else if (hour >= 15 && hour < 21) {
                thema = 2;
            } else {
                thema = 3;
            }
        } else {
            thema = 3;
        }
        if (s_ThemaIndex != thema) {
            s_ThemaIndex = thema;
        }
        for (unsigned int i = 0; i < m_bgList->getSize(); i++) {
            ui::UIObjectAcc bg(m_bgList->getObject(i));
            if (s_bgImages[i].m_mapId != 0) {
                mm::Pnt<short> pos;
                bg.setDisp(GfMenuObjWorldMap::chkMapCond(s_bgImages[i].m_mapId, &pos));
            }
            bg.setImageIndex(s_ThemaIndex);
        }
    }
}

void GfMenuObjMainMenu2BG::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjMainMenu2BG::update() {
    if (m_bgList != nullptr) {
        for (unsigned int i = 0; i < m_bgList->getSize(); i++) {
            ui::UIObjectAcc bg(m_bgList->getObject(i));
            if (!bg.isStreaming()) {
                bg.setAlpha(1.0f);
                bg.startAnimationFromIndex(1, false);
                m_bgList->delObject(bg.m_handle);
            }
        }
    }
    GfMenuObject::update();
}

void GfMenuObjMainMenu2BG::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        acc.setDisp(false);
        break;
    case 3:
        if (event.m_param0 == 1 && m_owner->m_resultHandle != 0) {
            GfMenuObject::addResultCallContext(m_owner->m_resultHandle, 1, 0);
            m_owner->m_resultHandle = 0;
        }
        break;
    case 0x101: {
        short screenW = GfScreenW();
        unsigned int count = event.m_param2;
        int move = event.m_param0;
        m_owner->m_resultHandle = event.m_param3;
        for (unsigned int i = 0; i < m_owner->m_list->getSize(); i++) {
            mm::Rect<short> rect;
            ui::UIObjectAcc bg(m_owner->m_list->getObject(i));
            bg.getRect(rect, 2);
            unsigned int step = (rect.w - screenW) / (count - 1);
            int dist = step * move;
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x80;
            param.m_curve = 1;
            param.m_time = event.m_param1Float;
            param.m_pos.x = -dist;
            param.m_eventId = 1;
            param.m_pos.y = 0;
            if (GfMenuObjUtil::isValidExpansion(3)) {
                if (m_owner->m_positions[i].m_flip == 1) {
                    param.m_pos.x = m_owner->m_positions[i].m_x + dist;
                } else {
                    param.m_pos.x = m_owner->m_positions[i].m_x - dist;
                }
            }
            int ctrl = GfMenuObjUtil::startCtrl(bg.m_handle, param, nullptr);
            if (i == 0) {
                GfMenuObject::hookCtrlEvent(handle, ctrl);
            }
        }
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjMainMenu2BG::move(GfMenuCallContext* context, unsigned int handle, const OpenMainMenuBg& param) {
    unsigned int bg = GfMenuObject::getAttachedObject(0x60);
    if (ui::UIObjectAcc(bg).m_object != nullptr) {
        if (!ui::UIObjectAcc(bg).isTerm()) {
            ui::EventData event;
            event.m_type = 0x101;
            event.m_param0 = param.m_move;
            event.m_param1Float = param.m_time;
            event.m_param2 = param.m_count;
            event.m_param3 = handle;
            ui::UIManager::get()->requestObjectEvent(bg, event, 0.0f);
        }
    }
}

}  // namespace gf
