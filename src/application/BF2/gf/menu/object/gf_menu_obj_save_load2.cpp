#include "classes/gf/GfMenuObjSaveLoad2.h"
#include "classes/gf/GfMenuObjSaveLoad2/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjFade.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuSoundManager.h"
#include "classes/gf/GfReqManager.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectNumberPlugin.h"
#include "classes/ui/UIObjectTextPlugin.h"
#include "classes/ui/UIObjectTimePlugin.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfDataBlade.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "gf/GfReqCommand.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjSaveLoad2::GfMenuObjSaveLoad2(unsigned int handle)
    : GfMenuObject(handle), m_context(nullptr), m_seq(this), m_saveReq(-1), m_mode(0), m_selectList(nullptr),
      m_yearPlugin(nullptr), m_timePlugin(nullptr), m_progressPlugin(nullptr), m_gameTimePlugin(nullptr),
      m_areaPlugin(nullptr), m_drivers(nullptr), m_blades(nullptr), m_numbers(), m_confirm(0) {
    for (int i = 0; i < 3; i++) {
        m_numbers[i] = nullptr;
    }
}

GfMenuObjSaveLoad2::~GfMenuObjSaveLoad2() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
    if (m_yearPlugin != nullptr) {
        m_yearPlugin->release();
        m_yearPlugin = nullptr;
    }
    if (m_timePlugin != nullptr) {
        m_timePlugin->release();
        m_timePlugin = nullptr;
    }
    if (m_progressPlugin != nullptr) {
        m_progressPlugin->release();
        m_progressPlugin = nullptr;
    }
    if (m_gameTimePlugin != nullptr) {
        m_gameTimePlugin->release();
        m_gameTimePlugin = nullptr;
    }
    if (m_areaPlugin != nullptr) {
        m_areaPlugin->release();
        m_areaPlugin = nullptr;
    }
    if (m_drivers != nullptr) {
        m_drivers->release();
        m_drivers = nullptr;
    }
    if (m_blades != nullptr) {
        m_blades->release();
        m_blades = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        m_numbers[i] = nullptr;
    }
}

void GfMenuObjSaveLoad2::registOpenParam(const OpenParam& param) {
    GfMenuTypes::Param layer;
    layer.m_halves.m_type = param.m_mode;
    GfMenuFullScreen::registLayerParam(GfMenuObject::getMenuLayerID(0x35), layer);
}

void GfMenuObjSaveLoad2::initialize() {
    {
        GfMenuTypes::Param layer;
        if (GfMenuObject::getFSLayerParam(m_fsLayer, layer)) {
            m_mode = layer.m_halves.m_type;
            GfMenuObject::removeFSLayerParam(m_fsLayer);
        }
    }
    ui::UIObjectAcc acc(m_handle);
    unsigned int main = acc.searchChild("LAY_main");
#line 168
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::attachExternalCall(0x75, main);
    m_context = GfMenuCallContext::create();
    {
        ui::UISelectObjList::CreateParam param;
        param.m_allocator = getAllocator(ALLOCATOR(0));
        m_selectList = ui::UISelectObjList::create(param);
    }
    m_drivers = GfMenuDriverList::create();
    GfMenuDriverList::PartySetup party;
    party.m_skipUnused = false;
    party.m_convertDriver = false;
    party.m_selectFlag = false;
    party.m_type = 0;
    m_drivers->setupFromParty(party);
    m_blades = GfMenuBladeList::create();
    {
        GfMenuBladeList::TeamSetup team;
        team.m_type = 1;
        team.m_team = 0;
        team.m_keepEmpty = true;
        m_blades->setupFromTeam(team);
    }
    for (int i = 0; i < 3; i++) {
        m_numbers[i] = GfMenuReferenceNumber::create();
        m_numbers[i]->m_value = 1;
    }
    acc.setDispChild(GfMenuManager::isClearCheck(), "IMG_clear_mark");
    GfMenuObject::initialize();
}

