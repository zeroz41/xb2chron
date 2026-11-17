#include "classes/gf/GfMenuObjMercenaryForm.h"
#include "classes/gf/GfGameMercenaries.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/GfMenuObjMercenaryForm/MainListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/ApplyListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/BlImgListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/FormListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/PresetListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/UnitListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/StartListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/LeaderListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/ListListener.h"
#include "classes/gf/GfMenuObjSort.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuMissionAdapter.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/gf/SCOM_PARTY_ADD.h"
#include "classes/gf/GfMenuObjMercenaryTop.h"
#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataMercenaries.h"
#include "mm/mtl/FixStr.h"
#include <algorithm>
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "ui/EventData.h"
#include "mm/mtl/Vector.h"

namespace gf {

GfMenuObjMercenaryForm::GfMenuObjMercenaryForm(unsigned int handle)
    : GfMenuObject(handle), m_teamId(0), m_unitBlades(nullptr), m_listBlades(nullptr), m_unitSelect(nullptr),
      m_unitCursor(nullptr), m_listSelect(nullptr), m_listCursor(nullptr), m_presetSelect(nullptr),
      m_presetCursor(nullptr), m_context(nullptr), m_numbers(), pad_100(0), m_waitFrames(0), m_seq(this),
      m_seqStep(false), m_subSeq(this), m_bladeIds(), pad_8F0(false), m_voice(nullptr), m_leaveVoice(-1),
      m_leaveRequest(false), m_voiceStopped(false) {
    for (int i = 0; i < 8; i++) {
        m_numbers[i] = GfMenuReferenceNumber::create();
    }
    m_context = GfMenuCallContext::create();
}

GfMenuObjMercenaryForm::~GfMenuObjMercenaryForm() {
    for (int i = 0; i < 8; i++) {
        m_numbers[i] = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        if (m_presetBlades[i] != nullptr) {
            m_presetBlades[i]->release();
            m_presetBlades[i] = nullptr;
        }
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_presetCursor != nullptr) {
        m_presetCursor->release();
        m_presetCursor = nullptr;
    }
    if (m_presetSelect != nullptr) {
        m_presetSelect->release();
        m_presetSelect = nullptr;
    }
    if (m_listCursor != nullptr) {
        m_listCursor->release();
        m_listCursor = nullptr;
    }
    if (m_listSelect != nullptr) {
        m_listSelect->release();
        m_listSelect = nullptr;
    }
    if (m_unitCursor != nullptr) {
        m_unitCursor->release();
        m_unitCursor = nullptr;
    }
    if (m_unitSelect != nullptr) {
        m_unitSelect->release();
        m_unitSelect = nullptr;
    }
    if (m_listBlades != nullptr) {
        m_listBlades->release();
        m_listBlades = nullptr;
    }
    if (m_unitBlades != nullptr) {
        m_unitBlades->release();
        m_unitBlades = nullptr;
    }
    if (m_formSelect != nullptr) {
        m_formSelect->release();
        m_formSelect = nullptr;
    }
    if (m_formCursor != nullptr) {
        m_formCursor->release();
        m_formCursor = nullptr;
    }
    if (m_idList != nullptr) {
        m_idList->release();
        m_idList = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        if (m_presetLists[i] != nullptr) {
            m_presetLists[i]->release();
            m_presetLists[i] = nullptr;
        }
    }
}

void GfMenuObjMercenaryForm::initialize() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    mm::mtl::FixStr<32> name;
    m_teamId = GfMenuReference::getReferenceTeamID();
    m_unitBlades = GfMenuBladeList::create();
    m_listBlades = GfMenuBladeList::create();
    {
        ui::UIListInfoBase::SetupParam param;
        param.m_pageRowSize = 6;
        m_unitBlades->setup(getAllocator(ALLOCATOR(0)), param);
        for (int i = 0; i < 3; i++) {
            m_presetBlades[i] = GfMenuBladeList::create();
            param.m_pageRowSize = 6;
            m_presetBlades[i]->setup(getAllocator(ALLOCATOR(0)), param);
        }
    }
    {
        GfMenuBladeList::TeamSetup setup;
        setup.m_type = 3;
        setup.m_team = 0;
        setup.m_param.m_pageRowSize = 3;
        setup.m_param.m_pageColumnSize = 5;
        setup.m_keepEmpty = false;
        m_listBlades->clear();
        m_listBlades->setupFromTeam(setup);
    }
    unsigned short sort = GfMenuObjSort::getSortID(0xE, 0);
    if (sort >= 4 && sort <= 6) {
        m_listBlades->sort(sort, true);
    } else {
        m_listBlades->sort(sort, false);
    }
    {
        ui::UIObjectAcc form(main.m_handle, "LAY_form");
#line 244
        FormListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) FormListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(form.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuAdapterManager::beginAddAfter();
    {
        ui::UIObjectAcc unit(main.m_handle, "LAY_form_unit_bl");
        {
            mm::mtl::IAllocator* allocator = getAllocator(ALLOCATOR(0));
            ui::UISelectObjList::CreateParam create;
            create.m_allocator = allocator;
            m_unitSelect = ui::UISelectObjList::create(create);
        }
        m_unitSelect->pickupObject(unit.m_handle, "LAY_form_unit_bl_face@%02d", 1);
        {
            ui::UICtrlCursorSelect::CursorSetting setting;
            setting.setType(0);
            setting.m_dockType = 0;
            m_unitCursor =
                ui::UICtrlCursorSelect::create(main.searchChild("IMG_form_unit_bl_cursor"), setting, m_unitSelect);
        }
        for (unsigned int i = 0; i < m_unitSelect->getSize(); i++) {
            name.format("IMG_form_unit_bl_face@%02d", i + 1);
            GfMenuCharDataAdapter::createFromBladeList(unit.searchChild(name.m_str), 3, m_unitBlades, i, false);
            name.format("IMG_form_unit_bl_lock@%02d", i + 1);
            GfMenuCharDataAdapter* adapter =
                GfMenuCharDataAdapter::createFromBladeList(unit.searchChild(name.m_str), 0x5A, m_unitBlades, i, true);
            if (adapter != nullptr) {
                adapter->setDispAlphaMode(true);
            }
            name.format("IMG_form_unit_bl_info_elem@%02d", i + 1);
            GfMenuCharDataAdapter::createFromBladeList(unit.searchChild(name.m_str), 0x2A, m_unitBlades, i, false);
            name.format("IMG_form_unit_bl_info_wpn@%02d", i + 1);
            adapter =
                GfMenuCharDataAdapter::createFromBladeList(unit.searchChild(name.m_str), 0x29, m_unitBlades, i, false);
            if (adapter != nullptr) {
                name.format("IMG_form_unit_bl_info_wpn_bg@%02d", i + 1);
                adapter->m_rowHandle = unit.searchChild(name.m_str);
            }
            name.format("IMG_form_unit_bl_info_role@%02d", i + 1);
            GfMenuCharDataAdapter::createFromBladeList(unit.searchChild(name.m_str), 0x42, m_unitBlades, i, false);
            name.format("IMG_form_unit_bl_info_dr@%02d", i + 1);
            GfMenuCharDataAdapter::createFromBladeListOwnerDriver(unit.searchChild(name.m_str), 3, m_unitBlades, i,
                                                                  false);
        }
#line 301
        UnitListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) UnitListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(unit.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::setFSInputObject(1, unit.m_handle);
    }
    {
#line 309
        ApplyListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ApplyListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_form_apply"), listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc list(main.m_handle, "LAY_form_list_bl");
        {
            mm::mtl::IAllocator* allocator = getAllocator(ALLOCATOR(0));
            ui::UISelectObjList::CreateParam create;
            create.m_allocator = allocator;
            m_listSelect = ui::UISelectObjList::create(create);
        }
        m_listSelect->pickupObject(list.m_handle, "LAY_form_lsit_bl_face@%02d", 1);
        {
            ui::UICtrlCursorSelect::CursorSetting setting;
            setting.setType(0);
            setting.m_dockType = 0;
            m_listCursor =
                ui::UICtrlCursorSelect::create(main.searchChild("IMG_form_list_bl_cursor"), setting, m_listSelect);
        }
        for (unsigned int i = 0; i < m_listSelect->getSize(); i++) {
            name.format("IMG_form_list_bl_face@%02d", i + 1);
            GfMenuCharDataAdapter* adapter =
                GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.m_str), 3, m_listBlades, i, false);
            if (adapter != nullptr) {
                adapter->setSlotList(m_unitBlades);
            }
            name.format("IMG_form_list_bl_lock@%02d", i + 1);
            adapter =
                GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.m_str), 0x5A, m_listBlades, i, true);
            if (adapter != nullptr) {
                adapter->setSlotList(m_unitBlades);
                adapter->setDispAlphaMode(true);
            }
            name.format("IMG_form_list_bl_info_elem@%02d", i + 1);
            GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.m_str), 0x2A, m_listBlades, i, false);
            name.format("IMG_form_list_bl_info_wpn@%02d", i + 1);
            adapter =
                GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.m_str), 0x29, m_listBlades, i, false);
            if (adapter != nullptr) {
                name.format("IMG_form_list_bl_info_wpn_bg@%02d", i + 1);
                adapter->m_rowHandle = list.searchChild(name.m_str);
            }
            name.format("IMG_form_list_bl_info_role@%02d", i + 1);
            GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.m_str), 0x42, m_listBlades, i, false);
            name.format("IMG_form_list_bl_info_dr@%02d", i + 1);
            GfMenuCharDataAdapter::createFromBladeListOwnerDriver(list.searchChild(name.m_str), 3, m_listBlades, i,
                                                                  false);
        }
