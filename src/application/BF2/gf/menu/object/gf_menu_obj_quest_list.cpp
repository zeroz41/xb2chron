#include "classes/gf/GfMenuObjQuestList.h"
#include "classes/gf/GfMenuObjQuestList/MainListener.h"
#include "classes/gf/GfMenuObjQuestList/ListListener.h"
#include "classes/gf/GfMenuObjQuestList/ThumbListener.h"
#include "classes/gf/GfMenuObjQuestList/TabListener.h"
#include "classes/gf/GfMenuObjQuestList/TabOpenListener.h"
#include "classes/gf/GfMenuObjQuestList/TabSelectListener.h"
#include "classes/gf/GfMenuObjQuestList/DetailListener.h"
#include "classes/gf/GfMenuObjQuestList/TaskListener.h"
#include "classes/gf/GfMenuObjQuestList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIEventManager.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuQuestList.h"
#include "classes/gf/GfQuestManager.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuFlag.h"
#include "gf/GfMenuTypes.h"
#include "gf/QuestListAcc.h"
#include "ui/EventData.h"
#include "gf/QuestTaskParam.h"
#include "gf/GfQuestUtil.h"
#include "gf/GfItemUtil.h"
#include "mm/mtl/FixStr.h"

#include "classes/gf/GfMenuReferenceQuest.h"
#include "classes/gf/GfMenuObjQuestReward.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuQuestAdapter.h"
#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
namespace gf {

GfMenuObjQuestList::GfMenuObjQuestList(unsigned int handle)
    : GfMenuObject(handle), m_questLists(), m_cursors(), m_view(0), m_menuFlag2(0), m_menuFlag3(0),
      m_selectLists(), m_context(nullptr), m_seq(this), m_quest(0), m_closeHandle(0), m_itemList(nullptr), m_closeWithFade(true) {
    m_context = GfMenuCallContext::create();
    m_subContext = GfMenuCallContext::create();
}

GfMenuObjQuestList::~GfMenuObjQuestList() {
    m_numbers[0] = nullptr;
    m_numbers[1] = nullptr;
    m_detailQuest = nullptr;
    m_detailNumber = nullptr;
    if (m_questLists[0] != nullptr) {
        m_questLists[0]->release();
        m_questLists[0] = nullptr;
    }
    if (m_questLists[1] != nullptr) {
        m_questLists[1]->release();
        m_questLists[1] = nullptr;
    }
    if (m_selectLists[0] != nullptr) {
        m_selectLists[0]->release();
        m_selectLists[0] = nullptr;
    }
    if (m_selectLists[1] != nullptr) {
        m_selectLists[1]->release();
        m_selectLists[1] = nullptr;
    }
    if (m_selectLists[2] != nullptr) {
        m_selectLists[2]->release();
        m_selectLists[2] = nullptr;
    }
    if (m_selectLists[3] != nullptr) {
        m_selectLists[3]->release();
        m_selectLists[3] = nullptr;
    }
    if (m_selectLists[4] != nullptr) {
        m_selectLists[4]->release();
        m_selectLists[4] = nullptr;
    }
    if (m_cursors[0] != nullptr) {
        m_cursors[0]->release();
        m_cursors[0] = nullptr;
    }
    if (m_cursors[1] != nullptr) {
        m_cursors[1]->release();
        m_cursors[1] = nullptr;
    }
    if (m_cursors[2] != nullptr) {
        m_cursors[2]->release();
        m_cursors[2] = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_subContext != nullptr) {
        m_subContext->release();
        m_subContext = nullptr;
    }
    if (m_itemList != nullptr) {
        m_itemList->release();
        m_itemList = nullptr;
    }
}

void GfMenuObjQuestList::registOpenParam(const OpenParam& param) {
    GfMenuTypes::Param layer;
    layer.m_menuId = param.m_questId;
    GfMenuFullScreen::registLayerParam(0x2F, layer);
}

void GfMenuObjQuestList::initialize() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    if (main.m_object != nullptr) {
        m_questLists[0] = GfMenuQuestList::create();
        m_questLists[1] = GfMenuQuestList::create();
        m_openQuest = 0;
        m_hasOpenQuest = false;
        GfMenuTypes::Param layer;
        if (GfMenuObject::getFSLayerParam(m_fsLayer, layer)) {
            m_openQuest = layer.m_menuId;
            QuestID parent = GfQuestInfo::getParentQuest(QuestID(m_openQuest));
            if (!parent.empty()) {
                m_openQuest = parent.m_id;
            }
            m_hasOpenQuest = true;
            GfMenuObject::removeFSLayerParam(m_fsLayer);
        }
        m_view = GfMenuFlag::get4(1);
        m_menuFlag2 = GfMenuFlag::get4(2);
        m_menuFlag3 = GfMenuFlag::get4(3);
#line 169
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        // the original stores the count after the listener's own fields, not with its base (as other menus' do)
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(main.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::disableInput(main.searchChild("LAY_list"));
        GfMenuObject::disableInput(main.searchChild("LAY_thumb"));
        GfMenuObject::disableInput(main.searchChild("LAY_tab"));
        GfMenuObject::disableInput(main.searchChild("LAY_tab_select"));
        GfMenuObject::disableInput(main.searchChild("LAY_tab_open"));
        GfMenuObject::disableInput(main.searchChild("LAY_detail"));
        GfMenuObject::disableInput(main.searchChild("LAY_detail_task"));
        GfMenuObject::initialize();
    }
}

void GfMenuObjQuestList::initializeSub(ui::UIObjectAcc& main) {
    mm::mtl::FixStr<32> name;
    GfMenuAdapterManager::beginAddAfter();
    {
        ui::UIObjectAcc list(main.m_handle, "LAY_list");
        {
            mm::mtl::IAllocator* allocator = getAllocator(ALLOCATOR(0));
            ui::UISelectObjList::CreateParam create;
            create.m_allocator = allocator;
            m_selectLists[0] = ui::UISelectObjList::create(create);
        }
        m_selectLists[0]->pickupObject(list.m_handle, "LAY_list_item@%02d", 1);
        for (unsigned int i = 0; i < (unsigned int)m_selectLists[0]->getSize(); i++) {
            name.format("TXT_list_item_title@%02d", i + 1);
            GfMenuQuestAdapter* title =
                GfMenuQuestAdapter::createFromList(list.searchChild(name.m_str), m_questLists[0], i, 0, false);
            if (title != nullptr) {
                title->m_rowHandle = m_selectLists[0]->getObject(i);
            }
            name.format("IMG_list_item_clear@%02d", i + 1);
            GfMenuQuestAdapter::createFromList(list.searchChild(name.m_str), m_questLists[0], i, 0x37, false);
            name.format("IMG_list_item_active@%02d", i + 1);
            GfMenuQuestAdapter::createFromList(list.searchChild(name.m_str), m_questLists[0], i, 0x38, true);
            name.format("LAY_list_base@%02d", i + 1);
            GfMenuObjUtil::createFollowDispPlugin(list.searchChild(name.m_str), m_selectLists[0]->getObject(i));
        }
        {
            ui::UICtrlCursorSelect::CursorSetting setting;
            setting.setType(0);
            setting.m_dockType = 0;
            m_cursors[0] = ui::UICtrlCursorSelect::create(list.searchChild("IMG_list_cursor"), setting, m_selectLists[0]);
        }
        GfMenuObjUtil::createVScrollBarPlugin(list.searchChild("IMG_list_scroll_bar"), m_questLists[0],
                                              "IMG_list_scroll_base", true);
#line 247
        ListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(list.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        if (m_view == 1) {
            sendMenuEvent(list.m_handle, 0x104);
            GfMenuObject::sendOpenEvent(list.m_handle, 0, 0.0f);
            if (!m_hasOpenQuest) {
                sendMenuEvent(list.m_handle, 0x102);
            }
        }
    }
    {
        ui::UIObjectAcc thumb(main.m_handle, "LAY_thumb");
        {
            mm::mtl::IAllocator* allocator = getAllocator(ALLOCATOR(0));
            ui::UISelectObjList::CreateParam create;
            create.m_allocator = allocator;
            m_selectLists[1] = ui::UISelectObjList::create(create);
        }
        m_selectLists[1]->pickupObject(thumb.m_handle, "LAY_thumb@%02d", 1);
        for (unsigned int i = 0; i < (unsigned int)m_selectLists[1]->getSize(); i++) {
            name.format("TXT_thumb_title@%02d", i + 1);
            GfMenuQuestAdapter* title =
                GfMenuQuestAdapter::createFromList(thumb.searchChild(name.m_str), m_questLists[1], i, 0, false);
            if (title != nullptr) {
                title->m_rowHandle = m_selectLists[1]->getObject(i);
            }
            name.format("IMG_thumb@%02d", i + 1);
            GfMenuQuestAdapter::createFromList(thumb.searchChild(name.m_str), m_questLists[1], i, 0x39, false);
            name.format("IMG_thumb_clear@%02d", i + 1);
            GfMenuQuestAdapter::createFromList(thumb.searchChild(name.m_str), m_questLists[1], i, 0x37, false);
            name.format("IMG_thumb_active@%02d", i + 1);
            GfMenuQuestAdapter::createFromList(thumb.searchChild(name.m_str), m_questLists[1], i, 0x38, true);
            name.format("LAY_thumb_base@%02d", i + 1);
            GfMenuObjUtil::createFollowDispPlugin(thumb.searchChild(name.m_str), m_selectLists[1]->getObject(i));
            name.format("LAY_thumb_ac@%02d", i + 1);
            GfMenuObjUtil::createFollowDispPlugin(thumb.searchChild(name.m_str), m_selectLists[1]->getObject(i));
        }
        {
            GfMenuQuestList::SetupParam param;
            param.m_pageRowSize = m_selectLists[0]->getSize();
            param.m_categoryMask = 0;
            param.m_stateMask = 0;
            m_questLists[1]->setup(param);
        }
        {
            ui::UICtrlCursorSelect::CursorSetting setting;
            setting.setType(0);
            setting.m_dockType = 0;
            m_cursors[1] = ui::UICtrlCursorSelect::create(thumb.searchChild("IMG_thumb_cursor"), setting, m_selectLists[1]);
        }
        m_numbers[0] = GfMenuReferenceNumber::create();
        m_numbers[1] = GfMenuReferenceNumber::create();
        GfMenuReferenceAdapter* page =
            GfMenuReferenceAdapter::create(thumb.searchChild("TXT_thumb_page_num"), m_numbers[0], true);
        if (page != nullptr) {
            page->m_offset = 1;
        }
        GfMenuReferenceAdapter::create(thumb.searchChild("TXT_thumb_page_max"), m_numbers[1], true);
#line 340
        ThumbListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ThumbListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(thumb.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        if (m_view == 0) {
            sendMenuEvent(thumb.m_handle, 0x104);
            GfMenuObject::sendOpenEvent(thumb.m_handle, 0, 0.0f);
            if (!m_hasOpenQuest) {
                sendMenuEvent(thumb.m_handle, 0x102);
            }
        }
    }
    GfMenuAdapterManager::endAddAfter();
    {
        ui::UIObjectAcc tab(main.m_handle, "LAY_tab");
        {
            mm::mtl::IAllocator* allocator = getAllocator(ALLOCATOR(0));
            ui::UISelectObjList::CreateParam create;
            create.m_allocator = allocator;
            m_selectLists[2] = ui::UISelectObjList::create(create);
        }
        m_selectLists[2]->pickupObject(tab.m_handle, "TXT_tab_title@%02d", 1);
        {
            mm::mtl::IAllocator* allocator = getAllocator(ALLOCATOR(0));
            ui::UISelectObjList::CreateParam create;
            create.m_allocator = allocator;
            m_selectLists[3] = ui::UISelectObjList::create(create);
        }
        m_selectLists[3]->pickupObject(tab.m_handle, "LAY_tab_select_item@%02d", 1);
        {
            ui::UICtrlCursorSelect::CursorSetting setting;
            setting.setType(0);
            setting.m_dockType = 0;
            m_cursors[2] =
                ui::UICtrlCursorSelect::create(tab.searchChild("IMG_tab_select_cursor"), setting, m_selectLists[3]);
        }
        {
#line 381
            TabListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TabListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(tab.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        {
#line 382
            TabSelectListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TabSelectListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(tab.searchChild("LAY_tab_select"), listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        tab.setDisp(false);
        tab.setDispChild(false, "LAY_tab_select");
    }
    {
        ui::UIObjectAcc open(main.m_handle, "LAY_tab_open");
        GfMenuObjUtil::setDockPos(open.searchChild("IMG_tab_open_btn"), open.searchChild("TXT_tab_open"), 1, true);
        GfMenuObjUtil::addPos(open.searchChild("IMG_tab_open_btn"), -4, 0);
#line 401
        TabOpenListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TabOpenListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(open.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        open.setDisp(false);
    }
    {
        ui::UIObjectAcc detail(main.m_handle, "LAY_detail");
        mm::mtl::FixStr<32> detailName;
        m_detailQuest = GfMenuReferenceQuest::create();
        m_detailNumber = GfMenuReferenceNumber::create();
        m_itemList = GfMenuItemList::create();
        m_itemList->setup(getAllocator(ALLOCATOR(0)), ui::UIListInfoBase::SetupParam());
        GfMenuQuestAdapter::createFromReference(detail.searchChild("TXT_detail_win_title"), m_detailQuest, 0, false);
        GfMenuQuestAdapter::createFromReference(detail.searchChild("IMG_detail_thumb"), m_detailQuest, 0x39, false);
        GfMenuQuestAdapter::createFromReference(detail.searchChild("TXT_detail_win_info"), m_detailQuest, 1, false);
        GfMenuQuestAdapter::createFromReference(detail.searchChild("TXT_detail_win_result"), m_detailQuest, 2, false);
        GfMenuQuestAdapter::createFromReference(detail.searchChild("TXT_detail_task_list_step"), m_detailQuest, 0x3A,
                                                false);
        for (int i = 0; i < 12; i++) {
            detailName.format("IMG_detail_task_cond_pt_face@%02d", i + 1);
            GfMenuQuestAdapter* face =
                GfMenuQuestAdapter::createFromReference(detail.searchChild(detailName.m_str), m_detailQuest, i + 3, false);
            if (face != nullptr) {
                face->m_task = 0;
            }
        }
        for (int i = 0; i < 4; i++) {
            detailName.format("TXT_detail_task_info@%02d", i + 1);
            GfMenuQuestAdapter* info =
                GfMenuQuestAdapter::createFromReference(detail.searchChild(detailName.m_str), m_detailQuest, 0x2E, false);
            if (info != nullptr) {
                info->m_task = i;
            }
            detailName.format("TXT_detail_task_item_name@%02d", i + 1);
            GfMenuItemAdapter::createFromList(detail.searchChild(detailName.m_str), 0, m_itemList, i, false);
            detailName.format("TXT_detail_task_item_num@%02d", i + 1);
            GfMenuQuestAdapter* itemNum =
                GfMenuQuestAdapter::createFromReference(detail.searchChild(detailName.m_str), m_detailQuest, 0x2F, false);
            if (itemNum != nullptr) {
                itemNum->m_task = i;
            }
            detailName.format("TXT_detail_task_item_max@%02d", i + 1);
            GfMenuQuestAdapter* itemMax =
                GfMenuQuestAdapter::createFromReference(detail.searchChild(detailName.m_str), m_detailQuest, 0x30, false);
            if (itemMax != nullptr) {
                itemMax->m_task = i;
            }
            detailName.format("IMG_detail_task_cond_tzone@%02d", i + 1);
            GfMenuQuestAdapter* tzone =
                GfMenuQuestAdapter::createFromReference(detail.searchChild(detailName.m_str), m_detailQuest, 0x32, false);
            if (tzone != nullptr) {
                tzone->m_task = i;
            }
            detailName.format("IMG_detail_task_cond_tzone2@%02d", i + 1);
            GfMenuQuestAdapter* tzone2 =
                GfMenuQuestAdapter::createFromReference(detail.searchChild(detailName.m_str), m_detailQuest, 0x33, false);
            if (tzone2 != nullptr) {
                tzone2->m_task = i;
            }
            detailName.format("IMG_detail_task_cond_tzone3@%02d", i + 1);
            GfMenuQuestAdapter* tzone3 =
                GfMenuQuestAdapter::createFromReference(detail.searchChild(detailName.m_str), m_detailQuest, 0x34, false);
            if (tzone3 != nullptr) {
                tzone3->m_task = i;
            }
            detailName.format("IMG_detail_task_cond_weather@%02d", i + 1);
            GfMenuQuestAdapter* weather =
                GfMenuQuestAdapter::createFromReference(detail.searchChild(detailName.m_str), m_detailQuest, 0x31, false);
            if (weather != nullptr) {
                weather->m_task = i;
            }
        }
        {
            GfMenuObjQuestReward::OpenParam param;
            param.m_quest = m_detailQuest;
            param.m_handle = detail.searchChild("LAY_detail_reward");
            GfMenuObjQuestReward::create(m_subContext, param, true);
        }
        {
#line 497
            DetailListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) DetailListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(detail.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        GfMenuObject::disableInput(detail.m_handle);
        {
#line 500
            TaskListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TaskListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(detail.searchChild("LAY_detail_task"), listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        if (m_hasOpenQuest) {
            GfMenuObject::sendCloseEvent(main.searchSibiling("LAY_tab_open"), 0, 0.0f);
            GfMenuObject::sendOpenEvent(detail.m_handle, 0, 0.0f);
            m_quest = m_openQuest;
        } else {
            GfMenuObject::sendOpenEvent(main.searchSibiling("LAY_tab_open"), 0, 0.0f);
        }
    }
    setupList(m_openQuest);
}

void GfMenuObjQuestList::finalize() {
    GfMenuFlag::set4(1, m_view);
    GfMenuFlag::set4(2, m_menuFlag2);
    GfMenuFlag::set4(3, m_menuFlag3);
    GfMenuObject::finalize();
}

void GfMenuObjQuestList::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjQuestList::setupList(unsigned int quest) {
    GfMenuQuestList::SetupParam param;
    param.m_categoryMask = 7;
    param.m_stateMask = 3;
    param.m_pageRowSize = m_selectLists[0]->getSize();
    param.m_pageScroll = true;
    switch (m_menuFlag2) {
    case 0:
        param.m_categoryMask = 7;
        break;
    case 1:
        param.m_categoryMask = 4;
        break;
    case 2:
        param.m_categoryMask = 1;
        break;
    case 3:
        param.m_categoryMask = 2;
        break;
    }
    if (m_menuFlag3 == 0) {
        param.m_stateMask = 1;
    } else if (m_menuFlag3 == 1) {
        param.m_stateMask = 2;
    }
    m_questLists[0]->clear();
    m_questLists[1]->clear();
    m_questLists[0]->setup(param);
    if (m_questLists[0]->getSize() != 0) {
        for (unsigned int i = 0; i < (unsigned int)m_selectLists[1]->getSize(); i++) {
            if (i < (unsigned int)m_questLists[0]->getSize()) {
                m_questLists[1]->addContents(m_questLists[0]->getContents(i));
            }
        }
    }
    unsigned int pages = (unsigned int)m_questLists[0]->getSize() / (unsigned int)m_selectLists[1]->getSize();
    if ((unsigned int)m_questLists[0]->getSize() % (unsigned int)m_selectLists[1]->getSize() != 0) {
        pages++;
    }
    m_numbers[0]->m_value = 0;
    m_numbers[1]->m_value = pages;
    {
        ui::UIObjectAcc page(m_handle, "LAY_thumb_page");
        page.setDisp(m_numbers[1]->m_value > 0);
    }
    m_questLists[0]->setIndex(0);
    m_questLists[1]->setIndex(0);
    if (quest != 0) {
        QuestID id(quest);
        if (!id.empty()) {
            id = GfQuestInfo::getParentQuest(id);
            for (unsigned int i = 0; i < (unsigned int)m_questLists[0]->getSize(); i++) {
                if (m_questLists[0]->getContents(i) == id) {
                    m_questLists[0]->setIndex(i);
                }
            }
        }
    }
}

void GfMenuObjQuestList::changeView(unsigned int view) {
    if (m_view == view) {
        return;
    }
    ui::UIObjectAcc main(m_handle, "LAY_main");
    switch (view) {
    case 1:
        GfMenuObject::sendOpenEvent(main.searchChild("LAY_list"), 0, 0.0f);
        GfMenuObject::sendCloseEvent(main.searchChild("LAY_thumb"), 0, 0.0f);
        break;
    case 0:
        GfMenuObject::sendOpenEvent(main.searchChild("LAY_thumb"), 0, 0.0f);
        GfMenuObject::sendCloseEvent(main.searchChild("LAY_list"), 0, 0.0f);
        break;
    default:
        return;
    }
    m_view = view;
}

bool GfMenuObjQuestList::changeThumbPage(int page) {
    int count = m_numbers[1]->m_value;
    if (count < 2) {
        return false;
    }
    int next = page;
    if (page < 0) {
        next = count - 1;
    }
    if (page >= count) {
        next = 0;
    }
    m_questLists[1]->clear();
    for (unsigned int i = 0; i < (unsigned int)m_selectLists[1]->getSize(); i++) {
        unsigned int index = i + m_selectLists[1]->getSize() * next;
        if (index < (unsigned int)m_questLists[0]->getSize()) {
            m_questLists[1]->addContents(m_questLists[0]->getContents(index));
        }
    }
    {
        ui::UIObjectAcc thumb(m_handle, "LAY_thumb");
        m_questLists[1]->setIndex(0);
        GfMenuObject::resetInputSelection(thumb.m_handle);
        GfMenuObject::setupInputSelectionFromList(thumb.m_handle, *m_questLists[1]);
        GfMenuObject::setupPadLineSelection(thumb.m_handle, 3);
    }
    m_numbers[0]->m_value = next;
    return true;
}

void GfMenuObjQuestList::ListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        acc.setDisp(false);
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            m_owner->m_questLists[0]->setIndex(index);
            m_owner->m_selectLists[0]->setIndex(m_owner->m_questLists[0]->getIndex(true));
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 8:
        if (event.m_param1 == 1 && m_owner->m_questLists[0]->getSize() != 0) {
            GfMenuQuestList* list = m_owner->m_questLists[0];
            if (list->getContents(list->getIndex(false)).m_id != 0) {
                m_owner->sendMenuEvent(acc.m_handle, 0x101);
                list = m_owner->m_questLists[0];
                m_owner->m_quest = list->getContents(list->getIndex(false)).m_id;
                GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_detail"), 0, 0.0f);
                GfMenuObjMainMenu2::setSystemKeyEnable(false);
                GfMenuObjUtil::playSECommonDecide();
                GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_tab_open"), 0, 0.0f);
                GfMenuObject::disableInput(acc.m_handle);
                GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            }
        }
        break;
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        acc.setDisp(false);
        break;
    case 0x101:
        acc.setDispChild(false, "IMG_list_cursor");
        if (m_owner->m_view == 1) {
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        }
        break;
    case 0x102:
        if (m_owner->m_view == 1) {
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjMainMenu2::setSystemKeyEnable(true);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            int size = m_owner->m_questLists[0]->getSize();
            if (size != 0) {
                acc.setDispChild(true, "IMG_list_cursor");
            } else {
                acc.setDispChild(false, "IMG_list_cursor");
            }
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 1, size != 0);
            GfMenuObject::resetInputSelection(acc.m_handle);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_questLists[0]);
        }
        break;
    case 0x104:
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjQuestList::ThumbListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        acc.setDispChild(m_owner->m_questLists[0]->getSize() != 0 && m_owner->m_numbers[1]->m_value > 1,
                         "LAY_thumb_input");
        acc.setDisp(false);
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            m_owner->m_questLists[1]->setIndex(index);
            m_owner->m_selectLists[1]->setIndex(m_owner->m_questLists[1]->getIndex(true));
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 8:
        if (event.m_param1 == 1 && m_owner->m_questLists[0]->getSize() != 0) {
            GfMenuQuestList* list = m_owner->m_questLists[0];
            if (list->getContents(list->getIndex(false)).m_id != 0) {
                m_owner->sendMenuEvent(acc.m_handle, 0x101);
                list = m_owner->m_questLists[1];
                m_owner->m_quest = list->getContents(list->getIndex(false)).m_id;
                GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_detail"), 0, 0.0f);
                GfMenuObjMainMenu2::setSystemKeyEnable(false);
                GfMenuObjUtil::playSECommonDecide();
                GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_tab_open"), 0, 0.0f);
                GfMenuObject::disableInput(acc.m_handle);
                GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            }
        }
        break;
    case 9: {
        GfMenuObjQuestList* owner;
        int page;
        if (event.m_param0 == 3) {
            owner = m_owner;
            page = owner->m_numbers[0]->m_value + 1;
        } else if (event.m_param0 == 4) {
            owner = m_owner;
            page = owner->m_numbers[0]->m_value - 1;
        } else {
            break;
        }
        if (owner->changeThumbPage(page)) {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        acc.setDisp(false);
        break;
    case 0x101:
        acc.setDispChild(false, "IMG_thumb_cursor");
        if (m_owner->m_view == 0) {
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        }
        break;
    case 0x102:
        if (m_owner->m_view == 0) {
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjMainMenu2::setSystemKeyEnable(true);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            int size = m_owner->m_questLists[0]->getSize();
            if (size != 0) {
                acc.setDispChild(true, "IMG_thumb_cursor");
            } else {
                acc.setDispChild(false, "IMG_thumb_cursor");
            }
            acc.setDispChild(size != 0 && m_owner->m_numbers[1]->m_value > 1, "LAY_thumb_input");
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 1, size != 0);
            GfMenuObject::resetInputSelection(acc.m_handle);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_questLists[1]);
            GfMenuObject::setupPadLineSelection(acc.m_handle, 3);
        }
        break;
    case 0x104:
        m_owner->changeThumbPage(0);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjQuestList::TabListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            int prev = event.m_param1;
            if (prev != -1) {
                ui::UIObjectAcc obj(m_owner->m_selectLists[2]->getObject(prev));
                obj.loadDefColor();
                obj.setBorderWeight(-0.5f);
            }
            m_owner->m_selectLists[2]->setIndex(index);
            {
                ui::UIObjectAcc select(m_owner->m_selectLists[2]->getSelectObject());
                GfMenuObjUtil::setColMulandAdd(select.m_handle, "txt_normal");
                select.setBorderWeight(1.0f);
            }
            if (prev != -1 && index != prev) {
                GfMenuObjUtil::playSECommonTab();
            }
        }
        break;
    }
    case 8:
        if (event.m_param1 == 2) {
            acc.setDisp(false);
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_tab_open"), 0, 0.0f);
            GfMenuObjUtil::playSECommonCancel();
        } else if (event.m_param1 == 1) {
            GfMenuObject::sendOpenEvent(acc.searchChild("LAY_tab_select"), m_owner->m_selectLists[2]->getIndex(false),
                                        0.0f);
            m_owner->sendMenuEvent(acc.m_handle, 0x101);
            m_owner->sendMenuEvent(acc.searchSibiling("LAY_thumb"), 0x101);
            m_owner->sendMenuEvent(acc.searchSibiling("LAY_list"), 0x101);
            GfMenuObjUtil::playSECommonDecide();
        }
        break;
    case 0x21:
        GfMenuObject::resetInputSelection(acc.m_handle);
        GfMenuObject::setupInputSelection(acc.m_handle, 0, m_owner->m_selectLists[2]->getSize());
        for (unsigned int i = 0; i < (unsigned int)m_owner->m_selectLists[2]->getSize(); i++) {
            ui::UIObjectAcc obj(m_owner->m_selectLists[2]->getObject(i));
            obj.loadDefColor();
            obj.setBorderWeight(-0.5f);
        }
        acc.setDisp(true);
        GfMenuObject::enableInput(acc.m_handle);
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        break;
    case 0x101:
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        break;
    case 0x102: {
        int mode = event.m_param0;
        bool toLists = mode == 2;  // also sends 0x104 to LAY_thumb and LAY_list (the name is not the original's)
        if (mode != 0) {
            acc.setDisp(false);
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_tab_open"), 0, 0.0f);
        } else {
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        }
        if (toLists) {
            m_owner->sendMenuEvent(acc.searchSibiling("LAY_thumb"), 0x104);
            m_owner->sendMenuEvent(acc.searchSibiling("LAY_list"), 0x104);
        }
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjQuestList::TabOpenListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 8:
        if (event.m_param1 == 9) {
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_tab"), 0, 0.0f);
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            m_owner->sendMenuEvent(acc.searchSibiling("LAY_thumb"), 0x101);
            m_owner->sendMenuEvent(acc.searchSibiling("LAY_list"), 0x101);
            GfMenuObjMainMenu2::setSystemKeyEnable(false);
            GfMenuObjUtil::playSECommonOpenSubMenu();
        }
        break;
    case 0x21:
        acc.setDisp(true);
        GfMenuObject::enableInput(acc.m_handle);
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        m_owner->sendMenuEvent(acc.searchSibiling("LAY_thumb"), 0x102);
        m_owner->sendMenuEvent(acc.searchSibiling("LAY_list"), 0x102);
        GfMenuObjMainMenu2::setSystemKeyEnable(true);
        break;
    case 0x22:
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjQuestList::DetailListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        acc.setDisp(false);
        m_questFinished = 0;
        break;
    case 3:
        if (event.m_param0 == 1) {
            unsigned int finished = m_questFinished;
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            QuestID id;
            m_owner->m_detailQuest->getQuest(id);
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 9, finished != 1);
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, finished != 1);
            if (finished != 1) {
                bool current = GfQuestManager::getCurrentQuest(QTYPE(0)).m_id == m_owner->m_quest;
                if (m_owner->m_openQuest == 0) {
                    GfMenuObjOperationInfo::changeText(acc.m_handle, 10, current);
                } else {
                    GfMenuObjOperationInfo::changeText(acc.m_handle, 10, current ? 2u : 0u);
                }
            }
        } else if (event.m_param0 == 2) {
            acc.setDisp(false);
        }
        break;
    case 8:
        if (event.m_param1 == 2) {
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_tab_open"), 0, 0.0f);
            GfMenuObjUtil::playSECommonCancel();
        } else if (event.m_param1 == 9) {
            QuestID id;
            m_owner->m_detailQuest->getQuest(id);
            if (!GfQuestInfo::isQuestFin(id)) {
                m_owner->sendMenuEvent(acc.m_handle, 0x101);
                GfMenuObject::sendOpenEvent(acc.searchChild("LAY_detail_task"), 0, 0.0f);
                GfMenuObjUtil::playSECommonOpenSubMenu();
            }
        } else if (event.m_param1 == 10) {
            QuestID id;
            m_owner->m_detailQuest->getQuest(id);
            if (!GfQuestInfo::isQuestFin(id)) {
                m_owner->m_closeHandle = acc.m_handle;
                m_owner->m_quest = id.m_id;
                m_owner->m_seq.addJob(&GfMenuObjQuestList::seqActivateStart);
                GfMenuObject::disableInput(acc.m_handle);
            }
        }
        break;
    case 0x21: {
        QuestID id(m_owner->m_quest);
        m_owner->m_detailQuest->m_quest = id;
        bool finished = GfQuestInfo::isQuestFin(id);
        acc.setDispChild(!finished, "LAY_detail_summary");
        acc.setDispChild(finished, "LAY_detail_result");
        acc.setDispChild(finished, "TXT_detail_complete");
        if (!finished) {
            mm::mtl::FixStr<32> name;
            for (unsigned int i = 0; i < 4; i++) {
                GfQuestTaskLogResult result;
                name.format("LAY_detail_task_status@%02d", i + 1);
                bool shown = GfQuestUtil::getMsgQuestTaskLog(result, QuestTaskParam(id, i, TASK_STATE(0)));
                acc.setDispChild(shown, name.m_str);
                if (shown) {
                    name.format("IMG_detail_task_st@%02d", i + 1);
                    ui::UIObjectAcc image(acc.m_handle, name.m_str);
                    image.setImageIndex(!result.m_complete);
                }
            }
            mm::mtl::FixedVector<unsigned short, 32> characters;
            bool needs = GfQuestUtil::getNeedCharacterByQuestTask(characters, id, 0) && characters.size() != 0;
            acc.setDispChild(needs, "IMG_detail_cond_member");
        }
        acc.setDispChild(!finished, "LAY_detail_task_list");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_setDefault = true;
        param.m_eventId = 1;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        GfMenuObjQuestReward::open(m_owner->m_subContext, false);
        m_questFinished = finished;
        break;
    }
    case 0x22: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_l";
        param.m_setDefault = true;
        param.m_startFlags = 10;
        param.m_eventId = 2;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        GfMenuObjUtil::playSECommonCancel();
        break;
    }
    case 0x101: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_l";
        param.m_eventId = 2;
        param.m_startFlags = 10;
        GfMenuObjUtil::startCtrl(acc.searchChild("LAY_detail_main"), param, nullptr);
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        break;
    }
    case 0x102: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_eventId = 1;
        int ctrl = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_detail_main"), param, nullptr);
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        break;
    }
    case 0x103: {
        bool current = GfQuestManager::getCurrentQuest(QTYPE(0)).m_id == m_owner->m_quest;
        if (m_owner->m_openQuest == 0) {
            GfMenuObjOperationInfo::changeText(acc.m_handle, 10, current);
        } else {
            GfMenuObjOperationInfo::changeText(acc.m_handle, 10, current ? 2u : 0u);
        }
        GfMenuObject::enableInput(acc.m_handle);
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjQuestList::seqActivateStart() {
    if (m_quest != 0) {
        m_context->reset();
        if (GfQuestManager::getCurrentQuest(QTYPE(0)).m_id == m_quest) {
            unsigned int text = 0x39;
            if (m_openQuest != 0) {
                text = 0xE2;
            }
            GfMenuObjCommonText::open(m_context, text, 0);
        } else {
            GfMenuObjCommonText::open(m_context, 1, 0);
        }
        m_seq.addJob(&GfMenuObjQuestList::seqActivateSelect);
        m_seq.addJob(&GfMenuObjQuestList::seqEnd);
    }
    return true;
}

void GfMenuObjQuestList::TaskListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        acc.setDisp(false);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        }
        break;
    case 8:
        if (event.m_param1 == 2) {
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            m_owner->sendMenuEvent(acc.getParentHandle(), 0x102);
            GfMenuObjUtil::playSECommonCloseSubMenu();
        }
        break;
    case 0x21: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_eventId = 1;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        QuestID id;
        QuestID progress;
        m_owner->m_detailQuest->getQuest(id);
        progress = GfQuestInfo::getProgressQuest(id);
        if (!progress.empty()) {
            id = progress;
        }
        bool needs;
        {
            mm::mtl::FixedVector<unsigned short, 32> characters;
            GfQuestUtil::getNeedCharacterByQuestTask(characters, id, 0);
            needs = characters.size() != 0;
        }
        acc.setDispChild(needs, "LAY_detail_task_cond_pt");
        unsigned int count = acc.countChild("LAY_detail_task@%02d", 1);
        mm::mtl::FixStr<32> name;
        unsigned int taskCount;
        unsigned int complete;
        GfQuestInfo::getQuestTaskInfo(taskCount, complete, id);
        m_owner->m_itemList->clear();
        for (unsigned int i = 0; i < count; i++) {
            bool show = false;
            MenuItemInfo item;
            if (i < taskCount) {
                QuestTaskParam task(id, i, TASK_STATE(0));
                GfQuestTaskLogResult result;
                if (GfQuestInfo::getTaskHide(task) != 1 && GfQuestUtil::getMsgQuestTaskLog(result, task)) {
                    item.m_id = result.m_count2;
                    item.m_count = 1;
                    item.m_type = GfItemUtil::getType(item.m_id);
                    show = result.m_count != 0;
                }
            }
            m_owner->m_itemList->addItem(item, false);
            name.format("LAY_detail_task_item@%02d", i + 1);
            acc.setDispChild(show, name.m_str);
        }
        break;
    }
    case 0x22: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_l";
        param.m_startFlags = 10;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjQuestList::seqActivateSelect() {
    if (m_context != nullptr) {
        if (m_context->isActive()) {
            return false;
        }
        GfMenuCallContext::GfMenuResult result;
        if (m_context->popResult(result) && result.m_value == 0 && result.m_id == 0) {
            if (GfQuestManager::getCurrentQuest(QTYPE(0)).m_id == m_quest) {
                GfQuestManager::setCurrentQuestForScenario();
            } else {
                GfQuestManager::setCurrentQuest(QuestID(m_quest));
            }
        }
    }
    return true;
}

bool GfMenuObjQuestList::seqEnd() {
    unsigned int handle = m_closeHandle != 0 ? m_closeHandle : ui::UIObjectAcc(m_handle, "LAY_main").m_handle;
    ui::EventData event;
    event.m_type = 0x103;
    GfMenuObject::sendEvent(handle, event, 0.0f);
    m_closeHandle = 0;
    return true;
}

void GfMenuObjQuestList::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        m_owner->initializeSub(acc);
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        GfMenuObjOperationInfo::setGuideText(4, 0);
        break;
    }
    case 2:
    case 0x22:
        if (!m_owner->m_closeWithFade) {
            ui::EventData close(3);
            close.m_param1 = 0;
            close.m_param0 = 2;
            ui::UIManager::get()->requestObjectEvent(handle, close, 0.0f);
        } else {
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 6;
            param.m_out = 1;
            param.m_eventId = 2;
            GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        }
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObjMainMenu2::setCloseKeyEnable(true);
        } else if (event.m_param0 == 2) {
            acc.setDisp(false);
            acc.setTerm();
        }
        break;
    case 0x24: {
        GfMenuObject::disableInput(acc.searchChild("LAY_list"));
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        m_owner->m_closeWithFade = false;
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf
