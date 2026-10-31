#include "classes/gf/GfMenuObjEnBook.h"
#include "classes/gf/GfMenuObjEnBook/DetailListener.h"
#include "classes/gf/GfMenuObjEnBook/EnListListener.h"
#include "classes/gf/GfMenuObjEnBook/FamilySelListener.h"
#include "classes/gf/GfMenuObjEnBook/GenusSelListener.h"
#include "classes/gf/GfMenuObjEnBook/IndexListener.h"
#include "classes/gf/GfMenuObjEnBook/LocationSelListener.h"
#include "classes/gf/GfMenuObjEnBook/MainListener.h"
#include "classes/gf/GfMenuObjEnBook/TopListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuModelView.h"
#include "classes/gf/GfMenuMsgList.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfDataEnBook.h"
#include "gf/GfDataEnemy.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjEnBook::GfMenuObjEnBook(unsigned int handle)
    : GfMenuObject(handle), m_listMode(0), m_family(0), m_genus(0), pad_30(nullptr), pad_38(nullptr), m_familyList(nullptr),
      pad_48(nullptr), m_genusList(nullptr), pad_58(nullptr), pad_60(nullptr), m_enBookList(nullptr), pad_70(nullptr),
      pad_78(nullptr), m_modelView(nullptr), pad_88(0), m_seq(this), pad_320(false) {
    m_familyList = GfMenuMsgList::create();
    m_genusList = GfMenuMsgList::create();
    pad_60 = GfMenuIDList::create();
    m_enBookList = GfMenuIDList::create();
}

GfMenuObjEnBook::~GfMenuObjEnBook() {
    if (pad_78 != nullptr) {
        pad_78->release();
        pad_78 = nullptr;
    }
    if (pad_70 != nullptr) {
        pad_70->release();
        pad_70 = nullptr;
    }
    if (m_enBookList != nullptr) {
        m_enBookList->release();
        m_enBookList = nullptr;
    }
    if (pad_60 != nullptr) {
        pad_60->release();
        pad_60 = nullptr;
    }
    if (pad_58 != nullptr) {
        pad_58->release();
        pad_58 = nullptr;
    }
    if (m_genusList != nullptr) {
        m_genusList->release();
        m_genusList = nullptr;
    }
    if (pad_48 != nullptr) {
        pad_48->release();
        pad_48 = nullptr;
    }
    if (m_familyList != nullptr) {
        m_familyList->release();
        m_familyList = nullptr;
    }
    if (pad_38 != nullptr) {
        pad_38->release();
        pad_38 = nullptr;
    }
    if (pad_30 != nullptr) {
        pad_30->release();
        pad_30 = nullptr;
    }
}

void GfMenuObjEnBook::setupFamilyMsgList() {
    ui::UIObjectAcc acc(m_handle, "LAY_type_sel_cate");
    unsigned char* bdat = m_familyList->m_dataBdat;
    {
        unsigned int rows = acc.countChild("LAY_type_sel_cate_item@%02d", 1);
        ui::UIListInfoBase::SetupParam param;
        param.m_pageRowSize = rows;
        param.m_pageScroll = true;
        m_familyList->setup(getAllocator(ALLOCATOR(0)), param);
    }
    m_familyList->clear();
    for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
        MsgID id = MsgID();
        id.m_id = Bdat::getIdTop(bdat) + i;
        m_familyList->addContents(id);
    }
}

bool GfMenuObjEnBook::seqWaitLoading() {
    return !m_modelView->isLoading();
}

bool GfMenuObjEnBook::seqStartTop() {
    ui::UIObjectAcc acc(m_handle, "LAY_top");
    GfMenuObject::sendOpenEvent(acc.m_handle, 0, 0.0f);
    return true;
}

void GfMenuObjEnBook::finalize() {
    if (m_modelView != nullptr) {
        delete m_modelView;
        m_modelView = nullptr;
    }
    GfMenuObject::finalize();
}

void GfMenuObjEnBook::update() {
    m_seq.update();
    if (m_modelView != nullptr) {
        m_modelView->update();
    }
    GfMenuObject::update();
}

void GfMenuObjEnBook::refreshFamilyList() {
    ui::UIStr text;
    mm::mtl::FixStr<32> name;
    unsigned int index = m_familyList->getIndex(true);
    for (unsigned int i = 0; i < pad_48->getSize(); i++) {
        ui::UIObjectAcc acc(pad_48->getObject(i));
        if (i < m_familyList->getSize()) {
            acc.setDisp(true);
            m_familyList->getMsg(i, text, true);
            name.format("TXT_type_sel_cate_item@%02d", i + 1);
            ui::UIObjectAcc child(acc.m_handle, name.m_str);
            child.setText(text);
            if (i == index) {
                GfMenuObjUtil::setColMulandAdd(child.m_handle, "txt_highlight");
            } else {
                child.loadDefColor();
            }
        } else {
            acc.setDisp(false);
        }
    }
}

