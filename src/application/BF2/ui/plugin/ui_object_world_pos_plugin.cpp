#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPosPlugin.h"
#include "classes/ui/UIObjectWorldPosPlugin.h"
#include "layer/LayerAccObjBase.h"
#include "ui/UIObjectPluginUtil.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UIObject.h"
#include "mm/Mat44.h"
#include "ui/UIUtil.h"

namespace ui {

UIObjectWorldPosPlugin::~UIObjectWorldPosPlugin() {
    ;  // the original stores the table before the base's destructor; clang drops the store for an empty body
}

UIObjectWorldPosPlugin* UIObjectWorldPosPlugin::create(unsigned int handle) {
#line 44
    UIObjectWorldPosPlugin* plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectWorldPosPlugin();
    plugin->addRef();
    if (UIObjectPluginUtil::attachPlugin(handle, plugin)) {
        layer::LayerAccObjBase acc(UIUtil::getObject(handle)->m_layer);
        acc.setSpace(layer::LAYER_SPACE_TYPE(1));
    } else if (plugin != nullptr) {
        plugin->release();
        plugin = nullptr;
    }
    return plugin;
}

void UIObjectWorldPosPlugin::execute(UIObjectAcc& acc) {
    UIObjectPosPlugin::execute(acc);
    UIUtil::getObject(acc.m_handle);
    mm::Vec3 pos = m_worldPos;
    mm::Mat44 matrix;
    matrix.m[0][0] = 1.0f;
    matrix.m[0][1] = 0.0f;
    matrix.m[0][2] = 0.0f;
    matrix.m[0][3] = 0.0f;
    matrix.m[1][0] = 0.0f;
    matrix.m[1][1] = 1.0f;
    matrix.m[1][2] = 0.0f;
    matrix.m[1][3] = 0.0f;
    matrix.m[2][0] = 0.0f;
    matrix.m[2][1] = 0.0f;
    matrix.m[2][2] = 1.0f;
    matrix.m[2][3] = 0.0f;
    matrix.m[3][0] = pos.x;
    matrix.m[3][1] = pos.y;
    matrix.m[3][2] = pos.z;
    matrix.m[3][3] = 1.0f;
    acc.setMatrix(matrix);
}

mm::mtl::RTTI UIObjectWorldPosPlugin::m_rtti("UIObjectWorldPosPlugin", &UIObjectPosPlugin::m_rtti, nullptr);

}  // namespace ui
