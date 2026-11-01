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
    m_references[0] = nullptr;
    m_references[1] = nullptr;
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
        m_owner->m_references[0]->getQuest(id);
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