#line 370
        ListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(list.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::setFSInputObject(2, list.m_handle);
        GfMenuObjUtil::createVScrollBarPlugin(list.searchChild("IMG_form_list_bl_scroll_bar"), m_listBlades,
                                              "IMG_form_list_bl_scroll_base", true);
    }
    {
        ui::UIObjectAcc mission(main.m_handle, "LAY_form_mission");
        for (int i = 0; i < 3; i++) {
            name.format("IMG_form_mis_cond_icon@%02d", i + 1);
            GfMenuMissionAdapter* adapter =
                GfMenuMissionAdapter::createFromReferenceMission(mission.searchChild(name.m_str), 0x13, i, false);
            if (adapter != nullptr) {
                name.format("LAY_form_mis_cond@%02d", i + 1);
                adapter->m_rowHandle = mission.searchChild(name.m_str);
            }
            name.format("TXT_form_mis_cond_txt@%02d", i + 1);
            GfMenuMissionAdapter::createFromReferenceMission(mission.searchChild(name.m_str), 0x12, i, false);
            unsigned int text = mission.searchChild(name.m_str);
            if (text != 0) {
                name.format("TXT_form_mis_cond_val@%02d", i + 1);
                GfMenuMissionAdapter::createFromReferenceMission(mission.searchChild(name.m_str), 0x14, i, false);
                GfMenuObjUtil::createDockPlugin(mission.searchChild(name.m_str), text, 1, mm::Pnt<short>(12, 0), 0);
                name.format("TXT_form_mis_cond_lv@%02d", i + 1);
                GfMenuMissionAdapter::createFromReferenceMission(mission.searchChild(name.m_str), 0x15, i, false);
                GfMenuObjUtil::createDockPlugin(mission.searchChild(name.m_str), text, 1, mm::Pnt<short>(12, 0), 0);
                name.format("TXT_form_mis_cond_num@%02d", i + 1);
                GfMenuReferenceAdapter::create(mission.searchChild(name.m_str), m_numbers[i], true);
                name.format("TXT_form_mis_cond_max@%02d", i + 1);
                GfMenuMissionAdapter::createFromReferenceMission(mission.searchChild(name.m_str), 0x17, i, false);
            }
        }
        for (int i = 0; i < 3; i++) {
            name.format("TXT_form_mis_fs_name@%02d", i + 1);
            GfMenuMissionAdapter* adapter =
                GfMenuMissionAdapter::createFromReferenceMission(mission.searchChild(name.m_str), 0x11, i, false);
            if (adapter != nullptr) {
                name.format("LAY_form_mis_fs@%02d", i + 1);
                adapter->m_rowHandle = mission.searchChild(name.m_str);
            }
            name.format("TXT_form_mis_fs_bl_num@%02d", i + 1);
            GfMenuReferenceAdapter::create(mission.searchChild(name.m_str), m_numbers[4 + i], true);
        }
    }
    {
        ui::UIObjectAcc leader(main.m_handle, "LAY_leader");
#line 453
        LeaderListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) LeaderListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(leader.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::setFSInputObject(4, leader.m_handle);
        {
            mm::mtl::IAllocator* allocator = getAllocator(ALLOCATOR(0));
            ui::UISelectObjList::CreateParam create;
            create.m_allocator = allocator;
            m_formSelect = ui::UISelectObjList::create(create);
        }
        {
            ui::UICtrlCursorSelect::CursorSetting setting;
            setting.setType(0);
            setting.m_dockType = 0;
            m_formCursor =
                ui::UICtrlCursorSelect::create(main.searchChild("IMG_leader_sel_list_bl_cursor"), setting, m_formSelect);
        }
        GfMenuCharDataAdapter::createFromReferenceBlade(leader.searchChild("TXT_leader_sel_index_name"), 2, 0, false);
        GfMenuCharDataAdapter::createFromReferenceBlade(leader.searchChild("TXT_leader_sel_info_name"), 0x58, 0, false);
        for (unsigned int i = 0; i < m_unitSelect->getSize(); i++) {
            name.format("IMG_leader_sel_list_bl_face@%02d", i + 1);
            GfMenuCharDataAdapter::createFromBladeList(leader.searchChild(name.m_str), 3, m_unitBlades, i, false);
        }
    }
    GfMenuAdapterManager::endAddAfter();
    {
        ui::UIObjectAcc start(main.m_handle, "LAY_start");
        for (int i = 0; i < 5; i++) {
            name.format("IMG_mis_start_bl@%02d", i + 1);
            GfMenuCharDataAdapter::createFromBladeList(start.searchChild(name.m_str), 0x36, m_unitBlades, i + 1, false);
        }
#line 498
        StartListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) StartListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(start.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc img(main.m_handle, "LAY_bl_img");
        GfMenuCharDataAdapter::createFromReferenceBlade(img.searchChild("IMG_leader_bl_img"), 0x36, 0, false);
#line 511
        BlImgListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) BlImgListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(img.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc preset(main.m_handle, "LAY_preset");
        {
            mm::mtl::IAllocator* allocator = getAllocator(ALLOCATOR(0));
            ui::UISelectObjList::CreateParam create;
            create.m_allocator = allocator;
            m_presetSelect = ui::UISelectObjList::create(create);
        }
        m_presetSelect->pickupObject(main.m_handle, "LAY_preset_bl_base@%02d", 1);
        {
            ui::UICtrlCursorSelect::CursorSetting setting;
            setting.setType(0);
            setting.m_dockType = 0;
            m_presetCursor = ui::UICtrlCursorSelect::create(main.searchChild("IMG_preset_cursor"), setting, m_presetSelect);
        }
        {
            ui::UIListInfoBase::SetupParam param;
            m_idList = GfMenuIDList::create();
            param.m_pageRowSize = 3;
            m_idList->setup(getAllocator(ALLOCATOR(0)), param);
            for (unsigned int i = 0; i < 8; i++) {
                m_idList->addContents(MenuID{i, 0});
            }
        }
        GfMenuObjUtil::createVScrollBarPlugin(preset.searchChild("IMG_preset_scroll_bar"), m_idList,
                                              "IMG_preset_scroll_base", false);
        for (int i = 0; i < 3; i++) {
            ui::UIListInfoBase::SetupParam param;
            param.m_pageRowSize = 6;
            m_presetLists[i] = GfMenuBladeList::create();
            m_presetLists[i]->setup(getAllocator(ALLOCATOR(0)), param);
            name.format("TXT_preset_bl_no@%02d", i + 1);
            GfMenuReferenceAdapter::create(preset.searchChild(name.m_str), m_numbers[4 + i], false);
            for (int j = 0; j < 6; j++) {
                name.format("IMG_preset_bl_face@%02d%02d", i + 1, j + 1);
                GfMenuCharDataAdapter::createFromBladeList(preset.searchChild(name.m_str), 3, m_presetLists[i], j,
                                                           false);
                GfMenuCharDataAdapter::createFromBladeList(preset.searchChild(name.m_str), 0x49, m_presetLists[i], j,
                                                           false);
                name.format("IMG_preset_bl_info_elem@%02d%02d", i + 1, j + 1);
                GfMenuCharDataAdapter::createFromBladeList(preset.searchChild(name.m_str), 0x2A, m_presetLists[i], j,
                                                           false);
                GfMenuCharDataAdapter::createFromBladeList(preset.searchChild(name.m_str), 0x39, m_presetLists[i], j,
                                                           false);
                name.format("IMG_preset_bl_info_wpn@%02d%02d", i + 1, j + 1);
                GfMenuCharDataAdapter::createFromBladeList(preset.searchChild(name.m_str), 0x29, m_presetLists[i], j,
                                                           false);
            }
        }
#line 582
        PresetListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) PresetListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(preset.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::setFSInputObject(3, preset.m_handle);
    }
