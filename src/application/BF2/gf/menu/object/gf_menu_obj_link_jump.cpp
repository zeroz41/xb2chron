#include "classes/ui/UIObjectAcc.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuObjLinkJump.h"
#include "classes/gf/GfMenuObjLinkJump/CategoryListener.h"
#include "classes/gf/GfMenuObjLinkJump/ListListener.h"
#include "classes/gf/GfMenuObjLinkJump/NotifyListener.h"
#include "classes/gf/GfMenuObjLinkJump/RootListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuEnemyList.h"
#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UICtrlObject.h"
#include "classes/ui/UICtrlRevolveSelect.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIListInfo.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Pnt.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjLinkJump::GfMenuObjLinkJump(unsigned int handle)
    : GfMenuObject(handle), m_lists(), m_categories(nullptr), m_revolve(nullptr), m_open(false) {}

GfMenuObjLinkJump::~GfMenuObjLinkJump() {
    for (int i = 0; i < 2; i++) {
        if (m_lists[i].m_cursor != nullptr) {
            m_lists[i].m_cursor->release();
            m_lists[i].m_cursor = nullptr;
        }
        if (m_lists[i].m_list != nullptr) {
            m_lists[i].m_list->release();
            m_lists[i].m_list = nullptr;
        }
        if (m_lists[i].m_selectList != nullptr) {
            m_lists[i].m_selectList->release();
            m_lists[i].m_selectList = nullptr;
        }
    }
    if (m_revolve != nullptr) {
        m_revolve->release();
        m_revolve = nullptr;
    }
    if (m_categories != nullptr) {
        m_categories->release();
        m_categories = nullptr;
    }
}

void GfMenuObjLinkJump::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_root");
    if (acc.m_object != nullptr) {
#line 72
        RootListener* root = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) RootListener(this);
        // the original stores the count after the listener's own fields, not with its base
        root->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(acc.m_handle, root);
        if (root != nullptr) {
            root->release();
        }
#line 73
        CategoryListener* category = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) CategoryListener(this);
        category->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(acc.searchChild("LAY_category_list"), category);
        if (category != nullptr) {
            category->release();
        }
#line 74
        NotifyListener* notify = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) NotifyListener(this);
        notify->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(acc.searchChild("LAY_notify"), notify);
        if (notify != nullptr) {
            notify->release();
        }
        setupListObject(0);
        setupListObject(1);
        ui::UIObjectAcc(m_handle, "IMG_bg").setAlpha(0.5f);
        GfMenuObject::initialize();
    }
}

