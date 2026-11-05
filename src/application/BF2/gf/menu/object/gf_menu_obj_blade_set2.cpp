#include "classes/gf/GfMenuObjBladeSet2.h"
#include "classes/gf/GfMenuObjBladeSet2/MainListener.h"
#include "classes/gf/GfMenuObjBladeSet2/BladeSlotListener.h"
#include "classes/gf/GfMenuObjBladeSet2/BladeListListener.h"
#include "classes/gf/GfMenuObjBladeSet2.h"
#include "classes/gf/GfMenuObjBladeSet2/MainListener.h"
#include "classes/gf/GfMenuObjBladeSet2/BladeSlotListener.h"
#include "classes/gf/GfMenuObjBladeSet2/BladeListListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "ui/EventData.h"
#include "mm/mtl/Delegate.h"
#include "gf/GfMenuSequence.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfDataBlade.h"
#include "gf/GfReqParam.h"
#include "mm/Vec2.h"
#include "mm/mtl/FixStr.h"

namespace gf {

GfMenuObjBladeSet2::GfMenuObjBladeSet2(unsigned int handle)
    : GfMenuObject(handle), m_slotList(nullptr), pad_30(nullptr), m_bladeList(nullptr), pad_40(nullptr),
      m_driverList(nullptr), pad_50(nullptr), pad_58(0), m_context(nullptr), pad_68(0), pad_78(false),
      m_subContext(nullptr), pad_88(false), pad_8C(0), pad_90(0), pad_94(0), m_openType(0),
      m_seq(this), m_subSeq(this) {}

GfMenuObjBladeSet2::~GfMenuObjBladeSet2() {
    if (m_subContext != nullptr) {
        m_subContext->release();
        m_subContext = nullptr;
    }
    if (m_slotList != nullptr) {
        m_slotList->release();
        m_slotList = nullptr;
    }
    if (pad_30 != nullptr) {
        pad_30->release();
        pad_30 = nullptr;
    }
    if (m_bladeList != nullptr) {
        m_bladeList->release();
        m_bladeList = nullptr;
    }
    if (pad_40 != nullptr) {
        pad_40->release();
        pad_40 = nullptr;
    }
    if (m_driverList != nullptr) {
        m_driverList->release();
        m_driverList = nullptr;
    }
    if (pad_50 != nullptr) {
        pad_50->release();
        pad_50 = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
}

void GfMenuObjBladeSet2::setCloseToReturn() {
    GfMenuTypes::Param param;
    param.m_menuId = 1;
    GfMenuFullScreen::registLayerParam(GfMenuObject::getMenuLayerID(0x1E), param);
}

void GfMenuObjBladeSet2::setCloseToFSClose() {
    GfMenuTypes::Param param;
    param.m_menuId = 2;
    GfMenuFullScreen::registLayerParam(GfMenuObject::getMenuLayerID(0x1E), param);
}

void GfMenuObjBladeSet2::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int main = acc.searchChild("LAY_main");
#line 187
    MainListener* mainListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main, mainListener);
    if (mainListener != nullptr) {
        mainListener->release();
    }
    GfMenuObject::attachExternalCall(0x67, main);
    unsigned int team = acc.searchChild("LAY_dr_team");
#line 192
    BladeSlotListener* slotListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) BladeSlotListener(this);
    slotListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(team, slotListener);
    if (slotListener != nullptr) {
        slotListener->release();
    }
    unsigned int list = acc.searchChild("LAY_bl_list");
#line 196
    BladeListListener* listListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) BladeListListener(this);
    listListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(list, listListener);
    if (listListener != nullptr) {
        listListener->release();
    }
    m_slotList = GfMenuBladeList::create();
    m_bladeList = GfMenuBladeList::create();
    m_driverList = GfMenuDriverList::create();
    m_context = GfMenuCallContext::create();
    m_subContext = GfMenuCallContext::create();
    m_openType = 0;
    GfMenuTypes::Param param;
    if (GfMenuObject::getFSLayerParam(m_fsLayer, param)) {
        m_openType = param.m_menuId;
        GfMenuObject::removeFSLayerParam(m_fsLayer);
    }
    GfMenuObjCmnStatus::openDrStatus(0, 0);
    GfMenuObjCmnStatus::openBlStatus(1, -1);
    GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_scroll_bar"), m_bladeList, "IMG_scroll_base", true);
    m_faceCount = acc.countChild("LAY_bl_facelayout@%02d", 1);
    GfMenuObject::initialize();
}

void GfMenuObjBladeSet2::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBladeSet2::update() {
    m_seq.update();
    m_subSeq.update();
    GfMenuObject::update();
}