#line 590
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    sendOpenEvent(main.searchChild("LAY_form_list_bl"), 0, 0.0f);
    GfMenuObject::disableFSInput();
    GfMenuObject::initialize();
}

void GfMenuObjMercenaryForm::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjMercenaryForm::update() {
    if (!m_seq.m_jobs.empty()) {
        if (m_leaveRequest && GfMenuObjUtil::isVoiceSkip()) {
            m_seqStep = false;
            m_seq.clear();
            m_seq.addJob(&GfMenuObjMercenaryForm::seqLeaveBlade);
            if (m_leaveVoice != -1) {
                GfGameVoice::playStop(reinterpret_cast<GF_SCOM_HANDLE*>(m_leaveVoice));
                m_leaveVoice = -1;
            }
            m_leaveRequest = false;
        }
    }
    m_seq.update();
    m_subSeq.update();
    if (m_waitFrames != 0) {
        m_waitFrames--;
    }
    GfMenuObject::update();
}


bool GfMenuObjMercenaryForm::seqLeaveBlade() {
    ui::UIObjectAcc image(m_handle, "LAY_bl_img");
    bool done;
    if (!m_seqStep) {
        {
            ui::EventData event;
            event.m_type = 0x101;
            GfMenuObject::sendEvent(image.m_handle, event, 0.0f);
        }
        mm::mtl::FixStr<32> motion;
        for (unsigned int i = 0; i < m_unitSelect->getSize(); i++) {
            motion.format("mnu090_anim_sub_%d", i + 1);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = motion.m_str;
            param.m_motion = "end";
            GfMenuObjUtil::startCtrl(m_unitSelect->getObject(i), param, nullptr);
        }
        {
            ui::UIObjectAcc effect(m_handle, "IMG_start_eff");
            effect.setDisp(true);
            effect.startAnimation("end", false);
        }
        done = false;
        m_seqStep = true;
        m_leaveRequest = false;
    } else {
        if (m_leaveVoice != -1 && GfMenuObjUtil::isVoiceSkip()) {
            GfGameVoice::playStop(reinterpret_cast<GF_SCOM_HANDLE*>(m_leaveVoice));
            m_leaveVoice = -1;
        }
        if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(image.m_handle))) {
            m_seq.addJob(&GfMenuObjMercenaryForm::seqDepartureEnd);
            done = true;
            m_seqStep = false;
        } else {
            done = false;
        }
    }
    return done;
}

void GfMenuObjMercenaryForm::setDetailBladePos(unsigned int handle) {
    ui::UIObjectAcc detail(m_handle, "LAY_form_bl_detail_bl");
    if (handle == 0) {
        detail.setDisp(false);
    } else {
        ui::UIObjectAcc blade(handle);
        mm::Rect<short> rect;
        blade.getRect(rect, 1);
        mm::Pnt<short> pos;
        pos.x = rect.x;
        pos.y = rect.y;
        detail.setPos(pos);
        detail.setDisp(true);
    }
}

void GfMenuObjMercenaryForm::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    case 2: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_out = 1;
        param.m_preset = 6;
        param.m_startFlag1 = true;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

inline void GfMenuObjMercenaryForm::sendOpenEvent(unsigned int handle, int param, float delay) {
    unsigned int target = handle != 0 ? handle : ui::UIObjectAcc(m_handle, "LAY_form_main").m_handle;
    ui::EventData open;
    open.m_type = 0x21;
    open.m_param0 = param;
    GfMenuObject::sendEvent(target, open, delay);
}

inline void GfMenuObjMercenaryForm::sendCloseEvent(unsigned int handle, int param, float delay) {
    unsigned int target = handle != 0 ? handle : ui::UIObjectAcc(m_handle, "LAY_form_main").m_handle;
    ui::EventData close;
    close.m_type = 0x22;
    close.m_param0 = param;
    GfMenuObject::sendEvent(target, close, delay);
}

