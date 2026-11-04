#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/gf/GfMenuObjCmnStatus/CharStatusListener.h"
#include "classes/gf/GfMenuObjCmnStatus/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuDiffAdapter.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/ui/UICtrlRadarGraph.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"

namespace gf {

bool GfMenuObjCmnStatus::s_DispFlag[2];
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAA1E2)
bool GfMenuObjCmnStatus::s_DispTeamName;

GfMenuObjCmnStatus::GfMenuObjCmnStatus(unsigned int handle)
    : GfMenuObject(handle), m_paramLists(), m_ideaGraph(nullptr) {
    ui::UISelectObjList::CreateParam create;
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_paramLists[0] = ui::UISelectObjList::create(create);
    create = ui::UISelectObjList::CreateParam();
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_paramLists[1] = ui::UISelectObjList::create(create);
    s_DispTeamName = false;
}

GfMenuObjCmnStatus::~GfMenuObjCmnStatus() {
    if (m_paramLists[0] != nullptr) {
        m_paramLists[0]->release();
        m_paramLists[0] = nullptr;
    }
    if (m_paramLists[1] != nullptr) {
        m_paramLists[1]->release();
        m_paramLists[1] = nullptr;
    }
    if (m_ideaGraph != nullptr) {
        m_ideaGraph->release();
        m_ideaGraph = nullptr;
    }
}

void GfMenuObjCmnStatus::openDrStatus(unsigned int param0, int param1) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x52));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0 = param0;
        event.m_param1 = param1;
        GfMenuObject::sendEvent(acc.searchChild("LAY_status_dr"), event, 0.0f);
        s_DispFlag[0] = true;
    }
}

void GfMenuObjCmnStatus::closeDrStatus() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x52));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(acc.searchChild("LAY_status_dr"), event, 0.0f);
        s_DispFlag[0] = false;
    }
}

bool GfMenuObjCmnStatus::swapDrStatus() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x52));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc page(acc.m_handle, "LAY_status_dr");
        ui::EventData event;
        event.m_type = 0x102;
        GfMenuObject::sendEvent(page.m_handle, event, 0.0f);
        s_DispFlag[0] = !s_DispFlag[0];
        return s_DispFlag[0];
    }
    return false;
}

bool GfMenuObjCmnStatus::isOpenDrStatus() {
    return s_DispFlag[0];
}

void GfMenuObjCmnStatus::openBlStatus(unsigned int param0, int param1) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x52));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0 = param0;
        event.m_param1 = param1;
        GfMenuObject::sendEvent(acc.searchChild("LAY_status_bl"), event, 0.0f);
        s_DispFlag[1] = true;
    }
}

void GfMenuObjCmnStatus::closeBlStatus() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x52));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(acc.searchChild("LAY_status_bl"), event, 0.0f);
        s_DispFlag[1] = false;
    }
}

bool GfMenuObjCmnStatus::swapBlStatus() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x52));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc page(acc.m_handle, "LAY_status_bl");
        ui::EventData event;
        event.m_type = 0x102;
        GfMenuObject::sendEvent(page.m_handle, event, 0.0f);
        s_DispFlag[1] = !s_DispFlag[1];
        return s_DispFlag[1];
    }
    return false;
}

bool GfMenuObjCmnStatus::isOpenBlStatus() {
    return s_DispFlag[1];
}

void GfMenuObjCmnStatus::setInputEnable() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x52));
    if (acc.m_object != nullptr) {
        GfMenuObject::enableInput(acc.m_handle);
    }
}

void GfMenuObjCmnStatus::setInputDisable() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x52));
    if (acc.m_object != nullptr) {
        GfMenuObject::disableInput(acc.m_handle);
    }
}

void GfMenuObjCmnStatus::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x52, acc.m_handle);
#line 247
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
#line 250
    CharStatusListener* dr = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) CharStatusListener(this);
    dr->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.searchChild("LAY_status_dr"), dr);
    if (dr != nullptr) {
        dr->release();
    }
#line 253
    CharStatusListener* bl = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) CharStatusListener(this);
    bl->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.searchChild("LAY_status_bl"), bl);
    if (bl != nullptr) {
        bl->release();
    }
    GfMenuObject::initialize();
}

void GfMenuObjCmnStatus::finalize() {
    GfMenuReference::resetDriverVirtual();
    GfMenuReference::resetBladeVirtual();
    GfMenuObject::finalize();
}

