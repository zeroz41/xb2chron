#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuPosAdapter.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectPlugin.h"
#include "fw/Transform.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "gf/GfUtil.h"
#include "gf/MenuOffset.h"
#include "mm/Pnt.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"

namespace gf {

GfMenuPosAdapter::~GfMenuPosAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuPosAdapter* GfMenuPosAdapter::create(unsigned int handle, GF_OBJ_HANDLE* object, const MenuOffset* offset) {
    GfMenuAdapter::PluginSetup setup;
    setup.m_type = 4;
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 103
    GfMenuPosAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuPosAdapter(plugin);
    if (adapter != nullptr) {
        adapter->setup(object, offset);
        adapter->m_pos = adapter->m_offset;
    }
    plugin->release();
    return adapter;
}

GfMenuPosAdapter* GfMenuPosAdapter::createDiffOffset(unsigned int handle, GF_OBJ_HANDLE* object,
                                                     const MenuOffset* offset, unsigned short limitX,
                                                     unsigned short limitY) {
    GfMenuAdapter::PluginSetup setup;
    setup.m_type = 6;
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 131
    GfMenuPosAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuPosAdapter(plugin);
    if (adapter != nullptr) {
        adapter->setup(object, offset);
        adapter->m_pos = adapter->m_offset;
        adapter->m_diffOffset = true;
        adapter->setOffsetLimit(limitX, limitY);
    }
    plugin->release();
    return adapter;
}

GfMenuPosAdapter* GfMenuPosAdapter::createFixedPoint(unsigned int handle, const mm::Vec3& pos, bool world) {
    GfMenuAdapter::PluginSetup setup;
    setup.m_type = 4;
    if (world) {
        setup.m_type = 5;
    }
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 210
    GfMenuPosAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuPosAdapter(plugin);
    if (adapter != nullptr) {
        adapter->setup(reinterpret_cast<GF_OBJ_HANDLE*>(-1), nullptr);
        adapter->m_pos = pos;
        adapter->m_world = world;
        adapter->m_fixedPoint = true;
    }
    plugin->release();
    return adapter;
}

void GfMenuPosAdapter::changeReference(GF_OBJ_HANDLE* object, const MenuOffset* offset) {
    setup(object, offset);
}

// update: not written yet (its candidate schedules the new position stores apart)

}  // namespace gf