void GfMenuObjMercenaryForm::FormListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        pad_0C = 0;
        pad_10 = 0;
        GfMenuObjOperationInfo::setGuideText(0x25, 0);
        GfMenuObjCmnStatus::openBlStatus(0, -1);
        break;
    case 3:
        if (event.m_param0 == 0) {
            break;
        }
        if (event.m_param0 == 2) {
            m_owner->sendOpenEvent(acc.searchSibiling("LAY_leader"), 0, 0.0f);
        }
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 0x102: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_eventId = 2;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        GfMenuObjCmnStatus::closeBlStatus();
        break;
    }
    case 0x103: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        m_owner->sendOpenEvent(acc.searchChild("LAY_form_list_bl"), 1, 0.0f);
        GfMenuObjOperationInfo::setGuideText(0x25, 0);
        GfMenuObjCmnStatus::openBlStatus(0, -1);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjMercenaryForm::UnitListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::resetInputSelection(acc.m_handle);
        GfMenuObject::setupInputSelection(acc.m_handle, 0, 6);
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            m_owner->m_unitBlades->setIndex(index);
            m_owner->m_unitSelect->setIndex(index);
            if (index < m_owner->m_unitBlades->getSize()) {
                GfMenuReference::setReferenceBladeID(0, m_owner->m_unitBlades->getContents(m_owner->m_unitBlades->getIndex(false)).m_blade);
            } else {
                GfMenuReference::setReferenceBladeID(0, 0);
            }
            m_owner->setDetailBladePos(m_owner->m_unitSelect->getSelectObject());
            m_owner->updateBladeCount(false, false);
            unsigned int blade = m_owner->m_unitBlades->getContents(index).m_blade;
            if (blade == 0) {
                GfMenuObjOperationInfo::setActionEnable(handle, 0xC, false);
            } else {
                bool valid = GfMenuObjUtil::isValidBlade(blade);
                GfMenuObjOperationInfo::setActionEnable(handle, 0xC, valid);
                if (valid) {
                    GfMenuObjOperationInfo::changeText(handle, 0xC, GfDataBlade::isBladeLock(blade));
                }
            }
            if (prev != -1 && index != prev) {
                GfMenuObjUtil::playSECommonCursor();
            }
        }
        break;
    }
    case 8: {
        int index = event.m_param0;
        if (event.m_param1 == 10) {
            if (index < m_owner->m_unitBlades->getSize()) {
                {
                    GfMenuBladeList* list = m_owner->m_unitBlades;
                    list->m_list.erase(list->m_list.begin() + (unsigned int)index);
                    list->subSize(1);
                    list->m_changed = true;
                }
                if (index < m_owner->m_unitBlades->getSize()) {
                    GfMenuReference::setReferenceBladeID(0, m_owner->m_unitBlades->getContents(m_owner->m_unitBlades->getIndex(false)).m_blade);
                } else {
                    GfMenuReference::setReferenceBladeID(0, 0);
                }
                m_owner->updateBladeCount(false, false);
                m_owner->refreshBladeList();
                if (m_owner->m_unitBlades->getSize() == 0) {
                    GfMenuObject::disableFSInput();
                    GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
                    m_owner->m_unitCursor->setDisp(false);
                    m_owner->sendOpenEvent(acc.searchSibiling("LAY_form_list_bl"), 0, 0.0f);
                }
                unsigned int blade = GfMenuReference::getReferenceBladeID(0);
                if (blade == 0) {
                    GfMenuObjOperationInfo::setActionEnable(handle, 0xC, false);
                } else {
                    bool valid = GfMenuObjUtil::isValidBlade(blade);
                    GfMenuObjOperationInfo::setActionEnable(handle, 0xC, valid);
                    if (valid) {
                        GfMenuObjOperationInfo::changeText(handle, 0xC, GfDataBlade::isBladeLock(blade));
                    }
                }
                GfMenuObjUtil::playSECommonCancel();
            }
        } else if (event.m_param1 == 12) {
            unsigned int blade = GfMenuReference::getReferenceBladeID(0);
            if (blade != 0 && GfMenuObjUtil::isValidBlade(blade)) {
                if (!GfDataBlade::isBladeLock(blade)) {
                    GfMenuObjUtil::setBladeFavorite(blade, true);
                    GfMenuObjUtil::playSECommonDecide();
                } else {
                    GfMenuObjUtil::setBladeFavorite(blade, false);
                    GfMenuObjUtil::playSECommonCancel();
                }
                bool valid = GfMenuObjUtil::isValidBlade(blade);
                GfMenuObjOperationInfo::setActionEnable(handle, 0xC, valid);
                if (valid) {
                    GfMenuObjOperationInfo::changeText(handle, 0xC, GfDataBlade::isBladeLock(blade));
                }
            }
        }
        break;
    }
    case 9:
        if (event.m_param0 == 2) {
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            m_owner->m_unitCursor->setDisp(false);
            m_owner->updateBladeCount(false, true);
            m_owner->sendOpenEvent(acc.searchSibiling("LAY_form_list_bl"), 0, 0.0f);
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    case 0x21: {
        GfMenuObject::enableFSInput(1);
        GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        m_owner->m_unitCursor->setDisp(true);
        GfMenuReference::setReferenceBladeID(0, m_owner->m_unitBlades->getContents(m_owner->m_unitBlades->getIndex(false)).m_blade);
        unsigned int blade = m_owner->m_unitBlades->getContents(m_owner->m_unitBlades->getIndex(false)).m_blade;
        if (blade == 0) {
            GfMenuObjOperationInfo::setActionEnable(handle, 0xC, false);
        } else {
            bool valid = GfMenuObjUtil::isValidBlade(blade);
            GfMenuObjOperationInfo::setActionEnable(handle, 0xC, valid);
            if (valid) {
                GfMenuObjOperationInfo::changeText(handle, 0xC, GfDataBlade::isBladeLock(blade));
            }
        }
        GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_form_apply"), 0, 0.0f);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjMercenaryForm::updateBladeCount(bool add, bool apply) {
    ui::UIObjectAcc acc(m_handle, "LAY_form");
    unsigned int mission = GfMenuReference::getReferenceMissionID();
    mm::mtl::FixStr<32> name;
    GfRequestBladeData cond = {};
    unsigned int added = -1;
    if (add && m_unitBlades->getSize() < 6u) {
        unsigned int blade = m_listBlades->getContents(m_listBlades->getIndex(false)).m_blade;
        unsigned int i;
        for (i = 0; i < m_unitBlades->getSize(); i++) {
            if (m_unitBlades->getContents(i).m_blade == blade) {
                break;
            }
        }
        if (i == m_unitBlades->getSize()) {
            MenuBladeInfo info;
            added = m_unitBlades->getSize();
            info.m_blade = blade;
            info.m_creator = GfDataBlade::getCreator(blade);
            m_unitBlades->addContents(info);
        }
    }
    int condCount = 0;
    int okCount = 0;
    for (unsigned int i = 0; i < 3; i++) {
        unsigned int count = 0;
        if (GfDataMercenaries::getRequestCondition(cond, mission, i)) {
            count = GfMenuObjUtil::getMissionCondBladeCount(cond, m_unitBlades);
            condCount++;
        }
        {
            name.format("TXT_form_mis_cond_txt@%02d", i + 1);
            ui::UIObjectAcc text(acc.m_handle, name.m_str);
            name.format("IMG_form_mis_cond_icon@%02d", i + 1);
            ui::UIObjectAcc icon(acc.m_handle, name.m_str);
            unsigned int need = cond.m_count == 0 ? 1 : cond.m_count;
            if (need > count) {
                GfMenuObjUtil::setColMulandAdd(text.m_handle, "txt_warning");
                icon.setAddColor("mer_cond_ng");
            } else {
                GfMenuObjUtil::setColDefault(text.m_handle);
                icon.setAddColor("mer_cond_ok");
                okCount++;
            }
        }
        m_numbers[i]->m_value = count;
    }
    if (!add && apply) {
        acc.setDispChild(okCount == condCount, "LAY_form_unit_apply");
        unsigned int target = acc.searchChild("LAY_form_apply");
        if (okCount == condCount) {
            sendOpenEvent(target, 0, 0.0f);
        } else {
            sendCloseEvent(target, 0, 0.0f);
        }
        bool enable = okCount == condCount;
        GfMenuObject::setInputActionEnable(acc.searchChild("LAY_form_list_bl"), 0x10, enable);
        GfMenuObject::setInputActionEnable(acc.searchChild("LAY_form_unit_bl"), 0x10, enable);
        pad_8F0 = enable;
    }
    for (unsigned int i = 0; i < 3; i++) {
        unsigned int skill = GfDataMercenaries::getFieldSkill(mission, i);
        int count = 0;
        if (skill != 0) {
            for (unsigned int j = 0; j < m_unitBlades->getSize(); j++) {
                DataParamAcc param(4, m_unitBlades->getContents(j).m_blade, GimmickType(0));
                if ((param.getFieldSkillLevel(0, false) != 0 && param.getFieldSkill(0, false) == skill) ||
                    (param.getFieldSkillLevel(1, false) != 0 && param.getFieldSkill(1, false) == skill) ||
                    (param.getFieldSkillLevel(2, false) != 0 && param.getFieldSkill(2, false) == skill)) {
                    count++;
                }
            }
        }
        m_numbers[4 + i]->m_value = count;
    }
    if (added != -1) {
        GfMenuBladeList* list = m_unitBlades;
        list->m_list.erase(list->m_list.begin() + added);
        list->subSize(1);
        list->m_changed = true;
    }
}

void GfMenuObjMercenaryForm::refreshBladeList() {
    ui::UIObjectAcc acc(m_handle, "LAY_form_list_bl");
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < m_listBlades->getPageSize(); i++) {
        const MenuBladeInfo& info = m_listBlades->getContents(m_listBlades->getPageIndex(i));
        bool selectable = GfMenuObjUtil::isBladeSelectable(info.m_blade, nullptr);
        name.format("IMG_form_list_bl_face@%02d", i + 1);
        {
            ui::UIObjectAcc face(acc.m_handle, name.m_str);
            unsigned short* last = m_bladeIds.end();
            if (selectable || std::find(m_bladeIds.begin(), last, static_cast<unsigned short>(info.m_blade)) != last) {
                face.setMulColor("white");
            } else {
                face.setMulColor("gray");
            }
        }
        bool member = false;
        for (unsigned int j = 0; j < m_unitBlades->getSize(); j++) {
            if (m_unitBlades->getContents(j).m_blade == info.m_blade) {
                member = true;
                break;
            }
        }
        name.format("IMG_form_list_bl_check@%02d", i + 1);
        {
            ui::UIObjectAcc check(acc.m_handle, name.m_str);
            check.setDisp(member);
        }
    }
}

