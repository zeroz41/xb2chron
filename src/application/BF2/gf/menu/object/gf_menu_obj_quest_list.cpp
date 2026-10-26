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
