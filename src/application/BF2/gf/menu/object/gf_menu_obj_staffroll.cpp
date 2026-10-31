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

void GfMenuObjStaffroll::update() {
    if (m_resource == nullptr) {
        return;
    }
    if (m_state == 0) {
        if (m_resource->valid()) {
            // getSize's out-parameters: the frame's first locals (just under the saved registers)
            short imageWidth;
            short imageHeight;
            m_reader.bind(m_resource->getAssetData(), m_resource->getAssetSize());
            unsigned int count = m_reader.getRowCount();
            m_rows.setAllocator(getAllocator(ALLOCATOR(0)));
            m_rows.reserve(count);
            unsigned int y = 0;
            for (unsigned int i = 0; i < count; ++i) {
                CreditReader::Row data;
                if (!m_reader.getRow(i, data)) {
                    continue;
                }
                if (!data.m_skip || data.m_param != 0) {
                    RowInfo info;
                    info.m_y = y;
                    info.m_height = 0;
                    info.m_index = i;
                    info.m_created = false;
                    info.m_done = false;
                    if (data.m_param != 0) {
                        mm::mtl::FixStr<32> name;
                        name.format("IMG_image@%02d", data.m_param);
                        ui::UIObjectAcc image(m_handle, name.m_str);
                        image.getSize(false, imageWidth, imageHeight);
                        info.m_height = imageHeight;
                    }
                    m_rows.push_back(info);
                }
                int height;
                if (data.m_skip) {
                    height = static_cast<unsigned int>(data.m_id) > 10 ? 24 : 8;
                } else {
                    height = 0;
                    for (int c = 0; c < 3; ++c) {
                        int size = data.m_columns[c].m_param0;
                        if (height < size) {
                            height = size < 24 ? 24 : size;
                        }
                    }
                }
                y += height;
            }
            m_scrollLength = y + 720;
            m_state = 1;
            m_end = false;
        }
    } else if (m_state == 2) {
        if (GfMenuManager::fn_710035A738()) {
            return;
        }
        m_scroll += m_scrollSpeed;
        unsigned int scroll = m_scroll;
        for (unsigned int i = m_row; i < m_rows.size(); ++i) {
            RowInfo& row = m_rows[i];
            if (!row.m_created) {
                if (scroll <= row.m_y) {
                    break;
                }
                CreditReader::Row data;
                m_reader.getRow(row.m_index, data);
                if (data.m_param != 0) {
                    mm::mtl::FixStr<32> name;
                    name.format("IMG_image@%02d", data.m_param);
                    ui::UIObjectAcc image(m_handle, name.m_str);
                    if (image.m_object != nullptr) {
                        unsigned int handle = image.m_handle;
                        row.m_texts.push_back(handle);
                        image.setDisp(true);
                    }
                } else {
                    for (unsigned int c = 0; c < 3; ++c) {
                        if (!(data.m_columns[c].m_param0 > 0)) {
                            continue;
                        }
                        row.m_texts.push_back(createText(c, data.m_columns[c]));
                    }
                }
                row.m_created = true;
            }
            if (row.m_created) {
                int y = row.m_y - scroll + 720;
                if (i >= m_rows.size() - 2 && y < 340) {
                    for (unsigned int j = i; j < m_rows.size(); ++j) {
                        m_rows[j].m_done = true;
                    }
                    m_end = true;
                    if (m_row >= m_rows.size() - 2) {
                        m_state = 4;
                    }
                }
                if (row.m_height + y < 0) {
                    for (unsigned int j = 0; j < row.m_texts.size(); ++j) {
                        ui::UIObjectAcc text(row.m_texts[j]);
                        text.setTerm();
                        row.m_texts[j] = 0;
                    }
                    m_row = i + 1;
                    if (m_end && m_row >= m_rows.size() - 2) {
                        m_state = 4;
                    }
                } else if (!row.m_done) {
                    for (unsigned int j = 0; j < row.m_texts.size(); ++j) {
                        ui::UIObjectAcc text(row.m_texts[j]);
                        mm::Pnt<short> pos;
                        text.getPos(pos);
                        pos.y = y;
                        text.setPos(pos);
                        if (GfMenuObjUtil::fn_710048FD30(3)) {
                            if (!(y >= 550)) {
                                if (y >= 530) {
                                    text.setAlpha((550 - y) / 20.0f);
                                } else if (y <= 20) {
                                    if (!(y > 0)) {
                                        text.setAlpha(0.0f);
                                    } else {
                                        text.setAlpha(y / 20.0f);
                                    }
                                } else {
                                    text.setAlpha(1.0f);
                                }
                            } else {
                                text.setAlpha(0.0f);
                            }
                        }
                    }
                }
            }
        }
    }
    GfMenuObject::update();
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