void GfMenuObjMercenaryForm::ListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::setPadLineSelectionLoop(acc.m_handle, false);
        m_owner->pad_100 = 0;
        m_index = -1;
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            m_owner->m_listBlades->setIndex(index);
            unsigned int select = index - m_owner->m_listBlades->getRowOffset() * m_owner->m_listBlades->getColumnSize();
            m_owner->m_listSelect->setIndex(select);
            m_owner->updateReserveBlade(index);
            unsigned int blade = m_owner->m_listBlades->getContents(index).m_blade;
            if (blade == 0) {
                GfMenuObjOperationInfo::setActionEnable(handle, 0xC, false);
            } else {
                bool valid = GfMenuObjUtil::isValidBlade(blade);
                GfMenuObjOperationInfo::setActionEnable(handle, 0xC, valid);
                if (valid) {
                    GfMenuObjOperationInfo::changeText(handle, 0xC, GfDataBlade::isBladeLock(blade));
                }
            }
            if (prev != -1 && index != prev) {
                GfMenuObjUtil::playSECommonCursor();
            }
        }
        m_index = index;
        break;
    }
    case 8: {
        int index = event.m_param0;
        switch (event.m_param1) {
        case 1: {
            if (m_owner->m_unitBlades->getSize() > 5u) {
                break;
            }
            unsigned int blade = m_owner->m_listBlades->getContents(index).m_blade;
            if (blade == 0) {
                GfMenuObjUtil::playSECommon(2);
                break;
            }
            if (!m_owner->chkUnitBladeList(blade) && GfDataBlade::getCreator(blade) == 1 &&
                GfMenuObjUtil::isBladeLastOne(blade, m_owner->m_unitBlades)) {
                GfMenuManager::openCommonWindow(0xDB);
                break;
            }
            if (!m_owner->chkUnitBladeList(blade) &&
                (m_owner->chkTempUnlink(blade) || GfMenuObjUtil::isBladeSelectable(blade, m_owner->m_unitBlades))) {
                if (GfGameManager::isClearGame() && GfMenuObjUtil::isBladeHana(blade)) {
                    m_owner->m_seq.clear();
                    m_owner->m_seq.addJob(&GfMenuObjMercenaryForm::seqConfirmHana);
                    GfMenuObject::disableFSInput();
                    GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
                } else {
                    MenuBladeInfo info;
                    info = m_owner->m_listBlades->getContents(m_owner->m_listBlades->getIndex(false));
                    m_owner->m_unitBlades->addContents(info);
                    m_owner->updateBladeCount(false, true);
                    SCOM_FIELD_VOICE::createMercenariesIn(info.m_blade);
                    GfMenuObjOperationInfo::changeText(acc.m_handle, 2, true);
                    if (m_owner->m_unitBlades->getSize() == 6) {
                        GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 1, false);
                    }
                    GfMenuObjUtil::playSECommonDecide();
                    m_owner->refreshBladeList();
                }
            } else if (GfDataBlade::isActivateDriver(blade) && !m_owner->chkTempUnlink(blade)) {
                if (GfGameManager::isClearGame() && GfMenuObjUtil::isBladeHana(blade) &&
                    m_owner->chkUnitBladeList(blade)) {
                    GfMenuManager::openCommonWindow(0x10E);
                    break;
                }
                if (!GfMenuObjUtil::canRemoveBlade(blade, &m_owner->m_bladeIds) &&
                    (!GfMenuObjUtil::isBladeHana(blade) || !GfMenuObjUtil::isAvailableTora())) {
                    GfMenuManager::openCommonWindow(0xCD);
                    break;
                }
                m_owner->m_seq.clear();
                m_owner->m_seq.addJob(&GfMenuObjMercenaryForm::seqConfirmRemoveBladeSet);
                GfMenuObject::disableFSInput();
                GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            } else if (GfMenuObjUtil::isBladeHana(blade)) {
                for (unsigned int i = 0; i < m_owner->m_unitBlades->getSize(); i++) {
                    if (blade != m_owner->m_unitBlades->getContents(i).m_blade &&
                        GfMenuObjUtil::isBladeHana(m_owner->m_unitBlades->getContents(i).m_blade)) {
                        GfMenuManager::openCommonWindow(0x10E);
                    }
                }
            }
            break;
        }
        case 2:
            if (m_owner->m_unitBlades->getSize() != 0) {
                unsigned int last = m_owner->m_unitBlades->getSize() - 1;
                // the original keeps this access's bounds asserts but nothing reads the content
                m_owner->m_unitBlades->getContents(last);
                GfMenuBladeList* list = m_owner->m_unitBlades;
                list->m_list.erase(list->m_list.begin() + last);
                list->subSize(1);
                list->m_changed = true;
                unsigned int reference = GfMenuReference::getReferenceBladeID(0);
                m_owner->updateBladeCount(false, true);
                if (reference != 0) {
                    m_owner->updateBladeCount(true, true);
                }
                GfMenuObjOperationInfo::changeText(acc.m_handle, 2, m_owner->m_unitBlades->getSize() != 0);
                GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 1, true);
                GfMenuObjUtil::playSECommonCancel();
                m_owner->refreshBladeList();
            } else {
                m_owner->m_seq.clear();
                m_owner->m_seq.addJob(&GfMenuObjMercenaryForm::seqReturnMissionSelect);
                GfMenuObjMainMenu2::setCloseKeyEnable(false);
                GfMenuObject::disableFSInput();
                GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            }
            break;
        case 0xC:
            if (index < m_owner->m_listBlades->getSize()) {
                unsigned int blade = m_owner->m_listBlades->getContents(m_owner->m_listBlades->getIndex(false)).m_blade;
                if (blade != 0 && GfMenuObjUtil::isValidBlade(blade)) {
                    if (!GfDataBlade::isBladeLock(blade)) {
                        GfMenuObjUtil::setBladeFavorite(blade, true);
                        GfMenuObjUtil::playSECommonDecide();
                    } else {
                        GfMenuObjUtil::setBladeFavorite(blade, false);
                        GfMenuObjUtil::playSECommonCancel();
                    }
                    bool valid = GfMenuObjUtil::isValidBlade(blade);
                    GfMenuObjOperationInfo::setActionEnable(handle, 0xC, valid);
                    if (valid) {
                        GfMenuObjOperationInfo::changeText(handle, 0xC, GfDataBlade::isBladeLock(blade));
                    }
                    break;
                }
            }
            GfMenuObjUtil::playSECommon(2);
            break;
        case 0x10:
            if (m_owner->pad_8F0) {
                ui::EventData data;
                data.m_type = 0x102;
                GfMenuObject::sendEvent(acc.getParentHandle(), data, 0.0f);
                GfMenuObject::disableFSInput();
                GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
                m_owner->m_listCursor->setDisp(false);
                GfMenuObjUtil::playSECommonDecide();
            }
            break;
        case 0x11:
            GfMenuObjSort::open(acc.m_handle, acc.searchChild("TXT_form_list_bl_sort_label"), 0xE, m_owner->pad_100);
            GfMenuObject::disableInput(handle);
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            break;
        }
        break;
    }
    case 9:
        if ((event.m_param0 == 1 || event.m_param0 == 3) && m_owner->m_unitBlades->getSize() != 0) {
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            m_owner->m_listCursor->setDisp(false);
            m_owner->sendOpenEvent(acc.searchSibiling("LAY_form_unit_bl"), 0, 0.0f);
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    case 0x21: {
        m_owner->pad_8F0 = false;
        if (event.m_param0 == 1) {
            m_owner->m_listBlades->setIndex(0);
            m_owner->refreshBladeList();
        }
        GfMenuObject::resetInputSelection(acc.m_handle);
        unsigned int size = m_owner->m_listBlades->getSize();
        int pad = 0;
        if (size % 5 != 0) {
            pad = 5 - size % 5;
        }
        unsigned int count = pad + size;
        int select = m_owner->m_listBlades->getIndex(false);
        if (m_index != -1) {
            select = m_index;
        }
        GfMenuObject::setupInputSelection(handle, select, count);
        m_index = select;
        GfMenuObject::setupPadLineSelection(acc.m_handle, 5);
        acc.setDispChild(true, "IMG_form_list_bl_cursor");
        GfMenuObject::enableFSInput(2);
        GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        GfMenuObjOperationInfo::changeText(acc.m_handle, 2, m_owner->m_unitBlades->getSize() != 0);
        GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 1, m_owner->m_unitBlades->getSize() < 6u);
        GfMenuObjSort::setSortLabelText(GfMenuObjSort::getSortID(0xE, m_owner->pad_100),
                                        acc.searchChild("TXT_form_list_bl_sort_label"));
        m_owner->updateBladeCount(false, true);
        break;
    }
    case 0x148: {
        GfMenuObject::enableInput(handle);
        GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        if (event.m_param1 == 0) {
            break;
        }
        unsigned short sort = GfMenuObjSort::getSortID(0xE, event.m_param0);
        if (sort >= 4 && sort <= 6) {
            m_owner->m_listBlades->sort(sort, true);
        } else {
            m_owner->m_listBlades->sort(sort, false);
        }
        m_owner->pad_100 = event.m_param0;
        m_owner->updateReserveBlade(m_index);
        unsigned int blade = m_owner->m_listBlades->getContents(m_index).m_blade;
        if (blade == 0) {
            GfMenuObjOperationInfo::setActionEnable(handle, 0xC, false);
        } else {
            bool valid = GfMenuObjUtil::isValidBlade(blade);
            GfMenuObjOperationInfo::setActionEnable(handle, 0xC, valid);
            if (valid) {
                GfMenuObjOperationInfo::changeText(handle, 0xC, GfDataBlade::isBladeLock(blade));
            }
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

inline void GfMenuObjMercenaryForm::updateReserveBlade(unsigned int index) {
    unsigned int blade = m_listBlades->getContents(index).m_blade;
    GfMenuReference::setReferenceBladeID(0, blade);
    updateBladeCount(blade != 0, true);
    refreshBladeList();
}

bool GfMenuObjMercenaryForm::chkUnitBladeList(unsigned int blade) {
    for (unsigned int i = 0; i < m_unitBlades->getSize(); i++) {
        if (m_unitBlades->getContents(i).m_blade == blade) {
            return true;
        }
        if (GfMenuObjUtil::isBladeHana(blade) && GfMenuObjUtil::isBladeHana(m_unitBlades->getContents(i).m_blade)) {
            return true;
        }
    }
    return false;
}

inline bool GfMenuObjMercenaryForm::chkTempUnlink(unsigned int blade) {
    unsigned short* last = m_bladeIds.end();
    return std::find(m_bladeIds.begin(), last, static_cast<unsigned short>(blade)) != last;
}

bool GfMenuObjMercenaryForm::seqConfirmHana() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    bool done;
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(0x10F);
        done = false;
        m_seqStep = true;
    } else if (GfMenuManager::isOpenCommonWindow()) {
        done = false;
    } else {
        short result = GfMenuManager::getCommonWindowResult();
        if (result == 0) {
            unsigned int blade = m_listBlades->getContents(m_listBlades->getIndex(false)).m_blade;
            if (!chkUnitBladeList(blade)) {
                MenuBladeInfo info;
                info.m_blade = blade;
                info.m_creator = GfDataBlade::getCreator(blade);
                m_unitBlades->addContents(info);
                updateBladeCount(false, true);
                SCOM_FIELD_VOICE::createMercenariesIn(info.m_blade);
            }
        }
        sendOpenEvent(acc.searchSibiling("LAY_form_list_bl"), 0, 0.0f);
        done = true;
        m_seqStep = false;
    }
    return done;
}