void GfMenuObjSaveLoad2::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjSaveLoad2::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjSaveLoad2::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        m_owner->setupSave(acc, m_owner->m_numbers);
        m_owner->refreshSave(acc, 0);
        if (m_owner->m_mode != 0) {
            GfMenuObjOperationInfo::open(handle, 0, 0, 0);
            GfMenuObjOperationInfo::setGuideText(0x23, 2);
            GfMenuSoundManager::fadeOutFieldBgm(0.5f);
        } else {
            GfMenuObjOperationInfo::add(handle, 0, 0, 0);
            GfMenuObjMainMenu2::setSubIndexText(0x15);
            GfMenuObjOperationInfo::setGuideText(0x23, 0);
        }
        GfMenuObjSaveLoad2::setFadeIn(handle, 2);
        break;
    case 3:
        if (event.m_param0 == 2) {
            GfMenuObject::returnFSSubLayer(m_owner);
        }
        break;
    case 8: {
        unsigned int input = event.m_param1;
        GfMenuObjUtil::playSECommonFromInput(input);
        switch (static_cast<unsigned short>(input)) {
        case 1:
            GfMenuObjCommonText::open(m_owner->m_context, 0x9D, 0);
            m_owner->m_confirm = 0;
            GfMenuObject::setCallContextEventHandler(m_owner->m_context, handle);
            GfMenuObject::disableInput(handle);
            break;
        case 2:
            if (m_owner->m_mode == 0) {
                GfMenuObjSaveLoad2::sendEvent(handle, 0x22, 0);
                break;
            }
            GfMenuObjCommonText::open(m_owner->m_context, 0xE3, 0);
            m_owner->m_confirm = 1;
            GfMenuObject::setCallContextEventHandler(m_owner->m_context, handle);
            GfMenuObject::disableInput(handle);
            break;
        }
        break;
    }
    case 0x22:
        if (m_owner->m_mode != 0) {
            GfMenuObjOperationInfo::close();
            GfMenuSoundManager::fadeInFieldBgm(1.0f);
        } else {
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            GfMenuObjMainMenu2::setCloseKeyEnable(false);
        }
        GfMenuObjSaveLoad2::setFadeOut(handle, 2);
        break;
    case 0x41: {
        unsigned int id = event.m_param0;
        GfMenuCallContext* context = m_owner->m_context;
        if (context != nullptr && context->m_id == id) {
            if (event.m_paramShort[4] != 0) {
                GfMenuObject::enableInput(handle);
            } else if (m_owner->m_confirm == 0) {
                bool close = GfDataBlade::fn_7100231884() > 10042;
                if (GfMenuObjUtil::isValidExpansion(3)) {
                    close = GfDataBlade::fn_7100231884() > 11125;
                }
                m_owner->m_seq.clear();
                m_owner->m_seq.addJob(&GfMenuObjSaveLoad2::seqSave);
                if (!close) {
                    m_owner->m_seq.addJob(&GfMenuObjSaveLoad2::seqSaveWait);
                } else {
                    m_owner->m_seq.addJob(&GfMenuObjSaveLoad2::seqSaveWaitToClose);
                }
            } else if (m_owner->m_confirm == 1) {
                GfMenuObjSaveLoad2::sendEvent(handle, 0x22, 0);
            }
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjSaveLoad2::setupSave(ui::UIObjectAcc& acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber>* numbers) {
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 3; i++) {
        name.format("TXT_char_name@%02d", i + 1);
        GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.m_str), 2, m_drivers, i, false);
        name.format("TXT_lv_num@%02d", i + 1);
        GfMenuReferenceAdapter::create(acc.searchChild(name.m_str), numbers[i], false);
    }
    m_yearPlugin = ui::UIObjectTimePlugin::create(acc.searchChild("TXT_year_num"), 1);
    m_timePlugin = ui::UIObjectTimePlugin::create(acc.searchChild("TXT_time_num"), 6);
    m_progressPlugin = ui::UIObjectNumberPlugin::create(acc.searchChild("TXT_progress"));
    m_gameTimePlugin = ui::UIObjectTimePlugin::create(acc.searchChild("TXT_game_time"), 7);
    m_areaPlugin = ui::UIObjectTextPlugin::create(acc.searchChild("TXT_area"));
}

bool GfMenuObjSaveLoad2::seqSave() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObject::disableInput(main.m_handle);
    GfMenuObjMainMenu2::setCloseKeyEnable(false);
    m_saveReq = GfReqCommand::reqSave(static_cast<SAVESLOT>(22));
    GfMenuObjFade::dispSaving(true, 0);
    return true;
}

bool GfMenuObjSaveLoad2::seqSaveWait() {
    if (GfReqManager::isValid(m_saveReq)) {
        return false;
    }
    GfMenuObjUtil::playSE(8);
    GfMenuObjFade::dispSaving(false, 0);
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc main(acc.searchChild("LAY_main"));
    refreshSave(main, 1);
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
    ui::UIObjectAcc input(m_handle, "LAY_main");
    GfMenuObject::enableInput(input.m_handle);
    m_saveReq = -1;
    return true;
}

bool GfMenuObjSaveLoad2::seqSaveWaitToClose() {
    if (GfReqManager::isValid(m_saveReq)) {
        return false;
    }
    GfMenuObjUtil::playSE(8);
    GfMenuObjFade::dispSaving(false, 0);
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc main(acc.searchChild("LAY_main"));
    refreshSave(main, 1);
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
    GfMenuObjSaveLoad2::sendEvent(main.m_handle, 0x22, 0);
    m_saveReq = -1;
    return true;
}

}  // namespace gf
