#include "classes/gf/GfMenuObjTargetInfo.h"
#include "classes/gf/GfMenuObjTargetInfo/EnemyListener.h"
#include "classes/gf/GfMenuObjTargetInfo/OtherListener.h"
#include "classes/gf/GfMenuObjTargetInfo/SymbolListener.h"
#include "classes/gf/GfMenuObjTargetInfo.h"
#include "classes/gf/GfMenuObjTargetInfo/EnemyListener.h"
#include "classes/gf/GfMenuObjTargetInfo/OtherListener.h"
#include "classes/gf/GfMenuObjTargetInfo/SymbolListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/gf/GfMenuGfObjAdapter.h"
#include "classes/gf/GfMenuPosAdapter.h"
#include "classes/ui/UIObjectDockPlugin.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/MenuOffset.h"
#include "mm/Pnt.h"
#include "mm/Vec2.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjTargetInfo::GfMenuObjTargetInfo(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjTargetInfo::~GfMenuObjTargetInfo() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjTargetInfo::initialize() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x11, main.m_handle);
    {
        ui::UIObjectAcc root(main.m_handle, "LAY_ene_root");
#line 90
        EnemyListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) EnemyListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(root.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::attachExternalCall(0xC, root.m_handle);
    }
    {
        ui::UIObjectAcc root(main.m_handle, "LAY_other_root");
#line 101
        OtherListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) OtherListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(root.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::attachExternalCall(0xD, root.m_handle);
    }
    {
        ui::UIObjectAcc root(main.m_handle, "LAY_symbol_root");
#line 113
        SymbolListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SymbolListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(root.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::attachExternalCall(0xE, root.m_handle);
    }
    GfMenuObject::initialize();
}

void GfMenuObjTargetInfo::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjTargetInfo::update() {
    GfMenuObject::update();
}

void GfMenuObjTargetInfo::EnemyListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 0x100: {
        ui::UIObjectAcc main(acc.searchDuplicatedChild("LAY_ene_main", event.m_param2));
        if (main.m_object != nullptr) {
            main.setDisp(true);
        }
        break;
    }
    case 0x101: {
        ui::UIObjectAcc main(acc.searchDuplicatedChild("LAY_ene_main", event.m_param2));
        if (main.m_object != nullptr) {
            main.setTerm();
            GfMenuObject::termCallContext(main.m_handle);
        }
        break;
    }
    case 1:
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjTargetInfo::OtherListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 0x100: {
        ui::UIObjectAcc main(acc.searchDuplicatedChild("LAY_other_main", event.m_param2));
        if (main.m_object != nullptr) {
            short baseWidth = 0;
            {
                short baseHeight;
                ui::UIObjectAcc base(main.m_handle, "IMG_other_base");
                base.getSize(true, baseWidth, baseHeight);
            }
            {
            ui::UIObjectAcc text(main.m_handle, "LAY_other_info_text");
            ui::UIObjectAcc active(main.m_handle, "IMG_other_active");
            ui::UIObjectAcc access(main.m_handle, "IMG_other_access");
            text.updateLayoutSize();
            short activeWidth, activeHeight;
            short textWidth, textHeight;
            text.getSize(true, textWidth, textHeight);
            active.getSize(false, activeWidth, activeHeight);
            activeWidth -= baseWidth;
            float scale = (float)textWidth / (float)activeWidth;
            if (scale < 1.0f) {
                scale = 1.0f;
            }
            active.setScale(mm::Vec2(scale, 1.0f));
            access.setScale(mm::Vec2(scale, 1.0f));
            ui::UIObjectAcc base(main.m_handle, "IMG_other_base");
            short width, height;
            base.getSize(true, width, height);
            GfMenuObjUtil::setDockPos(active.m_handle, base.m_handle, 2, true);
            GfMenuObjUtil::addPos(active.m_handle, -width, 0);
            GfMenuObjUtil::setDockPos(access.m_handle, base.m_handle, 2, true);
            GfMenuObjUtil::addPos(access.m_handle, -width, 0);
            }
            main.setDisp(true);
        }
        break;
    }
    case 0x101: {
        ui::UIObjectAcc main(acc.searchDuplicatedChild("LAY_other_main", event.m_param2));
        if (main.m_object != nullptr) {
            main.setTerm();
            GfMenuObject::termCallContext(main.m_handle);
        }
        break;
    }
    case 1:
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjTargetInfo::SymbolListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 0x100: {
        ui::UIObjectAcc main(acc.searchDuplicatedChild("LAY_symbol_main", event.m_param2));
        if (main.m_object != nullptr) {
            short baseWidth = 0;
            {
                short baseHeight;
                ui::UIObjectAcc base(main.m_handle, "IMG_symbol_base");
                base.getSize(true, baseWidth, baseHeight);
            }
            {
            ui::UIObjectAcc text(main.m_handle, "TXT_symbol_name");
            ui::UIObjectAcc active(main.m_handle, "IMG_symbol_active");
            ui::UIObjectAcc access(main.m_handle, "IMG_symbol_access");
            short activeWidth, activeHeight;
            short textWidth, textHeight;
            text.getSize(true, textWidth, textHeight);
            active.getSize(false, activeWidth, activeHeight);
            activeWidth -= baseWidth;
            float scale = (float)textWidth / (float)activeWidth;
            if (scale < 1.0f) {
                scale = 1.0f;
            }
            active.setScale(mm::Vec2(scale, 1.0f));
            access.setScale(mm::Vec2(scale, 1.0f));
            ui::UIObjectAcc base(main.m_handle, "IMG_symbol_base");
            short width, height;
            base.getSize(true, width, height);
            GfMenuObjUtil::setDockPos(active.m_handle, base.m_handle, 2, true);
            GfMenuObjUtil::addPos(active.m_handle, -width, 0);
            GfMenuObjUtil::setDockPos(access.m_handle, base.m_handle, 2, true);
            GfMenuObjUtil::addPos(access.m_handle, -width, 0);
            }
            main.setDisp(true);
        }
        break;
    }
    case 0x101: {
        ui::UIObjectAcc main(acc.searchDuplicatedChild("LAY_symbol_main", event.m_param2));
        if (main.m_object != nullptr) {
            main.setTerm();
            GfMenuObject::termCallContext(main.m_handle);
        }
        break;
    }
    case 1:
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