bool GfMenuObjMercenaryForm::seqConfirmRemoveBladeSet() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    bool done;
    if (!m_seqStep) {
        unsigned int blade = m_listBlades->getContents(m_listBlades->getIndex(false)).m_blade;
        if (GfMenuObjUtil::isBladeHana(blade)) {
            GfMenuManager::openCommonWindow(0x10F);
        } else {
            GfMenuManager::openCommonWindow(199);
        }
        done = false;
        m_seqStep = true;
    } else if (GfMenuManager::isOpenCommonWindow()) {
        done = false;
    } else {
        short result = GfMenuManager::getCommonWindowResult();
        if (result == 0) {
            unsigned int leave = m_listBlades->getContents(m_listBlades->getIndex(false)).m_blade;
            unsigned short* last = m_bladeIds.end();
            if (std::find(m_bladeIds.begin(), last, static_cast<unsigned short>(leave)) == last) {
                m_bladeIds.push_back(leave);
            }
            unsigned int blade = m_listBlades->getContents(m_listBlades->getIndex(false)).m_blade;
            if (!chkUnitBladeList(blade)) {
                MenuBladeInfo info;
                info.m_blade = blade;
                info.m_creator = GfDataBlade::getCreator(blade);
                m_unitBlades->addContents(info);
                updateBladeCount(false, true);
                SCOM_FIELD_VOICE::createMercenariesIn(info.m_blade);
            }
        }
        sendOpenEvent(acc.searchSibiling("LAY_form_list_bl"), 0, 0.0f);
        done = true;
        m_seqStep = false;
    }
    return done;
}

bool GfMenuObjMercenaryForm::seqReturnMissionSelect() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    bool done;
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(0x9F);
        done = false;
        m_seqStep = true;
    } else if (GfMenuManager::isOpenCommonWindow()) {
        done = false;
    } else {
        short result = GfMenuManager::getCommonWindowResult();
        if (result == 0) {
            if (m_bladeIds.size() != 0) {
                m_seq.addJob(&GfMenuObjMercenaryForm::seqRevertBladeSet);
            } else {
                GfMenuObject::returnFSSubLayer(this);
            }
        } else {
            GfMenuObjMainMenu2::setCloseKeyEnable(true);
            sendOpenEvent(acc.searchSibiling("LAY_form_list_bl"), 0, 0.0f);
        }
        done = true;
        m_seqStep = false;
    }
    return done;
}

void GfMenuObjMercenaryForm::PresetListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 6:
        if (event.m_param0 != -1) {
            m_owner->m_idList->setIndex(event.m_param0);
            m_owner->m_presetSelect->setIndex(m_owner->m_idList->getIndex(true));
            int row = m_owner->m_idList->getRowOffset();
            for (int i = 0; i < 3; i++) {
                GfDataMercenaries::Preset* preset = GfDataMercenaries::getPreset(row + i);
                GfMenuBladeList* list = m_owner->m_presetLists[i];
                MenuBladeInfo info;
                list->clear();
                for (int j = 0; j < 6; j++) {
                    info.m_blade = preset->m_blades[j];
                    info.m_creator = info.m_blade != 0 ? GfDataBlade::getCreator(info.m_blade) : 0;
                    list->addContents(info);
                }
                m_owner->m_numbers[i + 4]->m_value = row + i + 1;
            }
        }
        break;
    case 8:
        if (event.m_param1 == 1) {
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            m_owner->m_seq.clear();
            if (m_load == 0) {
                m_owner->m_seq.addJob(&GfMenuObjMercenaryForm::seqPresetSave);
            } else {
                m_owner->m_seq.addJob(&GfMenuObjMercenaryForm::seqPresetLoad);
            }
        } else if (event.m_param1 == 2) {
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            m_owner->sendCloseEvent(acc.m_handle, 0, 0.0f);
            m_owner->sendOpenEvent(acc.searchSibiling("LAY_form_menu"), 0, 0.0f);
        }
        break;
    case 0x21: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        GfMenuObject::enableFSInput(3);
        GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        m_load = event.m_param0;
        m_owner->m_idList->setIndex(0);
        GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_idList);
        break;
    }
    case 0x22: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjMercenaryForm::ApplyListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        acc.setDisp(true);
        ui::UIObjectAcc base(acc.m_handle, "IMG_form_apply_base");
        base.startAnimation("non", false);
        acc.setDispChild(false, "LAY_form_apply_caption");
        m_open = 0;
        break;
    }
    case 0xC:
        if (m_open == 1) {
            ui::UIObjectAcc base(acc.m_handle, "IMG_form_apply_base");
            base.startAnimation("loop", false);
        }
        break;
    case 0x21:
        if (m_open == 0) {
            ui::UIObjectAcc caption(acc.m_handle, "LAY_form_apply_caption");
            caption.setDisp(true);
            caption.setAlpha(1.0f);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_r";
            param.m_setDefault = true;
            param.m_startFlags = 8;
            GfMenuObjUtil::startCtrl(caption.m_handle, param, nullptr);
            {
                ui::UIObjectAcc base(acc.m_handle, "IMG_form_apply_base");
                base.startAnimation("start", false);
                GfMenuObject::hookAnimationEvent(acc.m_handle, base.m_handle, 0);
            }
            acc.setDisp(true);
            m_open = 1;
        }
        break;
    case 0x22: {
        ui::UIObjectAcc base(acc.m_handle, "IMG_form_apply_base");
        base.startAnimation("non", false);
        {
            ui::UIObjectAcc caption(acc.m_handle, "LAY_form_apply_caption");
            int slot = GfMenuObjUtil::getCtrlID(caption.m_handle);
            if (slot != -1) {
                GfMenuObjUtil::stopCtrl(slot);
            }
            caption.setDisp(false);
        }
        m_open = 0;
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjMercenaryForm::seqPresetSave() {
    bool done;
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(0x43);
        done = false;
        m_seqStep = true;
    } else if (GfMenuManager::isOpenCommonWindow()) {
        done = false;
    } else {
        short result = GfMenuManager::getCommonWindowResult();
        if (result == 0) {
            unsigned int index = m_idList->getIndex(true);
            GfMenuBladeList* list = m_presetLists[index];
            GfDataMercenaries::Preset* preset = GfDataMercenaries::getPreset(index);
            MenuBladeInfo info;
            list->clear();
            for (unsigned int i = 0; i < 6; i++) {
                if (i >= m_unitBlades->getSize()) {
                    break;
                }
                preset->m_blades[i] = m_unitBlades->getContents(i).m_blade;
                info.m_blade = preset->m_blades[i];
                info.m_creator = info.m_blade != 0 ? GfDataBlade::getCreator(info.m_blade) : 0;
                list->addContents(info);
            }
        }
        m_seq.addWait(30);
        m_seq.addJob(&GfMenuObjMercenaryForm::seqPresetEnd);
        done = true;
    }
    return done;
}

bool GfMenuObjMercenaryForm::seqPresetLoad() {
    GfDataMercenaries::Preset* preset = GfDataMercenaries::getPreset(m_idList->getIndex(true));
    MenuBladeInfo info;
    m_unitBlades->clear();
    for (int i = 0; i < 6; i++) {
        unsigned int blade = preset->m_blades[i];
        if (blade != 0 && !GfMenuObjUtil::isBladeSelectable(blade, nullptr)) {
            blade = 0;
        }
        info.m_blade = blade;
        info.m_creator = blade != 0 ? GfDataBlade::getCreator(blade) : 0;
        m_unitBlades->addContents(info);
    }
    m_seq.addJob(&GfMenuObjMercenaryForm::seqPresetEnd);
    return true;
}