void GfMenuObjCmnStatus::update() {
    GfMenuObject::update();
}

void GfMenuObjCmnStatus::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 0x101: {
        // the object to move the input to, the selected index and the selection's kind (the names are not the
        // original's)
        unsigned int object = event.m_param0;
        int index = event.m_param1;
        int kind = event.m_param2;
        if (object != 0) {
            GfMenuObject::enableInput(acc.m_handle);
            if (kind == 1) {
                GfMenuObject::setupInputSelection(acc.m_handle, 0, index);
            }
        } else {
            GfMenuObject::disableInput(acc.m_handle);
        }
        GfMenuObject::migrateInput(acc.m_handle, object);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjCmnStatus::updateBladeBase(unsigned int id) {
    bool sk = id >= 2 && id <= 6;
    ui::UIObjectAcc index(m_handle, "LAY_status_bl_index");
    ui::UIObjectAcc indexSk(m_handle, "LAY_status_bl_index_sk");
    ui::UIObjectAcc base(m_handle, "IMG_status_bl_base");
    ui::UIObjectAcc baseSk(m_handle, "IMG_status_bl_base_sk");
    index.setDisp(!sk);
    base.setDisp(!sk);
    indexSk.setDisp(sk);
    baseSk.setDisp(sk);
}

void GfMenuObjCmnStatus::setDrPageParam(unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_hp"), 0x0, 0, true);
    {
        GfMenuCharDataAdapter* now =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_r_hp"), 0x0, 0, true);
        GfMenuCharDataAdapter* next =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_l_hp"), 0x0, 0, true);
        if (next != nullptr) {
            next->m_virtualMode = 1;
        }
        GfMenuDiffAdapter::create(acc.searchChild("LAY_status_dr_param_now_hp"), now, next, 3, true);
        GfMenuDiffAdapter::create(acc.searchChild("LAY_status_dr_param_dif_hp"), now, next, 4, true);
        GfMenuDiffAdapter::create(acc.searchChild("TXT_status_dr_param_l_hp"), now, next, 1, true);
    }
    GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_str"), 0xD, 0, true);
    {
        GfMenuCharDataAdapter* now =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_r_str"), 0xD, 0, true);
        GfMenuCharDataAdapter* next =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_l_str"), 0xD, 0, true);
        if (next != nullptr) {
            next->m_virtualMode = 1;
        }
        GfMenuDiffAdapter::create(acc.searchChild("LAY_status_dr_param_now_str"), now, next, 3, true);
        GfMenuDiffAdapter::create(acc.searchChild("LAY_status_dr_param_dif_str"), now, next, 4, true);
        GfMenuDiffAdapter::create(acc.searchChild("TXT_status_dr_param_l_str"), now, next, 1, true);
    }
    GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_eth"), 0xE, 0, true);
    {
        GfMenuCharDataAdapter* now =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_r_eth"), 0xE, 0, true);
        GfMenuCharDataAdapter* next =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_l_eth"), 0xE, 0, true);
        if (next != nullptr) {
            next->m_virtualMode = 1;
        }
        GfMenuDiffAdapter::create(acc.searchChild("LAY_status_dr_param_now_eth"), now, next, 3, true);
        GfMenuDiffAdapter::create(acc.searchChild("LAY_status_dr_param_dif_eth"), now, next, 4, true);
        GfMenuDiffAdapter::create(acc.searchChild("TXT_status_dr_param_l_eth"), now, next, 1, true);
    }
    GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_dex"), 0xF, 0, true);
    {
        GfMenuCharDataAdapter* now =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_r_dex"), 0xF, 0, true);
        GfMenuCharDataAdapter* next =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_l_dex"), 0xF, 0, true);
        if (next != nullptr) {
            next->m_virtualMode = 1;
        }
        GfMenuDiffAdapter::create(acc.searchChild("LAY_status_dr_param_now_dex"), now, next, 3, true);
        GfMenuDiffAdapter::create(acc.searchChild("LAY_status_dr_param_dif_dex"), now, next, 4, true);
        GfMenuDiffAdapter::create(acc.searchChild("TXT_status_dr_param_l_dex"), now, next, 1, true);
    }
    GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_agl"), 0x10, 0, true);
    {
        GfMenuCharDataAdapter* now =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_r_agl"), 0x10, 0, true);
        GfMenuCharDataAdapter* next =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_l_agl"), 0x10, 0, true);
        if (next != nullptr) {
            next->m_virtualMode = 1;
        }
        GfMenuDiffAdapter::create(acc.searchChild("LAY_status_dr_param_now_agl"), now, next, 3, true);
        GfMenuDiffAdapter::create(acc.searchChild("LAY_status_dr_param_dif_agl"), now, next, 4, true);
        GfMenuDiffAdapter::create(acc.searchChild("TXT_status_dr_param_l_agl"), now, next, 1, true);
    }
    GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_lck"), 0x11, 0, true);
    {
        GfMenuCharDataAdapter* now =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_r_lck"), 0x11, 0, true);
        GfMenuCharDataAdapter* next =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_l_lck"), 0x11, 0, true);
        if (next != nullptr) {
            next->m_virtualMode = 1;
        }
        GfMenuDiffAdapter::create(acc.searchChild("LAY_status_dr_param_now_lck"), now, next, 3, true);
        GfMenuDiffAdapter::create(acc.searchChild("LAY_status_dr_param_dif_lck"), now, next, 4, true);
        GfMenuDiffAdapter::create(acc.searchChild("TXT_status_dr_param_l_lck"), now, next, 1, true);
    }
    GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_exp"), 0x13, 0, true);
    {
        GfMenuCharDataAdapter* now =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_exp_n"), 0x14, 0, true);
        GfMenuCharDataAdapter* next =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_status_dr_param_l_exp_n"), 0x23, 0, true);
        GfMenuDiffAdapter::create(acc.searchChild("LAY_status_dr_param_now_exp_n"), now, next, 3, true);
        GfMenuDiffAdapter::create(acc.searchChild("LAY_status_dr_param_diff_exp_n"), now, next, 4, true);
    }
    {
        mm::mtl::FixStr<32> name;
        for (int i = 1; i < 4; i++) {
            int slot = i - 1;
            name.format("TXT_status_dr_param_bl_name@%02d", i);
            GfMenuCharDataAdapter* blade = GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.m_str), 2, 0, slot, true);
            if (blade != nullptr) {
                name.format("LAY_status_dr_param_bl@%02d", i);
                blade->m_rowHandle = acc.searchChild(name.m_str);
            }
            name.format("TXT_status_dr_param_bl_comp@%02d", i);
            GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.m_str), 0x4D, 0, slot, true);
            name.format("TXT_status_dr_param_bl_role@%02d", i);
            GfMenuCharDataAdapter::createFromReferenceBladeSet(acc.searchChild(name.m_str), 0x41, 0, slot, true);
        }
    }
    {
        mm::mtl::FixStr<32> name;
        {
            ui::UICtrlRadarGraph::Setting setting = {};
            m_ideaGraph = ui::UICtrlRadarGraph::create(acc.searchChild("POL_status_dr_idea_graph"), setting);
        }
        for (int i = 0; i < 4; i++) {
            name.format("TXT_status_dr_idea_lv@%02d", i + 1);
            GfMenuCharDataAdapter* lv = GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild(name.m_str), 0x22, 0, true);
            if (lv != nullptr) {
                lv->m_index = i;
            }
            if (m_ideaGraph != nullptr) {
                m_ideaGraph->setNumberPlugin(i, acc.searchChild(name.m_str));
            }
            name.format("TXT_status_dr_idea_lv_index@%02d", i + 1);
            ui::UIObjectAcc index(acc.m_handle, name.m_str);
            if (index.m_object != nullptr) {
                ui::UIStr text(GfDataBdat::getFP(0x126), i + 1);
                index.setText(text);
            }
        }
    }
}

void GfMenuObjCmnStatus::setIraFrontMode(bool disp) {
    s_DispTeamName = disp;
}

void GfMenuObjCmnStatus::updateDriverBase(unsigned int id) {
    bool sk = id == 4 || id == 5;
    ui::UIObjectAcc index(m_handle, "LAY_status_dr_index");
    ui::UIObjectAcc indexSk(m_handle, "LAY_status_dr_index_sk");
    ui::UIObjectAcc base(m_handle, "IMG_status_dr_base");
    ui::UIObjectAcc baseSk(m_handle, "IMG_status_dr_base_sk");
    index.setDisp(!sk);
    base.setDisp(!sk);
    indexSk.setDisp(sk);
    baseSk.setDisp(sk);
}

}  // namespace gf