void GfMenuObjLinkJump::setupListObject(unsigned int index) {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (acc.m_object == nullptr) {
        return;
    }
    ui::UIObjectAcc list(acc.duplicateChild("LAY_list"));
    if (list.m_object == nullptr) {
        return;
    }
    unsigned int handle = list.m_handle;
    list.setDisp(true);
    ui::UISelectObjList* selectList;
    {
        ui::UISelectObjList::CreateParam create;
        create.m_allocator = getAllocator(ALLOCATOR(0));
        selectList = ui::UISelectObjList::create(create);
    }
    if (selectList != nullptr) {
        selectList->pickupObject(list.m_handle, "TXT_item%02d", 1);
        selectList->getSize();
    }
    ui::UICtrlCursorSelect* cursor;
    {
        ui::UICtrlCursorSelect::CursorSetting setting;
        setting.m_dockType = 4;
        cursor = ui::UICtrlCursorSelect::create(list.searchChild("IMG_cursor"), setting, selectList);
    }
    ui::UIListInfoBase* contents;
    if (index == 0) {
        for (unsigned int i = 0; i < static_cast<unsigned int>(selectList->getSize()); i++) {
            GfMenuCharDataAdapter::createFromEnemyList(selectList->getObject(i), 2, GfMenuReference::getEnemyLinkList(),
                                                       i, false);
        }
        contents = GfMenuReference::getEnemyLinkList();
        contents->addRef();
    } else if (index == 1) {
        for (unsigned int i = 0; i < static_cast<unsigned int>(selectList->getSize()); i++) {
            GfMenuItemAdapter::createFromList(selectList->getObject(i), 0, GfMenuReference::getItemLinkList(), i, false);
        }
        contents = GfMenuReference::getItemLinkList();
        contents->addRef();
    } else {
        contents = nullptr;
    }
    {
        ui::UIObjectAcc bar(list.searchChild("IMG_scroll_bar"));
        GfMenuObjUtil::createVScrollBarPlugin(bar.m_handle, contents, "IMG_scroll_base", true);
    }
    mm::mtl::FixStr<32> name;
    name.format("TXT_title%02d", index + 1);
    list.setDispChild(true, name.m_str);
    ListObject& object = m_lists[index];
    object.m_handle = handle;
    object.m_list = contents;
    object.m_selectList = selectList;
    object.m_cursor = cursor;
#line 680
    ListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListListener(this, &object);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(list.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
}

void GfMenuObjLinkJump::finalize() {
    GfMenuReference::clearLinkList();
    GfMenuObject::finalize();
}

void GfMenuObjLinkJump::update() {
    GfMenuObject::update();
}

void GfMenuObjLinkJump::RootListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        ui::EventData open;
        open.m_type = 0x21;
        GfMenuObject::sendEvent(acc.searchChild("LAY_notify"), open, 0.0f);
        m_owner->m_open = false;
        break;
    }
    case 8:
        if (event.m_param1 == 9 && !m_owner->m_open) {
            ui::EventData open;
            open.m_type = 0x21;
            GfMenuObject::sendEvent(acc.searchChild("LAY_category_list"), open, 0.0f);
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjLinkJump::CategoryListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 0x21: {
        if (m_owner->m_revolve->isMoving()) {
            UIObjectListener::reciveEvent(event, handle);
            break;
        }
        if (m_owner->m_open) {
            break;
        }
        ui::UISelectObjList* categories = m_owner->m_categories;
        categories->clear();
        int index = -1;
        for (int i = 0; i < 2; i++) {
            if (m_owner->m_lists[i].m_list->getSize() == 0) {
                ui::UIObjectAcc(m_owner->m_lists[i].m_handle).setDisp(false);
            } else {
                if (index == -1) {
                    index = i;
                }
                categories->addContents(m_owner->m_lists[i].m_handle);
            }
        }
        categories->setIndex(0);
        GfMenuObject::setupInputSelectionFromList(acc.m_handle, *categories);
        m_owner->m_revolve->moveCenterOffset(mm::Pnt<short>(0, 720), true);
        m_owner->changeCategory(index);
        m_owner->m_open = true;
        acc.setDisp(true);
        acc.setDispChild(true, "LAY_main");
        {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 4;
            param.m_time = 0.5f;
            param.m_alpha = 0.5f;
            GfMenuObjUtil::startCtrl(acc.searchChild("IMG_bg"), param, nullptr);
        }
        ui::UIObjectAcc category(acc.m_handle);
        if (category.m_object != nullptr) {
            ui::UIObjectAcc main(acc.m_handle, "LAY_main");
            if (main.m_object != nullptr) {
                GfMenuObject::disableInput(category.m_handle);
                GfMenuObject::disableInput(main.m_handle);
            }
        }
        break;
    }
    case 1: {
        {
            ui::UISelectObjList::CreateParam create;
            create.m_allocator = getAllocator(ALLOCATOR(0));
            m_owner->m_categories = ui::UISelectObjList::create(create);
        }
        ui::UICtrlRevolveSelect::RevolveSetting setting;
        setting.m_angleRange = 360;
        setting.m_type = 2;
        setting.m_radius = 100;
        setting.m_center = mm::Pnt<short>(640, -360);
        setting.m_rollTime = 0.25f;
        setting.m_moveTime = 0.5f;
        setting.m_moveCurve = ui::CURVE_SIN90;
        setting.m_scaleRate = 0.0f;
        m_owner->m_revolve = ui::UICtrlRevolveSelect::create(acc.searchChild("LAY_main"), setting, m_owner->m_categories);
        m_owner->m_revolve->setupEventHanding(acc.m_handle, 1);
        acc.setDisp(false);
        break;
    }
    case 6: {
        int index = event.m_param0;
        m_owner->changeCategory(index);
        break;
    }
    case 8:
        if (m_owner->m_revolve->isMoving()) {
            UIObjectListener::reciveEvent(event, handle);
            break;
        }
        if (event.m_param1 == 2 && m_owner->m_open) {
            m_owner->m_revolve->moveCenterOffset(mm::Pnt<short>(0, 0), true);
            m_owner->m_open = false;
            {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 2;
                param.m_time = 0.5f;
                GfMenuObjUtil::startCtrl(acc.searchChild("IMG_bg"), param, nullptr);
            }
            ui::UIObjectAcc category(acc.m_handle);
            if (category.m_object != nullptr) {
                ui::UIObjectAcc main(acc.m_handle, "LAY_main");
                if (main.m_object != nullptr) {
                    GfMenuObject::disableInput(category.m_handle);
                    GfMenuObject::disableInput(main.m_handle);
                }
            }
        }
        break;
    case 0xE:
        if (ui::UICtrlObject::getEventCtrlObjID(event) == 1) {
            m_owner->listenerCategorySelect(event);
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjLinkJump::changeCategory(int index) {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (acc.m_object != nullptr) {
        m_categories->setIndex(index);
        unsigned int selected = m_categories->getSelectObject();
        if (m_lists[0].m_list != nullptr && m_lists[0].m_handle == selected) {
            m_lists[0].m_list->setIndex(0);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_lists[0].m_list);
        }
        if (m_lists[1].m_list != nullptr && m_lists[1].m_handle == selected) {
            m_lists[1].m_list->setIndex(0);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_lists[1].m_list);
        }
        GfMenuObject::migrateInput(acc.m_handle, selected);
    }
}

