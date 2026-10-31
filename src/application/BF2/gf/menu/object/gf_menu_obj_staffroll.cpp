#include "ui/EventData.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuObjStaffroll.h"
#include "classes/gf/GfMenuObjStaffroll/MainListener.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Pnt.h"
#include "classes/fw/CommonResource.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UISelectObjList.h"
#include "fw/LangUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/UIUtil.h"
#include "ui/UIStr.h"

namespace gf {

GfMenuObjStaffroll::GfMenuObjStaffroll(unsigned int handle)
    : GfMenuObject(handle), m_resource(nullptr), m_state(0), m_scrollLength(0), m_row(0), m_scroll(0.0f),
      m_scrollSpeed(0.0f), m_end(false) {
    ui::UISelectObjList::CreateParam create;
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_list = ui::UISelectObjList::create(create);
}

GfMenuObjStaffroll::~GfMenuObjStaffroll() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
    if (m_resource != nullptr) {
        m_resource->release();
        m_resource = nullptr;
    }
}

void GfMenuObjStaffroll::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
#line 110
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::attachExternalCall(0x85, acc.m_handle);
    mm::mtl::FixStr<128> path;
    const char* file;
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        if (fw::LangUtil::getLangType() == 0 || fw::LangUtil::getLangType() == 6 || fw::LangUtil::getLangType() == 11) {
            file = "dlc3_endroll.crt";
        } else {
            file = "dlc3_endroll_us.crt";
        }
    } else {
        file = GfMenuManager::isRegionUS() ? "endroll_us.crt" : "endroll.crt";
    }
    path.format("%s/credit/%s", ui::UIUtil::fn_7100696940(), file);
    m_resource = fw::CommonResource::request(ui::UIUtil::getResourceAllocator(), path.m_str, 10, false);
    GfMenuObject::initialize();
}

void GfMenuObjStaffroll::finalize() {
    if (m_rows.capacity() != 0) {
        m_rows.destroy();
    }
    GfMenuObject::finalize();
}

// the text parts createText duplicates, per column (lbl_7100B64B20; the name is not the original's)
static const char* const s_textNames[] = {"TXT_left", "TXT_center", "TXT_right", "TXT_right2"};

unsigned int GfMenuObjStaffroll::createText(unsigned int index, const CreditReader::Column& column) {
    mm::mtl::FixStr<32> name;
    const char* size;
    if (column.m_param0 < 22) {
        size = "_px20";
    } else if (column.m_param0 < 24) {
        size = "_px22";
    } else if (column.m_param0 < 28) {
        size = "_px24";
    } else {
        size = "_px28";
    }
    if (index == 1 && column.m_param1 == 0) {
        index = 3;
    }
    name.format("%s%s", s_textNames[index], size);
    ui::UIObjectAcc main(m_handle, "LAY_main");
    ui::UIObjectAcc text(main.duplicateChild(name.m_str));
    if (text.m_object == nullptr) {
        return 0;
    }
    switch (column.m_param1) {
    case 0:
        text.setTextAlignH(0);
        break;
    case 1:
        text.setTextAlignH(1);
        break;
    case 2:
        text.setTextAlignH(2);
        break;
    }
    text.setBorderWeight(-0.5f);
    text.setSlopeRot(-12.0f);
    if (column.m_enable) {
        text.setBorderWeight(1.0f);
        text.setAddColor("white");
    }
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        text.setBorderWeight(1.0f);
    }
    text.setText(ui::UIStr(column.m_text, false));
    text.setDisp(true);
    return text.m_handle;
}

void GfMenuObjStaffroll::start(float speed, int type) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x85));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0Float = speed;
        event.m_param1 = type;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjStaffroll::fadeout() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x85));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjStaffroll::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 0x21: {
        float time = event.m_param0Float;
        short x = event.m_param1;
        m_owner->m_scrollSpeed = m_owner->m_scrollLength / (time * 30.0f);
        m_owner->m_state = 2;
        mm::Pnt<short> pos(x, 0);
        acc.setPos(pos);
        acc.setDisp(true);
        bool disp = !GfMenuObjUtil::fn_710048FD30(3);
        ui::UIObjectAcc grade(acc.searchSibiling("LAY_grade"));
        grade.setDisp(disp);
        break;
    }
    case 0x22: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = 2.0f;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        ui::UIObjectAcc grade(acc.searchSibiling("LAY_grade"));
        grade.setDisp(false);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf
