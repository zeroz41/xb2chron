#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuZoneMapAdapter.h"
#include "classes/gf/GfMenuZoneMapAdapter/IConverter.h"
#include "classes/gf/GfMenuZoneMapAdapter/ListConverter.h"
#include "classes/gf/GfMenuZoneMapList.h"
#include "classes/gf/GfMenuObjWorldMap.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (text)
static GfMenuZoneMapAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuZoneMapAdapter::update_ZoneMapName, {2, 0, 0}},
    {&GfMenuZoneMapAdapter::update_ZonePointName, {2, 0, 0}},
};

GfMenuZoneMapAdapter::~GfMenuZoneMapAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuZoneMapAdapter* GfMenuZoneMapAdapter::create(unsigned int handle, unsigned int type, unsigned int mapId,
                                                   unsigned int param, bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 197
    GfMenuZoneMapAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuZoneMapAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_mapId = mapId;
    adapter->m_param = param;
    plugin->release();
    return adapter;
}

bool GfMenuZoneMapAdapter::update_ZoneMapName() {
    unsigned char* table;
    if (m_groupMode) {
        table = GfDataBdat::getFP(0x17B);
    } else {
        table = GfDataBdat::getFP(0x17A);
    }
    unsigned int name = (unsigned short)Bdat::getVal(table, "disp_name", m_mapId);
    ui::UIStr text(GfDataBdat::getFP(0x12E), name);
    setText(text);
    return true;
}

bool GfMenuZoneMapAdapter::update_ZonePointName() {
    unsigned char* message = GfDataBdat::getFP(0x1B3);
    if (GfMenuObjWorldMap::fn_7100495A98(m_mapId)) {
        ui::UIStr text(message, m_param);
        setText(text);
    } else {
        ui::UIStr text(GfDataBdat::getFP(0xF5), 0x67C);
        setText(text);
    }
    return true;
}

GfMenuZoneMapAdapter* GfMenuZoneMapAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                               IConverter* converter, bool changed) {
    if (handle == 0) {
        return nullptr;
    }
    unsigned int mapId = converter->getMapId();
    GfMenuZoneMapAdapter* adapter = create(handle, type, mapId, converter->getParam(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuZoneMapAdapter* GfMenuZoneMapAdapter::createFromList(unsigned int handle, unsigned int type,
                                                           GfMenuZoneMapList* list, unsigned int index, bool onPage,
                                                           bool changed) {
    if (handle == 0) {
        return nullptr;
    }
#line 233
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        ListConverter(list, index, onPage);
    return createFromCoverter(handle, type, converter, changed);
}

void GfMenuZoneMapAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int mapId = m_converter->getMapId();
        unsigned int param = m_converter->getParam();
        bool groupMode = m_converter->isGroupMode();
        if (m_mapId != mapId) {
            m_mapId = mapId;
            setChange();
        }
        if (m_param != param) {
            m_param = param;
            setChange();
        }
        if (m_groupMode != groupMode) {
            m_groupMode = groupMode;
            setChange();
        }
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        if (m_mapId != 0) {
            setDisp(m_update());
        } else {
            setDisp(false);
        }
        m_flags &= ~1;
    }
}

GfMenuZoneMapAdapter::ListConverter::~ListConverter() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

unsigned int GfMenuZoneMapAdapter::ListConverter::getMapId() {
    if (m_index == -1) {
        return m_list->getContents(m_list->getIndex(false)).m_mapId;
    }
    if (m_onPage) {
        if (m_index < m_list->getSize()) {
            return m_list->getContents(m_list->getPageIndex(m_index)).m_mapId;
        }
    } else {
        if (m_index < m_list->getSize()) {
            return m_list->getContents(m_index).m_mapId;
        }
    }
    return 0;
}

unsigned int GfMenuZoneMapAdapter::ListConverter::getParam() {
    if (m_index == -1) {
        return m_list->getContents(m_list->getIndex(false)).m_param;
    }
    if (m_onPage) {
        if (m_index < m_list->getSize()) {
            return m_list->getContents(m_list->getPageIndex(m_index)).m_param;
        }
    } else {
        if (m_index < m_list->getSize()) {
            return m_list->getContents(m_index).m_param;
        }
    }
    return 0;
}

bool GfMenuZoneMapAdapter::ListConverter::isGroupMode() {
    return m_list->m_groupMode;
}

}  // namespace gf
