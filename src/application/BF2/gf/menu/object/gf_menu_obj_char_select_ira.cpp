#include "gf/GfDataDriver.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/TUnk_B61178.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfReqManager.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"

namespace gf {

int TUnk_B61178::s_state;

TUnk_B61178::TUnk_B61178(unsigned int handle)
    : GfMenuObject(handle), m_driverList(nullptr), m_selectList(nullptr), m_driver(0), m_partyId(0), m_seq(this),
      m_seq2(this), pad_578(0), pad_57C(0), m_selectList2(nullptr), m_unusedList(nullptr), m_driverList2(nullptr),
      m_shownDriver(0), pad_5C4(0), m_req(-1), pad_61C(false) {
    m_driverList = GfMenuDriverList::create();
    m_driverList2 = GfMenuDriverList::create();
    {
        ui::UIListInfoBase::SetupParam param;
        m_driverList2->setup(getAllocator(ALLOCATOR(0)), param);
    }
    m_driverList2->clear();
    {
        ui::UISelectObjList::CreateParam create;
        create.m_allocator = getAllocator(ALLOCATOR(0));
        m_selectList = ui::UISelectObjList::create(create);
    }
    {
        ui::UISelectObjList::CreateParam create;
        create.m_allocator = getAllocator(ALLOCATOR(0));
        m_selectList2 = ui::UISelectObjList::create(create);
    }
}

TUnk_B61178::~TUnk_B61178() {
    if (m_unusedList != nullptr) {
        m_unusedList->release();
        m_unusedList = nullptr;
    }
    if (m_selectList2 != nullptr) {
        m_selectList2->release();
        m_selectList2 = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
    if (m_driverList2 != nullptr) {
        m_driverList2->release();
        m_driverList2 = nullptr;
    }
    if (m_driverList != nullptr) {
        m_driverList->release();
        m_driverList = nullptr;
    }
    s_state = 0;
}

void TUnk_B61178::fn_71003D1670() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x61));
    if (acc.m_object != nullptr) {
        GfMenuObject::sendOpenEvent(acc.searchChild("LAY_move"), 0, 0.0f);
    }
}

void TUnk_B61178::fn_71003D16C8() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x61));
    if (acc.m_object != nullptr) {
        GfMenuObject::sendCloseEvent(acc.searchChild("LAY_move"), 0, 0.0f);
    }
}

int TUnk_B61178::fn_71003D1720() {
    return s_state;
}

bool TUnk_B61178::fn_71003D2558() {
    ui::UIObjectAcc acc(m_handle, "LAY_char");
    GfMenuObject::sendOpenEvent(acc.m_handle, 0, 0.0f);
    return true;
}

void TUnk_B61178::finalize() {
    GfMenuObject::finalize();
}

void TUnk_B61178::update() {
    m_seq.update();
    m_seq2.update();
    unsigned int driver = 0;
    if (s_state == 1) {
        driver = GfMenuReference::getReferenceDriverID(0);
    } else if (s_state == 2) {
        driver = GfDataBlade::fn_7100236518(GfMenuReference::getReferenceBladeID(0));
    }
    if (driver != 0 && m_shownDriver != driver) {
        ui::UIObjectAcc acc(m_handle, "LAY_move");
        ui::EventData event;
        event.m_type = 0x101;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        m_shownDriver = driver;
        fn_71003D273C(driver);
    }
    GfMenuObject::update();
}

void TUnk_B61178::fn_71003D273C(unsigned int driver) {
    if (GfDataDriver::fn_7100237A94(driver)) {
        GfMenuReference::setReferenceDriverID(0, driver);
        GfMenuReference::setReferenceDriverID(1, driver);
        GfMenuReference::setReferenceBladeID(0, 0);
    } else {
        GfMenuReference::setReferenceDriverID(0, GfDataDriver::fn_71002417DC(driver));
        GfMenuReference::setReferenceDriverID(1, driver);
        GfMenuReference::setReferenceBladeID(0, GfDataBlade::fn_7100237B70(driver, -1));
    }
}

bool TUnk_B61178::fn_71003D4568() {
    if (m_req == -1) {
        return true;
    }
    return GfReqManager::isValid(m_req);
}

bool TUnk_B61178::fn_71003D478C() {
    ui::UIObjectAcc acc(m_handle, "LAY_char");
    if (GfMenuObjUtil::getCtrlID(acc.m_handle) == -1) {
        fn_71003D27B8(m_driver, true);
        GfMenuObject::sendOpenEvent(acc.m_handle, 2, 0.0f);
    }
    return true;
}

void TUnk_B611D8::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 0x104) {
        if (TUnk_B61178::s_state == 1) {
            TUnk_B61178* owner = m_owner;
            unsigned int driver = GfMenuReference::getReferenceDriverID(0);
            if (owner->m_driver != driver) {
                owner->fn_71003D3EC0(driver);
                owner->fn_71003D27B8(owner->m_driver, false);
            }
        } else if (TUnk_B61178::s_state == 2) {
            unsigned int blade = GfMenuReference::getReferenceBladeID(0);
            m_owner->fn_71003D3F94(GfMenuReference::getReferenceBladeID(0));
            TUnk_B61178::fn_71003D273C(GfDataBlade::fn_7100236518(blade));
        }
        GfMenuObject::sendOpenEvent(acc.searchChild("LAY_sub_menu"), 1, 0.0f);
    } else {
        UIObjectListener::reciveEvent(event, handle);
    }
}

bool TUnk_B61178::fn_71003D5C48() {
    ui::UIObjectAcc acc(m_handle, "LAY_char");
    if (GfMenuObjUtil::getCtrlID(acc.m_handle) == -1) {
        fn_71003D27B8(m_driver, false);
        GfMenuObject::sendOpenEvent(acc.m_handle, 1, 0.0f);
    }
    return true;
}

void TUnk_B61228::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 2:
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 1, 0);
        break;
    case 3:
        if (event.m_param0 == 1) {
            acc.setTerm();
        }
        break;
    case 0x21:
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 0, 0);
        break;
    case 0x22:
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 0, 0);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool TUnk_B61178::fn_71003D6E94() {
    ui::UIObjectAcc acc(m_handle, "IMG_char_move_img");
    return !acc.isStreaming();
}

}  // namespace gf