void GfMenuObjMercenaryForm::LeaderListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(4);
            GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        } else if (event.m_param0 == 2) {
            m_owner->m_unitBlades->getContents(m_owner->m_unitBlades->getIndex(false));
            for (unsigned int i = 0; i < m_owner->m_unitBlades->getSize(); i++) {
                const MenuBladeInfo& info = m_owner->m_unitBlades->getContents(i);
                if (GfDataBlade::isActivateDriver(info.m_blade)) {
                    unsigned int driver = GfDataBlade::getSetDriver(info.m_blade);
                    int slot = GfDataBlade::getDriverSetID(info.m_blade);
                    if (slot != -1) {
                        GfDataBlade::setEnableEngageRex(info.m_blade, false);
                        SCOM_PARTY_ADD::removeBladeForMenu(driver, slot, true);
                    }
                }
            }
            m_owner->sendOpenEvent(acc.searchSibiling("LAY_start"), 0, 0.0f);
        } else if (event.m_param0 == 3) {
            ui::EventData form;
            form.m_type = 0x103;
            GfMenuObject::sendEvent(acc.searchSibiling("LAY_form"), form, 0.0f);
        }
        break;
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            int prev = event.m_param1;
            m_owner->m_unitBlades->setIndex(index);
            m_owner->m_formSelect->setIndex(index);
            unsigned int blade = m_owner->m_unitBlades->getContents(m_owner->m_unitBlades->getIndex(false)).m_blade;
            bool different = GfMenuObjUtil::isBladeDifferentImage(blade, GfMenuReference::getReferenceBladeID(0));
            GfMenuReference::setReferenceBladeID(
                0, m_owner->m_unitBlades->getContents(m_owner->m_unitBlades->getIndex(false)).m_blade);
            if (prev == -1 || different) {
                ui::UIObjectAcc main(m_owner->m_handle, "LAY_main");
                ui::UIObjectAcc image(main.m_handle, "IMG_leader_bl_img");
                int ctrl = GfMenuObjUtil::getCtrlID(image.m_handle);
                if (ctrl != -1) {
                    GfMenuObjUtil::stopCtrl(ctrl);
                }
                image.setAlpha(0.0f);
                GfMenuObject::sendOpenEvent(main.searchSibiling("LAY_bl_img"), 0, 0.0f);
            }
            if (prev != -1 && index != prev) {
                GfMenuObjUtil::playSECommonCursor();
            }
        }
        break;
    }
    case 8:
        if (event.m_param1 == 1) {
            unsigned int leader = GfDataMercenaries::getBladeWithLeader(GfMenuReference::getReferenceMissionID());
            if (leader != 0 &&
                leader != m_owner->m_unitBlades->getContents(m_owner->m_unitBlades->getIndex(false)).m_blade) {
                GfMenuObjUtil::playSECommon(2);
                break;
            }
            m_owner->m_seq.clear();
            m_owner->m_seq.addJob(&GfMenuObjMercenaryForm::seqConfirmStart);
        } else if (event.m_param1 == 2) {
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 6;
            param.m_out = 1;
            param.m_eventId = 3;
            GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_bl_img"), 0, 0.0f);
            GfGameMercenaries::clearTeamMember(GfMenuReference::getReferenceTeamID());
            GfMenuObjUtil::playSECommonCancel();
        } else {
            break;
        }
        GfMenuObject::disableFSInput();
        GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
        break;
    case 0x21: {
        GfMenuObjOperationInfo::setGuideText(0x26, 0);
        {
        mm::mtl::FixStr<32> name;
        unsigned int leader = GfDataMercenaries::getBladeWithLeader(GfMenuReference::getReferenceMissionID());
        m_owner->m_formSelect->clear();
        for (unsigned int i = 0; i < 6; i++) {
            name.format("LAY_leader_sel_list_bl@%02d", i + 1);
            ui::UIObjectAcc obj(acc.m_handle, name.m_str);
            if (i < m_owner->m_unitBlades->getSize()) {
                m_owner->m_formSelect->addObject(obj.m_handle);
                obj.setDisp(true);
                if (leader != 0) {
                    const char* color = "white";
                    if (leader != m_owner->m_unitBlades->getContents(i).m_blade) {
                        color = "gray";
                    }
                    obj.setMulColor(color);
                }
            } else {
                obj.setDisp(false);
            }
        }
        }
        {
            mm::Rect<short> first;
            acc.getLayoutRect("blade_l_1", first);
            mm::Rect<short> second;
            acc.getLayoutRect("blade_l_2", second);
            GfMenuObjUtil::placeObjectH(m_owner->m_formSelect,
                                        mm::Pnt<short>(first.x + first.w / 2, first.y + first.h / 2),
                                        second.x - first.x);
        }
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        GfMenuObjUtil::playSE(0x10);
        m_owner->m_unitBlades->setIndex(0);
        GfMenuObject::resetInputSelection(acc.m_handle);
        GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_unitBlades);
        m_owner->m_formCursor->setDisp(true);
        break;
    }
    case 0x104:
        if (event.m_param0 == 1) {
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 6;
            param.m_out = 1;
            param.m_eventId = 2;
            GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            GfMenuObjUtil::playJingle(6);
            GfMenuObjMainMenu2::setCloseKeyEnable(false);
        } else {
            GfMenuObject::enableFSInput(4);
            GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjMercenaryForm::BlImgListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 3:
        break;
    case 0x21:
        if (GfMenuReference::getReferenceBladeID(0) != 0) {
            acc.setDisp(true);
            acc.setAlpha(1.0f);
            m_owner->m_subSeq.clear();
            m_owner->m_subSeq.addJob(&GfMenuObjMercenaryForm::seqOpenImage);
        }
        break;
    case 0x22: {
        ui::UIObjectAcc image(acc.m_handle, "IMG_leader_bl_img");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_r";
        param.m_startFlags = 2;
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(image.m_handle, param, nullptr);
        break;
    }
    case 0x100: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "mnu090_anim_leader";
        param.m_motion = "start";
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        GfMenuObjUtil::playSE(0xF);
        break;
    }
    case 0x101: {
        acc.setScale(mm::Vec2(1.0f, 1.0f));
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "mnu090_anim_leader";
        param.m_motion = "end";
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        GfMenuObjUtil::playSE("se_fld_allmap_503");
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjMercenaryForm::seqConfirmStart() {
    ui::UIObjectAcc acc(m_handle, "LAY_leader");
    bool done;
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(0xA0);
        done = false;
        m_seqStep = true;
    } else if (GfMenuManager::isOpenCommonWindow()) {
        done = false;
    } else {
        short result = GfMenuManager::getCommonWindowResult();
        bool yes = result == 0;
        ui::EventData event;
        // stored again although the constructor zeroes it: the original's lone early store of this parameter
        event.m_param2 = 0;
        event.m_type = 0x104;
        event.m_param0 = yes;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        done = true;
        m_seqStep = false;
    }
    return done;
}

bool GfMenuObjMercenaryForm::seqOpenImage() {
    ui::UIObjectAcc image(m_handle, "IMG_leader_bl_img");
    bool done;
    if (!image.isStreaming()) {
        ui::UIObjectAcc layout(m_handle, "LAY_bl_img");
        unsigned int blade = GfMenuReference::getReferenceBladeID(0);
        layout.setLayout(image.m_handle, "character");
        GfMenuObjUtil::ImageParam imageParam;
        if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
            mm::Vec2 scale;
            image.getScale(scale);
            scale.x *= imageParam.m_scale;
            scale.y *= imageParam.m_scale;
            image.setScale(scale);
            GfMenuObjUtil::addPos(image.m_handle, imageParam.m_x, imageParam.m_y);
        }
        image.setAlpha(1.0f);
        GfMenuObjUtil::CtrlParam fade;
        fade.m_methods = 0x10000000;
        fade.m_motionLib = "cmn_fade_motion_lr";
        fade.m_motion = "fade_in_r";
        fade.m_startFlags = 8;
        fade.m_setDefault = true;
        GfMenuObjUtil::startCtrl(image.m_handle, fade, nullptr);
        image.setAlpha(0.0f);
        GfMenuObjUtil::playSE("se_fld_allmap_503");
        done = true;
    } else {
        image.setAlpha(0.0f);
        done = false;
    }
    return done;
}