void GfMenuObjEnBook::setupGenusMsgList() {
    unsigned char* bdat = GfDataBdat::getFP(0x28);
    if (bdat == nullptr) {
        return;
    }
    int top = Bdat::getIdTop(bdat);
    {
        ui::UIListInfoBase::SetupParam param;
        param.m_pageRowSize = pad_58->getSize();
        param.m_pageScroll = true;
        m_genusList->setup(getAllocator(ALLOCATOR(0)), param);
    }
    m_genusList->clear();
    GfBdatRsc* rsc = GfBdatRsc::get();
    for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
        unsigned long enemy = Bdat::getVal(bdat, "BaseEnemyID", top + i);  // a u16 column
        if (static_cast<unsigned short>(enemy)) {
            unsigned int rscId = GfDataEnemy::getRscIdByArrangeId(static_cast<unsigned short>(enemy));
            if (rsc->getRscEnTypeFamily(rscId) == m_family) {
                unsigned int genus = rsc->getRscEnTypeGenus(rscId);
                MsgID id = MsgID();
                id.m_id = rsc->getRscEnGenusNAME(genus);
                bool found = false;
                for (unsigned int j = 0; j < m_genusList->getSize(); j++) {
                    if (m_genusList->getContents(j).m_id == id.m_id) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    m_genusList->addContents(id);
                }
            }
        }
    }
}

void GfMenuObjEnBook::refreshGenusMsgList() {
    ui::UIStr text;
    mm::mtl::FixStr<32> name;
    unsigned int index = m_genusList->getIndex(true);
    for (unsigned int i = 0; i < pad_58->getSize(); i++) {
        ui::UIObjectAcc acc(pad_58->getObject(i));
        if (i < m_genusList->getSize()) {
            acc.setDisp(true);
            m_genusList->getMsg(i, text, true);
            name.format("TXT_type_sel_fam_item@%02d", i + 1);
            ui::UIObjectAcc child(acc.m_handle, name.m_str);
            child.setText(text);
            if (i == index) {
                GfMenuObjUtil::setColMulandAdd(child.m_handle, "txt_highlight");
            } else {
                child.loadDefColor();
            }
        } else {
            acc.setDisp(false);
        }
    }
}

void GfMenuObjEnBook::setupEnBookIDList() {
    m_enBookList->clear();
    switch (m_listMode) {
    case 0: {
        unsigned char* bdat = GfDataBdat::getFP(0x28);
        int top = Bdat::getIdTop(bdat);
        for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
            MenuID id;
            id.m_id = top + i;
            id.m_subId = 0;
            unsigned long enemy = Bdat::getVal(bdat, "BaseEnemyID", id.m_id);  // a u16 column
            if (static_cast<unsigned short>(enemy) &&
                GfDataEnemy::getRscIdByArrangeId(static_cast<unsigned short>(enemy)) != 0) {
                m_enBookList->addContents(id);
            }
        }
        break;
    }
    case 1: {
        GfBdatRsc* rsc = GfBdatRsc::get();
        unsigned char* bdat = GfDataBdat::getFP(0x28);
        int top = Bdat::getIdTop(bdat);
        for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
            MenuID id;
            id.m_id = top + i;
            id.m_subId = 0;
            unsigned long enemy = Bdat::getVal(bdat, "BaseEnemyID", id.m_id);  // a u16 column
            if (static_cast<unsigned short>(enemy)) {
                unsigned int rscId = GfDataEnemy::getRscIdByArrangeId(static_cast<unsigned short>(enemy));
                if (rscId != 0 && rsc->getRscEnTypeFamily(rscId) == m_family &&
                    rsc->getRscEnGenusNAME(rsc->getRscEnTypeGenus(rscId)) == m_genus) {
                    m_enBookList->addContents(id);
                }
            }
        }
        break;
    }
    }
}

void GfMenuObjEnBook::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
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

