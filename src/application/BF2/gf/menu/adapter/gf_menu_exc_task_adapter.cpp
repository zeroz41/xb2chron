#include "classes/gf/GfMenuAdapter.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UIListInfo.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuExcTaskAdapter.h"
#include "classes/gf/GfMenuExcTaskAdapter/IConverter.h"
#include "classes/gf/GfMenuExcTaskAdapter/ListConverter.h"
#include "classes/gf/GfMenuExcTaskAdapter.h"
#include "classes/gf/GfMenuExcTaskAdapter/ListConverter.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfMenuBdat.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (text)
static GfMenuExcTaskAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuExcTaskAdapter::update_Name, {2, 0, 0}},
};

GfMenuExcTaskAdapter::~GfMenuExcTaskAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuExcTaskAdapter* GfMenuExcTaskAdapter::create(unsigned int handle, unsigned int type, unsigned int taskId,
                                                   bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 113
    GfMenuExcTaskAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuExcTaskAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_taskId = taskId;
    plugin->release();
    return adapter;
}

bool GfMenuExcTaskAdapter::update_Name(unsigned int taskId) {
    unsigned char* fp = GfDataBdat::getFP(0xF2);
    if (!GfMenuBdat::isValidBdatID(fp, taskId)) {
        return false;
    }
    unsigned short name = (unsigned short)Bdat::getVal(fp, "Name", taskId);
    ui::UIStr text(GfDataBdat::getFP(0x1BF), name);
    setText(text);
    return true;
}

GfMenuExcTaskAdapter* GfMenuExcTaskAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                               IConverter* converter, bool changed) {
    unsigned int taskId = 0;
    converter->getTaskID(taskId);
    GfMenuExcTaskAdapter* adapter = create(handle, type, taskId, changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuExcTaskAdapter* GfMenuExcTaskAdapter::createFromList(unsigned int handle, unsigned int type,
                                                           GfMenuIDList* list, int index, bool changed) {
#line 144
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListConverter(list, index);
    return createFromCoverter(handle, type, converter, changed);
}

void GfMenuExcTaskAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int taskId = 0;
        m_converter->getTaskID(taskId);
        if (m_taskId != taskId) {
            m_taskId = taskId;
            setChange();
        }
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        if (m_taskId != 0) {
            setDisp(m_update(m_taskId));
        } else {
            setDisp(false);
        }
        m_flags &= ~1;
    }
}

GfMenuExcTaskAdapter::ListConverter::~ListConverter() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

void GfMenuExcTaskAdapter::ListConverter::getTaskID(unsigned int& taskId) {
    if (m_index == -1) {
        taskId = m_list->getContents(m_list->getIndex(false)).m_id;
        return;
    }
    if (m_index >= m_list->getSize()) {
        return;
    }
    taskId = m_list->getContents(m_list->getPageIndex(m_index)).m_id;
}

void GfMenuExcTaskAdapter::ListConverter::fromList() {}

}  // namespace gf