void GfMenuObjMercenaryForm::StartListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 0x21: {
        // the selected team blade moves to the top (its copy's slot is reused by the names below)
        {
            MenuBladeInfo info = m_owner->m_unitBlades->getContents(m_owner->m_unitBlades->getIndex(false));
            {
                GfMenuBladeList* list = m_owner->m_unitBlades;
                unsigned int index = list->getIndex(false);
                list->m_list.erase(list->m_list.begin() + index);
                list->subSize(1);
                list->m_changed = true;
            }
            GfMenuBladeList* list = m_owner->m_unitBlades;
            if (list->getSize() == 0) {
                list->addContents(info);
            } else {
                list->m_list.insert(list->m_list.begin(), info);
                list->addSize(1);
                list->m_changed = true;
            }
        }
        mm::mtl::FixStr<32> name;
        m_owner->m_unitSelect->clear();
        for (unsigned int i = 0; i < 5; i++) {
            if (i < m_owner->m_unitBlades->getSize() - 1) {
                name.format("LAY_mis_start_bl@%02d", i + 1);
                m_owner->m_unitSelect->addObject(acc.searchChild(name.m_str));
            }
            acc.setDispChild(false, name.m_str);
        }
        acc.setDisp(true);
        m_owner->m_seq.clear();
        m_owner->m_seq.addJob(&GfMenuObjMercenaryForm::seqDepartureStart);
        break;
    }
    case 0x22: {
        GfMenuObjMercenaryTop::OpenParam param;
        param.m_value = 0;
        GfMenuObjMercenaryTop::registOpenParam(param);
        GfMenuObject::returnFSSubLayer(acc.m_handle, 2);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjMercenaryForm::seqDepartureStart() {
    m_seqStep = false;
    m_seq.addJob(&GfMenuObjMercenaryForm::seqApperBlade);
    m_voice = SCOM_FIELD_VOICE::createMercenariesLeader(GfMenuReference::getReferenceBladeID(0));
    m_voiceStopped = false;
    return true;
}

bool GfMenuObjMercenaryForm::seqApperBlade() {
    if (m_voice != nullptr) {
        if (GfMenuObjUtil::isVoiceSkip()) {
            GfGameVoice::playStop(m_voice);
            m_voice = nullptr;
            m_voiceStopped = true;
        } else if (m_voice != nullptr) {
            if (GfGameVoice::getResult(m_voice) >= 3) {
                m_voice = nullptr;
            } else {
                return false;
            }
        }
    }
    ui::UIObjectAcc image(m_handle, "LAY_bl_img");
    bool done;
    if (!m_seqStep) {
        {
            ui::EventData event;
            event.m_type = 0x100;
            GfMenuObject::sendEvent(image.m_handle, event, 0.0f);
        }
        {
            ui::UIObjectAcc start(m_handle, "LAY_start");
            mm::mtl::FixStr<32> name;
            mm::mtl::FixStr<32> motion;
            for (unsigned int i = 0; i < m_unitSelect->getSize(); i++) {
                unsigned int blade = m_unitBlades->getContents(i + 1).m_blade;
                name.format("IMG_mis_start_bl@%02d", i + 1);
                {
                    ui::UIObjectAcc face(start.m_handle, name.m_str);
                    start.setLayout(face.m_handle, "mnu090_anim_sub_1");
                    GfMenuObjUtil::ImageParam imageParam;
                    if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
                        mm::Vec2 scale;
                        face.getScale(scale);
                        scale.x *= imageParam.m_scale;
                        scale.y *= imageParam.m_scale;
                        face.setScale(scale);
                        GfMenuObjUtil::addPos(face.m_handle, imageParam.m_x, imageParam.m_y);
                    }
                }
                motion.format("mnu090_anim_sub_%d", i + 1);
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = motion.m_str;
                param.m_motion = "start";
                GfMenuObjUtil::startCtrl(m_unitSelect->getObject(i), param, nullptr);
            }
        }
        done = false;
        m_leaveRequest = false;
        m_seqStep = true;
    } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(image.m_handle))) {
        if (!m_voiceStopped) {
            m_leaveVoice = SCOM_FIELD_VOICE::createMercenariesStart(m_unitBlades->getContents(0).m_blade);
            m_leaveRequest = true;
            m_seq.addWait(60);
        }
        m_seq.addJob(&GfMenuObjMercenaryForm::seqLeaveBlade);
        done = true;
        m_seqStep = false;
    } else {
        done = false;
    }
    return done;
}

bool GfMenuObjMercenaryForm::seqDepartureEnd() {
    bool done;
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(0x25);
        done = false;
        m_seqStep = true;
    } else if (GfMenuManager::isOpenCommonWindow()) {
        done = false;
    } else {
        ui::UIObjectAcc start(m_handle, "LAY_start");
        sendCloseEvent(start.m_handle, 0, 0.0f);
        unsigned int teamId = GfMenuReference::getReferenceTeamID();
        unsigned int mission = GfMenuReference::getReferenceMissionID();
        for (unsigned int i = 0; i < m_unitBlades->getSize(); i++) {
            GfGameMercenaries::addTeamMember(teamId, m_unitBlades->getContents(i).m_blade);
        }
        GfGameMercenaries::orderMission(teamId, mission);
        done = true;
    }
    return done;
}

// 2.0.0's (name from its symbols); 3.0.1's linker dropped it as unused, leaving its strings in this file's .rodata.
bool GfMenuObjMercenaryForm::seqStartActiveFS() {
    ui::UIObjectAcc base(m_handle, "IMG_start_fs_base");
    bool done;
    if (!m_seqStep) {
        ui::UIObjectAcc layout(m_handle, "LAY_start_fs");
        layout.setDisp(true);
        base.startAnimation("start", false);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_r";
        GfMenuObjUtil::startCtrl(m_handle, param, "LAY_start_fs_on");
        m_seqStep = true;
        done = false;
    } else if (!base.isPlayingAnimation()) {
        m_seqStep = false;
        m_seq.addJob(&GfMenuObjMercenaryForm::seqOpenActiveFS);
        done = true;
    } else {
        done = false;
    }
    return done;
}

// 2.0.0's (name from its symbols); 3.0.1's linker dropped it as unused.
bool GfMenuObjMercenaryForm::seqOpenActiveFS() {
    ui::UIObjectAcc base(m_handle, "IMG_start_fs_base");
    bool done;
    if (!m_seqStep) {
        ui::UIObjectAcc layout(m_handle, "LAY_start_fs");
        layout.setDispChild(false, "LAY_start_fs_on");
        base.startAnimation("result", false);
        m_seqStep = true;
        done = false;
    } else if (!base.isPlayingAnimation()) {
        m_seqStep = false;
        m_seq.addJob(&GfMenuObjMercenaryForm::seqDispActiveFS);
        done = true;
    } else {
        done = false;
    }
    return done;
}

// 2.0.0's (name from its symbols); 3.0.1's linker dropped it as unused, leaving its strings in this file's .rodata.
bool GfMenuObjMercenaryForm::seqDispActiveFS() {
    ui::UIObjectAcc base(m_handle, "IMG_start_fs_base");
    bool done;
    if (!m_seqStep) {
        base.startAnimation("fade_in_info", false);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_r";
        GfMenuObjUtil::startCtrl(m_handle, param, "LAY_start_fs_info");
        done = false;
        m_seqStep = true;
    } else if (!base.isPlayingAnimation()) {
        m_seq.addWait(90);
        m_seq.addJob(&GfMenuObjMercenaryForm::seqEndActiveFS);
        done = true;
    } else {
        done = false;
    }
    return done;
}

// 2.0.0's (name from its symbols); 3.0.1's linker dropped it as unused.
bool GfMenuObjMercenaryForm::seqEndActiveFS() {
    ui::UIObjectAcc layout(m_handle, "LAY_start_fs");
    layout.setDisp(false);
    m_seq.addJob(&GfMenuObjMercenaryForm::seqLeaveBlade);
    return true;
}

bool GfMenuObjMercenaryForm::seqPresetEnd() {
    ui::UIObjectAcc preset(m_handle, "LAY_preset");
    sendCloseEvent(preset.m_handle, 0, 0.0f);
    sendOpenEvent(preset.searchSibiling("LAY_form_menu"), 0, 0.0f);
    return true;
}

bool GfMenuObjMercenaryForm::seqRevertBladeSet() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    bool done;
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(200);
        done = false;
        m_seqStep = true;
    } else if (GfMenuManager::isOpenCommonWindow()) {
        done = false;
    } else {
        GfMenuObject::returnFSSubLayer(this);
        done = true;
        m_seqStep = false;
    }
    return done;
}
}  // namespace gf