void GfMenuObjEnBook::TopListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObjOperationInfo::setGuideText(0x3A, 0);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(0);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->pad_30);
        }
        break;
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            mm::mtl::FixStr<32> name;
            if (event.m_param1 != -1) {
                name.format("IMG_top_item_base@%02d", event.m_param1 + 1);
                ui::UIObjectAcc(acc.m_handle, name.m_str).startAnimation("idol", false);
            }
            m_owner->pad_30->setIndex(index);
            name.format("IMG_top_item_base@%02d", index + 1);
            ui::UIObjectAcc(acc.m_handle, name.m_str).startAnimation("sellect", false);
        }
        break;
    }
    case 8:
        if (event.m_param1 == 1) {
            int mode = event.m_param0;
            m_owner->m_listMode = mode;
            if (mode == 0) {
                GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(4), 0, 0.0f);
            } else if (mode == 1) {
                GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(1), 0, 0.0f);
            } else if (mode == 2) {
                GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(3), 0, 0.0f);
            } else {
                break;
            }
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            GfMenuObject::disableFSInput();
        } else if (event.m_param1 == 2) {
            GfMenuObject::returnFSSubLayer(m_owner);
        } else {
            break;
        }
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        break;
    case 0x21: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
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

void GfMenuObjEnBook::IndexListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 0x21: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
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

void GfMenuObjEnBook::FamilySelListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(1);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_familyList);
        }
        break;
    case 6:
        if (event.m_param0 != -1) {
            m_owner->m_familyList->setIndex(event.m_param0);
            m_owner->refreshFamilyList();
        }
        break;
    case 8:
        if (event.m_param1 == 1) {
            GfMenuMsgList* list = m_owner->m_familyList;
            m_owner->m_family = list->getContents(list->getIndex(false)).m_id - 1;
            GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(2), 0, 0.0f);
        } else if (event.m_param1 == 2) {
            GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(0), 0, 0.0f);
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        }
        break;
    case 0x21: {
        int from = event.m_param0;  // the name is not the original's
        switch (from) {
        default: {
            int eventId = 0;
            if (from != 4) {
                m_owner->m_familyList->setIndex(0);
                m_owner->refreshFamilyList();
                eventId = 1;
            }
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 6;
            param.m_out = 0;
            param.m_eventId = eventId;
            GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            break;
        }
        case 2:
            GfMenuObject::enableFSInput(1);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            break;
        }
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

void GfMenuObjEnBook::GenusSelListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(2);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_genusList);
        }
        break;
    case 6:
        if (event.m_param0 != -1) {
            m_owner->m_genusList->setIndex(event.m_param0);
            m_owner->refreshGenusMsgList();
        }
        break;
    case 8:
        if (event.m_param1 == 1) {
            GfMenuMsgList* list = m_owner->m_genusList;
            m_owner->m_genus = list->getContents(list->getIndex(false)).m_id;
            GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(4), 2, 0.0f);
            GfMenuObject::sendCloseEvent(GfMenuObject::getFSInputObject(1), 0, 0.0f);
        } else if (event.m_param1 == 2) {
            GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(1), 2, 0.0f);
        } else {
            break;
        }
        GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
        GfMenuObject::disableFSInput();
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        break;
    case 0x21: {
        int from = event.m_param0;  // the name is not the original's
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        if (from != 4) {
            m_owner->setupGenusMsgList();
            m_owner->refreshGenusMsgList();
        }
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

void GfMenuObjEnBook::LocationSelListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
    case 8:
        break;
    case 0x21: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
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

void GfMenuObjEnBook::DetailListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(5);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            GfMenuIDList* list = m_owner->m_enBookList;
            unsigned int id = list->getContents(list->getIndex(false)).m_id;
            bool defeated = false;
            unsigned char* bdat = GfDataBdat::getFP(0x28);
            if (bdat != nullptr) {
                unsigned long enemy = Bdat::getVal(bdat, "BaseEnemyID", id);  // a u16 column
                defeated = GfDataEnBook::getDefeatNum(static_cast<unsigned short>(enemy)) != 0;
            }
            if (defeated) {
                GfMenuObject::setupInputSelection(acc.m_handle, 0, m_owner->pad_78->getSize());
            } else {
                GfMenuObject::setupInputSelection(acc.m_handle, 0, m_owner->pad_78->getSize() - 1);
            }
        }
        break;
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            if (event.m_param1 != -1) {
                ui::UIObjectAcc old(m_owner->pad_78->getObject(event.m_param1));
                old.setDisp(false);
            }
            m_owner->pad_78->setIndex(index);
            ui::UIObjectAcc select(m_owner->pad_78->getSelectObject());
            select.setDisp(true);
        }
        break;
    }
    case 8:
        if (event.m_param1 == 2) {
            ui::EventData open(0x100);
            GfMenuObject::sendEvent(GfMenuObject::getFSInputObject(4), open, 0.0f);
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        }
        break;
    case 0x21: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        m_owner->pad_78->setIndex(0);
        ui::UIObjectAcc select(m_owner->pad_78->getSelectObject());
        select.setDisp(true);
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

}  // namespace gf
