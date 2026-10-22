#include "classes/ui/UICtrlRadarGraph.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIObjectNumberPlugin.h"
#include "classes/ui/UIShapeSimpleFace.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/UpdateInfo.h"
#include "layer/LayerPolyVertex.h"
#include "mm/mtl/RTTI.h"
#include "math.h"

namespace ui {

// the destructor (0x7100670DB4, 0x7100670E0C) is not written yet: the candidate is not identical (see the worker
// report)

// create (0x7100670E6C) is not written yet: the candidate is not identical (see the worker report)

void UICtrlRadarGraph::setNumberPlugin(unsigned int index, unsigned int handle) {
    if (index >= m_values.size()) {
        return;
    }
    UIObject* object = UIUtil::getObject(handle);
    if (object == nullptr) {
        return;
    }
    UIObjectPlugin* plugin = object->m_plugins;
    if (plugin == nullptr) {
        return;
    }
    UIObjectNumberPlugin* number = mm::mtl::rttiCast<UIObjectNumberPlugin>(plugin);
    if (number == nullptr) {
        return;
    }
    m_values[index].m_number = number->m_number;
    m_values[index].m_plugin = number;
}

void UICtrlRadarGraph::update(const fw::UpdateInfo& info) {
    short width;
    short height;
    UIObjectAcc acc(m_handle);
    if (acc.m_object == nullptr) {
        return;
    }
    UIShapeSimpleFace* face = mm::mtl::rttiCast<UIShapeSimpleFace>(acc.getShape());
    unsigned int count = face->m_vertices.size();
    if (count == 0) {
        return;
    }
    layer::LayerPolyVertex vertex;
    vertex.u = 0.0f;
    vertex.r = vertex.g = vertex.b = vertex.a = 0xFF;
    vertex.v = 0.0f;
    acc.getSize(false, width, height);
    if (m_values.size() == 0) {
        return;
    }
    float step = (float)(360 / count) * 0.0174532924f;
    float angle = 1.57079637f;
    for (unsigned int i = 0; i < m_values.size(); i++) {
        Value& value = m_values[i];
        if (value.m_ctrl.isBusy()) {
            value.m_ctrl.update(info.m_deltaTime);
            value.m_number = value.m_ctrl.m_value[0];
        } else {
            value.m_number = value.m_plugin->m_number;
        }
        float rate = (float)value.m_number / (float)value.m_plugin->m_max;
        if (rate == 0.0f) {
            rate = 0.05f;
        }
        float x = cosf(angle) * rate;
        float y = -(sinf(angle) * rate);
        vertex.x = x;
        vertex.y = y;
        face->writeFaceVertex(&vertex, 1, i);
        angle += step;
    }
}

}  // namespace ui
