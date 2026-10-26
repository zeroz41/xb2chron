#include "classes/gf/TUnk_B60AA8.h"
#include "gf/gf_menu_obj_camp_menu.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuFade.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuFlag.h"
#include "mm/Col4.h"
#include "ui/EventData.h"

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAA1D0)
int g_campMenuState;

TUnk_B60AA8::TUnk_B60AA8(unsigned int handle)
    : GfMenuObject(handle), m_seq(this), m_jobStarted(false), m_driverList0(nullptr), m_driverList1(nullptr),
      m_selectList(nullptr), pad_2D8(nullptr), m_context(nullptr), m_voice(nullptr), m_sound(0) {
    m_driverList0 = GfMenuDriverList::create();
    m_driverList1 = GfMenuDriverList::create();
    ui::UISelectObjList::CreateParam create;
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_selectList = ui::UISelectObjList::create(create);
    m_context = GfMenuCallContext::create();
}

TUnk_B60AA8::~TUnk_B60AA8() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (pad_2D8 != nullptr) {
        pad_2D8->release();
        pad_2D8 = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
    if (m_driverList1 != nullptr) {
        m_driverList1->release();
        m_driverList1 = nullptr;
    }
    if (m_driverList0 != nullptr) {
        m_driverList0->release();
        m_driverList0 = nullptr;
    }
}

int fn_71003BBB38() {
    return g_campMenuState;
}

void fn_71003BBB48() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8D));
    if (acc.m_object != nullptr) {
        GfMenuObject::sendOpenEvent(acc.searchChild("LAY_menu"), 0, 0.0f);
        g_campMenuState = 0;
    }
}

void fn_71003BBBAC() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8D));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x101;
        GfMenuObject::sendEvent(acc.searchChild("LAY_shop"), event, 0.0f);
        g_campMenuState = 0;
    }
}

void fn_71003BBC1C() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8D));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc child(acc.m_handle, "LAY_chr_change");
        GfMenuObject::enableInput(child.m_handle);
    }
}

void fn_71003BBC7C() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8D));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc child(acc.m_handle, "LAY_chr_change");
        GfMenuObject::disableInput(child.m_handle);
    }
}

void fn_71003BBCDC() {
    GfMenuFlag::set1(0x54, 0);
}

void TUnk_B60AA8::finalize() {
    GfMenuObject::detachExternalCall(0x8D);
    GfMenuObject::finalize();
}

void TUnk_B60AA8::update() {
    m_seq.update();
    if (m_voice != nullptr && GfGameVoice::getResult(m_voice) >= 3) {
        m_voice = nullptr;
    }
    GfMenuObject::update();
}

bool TUnk_B60AA8::fn_71003BCEAC() {
    if (!m_jobStarted) {
        GfMenuManager::openCommonWindow(0x11F);
        m_jobStarted = true;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    if (static_cast<unsigned short>(GfMenuManager::getCommonWindowResult()) != 0) {
        ui::UIObjectAcc menu(m_handle, "LAY_menu");
        ui::EventData event;
        event.m_type = 0x100;
        GfMenuObject::sendEvent(menu.m_handle, event, 0.0f);
    } else {
        {
            ui::UIObjectAcc menu(m_handle, "LAY_menu");
            GfMenuObject::sendCloseEvent(menu.m_handle, 0, 0.0f);
            GfMenuObjOperationInfo::remove(menu.m_handle, 0, 0, 0);
        }
        ui::UIObjectAcc sleep(m_handle, "LAY_sleep");
        GfMenuObject::sendOpenEvent(sleep.m_handle, 0, 0.0f);
    }
    m_jobStarted = false;
    return true;
}

bool TUnk_B60AA8::fn_71003BCFB8() {
    if (!m_jobStarted) {
        GfMenuManager::openCommonWindow(0x11E);
        m_jobStarted = true;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    {
        ui::UIObjectAcc menu(m_handle, "LAY_menu");
        ui::EventData event;
        event.m_type = 0x100;
        event.m_param0 = static_cast<unsigned short>(GfMenuManager::getCommonWindowResult()) == 0;
        GfMenuObject::sendEvent(menu.m_handle, event, 0.0f);
    }
    m_jobStarted = false;
    return true;
}

bool TUnk_B60AA8::fn_71003BD924() {
    if (!m_jobStarted) {
        GfMenuFade::setFade(2, 30, mm::Col4::black);
        m_jobStarted = true;
        return false;
    }
    return !GfMenuManager::isFading();
}

bool TUnk_B60AA8::fn_71003BE0FC() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    if (m_context->isTerm()) {
        GfMenuObject::sendCloseEvent(main.searchChild("LAY_shop"), 0, 0.0f);
        m_jobStarted = false;
        return true;
    }
    return false;
}

bool TUnk_B60AA8::fn_71003BE178() {
    GfMenuFade::setFade(1, 15, mm::Col4::black);
    return true;
}

bool TUnk_B60AA8::fn_71003BE1A0() {
    return !GfMenuManager::isFading();
}

bool TUnk_B60AA8::fn_71003BE1BC() {
    mm::mtl::PtrSingleton<GfFieldTime>::sys()->setTime(7, 0);
    GfGameManager::fn_71002AC6A8();
    return true;
}

bool TUnk_B60AA8::fn_71003BE1EC() {
    return true;
}

bool TUnk_B60AA8::fn_71003BE1F4() {
    mm::mtl::PtrSingleton<ui::UIManager>::sys()->terminateLayer(m_fsLayer, true);
    m_jobStarted = false;
    return true;
}

bool TUnk_B60AA8::fn_71003BE7EC(unsigned int driver, unsigned short* shop) {
    unsigned char* fp = GfDataBdat::getFP(0x10E);
    if (fp != nullptr) {
        for (int i = 0; i < Bdat::getIdCount(fp); i++) {
            unsigned short id = Bdat::getIdTop(fp) + i;
            if (static_cast<unsigned short>(Bdat::getVal(fp, "driver_id", id)) ==
                driver) {
                shop[0] = static_cast<unsigned short>(Bdat::getVal(fp, "shop_id", id));
                shop[1] =
                    static_cast<unsigned short>(Bdat::getVal(fp, "summary_msg", id));
                return true;
            }
        }
    }
    return false;
}

bool TUnk_B60AA8::fn_71003BEB30() {
    return !GfMenuManager::isOpenFullScreen();
}

bool TUnk_B60AA8::fn_71003BEB4C() {
    mm::mtl::PtrSingleton<ui::UIManager>::sys()->terminateLayer(m_fsLayer, true);
    m_jobStarted = false;
    return true;
}

}  // namespace gf
