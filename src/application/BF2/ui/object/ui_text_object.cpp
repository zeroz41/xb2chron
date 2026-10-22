#include "layer/LayerAccObjBase.h"
#include "layer/LayerAccLayoutObj.h"
#include "layer/LayerAccFontObj.h"
#include "mm/Pnt.h"
#include "ui/UIStr.h"
#include "classes/ui/UIObjectBase.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UITextObject.h"
#include "classes/ui/UIFontManager.h"
#include "classes/ui/UITagParser.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UITextObject.h"
#include "classes/ui/UIFontManager.h"
#include "classes/ui/UITagParser.h"
#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/mm/mtl/IAllocator.h"
#include "layer/LayerAccLayoutObj.h"
#include "layer/LayerAccFontObj.h"
#include "mm/Vec2.h"
#include "mm/mtl/FixStr.h"
#include "ui/UIStr.h"
#include "ui/UIUtil.h"

namespace ui {

// inline: 3.0.1 keeps no copy of it (create inlines it)
inline UITextObject::UITextObject(layer::LayerBase* layer, const mm::mtl::FixStr<32>& name)
    : UIObject(layer, name, 1) {
    m_style = 0xFFFF;
    m_facePattern = -1;
}

UITextObject::~UITextObject() {}

UITextObject* UITextObject::create(UILayoutObject* parent, const mm::mtl::FixStr<32>& name,
                                   mm::mtl::IAllocator* allocator) {
    layer::LayerAccLayoutObj layout(parent->m_layer);
    layer::LayerBase* layer = layout.createFontObj();
    if (layer == nullptr) {
        return nullptr;
    }
    layer::LayerAccFontObj font(layer);
    font.setDisplayArea(static_cast<layer::LayerFontDisplayArea>(1));
    font.setBorderWeight(0.5f);
    font.setSlopeRot(0.20943952f);  // 12 degrees
#line 80
    return new (allocator, 16, __FILE__, __LINE__) UITextObject(layer, mm::mtl::FixStr<32>(name.m_str));
}

void UITextObject::applyText(const char* text) {
    unsigned short style = m_style;
    layer::LayerAccFontObj font(m_layer);
    unsigned short width = m_displayInfo.m_pixelWidth;
    unsigned short height = m_displayInfo.m_pixelHeight;
    if (style == 0xFFFF) {
        font.setMsg(text);
    } else {
        UIFontManager::FontRes* res = mm::mtl::PtrSingleton<UIFontManager>::get()->getFontResFromStyle(style);
        if (res == nullptr) {
            return;
        }
        font.setMsg(text, res->m_font, style);
    }
    UIObject::importDisplaySize(m_displayInfo, m_layer);
    if (m_displayInfo.m_center == 1) {
        // kept centred on the same point
        mm::Pnt<short> pos = m_transform.m_pos;
        mm::Pnt<short> topLeft(pos.x - width / 2, pos.y - height / 2);
        m_transform.setPos(topLeft.x + m_displayInfo.m_pixelWidth / 2, topLeft.y + m_displayInfo.m_pixelHeight / 2);
    }
}

inline const char* UITextObject::getBaseText() {
    return m_baseText.isValid() ? m_baseText.c_str() : nullptr;
}

void UITextObject::setText(const UIStr& text) {
    if (!text.isValid()) {
        return;
    }
    m_baseText.copy(text);
    if (m_style == 0xFFFF) {
        m_style = text.getStyle();
    }
    if (m_baseText.isValid() && m_baseText.c_str() != nullptr) {
        UITagParser* parser = mm::mtl::PtrSingleton<UITagParser>::get();
        parser->m_ownerId = text.m_ownerId;
        parser->parse(getBaseText());
        m_text.deepcopy(UIStr(mm::mtl::PtrSingleton<UITagParser>::get()->getResult(), false));
        if (m_text.isValid() && m_text.c_str() != nullptr) {
            applyText(m_text.c_str());
        }
    }
}

void UITextObject::setTextAlignH(unsigned char align) {
    if (m_layer != nullptr) {
        layer::LayerAccFontObj font(m_layer);
        if (align == 0) {
            font.setDisplayArea(static_cast<layer::LayerFontDisplayArea>(0));
            font.setHorizontal(static_cast<layer::LayerFontHorizontal>(0));
        } else if (align == 1) {
            font.setDisplayArea(static_cast<layer::LayerFontDisplayArea>(0));
            font.setHorizontal(static_cast<layer::LayerFontHorizontal>(1));
        } else if (align == 2) {
            font.setDisplayArea(static_cast<layer::LayerFontDisplayArea>(0));
            font.setHorizontal(static_cast<layer::LayerFontHorizontal>(2));
        } else {
            font.setDisplayArea(static_cast<layer::LayerFontDisplayArea>(1));
            font.setHorizontal(static_cast<layer::LayerFontHorizontal>(0));
        }
    }
}

void UITextObject::setTextAlignV(unsigned char align) {
    if (m_layer != nullptr) {
        layer::LayerAccFontObj font(m_layer);
        if (align == 0) {
            font.setVertical(static_cast<layer::LayerFontVertical>(0));
        } else if (align == 1) {
            font.setVertical(static_cast<layer::LayerFontVertical>(1));
        } else if (align == 2) {
            font.setVertical(static_cast<layer::LayerFontVertical>(2));
        } else {
            font.setVertical(static_cast<layer::LayerFontVertical>(0));
        }
    }
}

inline unsigned char UITextObject::getTextAlignH() {
    if (m_layer == nullptr) {
        return 0;
    }
    layer::LayerAccFontObj font(m_layer);
    unsigned int align = font.getHorizontal();
    return align < 3 ? align : 0;
}

inline unsigned char UITextObject::getTextAlignV() {
    if (m_layer == nullptr) {
        return 0;
    }
    layer::LayerAccFontObj font(m_layer);
    unsigned int align = font.getVertical();
    return align < 3 ? align : 0;
}

void UITextObject::setBorderWeight(float weight) {
    layer::LayerAccFontObj font(m_layer);
    font.setBorderWeight(weight + 0.5f);
}

inline float UITextObject::getBorderWeight() {
    layer::LayerAccFontObj font(m_layer);
    return font.getBorderWeight() - 0.5f;
}

void UITextObject::setSlopeRot(float rot) {
    layer::LayerAccFontObj font(m_layer);
    font.setSlopeRot(rot + 0.20943952f);
}

inline float UITextObject::getSlopeRot() {
    layer::LayerAccFontObj font(m_layer);
    return font.getSlopeRot() - 0.20943952f;
}

void UITextObject::setTextFacePattern(unsigned int pattern) {
    layer::LayerAccFontObj font(m_layer);
    font.setColorMap(mm::mtl::PtrSingleton<UIFontManager>::get()->m_colorMap, pattern);
    m_facePattern = pattern;
}

void UITextObject::reloadText() {
    if (m_baseText.m_type == 1) {
        UITagParser* parser = mm::mtl::PtrSingleton<UITagParser>::get();
        parser->m_ownerId = m_baseText.m_ownerId;
        parser->parse(getBaseText());
        m_text.deepcopy(UIStr(mm::mtl::PtrSingleton<UITagParser>::get()->getResult(), false));
        applyText(m_text.c_str());
        UIObjectPlugin* plugin = m_plugins;
        if (plugin != nullptr && plugin->getRTTI()->isKindOf(&UIObjectPlugin::m_rtti)) {
            UIObjectAcc acc(m_handle);
            plugin->reload(acc);
        }
    }
}

void UITextObject::apply() {
    UIObject::apply();
}

void UITextObject::getTransformPosOffs(mm::Vec2& offs) {
    UIObject::getTransformPosOffs(offs);
    UIFontManager::StyleInfo info;
    if (mm::mtl::PtrSingleton<UIFontManager>::get()->getFontStyleInfo(m_style, info)) {
        offs.y -= (float)(int)(info.m_offsetY * 4.0f);
    }
}

void UITextObject::getDisplayOffset(unsigned short mode, mm::Pnt<short>& offs) const {
    UIObject::getDisplayOffset(mode, offs);
    layer::LayerAccFontObj font(m_layer);
    offs.x += font.getFontPixelX();
    offs.y += font.getFontPixelY();
}

unsigned int UITextObject::duplicateImpl(unsigned int handle) {
    UILayoutObject* parent = UIUtil::getLayoutObject(handle);
    if (parent == nullptr) {
        return 0;
    }
    UITextObject* object = create(parent, mm::mtl::FixStr<32>(m_name.m_str), UIUtil::getProgAllocator());
    if (object == nullptr) {
        return 0;
    }
    object->addRef();
    object->setTextAlignH(getTextAlignH());
    object->setTextAlignV(getTextAlignV());
    object->setBorderWeight(getBorderWeight());
    object->setSlopeRot(getSlopeRot());
    object->m_style = m_style;
    if (m_facePattern != -1) {
        object->setTextFacePattern(m_facePattern);
    }
    object->setText(m_baseText);
    unsigned int child = parent->addChild(handle, object);
    object->release();
    return child;
}

mm::mtl::RTTI UITextObject::m_rtti("UITextObject", &UIObject::m_rtti, nullptr);

}  // namespace ui
