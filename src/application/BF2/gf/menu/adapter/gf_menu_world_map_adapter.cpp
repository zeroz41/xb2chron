#include "classes/gf/GfMenuWorldMapAdapter.h"
#include "classes/gf/GfMenuWorldMapAdapter/IConverter.h"
#include "classes/gf/GfMenuWorldMapAdapter/ListConverter.h"
#include "classes/gf/GfMenuWorldMapAdapter/ReferenceConverter.h"
#include "classes/gf/GfMenuMissionAdapter/MissionListConverter.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfDataDevelop.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (text, number from 0 to 20000, image index,
// disp)
static GfMenuWorldMapAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuWorldMapAdapter::update_WorldMapName, {2, 0, 0}},
    {&GfMenuWorldMapAdapter::update_DevelopPoint, {0, 0, 20000}},
    {&GfMenuWorldMapAdapter::update_DevelopLvIcon, {1, 0, 0}},
    {&GfMenuWorldMapAdapter::update_CurrentDisp, {3, 0, 0}},
};

// a map and the zone it belongs to (GfDataDevelop's); the names are not the original's
struct MapZone {
    unsigned int m_mapId;
    unsigned int m_zoneId;
};
static const MapZone s_mapZones[] = {
    {3, 1}, {6, 2}, {9, 3}, {10, 4}, {14, 5}, {12, 6}, {13, 7},
};

GfMenuWorldMapAdapter::~GfMenuWorldMapAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuWorldMapAdapter* GfMenuWorldMapAdapter::create(unsigned int handle, unsigned int type, unsigned short mapId,
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
#line 225
    GfMenuWorldMapAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuWorldMapAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_mapId = mapId;
    plugin->release();
    return adapter;
}

bool GfMenuWorldMapAdapter::update_WorldMapName() {
    unsigned int name = (unsigned short)Bdat::getVal(GfDataBdat::getFP(0x5D), "nameID", m_mapId);
    ui::UIStr text(GfDataBdat::getFP(0x1B4), name);
    setText(text);
    return true;
}

unsigned int GfMenuWorldMapAdapter::convMap2Zone(unsigned int mapId) {
    for (unsigned int i = 0; i < sizeof(s_mapZones) / sizeof(s_mapZones[0]); i++) {
        if (s_mapZones[i].m_mapId == mapId) {
            return s_mapZones[i].m_zoneId;
        }
    }
    return 0;
}

bool GfMenuWorldMapAdapter::update_DevelopPoint() {
    unsigned int zoneId = convMap2Zone(m_mapId);
    if (zoneId == 0) {
        return false;
    }
    setNumber(GfDataDevelop::getPoint(zoneId));
    return true;
}

bool GfMenuWorldMapAdapter::update_DevelopLvIcon() {
    unsigned int zoneId = convMap2Zone(m_mapId);
    if (zoneId == 0) {
        return false;
    }
    setNumber(GfDataDevelop::getLevel(zoneId));
    return true;
}

bool GfMenuWorldMapAdapter::update_CurrentDisp() {
    return m_mapId == GfGameManager::getMapID();
}

GfMenuWorldMapAdapter* GfMenuWorldMapAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                                 IConverter* converter, bool changed) {
    if (handle == 0) {
        return nullptr;
    }
    GfMenuWorldMapAdapter* adapter = create(handle, type, converter->getMapId(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuWorldMapAdapter* GfMenuWorldMapAdapter::createFromList(unsigned int handle, unsigned int type,
                                                             GfMenuIDList* list, int index, bool onPage,
                                                             bool changed) {
    if (handle == 0) {
        return nullptr;
    }
#line 257
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListConverter(list, index, onPage);
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuWorldMapAdapter* GfMenuWorldMapAdapter::fn_710034D118(unsigned int handle, unsigned int type,
                                                            GfMenuIDList* list, int index, bool onPage,
                                                            bool changed) {
    if (handle == 0) {
        return nullptr;
    }
#line 266
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuMissionAdapter::MissionListConverter(list, index, onPage);
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuWorldMapAdapter* GfMenuWorldMapAdapter::createFromReference(unsigned int handle, unsigned int type,
                                                                  bool changed) {
    if (handle == 0) {
        return nullptr;
    }
#line 276
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceConverter();
    return createFromCoverter(handle, type, converter, changed);
}

void GfMenuWorldMapAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int mapId = m_converter->getMapId();
        if (m_mapId != mapId) {
            m_mapId = mapId;
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

}  // namespace gf
