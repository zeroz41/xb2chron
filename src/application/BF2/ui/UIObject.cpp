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

// the layer's blend type for each blend type (UIObject::setBlendType)
static const layer::LayerBlendType s_blendTypes[] = {(layer::LayerBlendType)0, (layer::LayerBlendType)1};

UIObject::UIObject(layer::LayerBase* layer, const mm::mtl::FixStr<32>& name, unsigned int type)
    : UIObjectBase(name), m_layer(layer), m_layerAcc(layer), m_type(type), m_duplicateCount(0), m_parent(0), m_plugins(nullptr) {
    m_handle = UIUtil::registObject(this);
    m_nameHash = mm::mtl::hashStrCrc(m_name.m_str);
}

UIObject::~UIObject() {
    if (m_layer != nullptr) {
        m_layer->release();
        m_layer = nullptr;
    }
    for (mm::mtl::IntrusiveList<UIObjectParam>::iterator it = m_params.begin(); it != m_params.end(); ++it) {
        (*it).m_handle = 0;
    }
    UIObjectPlugin* plugin = m_plugins;
    while (plugin != nullptr) {
        UIObjectPlugin* next = plugin->m_next;
        plugin->release();
        plugin = next;
    }
    m_plugins = nullptr;
}

void UIObject::update() {
    if (m_flags.test(4) && !m_flags.test(3)) {
        UIObject* parent = UIUtil::getObject(m_parent);
        if (parent->m_flags.test(3)) {
            setTerm();
            return;
        }
    }
    if (!m_flags.test(15) && m_displayInfo.m_disp) {
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

void UIObject::applyTransform(const UIObjectParam::AdditionalParam&) {
    layer::LayerBase* layer = m_layer;
    layer::LayerAccManager manager;
    const mm::Pnt<short>& pos = m_transform.m_pos;
    float x = pos.x;
    float y = pos.y;
    if (m_type == 1 && m_displayInfo.m_center == 1) {
        layer::LayerAccFontObj font(m_layer);
        if (font.getDisplayArea() == 0) {
            x = x - m_displayInfo.m_pixelWidth / 2U + font.getPixelWidth() / 2U;
            y += (font.getPixelHeight() >> 1) - (m_displayInfo.m_pixelHeight >> 1);
        }
    }
    mm::Vec2 offs;
    getTransformPosOffs(offs);
    x += offs.x;
    y += offs.y;
    if (manager.getCoordinate() == 1) {
        x /= manager.getScreenWidth();
        y /= manager.getScreenWidth();
    }
    m_layerAcc.setPos(x, y);
    float scaleX = m_transform.m_scale.x;
    float scaleY = m_transform.m_scale.y;
    if (manager.getCoordinate() == 1 && layer->m_objType == 1) {
        float ratio = m_layerAcc.getPixelWidth() / manager.getScreenWidth();
        scaleX *= ratio;
        scaleY *= ratio;
    }
    m_layerAcc.setScale(scaleX, scaleY);
    m_layerAcc.setRot(m_flags.test(10) ? 0.0f : m_transform.m_rotation);
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
    unsigned short width = m_displayInfo.m_pixelWidth * m_transform.m_scale.x;
    unsigned short height = m_displayInfo.m_pixelHeight * m_transform.m_scale.y;
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

void UIObject::importTransform(UITransform& transform, layer::LayerBase* layer) {
    float rot;
    layer::LayerAccManager manager;
    layer::LayerAccObjBase acc(layer);
    float aspect = manager.getScreenWidth() / manager.getScreenHeight();
    float pos[2];
    acc.getPos(pos[0], pos[1]);
    float scale[2];
    acc.getScale(scale[0], scale[1]);
    acc.getRot(rot);
    if (layer->m_objType == 1 && manager.getCoordinate() == 1) {
        float ratio = acc.getPixelWidth() / manager.getScreenWidth();
        scale[0] /= ratio;
        scale[1] /= ratio;
    }
    if (manager.getCoordinate() == 1) {
        transform.setPos(pos[0] * manager.getScreenWidth(), aspect * (pos[1] * manager.getScreenHeight()));
    } else {
        transform.setPos(pos[0], pos[1]);
    }
    transform.setScale(scale[0], scale[1]);
    transform.m_rotation = rot;
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
