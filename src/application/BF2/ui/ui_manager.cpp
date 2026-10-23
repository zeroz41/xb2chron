#include "layer/LayerAccObjBase.h"
#include "classes/ui/UIDisplayInfo.h"
#include "classes/ui/UIObjectBase.h"
#include "classes/ui/UIObjectParam.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectAcc.h"
#include "layer/LayerBase.h"
#include "layer/LayerAccMemObj.h"
#include "layer/LayerAccFontObj.h"
#include "layer/LayerAccManager.h"
#include "mm/mtl/Hash.h"
#include "ui/UIUtil.h"

namespace ui {

// the layer's centre type for each display mode (UIObject::apply)
static const layer::LayerCenterType s_centerTypes[] = {(layer::LayerCenterType)0, (layer::LayerCenterType)2};
// the layer's blend type for each blend type (UIObject::setBlendType)
static const layer::LayerBlendType s_blendTypes[] = {(layer::LayerBlendType)0, (layer::LayerBlendType)1};

UIObject::UIObject(layer::LayerBase* layer, const mm::mtl::FixStr<32>& name, unsigned int type)
    : UIObjectBase(name), m_layer(layer), m_layerAcc(layer), m_type(type), pad_DA(0), m_parent(0), m_plugins(nullptr) {
    m_handle = UIUtil::registObject(this);
    m_nameHash = mm::mtl::hashStrCrc(m_name.m_str);
}

void UIObject::update() {
    if ((m_flags & 0x18) == 0x10) {
        UIObject* parent = UIUtil::getObject(m_parent);
        if ((parent->m_flags >> 3) & 1) {
            setTerm();
            return;
        }
    }
    if (!((m_flags >> 15) & 1) && m_displayInfo.m_disp) {
        UIObjectBase::update();
    }
}

UIObject* UIObject::getParentPtr() const {
    if (m_parent == 0) {
        return nullptr;
    }
    return UIUtil::getObject(m_parent);
}

void UIObject::updatePlugin() {
    UIObjectAcc acc(this);
    for (UIObjectPlugin* plugin = m_plugins; plugin != nullptr; plugin = plugin->m_next) {
        if (plugin->isNeedUpdate(acc)) {
            plugin->execute(acc);
        }
    }
}

void UIObject::setParent(unsigned int handle) {
    if (m_parent != handle) {
        m_parent = handle;
    }
}

void UIObject::getPos(mm::Pnt<short>& pos) const {
    pos = m_transform.m_pos;
    mm::Pnt<short> offset;
    getDisplayOffset(0, offset);
    pos.x += offset.x;
    pos.y += offset.y;
}

void UIObject::getPosCenter(mm::Pnt<short>& pos) const {
    pos = m_transform.m_pos;
    mm::Pnt<short> offset;
    getDisplayOffset(1, offset);
    pos.x += offset.x;
    pos.y += offset.y;
}

void UIObject::setPos(const mm::Pnt<short>& pos) {
    short x = pos.x;
    short y = pos.y;
    mm::Pnt<short> offset;
    getDisplayOffset(0, offset);
    m_transform.setPos(x - offset.x, y - offset.y);
}

void UIObject::setPosCenter(const mm::Pnt<short>& pos) {
    short x = pos.x;
    short y = pos.y;
    mm::Pnt<short> offset;
    getDisplayOffset(1, offset);
    m_transform.setPos(x - offset.x, y - offset.y);
}

void UIObject::resetDirty() {
    m_transform.m_changed = false;
    m_displayInfo.m_changed = false;
}

void UIObject::attachPlugin(UIObjectPlugin* plugin) {
    plugin->m_next = m_plugins;
    m_plugins = plugin;
    plugin->addRef();
}

void UIObject::registAdditionalParam(UIObjectParam* param) {
    if (param != nullptr) {
        mm::mtl::IntrusiveListBase::linkNode(param, &m_params.m_root);
        ++m_params.m_size;
    }
}

void UIObject::getDisplayOffset(unsigned short mode, mm::Pnt<short>& offset) const {
    offset.x = 0;
    offset.y = 0;
    unsigned short width = m_displayInfo.m_pixelWidth * m_transform.m_scaleX;
    unsigned short height = m_displayInfo.m_pixelHeight * m_transform.m_scaleY;
    if (m_displayInfo.m_center == 0) {
        if (mode == 1) {
            offset.x = width >> 1;
            offset.y = height >> 1;
        }
    } else if (m_displayInfo.m_center == 1) {
        if (mode == 0) {
            offset.x = -(width >> 1);
            offset.y = -(height >> 1);
        }
    }
}

void UIObject::setBlendType(unsigned short type) {
    m_displayInfo.m_blendType = type;
    m_layerAcc.setBlendType(s_blendTypes[type]);
}

void UIObject::setPriority(unsigned short priority) {
    m_displayInfo.m_priority = priority;
}

void UIObject::setAddColor(const mm::Col3& color) {
    m_displayInfo.m_addColor = color;
}

bool UIObject::isDebugDraw() const {
    return false;
}

void UIObject::importDisplaySize(UIDisplayInfo& info, layer::LayerBase* layer) {
    layer::LayerAccObjBase acc(layer);
    if (layer->m_objType == 2) {
        layer::LayerAccFontObj font(layer);
        info.setPixelWidth(font.getFontPixelWidth());
        info.setPixelHeight(font.getFontPixelHeight());
        info.m_changed = true;
    } else if (layer->m_objType == 5) {
        layer::LayerAccMemObj mem(layer);
        info.setPixelWidth(mem.getMemWidth());
        info.setPixelHeight(mem.getMemHeight());
    } else {
        info.setPixelWidth(acc.getPixelWidth());
        info.setPixelHeight(acc.getPixelHeight());
    }
}

void UIObject::importDisplayInfo(UIDisplayInfo& info, layer::LayerBase* layer) {
    layer::LayerAccObjBase acc(layer);
    importDisplaySize(info, layer);
    if (acc.getCenterType() == 0) {
        info.m_center = 0;
    } else if (acc.getCenterType() == 2) {
        info.m_center = 1;
    }
    mm::Col4 color = acc.getMulCol();
    info.m_mulColor = color;
}

mm::mtl::RTTI UIObject::m_rtti("UIObject", nullptr, nullptr);

}  // namespace ui