void GfMenuObjLinkJump::listenerCategorySelect(const ui::EventData& event) {
    unsigned short type = ui::UICtrlObject::getEventType(event);
    if (type == 2) {
        if (m_open) {
            ui::UIObjectAcc notify(m_handle, "LAY_notify");
            ui::EventData close;
            close.m_type = 0x22;
            GfMenuObject::sendEvent(notify.m_handle, close, 0.0f);
        }
    } else if (type == 3) {
        if (!m_open) {
            ui::UIObjectAcc notify(m_handle, "LAY_notify");
            ui::EventData open;
            open.m_type = 0x21;
            GfMenuObject::sendEvent(notify.m_handle, open, 0.0f);
            ui::UIObjectAcc(m_handle).setDispChild(false, "LAY_main");
            ui::UIObjectAcc(m_handle).setDispChild(false, "IMG_bg");
        } else {
            ui::UIObjectAcc category(m_handle, "LAY_category_list");
            if (category.m_object != nullptr) {
                ui::UIObjectAcc main(m_handle, "LAY_main");
                if (main.m_object != nullptr) {
                    GfMenuObject::enableInput(category.m_handle);
                    GfMenuObject::enableInput(main.m_handle);
                }
            }
        }
    }
}

void GfMenuObjLinkJump::NotifyListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        ui::UIObjectAcc button(acc.m_handle, "IMG_notify_btn");
        if (button.m_object != nullptr) {
            short icon = GfMenuObjUtil::getBtnIconNumber(8);
            if (icon != -1) {
                button.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
            }
        }
        acc.setDisp(false);
        m_ctrl = -1;
        break;
    }
    case 0x21: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 2;
        param.m_out = 0;
        param.m_startFlag4 = true;
        param.m_slot = m_ctrl;
        m_ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    case 0x22: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_out = 1;
        param.m_preset = 2;
        param.m_startFlag4 = true;
        param.m_slot = m_ctrl;
        m_ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjLinkJump::ListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
    case 0x21:
        break;
    case 6: {
        unsigned int index = event.m_param0;
        m_list->m_list->setIndex(index);
        m_list->m_selectList->setIndex(m_list->m_list->getIndex(true));
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf
