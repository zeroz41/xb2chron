#include "classes/gf/GfMenuObjTargetInfo.h"
#include "gf/GfDataBlade.h"
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
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuShopAdapter.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataItem.h"
#include "gf/GfItemUtil.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuItemUtil.h"
#include "gf/GfObjAcc.h"
#include "mm/Col3.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/MenuOffset.h"
#include "mm/Pnt.h"
#include "mm/Vec2.h"
#include "ui/EventData.h"
#include "gf/GfDataNpc.h"

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

// the colors openOther and openSymbol give the access copy of the name. Proposed names, not the original's: the
// symbols leave them unnamed (lbl_71009C4990, lbl_71009C499C)
static const mm::Col3 s_accessMulColor(1.0f, 176.0f / 255.0f, 222.0f / 255.0f);
static const mm::Col3 s_accessAddColor(131.0f / 255.0f, 48.0f / 255.0f, 146.0f / 255.0f);

// the text a blade object (type 6) has for its shop name: a helper so its object takes the stack slot the original
// gives it (the name is not the original's)
static inline bool getBladeShopName(unsigned char*& bdat, unsigned int& id, GF_OBJ_HANDLE* handle) {
    GfObjAcc obj(handle);
    if (obj.getType() != 6) {
        return false;
    }
    if (!GfDataNpc::getJobMsg(bdat, id, obj.getNpcRscId())) {
        bdat = nullptr;
        id = 0;
        return false;
    }
    return true;
}

// tells the root that a duplicated menu opened (0x100 with the duplicate's index): a helper so its objects take
// the stack slots the original gives them (the name is not the original's)
static inline void requestOpenEvent(unsigned int root, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (acc.isDuplicate()) {
        ui::EventData event(0x100);
        event.m_param2 = acc.getDuplicateIndex();
        ui::UIManager::get()->requestObjectEvent(root, event, 0.0f);
    }
}