void GfMenuObjBladeSet2::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObjUtil::setChildIcon(acc.m_handle, "IMG_l_button", 0x14);
        GfMenuObjUtil::setChildIcon(acc.m_handle, "IMG_r_button", 0x15);
        GfMenuObjUtil::setChildIcon(acc.m_handle, "IMG_release_button", 10);
        acc.setDisp(true);
        setFadeIn(handle);
        break;
    case 3:
        if (event.m_param0 == 2) {
            acc.setDisp(false);
            acc.setTerm();
            if (m_owner->m_openType == 1) {
                GfMenuObjMainMenu2::closeCharChange();
                GfMenuObject::returnFSSubLayer(m_owner);
            } else if (m_owner->m_openType == 0) {
                GfMenuObjCharSelect::returnSubMenu();
                GfMenuObject::returnFSSubLayer(m_owner);
            } else {
                GfMenuObject::closeFSLayer(acc.m_handle, true, true);
            }
        }
        break;
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        GfMenuObjCmnStatus::closeDrStatus();
        GfMenuObjCmnStatus::closeBlStatus();
        setFadeOut(handle);
        break;
    case 0x41:
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjBladeSet2::setupBldeSlot(ui::UIObjectAcc& acc, const GfMenuBladeList* list) {
    mm::mtl::FixStr<32> name;
    GfMenuAdapterManager::beginAddAfter();
    for (int i = 0; i < 3; i++) {
        name.format("IMG_tface@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 3, list, i, false);
        name.format("IMG_twpnicon@%02d", i + 1);
        GfMenuCharDataAdapter* weapon =
            GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 0x29, list, i, false);
        if (weapon != nullptr) {
            name.format("IMG_twpnicon_base@%02d", i + 1);
            weapon->m_rowHandle = acc.searchChild(name.m_str);
        }
        name.format("IMG_telemicon@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 0x2A, list, i, false);
        name.format("IMG_trole_icon@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 0x42, list, i, false);
        name.format("IMG_tlock@%02d", i + 1);
        GfMenuCharDataAdapter* lock =
            GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 0x5A, list, i, true);
        if (lock != nullptr) {
            lock->setDispAlphaMode(true);
        }
    }
    for (int i = 0; i < 3; i++) {
        name.format("TXT_dr_class_name@%02d", i + 1);
        ui::UIObjectAcc text(acc.m_handle, name.m_str);
        GfMenuCharDataAdapter* className = GfMenuCharDataAdapter::createFromReferenceDriver(text.m_handle, 0x25, 0, true);
        if (className != nullptr) {
            className->m_index = i;
            className->m_virtualMode = 1;
        }
        name.format("IMG_dr_class_eff_lv@%02d", i + 1);
        GfMenuCharDataAdapter* level =
            GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild(name.m_str), 0x27, 0, true);
        if (level != nullptr) {
            level->m_index = i;
            level->m_virtualMode = 1;
        }
        name.format("IMG_dr_class_empty@%02d", i + 1);
        GfMenuObjUtil::createSyncPlugin(acc.searchChild(name.m_str), text.m_handle, 0x40);
    }
    GfMenuAdapterManager::endAddAfter();
    GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_drimg01"), 0x1C, 0, false);
    GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_blimg01"), 0x36, 0, false);
    {
        ui::UIObjectAcc image(acc.searchChild("IMG_blimg01"));
        image.setStreamImage2nd();
    }
    GfMenuObject::addNumberEventCondition(acc.m_handle, "IMG_blimg01", 0, 0);
}

bool GfMenuObjBladeSet2::seqOpenImage() {
    ui::UIObjectAcc image(m_handle, "IMG_blimg01");
    if (image.isStreaming()) {
        image.setAlpha(0.0f);
        return false;
    }
    {
        ui::UIObjectAcc acc(m_handle, "LAY_bl_list");
        unsigned int blade = GfMenuReference::getReferenceBladeID(0);
        acc.setLayout(image.m_handle, "blade");
        GfMenuObjUtil::ImageParam imageParam;
        if (blade != 0 && GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
            mm::Vec2 scale;
            image.getScale(scale);
            scale.x = imageParam.m_scale * scale.x;
            scale.y = imageParam.m_scale * scale.y;
            image.setScale(scale);
            GfMenuObjUtil::addPos(image.m_handle, imageParam.m_x, imageParam.m_y);
        }
    }
    image.setAlpha(1.0f);
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = "fade_in_r";
    param.m_startFlags = 8;
    param.m_setDefault = true;
    GfMenuObjUtil::startCtrl(image.m_handle, param, nullptr);
    image.setAlpha(0.0f);
    return true;
}

void GfMenuObjBladeSet2::makeSetupBlade_Remove(RQ_SETUP_BLADE& setup, unsigned int driver, unsigned int blade) {
    GfMenuObjUtil::getDriverPartyID(driver);
    bool homura = GfMenuObjUtil::hasHomura(driver);
    DataParamAcc acc(3, driver, GimmickType(0));
    int slot = acc.getBladeSet(false);
    if (slot == 3) {
        slot = GfDataBlade::getDriverSetID(0x3E9);
    }
    if (acc.getBlade(-1, false) == blade) {
        do {
            slot = slot + 1 < (int)GfMenuObjUtil::getBladeSlotMax() ? slot + 1 : 0;
        } while (acc.getBlade(slot, false) == 0);
    }
    int active = slot;
    if (acc.getBlade(slot, false) == 0x3E9 && GfDataBlade::isHikariCurrent()) {
        active = 3;
    }
    if (blade == 0x3EA && homura) {
        blade = 0x3E9;
    }
    for (int i = 0; i < 5; i++) {
        setup.m_blades[i] = acc.getBlade(i, false) != blade ? acc.getBlade(i, false) : 0;
    }
    setup.m_driver = driver;
    setup.m_activeBlade = setup.m_blades[active];
}

