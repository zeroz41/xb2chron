#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"

namespace gf {

GfMenuReferenceAdapter::~GfMenuReferenceAdapter() {
    m_reference = nullptr;
}

GfMenuReferenceAdapter* GfMenuReferenceAdapter::create(unsigned int handle,
                                                       mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference,
                                                       bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    GfMenuAdapter::PluginSetup setup;
    setup.m_type = 0;
    setup.m_min = reference->m_min;
    setup.m_max = reference->m_max;
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 52
    GfMenuReferenceAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuReferenceAdapter(plugin, changed);
    if (adapter == nullptr) {
        plugin->release();
        return nullptr;
    }
    adapter->m_reference = reference;
    plugin->release();
    return adapter;
}

void GfMenuReferenceAdapter::update(const fw::UpdateInfo& info) {
    if ((m_flags & 3) == 0) {
        bool changed = m_number != m_reference->m_value;
        changed |= m_max != m_reference->m_max;
        changed |= m_min != m_reference->m_min;
        if (!changed) {
            return;
        }
    }
    int number = m_reference->m_value + m_offset;
    setNumberMax(m_reference->m_max);
    setNumberMin(m_reference->m_min);
    setNumber(number);
    m_number = number;
    m_max = m_reference->m_max;
    m_min = m_reference->m_min;
    setDisp(number >= m_reference->m_min && number <= m_reference->m_max);
    m_flags &= ~1;
}

}  // namespace gf