void GfMenuObjTargetInfo::openOther(GfMenuCallContext* context, const OpenOtherParam& param) {
    if (param.m_symbol) {
        OpenSymbolParam symbol;
        symbol.m_nameBdat = param.m_nameBdat;
        symbol.m_nameId = param.m_nameId;
        symbol.m_pointBdat = param.m_pointBdat;
        symbol.m_pointId = param.m_pointId;
        symbol.m_obj = param.m_obj;
        symbol.m_offset = param.m_offset;
        symbol.m_icon = param.m_shopId;
        if (GfMenuObjUtil::isValidExpansion(3)) {
            symbol.m_collect = param.m_collect;
        }
        openSymbol(context, symbol);
        return;
    }
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0xD));
    if (root.m_object != nullptr && !root.isTerm()) {
        ui::UIObjectAcc main(root.duplicateChild("LAY_other_main"));
        if (main.m_object != nullptr) {
            {
                ui::UIObjectAcc self(main.m_handle);
                if (self.m_object != nullptr) {
                    GfMenuPosAdapter::create(self.m_handle, param.m_obj, &param.m_offset)->setPosOffsMode(1);
                    GfMenuGfObjAdapter* adapter = GfMenuGfObjAdapter::create(self.m_handle, 3, param.m_obj, true);
                    adapter->setDispFadeMode(0.25f);
                    adapter->setDispSuspendMode(true);
                }
            }
            {
                ui::UIObjectAcc info(main.searchChild("LAY_other_info"));
                if (info.m_object != nullptr) {
                    GfMenuGfObjAdapter::create(info.m_handle, 2, param.m_obj, true)->setDispFadeMode(0.25f);
                }
                ui::UIObjectAcc base(main.searchChild("IMG_other_base"));
                if (base.m_object != nullptr) {
                    GfMenuGfObjAdapter* adapter = GfMenuGfObjAdapter::create(base.m_handle, 2, param.m_obj, true);
                    adapter->setDispReverseMode(true);
                    adapter->setDispFadeMode(0.25f);
                }
                ui::UIObjectAcc active(main.searchChild("IMG_other_active"));
                if (active.m_object != nullptr) {
                    GfMenuGfObjAdapter::create(active.m_handle, 6, param.m_obj, true)->setDispReverseMode(true);
                    {
                        ui::UIObjectAcc name(main.m_handle, "TXT_other_name");
                        GfMenuObjUtil::createSyncPlugin(name.m_handle, active.m_handle, 0x20);
                    }
                    ui::UIObjectAcc access(main.searchChild("IMG_other_access"));
                    if (access.m_object != nullptr) {
                        GfMenuGfObjAdapter::create(access.m_handle, 6, param.m_obj, true);
                        GfMenuObjUtil::createSyncPlugin(access.m_handle, active.m_handle, 1);
                        GfMenuObjUtil::createSyncPlugin(ui::UIObjectAcc(main.m_handle, "TXT_other_name_access").m_handle,
                                                        access.m_handle, 0x20);
                    }
                }
            }
            if (param.m_nameBdat != nullptr && param.m_nameId != 0) {
                ui::UIObjectAcc name(main.m_handle, "TXT_other_name");
                ui::UIObjectAcc access(main.m_handle, "TXT_other_name_access");
                name.setText(ui::UIStr(param.m_nameBdat, param.m_nameId));
                name.saveDefColor();
                access.setText(ui::UIStr(param.m_nameBdat, param.m_nameId));
                access.setMulColor(s_accessMulColor);
                access.setAddColor(s_accessAddColor);
            }
            bool layer3 = GfMenuObjUtil::isValidExpansion(3);
            if (!layer3) {
                if (param.m_shopId != 0) {
                    ui::UIObjectAcc shop(main.m_handle, "TXT_other_shop_name");
                    ui::UIObjectAcc owner(main.m_handle, "IMG_other_owner_icon");
                    GfMenuShopAdapter::create(shop.m_handle, 0, param.m_shopId, false);
                    GfMenuShopAdapter::create(owner.m_handle, 4, param.m_shopId, true);
                    GfMenuObjUtil::createDockPlugin(owner.m_handle, shop.m_handle, 1, mm::Pnt<short>(0, 0), 0);
                } else {
                    main.setDispChild(false, "TXT_other_shop_name");
                }
            } else {
                ui::UIObjectAcc shop(main.m_handle, "TXT_other_shop_name");
                unsigned char* bdat = nullptr;
                unsigned int id = 0;
                if (getBladeShopName(bdat, id, param.m_obj) && bdat != nullptr && id != 0) {
                    shop.setText(ui::UIStr(bdat, id));
                    shop.setDisp(true);
                } else {
                    shop.setDisp(false);
                }
                main.setDispChild(false, "IMG_other_owner_icon");
            }
            {
                ui::UIObjectAcc icon(main.searchChild("IMG_other_icon"));
                if (icon.m_object != nullptr) {
                    GfMenuGfObjAdapter::create(icon.m_handle, 4, param.m_obj, true);
                }
            }
            if (layer3) {
                ui::UIObjectAcc status(main.m_handle, "LAY_other_status");
                if (status.m_object != nullptr) {
                    status.setDisp(true);
                    ui::UIObjectAcc image(status.m_handle, "IMG_other_status");
                    if (image.m_object != nullptr) {
                        image.setDisp(false);
                        GfMenuGfObjAdapter::create(image.m_handle, 0x2B, param.m_obj, true);
                    }
                }
            }
            requestOpenEvent(root.m_handle, main.m_handle);
            GfMenuObject::startCallContext(context, 0xD, main.m_handle);
        }
    }
}