bool GfMenuObjBladeSet2::seqReturnBlSlot() {
    ui::UIObjectAcc acc(m_handle, "LAY_dr_team");
    sendEvent(acc.m_handle, 0x101, 1);
    refreshBladeList();
    return true;
}

void GfMenuObjBladeSet2::refreshBladeSlot(GfMenuBladeList* list) {
    unsigned int driver = GfMenuReference::getReferenceDriverID(0);
    GfMenuBladeList::DriverSetup setup;
    setup.pad_1C = true;
    setup.pad_1D = false;
    setup.pad_1E = false;
    setup.m_type = 1;
    setup.m_driver = driver;
    setup.m_param.m_pageRowSize = GfMenuObjUtil::getBladeSlotMax();
    list->setupFromDriver(setup);
    while ((unsigned int)list->getSize() < 3) {
        MenuBladeInfo info;
        info.m_blade = 0;
        info.m_creator = driver;
        list->addContents(info);
    }
}

void GfMenuObjBladeSet2::refreshBladeList() {
    if (m_faceCount == 0) {
        return;
    }
    m_bladeList->updateOwner();
    ui::UIObjectAcc face(m_handle, "LAY_bl_facelayout");
    ui::UIObjectAcc info(m_handle, "LAY_bl_infolayout");
    mm::mtl::FixStr<32> name;
    unsigned int driver = GfMenuReference::getReferenceDriverID(0);
    for (unsigned int i = 0; i < m_faceCount; i++) {
        unsigned int blade = m_bladeList->getContents(m_bladeList->getPageIndex(i)).m_blade;
        name.format("IMG_fadeselect@%02d", i + 1);
        bool disp = GfDataBlade::getSetDriver(m_bladeList->getContents(m_bladeList->getPageIndex(i)).m_blade) == driver;
        if (disp && blade == 0x3EA) {
            if (GfDataBlade::isActivateDriver(0x3E9)) {
                disp = GfDataBlade::getDriverSetID(0x3E9) != -1;
            } else {
                disp = true;
            }
        }
        face.setDispChild(disp, name.m_str);
    }
}

void GfMenuObjBladeSet2::setupBldeList(ui::UIObjectAcc& acc, const GfMenuBladeList* list, GfMenuBladeList* slotList) {
    GfMenuAdapterManager::beginAddAfter();
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 15; i++) {
        name.format("IMG_face@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 3, list, i, false);
        name.format("IMG_wpnicon@%02d", i + 1);
        GfMenuCharDataAdapter* weapon =
            GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 0x29, list, i, false);
        if (weapon != nullptr) {
            name.format("IMG_wpnicon_base@%02d", i + 1);
            weapon->m_rowHandle = acc.searchChild(name.m_str);
        }
        name.format("IMG_elemicon@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 0x2A, list, i, false);
        name.format("IMG_role_icon@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 0x42, list, i, false);
        name.format("LAY_mericon@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 0x53, list, i, true);
        name.format("IMG_dr_icon@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeListOwnerDriver(acc.searchChild(name.m_str), 3, list, i, true);
        name.format("IMG_face@%02d", i + 1);
        GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 0x4A, list, i, true)->setSlotList(slotList);
        name.format("IMG_lock@%02d", i + 1);
        GfMenuCharDataAdapter* lock =
            GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 0x5A, list, i, true);
        if (lock != nullptr) {
            lock->setDispAlphaMode(true);
        }
    }
    GfMenuAdapterManager::endAddAfter();
}

bool GfMenuObjBladeSet2::checkBladeSet(unsigned int blade, GfMenuBladeList* list) {
    unsigned int index = list->getIndex(false);
    // the selected content read in place (an if/else, not getContents' if-then: the original keeps m_dummy's
    // address out of the entry block)
    unsigned int selected = list->getIndex(false);
    const MenuBladeInfo& current = selected < list->m_list.size() ? list->m_list[selected] : list->m_dummy;
    if (current.m_blade != 0) {
        for (unsigned int i = 0; i < (unsigned int)list->getSize(); i++) {
            const MenuBladeInfo& info = list->getContents(i);
            if (index != i && info.m_blade == blade) {
                return true;
            }
        }
    }
    for (unsigned int i = 0; i < (unsigned int)list->getSize(); i++) {
        if (list->getContents(i).m_blade == blade) {
            return false;
        }
    }
    return true;
}
}  // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBladeSet2>(const mm::mtl::Delegate<bool()>*);

template bool gf::GfMenuSequence<gf::GfMenuObjBladeSet2, 8>::wait();

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjBladeSet2, 8>>(const mm::mtl::Delegate<bool()>*);

namespace gf {

}  // namespace gf