// the layouts openEnemy duplicates show the enemy: written as a helper so its objects take the stack slots the
// original gives them (the name is not the original's)
static inline void setupEnemy(ui::UIObjectAcc& main, const GfMenuObjTargetInfo::OpenEnemyParam& param) {
        {
            ui::UIObjectAcc enemy(main.searchChild("LAY_ene"));
            if (enemy.m_object != nullptr) {
                GfMenuPosAdapter::create(enemy.m_handle, param.m_obj, &param.m_offset)->setPosOffsMode(1);
                GfMenuGfObjAdapter* adapter = GfMenuGfObjAdapter::create(enemy.m_handle, 2, param.m_obj, true);
                adapter->setDispFadeMode(0.25f);
                adapter->setDispSuspendMode(true);
                GfMenuGfObjAdapter* bg =
                    GfMenuGfObjAdapter::create(enemy.searchChild("IMG_ene_bg"), 5, param.m_obj, true);
                bg->setDispReverseMode(true);
                bg->setDispAlphaMode(true);
            }
        }
        {
            ui::UIObjectAcc bg(main.searchChild("IMG_ene_bg"));
            GfMenuGfObjAdapter::create(bg.m_handle, 0x20, param.m_obj, false);
        }
        {
            ui::UIObjectAcc gauge(main.searchChild("IMG_hpgauge"));
            if (gauge.m_object != nullptr) {
                GfMenuGfObjAdapter::create(gauge.m_handle, 0, param.m_obj, true);
                gauge.setExtType(1);
            }
        }
        {
            ui::UIObjectAcc scout(main.searchChild("IMG_scout"));
            if (scout.m_object != nullptr) {
                GfMenuGfObjAdapter::create(scout.m_handle, 0x21, param.m_obj, true);
            }
        }
        {
            ui::UIObjectAcc level(main.searchChild("TXT_ene_lvnum"));
            if (level.m_object != nullptr) {
                GfMenuObjUtil::createDockPlugin(main.searchChild("TXT_ene_lvtitle"), level.m_handle, 0,
                                                mm::Pnt<short>(-2, 0), 0);
                GfMenuGfObjAdapter::create(main.searchChild("TXT_ene_lvnum"), 7, param.m_obj, true);
            }
        }
        {
            ui::UIObjectAcc info(main.searchChild("LAY_infoicon"));
            if (info.m_object != nullptr) {
                ui::UIObjectAcc enemy(main.searchChild("LAY_ene"));
                ui::UIObjectDockPlugin* dock = ui::UIObjectDockPlugin::create(info.m_handle, 0, -2, enemy.m_handle);
                dock->m_side = 2;
                if (dock != nullptr) {
                    dock->release();
                }
            }
            ui::UIObjectAcc icon(main.searchChild("IMG_infoicon"));
            if (icon.m_object != nullptr) {
                GfMenuGfObjAdapter::create(icon.m_handle, 4, param.m_obj, true)->setDispFadeMode(0.25f);
            }
        }
}

void GfMenuObjTargetInfo::openEnemy(GfMenuCallContext* context, const OpenEnemyParam& param) {
    if (context->getState() == 0) {
        ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0xC));
        if (root.m_object != nullptr && !root.isTerm()) {
            ui::UIObjectAcc main(root.duplicateChild("LAY_ene_main"));
            if (main.m_object != nullptr) {
                setupEnemy(main, param);
                {
                    unsigned int handle = root.m_handle;
                    ui::UIObjectAcc acc(main.m_handle);
                    if (acc.isDuplicate()) {
                        ui::EventData event(0x100);
                        event.m_param2 = acc.getDuplicateIndex();
                        ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
                    }
                }
                GfMenuObject::startCallContext(context, 0xC, main.m_handle);
            }
        }
    }
}

void GfMenuObjTargetInfo::close(GfMenuCallContext* context) {
    if (context == nullptr) {
        return;
    }
    if (!context->isActive()) {
        return;
    }
    unsigned int handle = 0;
    switch (context->m_objectId) {
    case 0xC:
        handle = GfMenuObject::getAttachedObject(0xC);
        break;
    case 0xD:
        handle = GfMenuObject::getAttachedObject(0xD);
        break;
    case 0xE:
        handle = GfMenuObject::getAttachedObject(0xE);
        break;
    case 0xF:
        return;
    }
    ui::UIObjectAcc acc(handle);
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::UIObjectAcc target(context->m_handle);
        GfMenuObject::nextCallContext(context, 0xF);
        ui::EventData event;
        event.m_type = 0x101;
        event.m_param2 = target.getDuplicateIndex();
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjTargetInfo::disp(bool disp) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x11));
    if (acc.m_object != nullptr) {
        acc.setDisp(disp);
    }
}

void GfMenuObjTargetInfo::dispAllOther(bool disp) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0xD));
    if (acc.m_object != nullptr) {
        acc.setDisp(disp);
    }
}

void GfMenuObjTargetInfo::dispAllSymbol(bool disp) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0xE));
    if (acc.m_object != nullptr) {
        acc.setDisp(disp);
    }
}

}  // namespace gf