void GfMenuObjTargetInfo::openSymbol(GfMenuCallContext* context, const OpenSymbolParam& param) {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0xE));
    if (root.m_object != nullptr && !root.isTerm()) {
        ui::UIObjectAcc main(root.duplicateChild("LAY_symbol_main"));
        if (main.m_object != nullptr) {
            {
                ui::UIObjectAcc self(main.m_handle);
                if (self.m_object != nullptr) {
                    GfMenuPosAdapter::create(self.m_handle, param.m_obj, &param.m_offset)->setPosOffsMode(1);
                    GfMenuGfObjAdapter* adapter = GfMenuGfObjAdapter::create(self.m_handle, 3, param.m_obj, true);
                    adapter->setDispFadeMode(0.25f);
                    adapter->setDispSuspendMode(true);
                }
            }
            {
                ui::UIObjectAcc info(main.searchChild("LAY_symbol_info"));
                if (info.m_object != nullptr) {
                    GfMenuGfObjAdapter::create(info.m_handle, 2, param.m_obj, true)->setDispFadeMode(0.25f);
                }
                ui::UIObjectAcc base(main.searchChild("IMG_symbol_base"));
                if (base.m_object != nullptr) {
                    GfMenuGfObjAdapter* adapter = GfMenuGfObjAdapter::create(base.m_handle, 2, param.m_obj, true);
                    adapter->setDispReverseMode(true);
                    adapter->setDispFadeMode(0.25f);
                }
                ui::UIObjectAcc active(main.searchChild("IMG_symbol_active"));
                if (active.m_object != nullptr) {
                    GfMenuGfObjAdapter::create(active.m_handle, 6, param.m_obj, true)->setDispReverseMode(true);
                    {
                        ui::UIObjectAcc name(main.m_handle, "TXT_symbol_name");
                        GfMenuObjUtil::createSyncPlugin(name.m_handle, active.m_handle, 0x20);
                    }
                    ui::UIObjectAcc access(main.searchChild("IMG_symbol_access"));
                    if (access.m_object != nullptr) {
                        GfMenuGfObjAdapter::create(access.m_handle, 6, param.m_obj, true);
                        GfMenuObjUtil::createSyncPlugin(access.m_handle, active.m_handle, 1);
                        GfMenuObjUtil::createSyncPlugin(
                            ui::UIObjectAcc(main.m_handle, "TXT_symbol_name_access").m_handle, access.m_handle, 0x20);
                    }
                }
            }
            if (param.m_nameBdat != nullptr && param.m_nameId != 0) {
                ui::UIObjectAcc name(main.m_handle, "TXT_symbol_name");
                ui::UIObjectAcc access(main.m_handle, "TXT_symbol_name_access");
                name.setText(ui::UIStr(param.m_nameBdat, param.m_nameId));
                name.saveDefColor();
                access.setText(ui::UIStr(param.m_nameBdat, param.m_nameId));
                access.setMulColor(s_accessMulColor);
                access.setAddColor(s_accessAddColor);
            }
            if (param.m_pointBdat != nullptr && param.m_pointId != 0) {
                ui::UIObjectAcc point(main.m_handle, "TXT_symbol_point_name");
                ui::UIStr text(param.m_pointBdat, param.m_pointId);
                if (text.isValid()) {
                    point.setText(text);
                    point.setDisp(true);
                }
            }
            {
                ui::UIObjectAcc icon(main.searchChild("IMG_symbol_icon"));
                if (icon.m_object != nullptr) {
                    icon.setImageIndex(param.m_icon);
                }
            }
            {
                ui::UIObjectAcc eff(main.searchChild("IMG_symbol_eff"));
                if (eff.m_object != nullptr) {
                    eff.startAnimationFromID(1, false);
                }
            }
            if (GfMenuObjUtil::isValidExpansion(3) && param.m_icon == 2 && param.m_collect != 0) {
                unsigned char* bdat = GfDataBdat::getFP(0x1E0);
                if (GfMenuBdat::isValidBdatID(bdat, param.m_collect)) {
                    unsigned short item = Bdat::getVal(bdat, "itm1ID", param.m_collect);
                    if (item != 0) {
                        ui::UIObjectAcc collect(main.searchChild("LAY_symbol_collect"));
                        if (collect.m_object != nullptr) {
                            unsigned int type = GfDataItem::getItemType(item);
                            unsigned int id;
                            if (type == 10) {
                                ItemProperty property;
                                GfItemUtil::getProperty(property, item, 0);
                                id = property.m_favoriteKey;
                            } else if (type == 7) {
                                ItemProperty property;
                                GfItemUtil::getProperty(property, item, 0);
                                id = property.m_collectionKey;
                            } else if (type == 2) {
                                ItemProperty property;
                                GfItemUtil::getProperty(property, item, 0);
                                id = property.m_iconIndex + 1;
                            } else {
                                id = 0;
                            }
                            unsigned int number;
                            if (GfMenuItemUtil::getIconNumber(static_cast<ItemType::Type>(type), id, number, false)) {
                                ui::UIObjectAcc image(collect.m_handle, "IMG_symbol_collect_item");
                                collect.setDisp(true);
                                image.setImageIndex(number);
                            }
                        }
                    }
                }
            }
            requestOpenEvent(root.m_handle, main.m_handle);
            GfMenuObject::startCallContext(context, 0xE, main.m_handle);
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
