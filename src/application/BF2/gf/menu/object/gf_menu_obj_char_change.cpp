#include "classes/gf/TUnk_B60E28.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuArtsList.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

TUnk_B60E28::TUnk_B60E28(unsigned int handle)
    : GfMenuObject(handle), pad_24(-1), pad_28(false), pad_29(false), pad_2A(true), m_seq(this), pad_190(), m_chainFlags(),
      pad_1B8(-1), m_artsList(nullptr) {
    pad_1C0 = false;
    pad_1BC = 0;
    m_artsList = GfMenuArtsList::create();
    ui::UIListInfoBase::SetupParam param;
    param.m_pageRowSize = 2;
    m_artsList->setup(getAllocator(ALLOCATOR(0)), param);
}

TUnk_B60E28::~TUnk_B60E28() {
    if (m_artsList != nullptr) {
        m_artsList->release();
        m_artsList = nullptr;
    }
}


void TUnk_B60E28::fn_71003C32F8() {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::EventData event;
            event.m_type = 0x108;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void TUnk_B60E28::fn_71003C3368() {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::EventData event;
            event.m_type = 0x109;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void TUnk_B60E28::fn_71003C33D8(bool disp) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x3C);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::UIObjectAcc(handle).setDisp(disp);
        }
    }
}


void TUnk_B60E28::fn_71003C3470() {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::EventData event;
            event.m_type = 0x10A;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void TUnk_B60E28::fn_71003C34E0() {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::EventData event;
            event.m_type = 0x10B;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void TUnk_B60E28::fn_71003C3550(bool flag) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
        if (acc.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x106;
            event.m_param0 = flag;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void TUnk_B60E28::fn_71003C35C8(unsigned int value) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
        if (acc.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x107;
            event.m_param0 = value;
            GfMenuObject::sendEvent(acc.searchChild("LAY_cmd"), event, 0.0f);
        }
    }
}

void TUnk_B60E28::fn_71003C3648(bool disp) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x10F;
        event.m_param0 = disp;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void TUnk_B60E28::fn_71003C5164(unsigned int index) {
    ui::UIObjectAcc chain(m_handle, "LAY_chain");
    unsigned int count = chain.countChild("LAY_chain@%02d", 1);
    mm::mtl::FixStr<32> name;
    if (index < count) {
        name.format("IMG_chain_recast@%02d", index + 1);
        ui::UIObjectAcc recast(chain.m_handle, name.m_str);
        if (recast.m_object != nullptr) {
            name.format("IMG_chain_face@%02d", index + 1);
            ui::UIObjectAcc face(chain.m_handle, name.m_str);
            const char* color;
            if (m_chainFlags[index] & 2) {
                recast.setAlpha(0.0f);
                color = "white";
            } else {
                recast.setAlpha(1.0f);
                color = "gray";
            }
            face.setMulColor(color);
        }
    }
}

void TUnk_B60E28::fn_71003C55E0(bool disp) {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    acc.setDispChild(disp, "LAY_info");
    acc.setDispChild(disp, "LAY_char2_reserve_elem_root@01");
    acc.setDispChild(disp, "LAY_char2_active_elem_root@01");
    acc.setDispChild(disp, "LAY_char2_reserve_elem_root@02");
    acc.setDispChild(disp, "LAY_char2_active_elem_root@02");
    ui::UIObjectAcc chain(acc.searchSibiling("LAY_chain"));
    chain.setDispChild(disp, "LAY_chain_info");
}

void TUnk_B60E28::finalize() {
    GfMenuObject::finalize();
}

}  // namespace gf
