#ifndef CLASSES_UI_UIFONTMANAGER_H
#define CLASSES_UI_UIFONTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIFontManager; }
namespace layer { class LayerBase; }

namespace ui {
// table 0x7100B74A90
class UIFontManager : public ::mm::mtl::PtrSingleton< ::ui::UIFontManager> {
public:
    // a loaded font (getFontResFromStyle's; the names are not the original's)
    struct FontRes {
        unsigned char pad_0[0x8];
        layer::LayerBase* m_font;  // its font resource object (UITextObject::applyText draws with it)
    };
    // a font style's values (getFontStyleInfo copies two of them from the style object; the field name is not the
    // original's)
    struct StyleInfo {
        unsigned char pad_0[0x4];
        float m_offsetY;  // UITextObject::getTransformPosOffs moves its text up by four times it
    };
    virtual ~UIFontManager();  // slot 0
    FontRes* getFontResFromStyle(unsigned short style);  // null when no loaded font is the style's
    bool getFontStyleInfo(unsigned short style, StyleInfo& info);  // false for no such style
    bool findFacePattern(const char* name, unsigned int& index);  // false when no pattern has that name
    unsigned char pad_08[0x90];
    layer::LayerBase* m_colorMap;  // the face patterns' colour map object (UITextObject::setTextFacePattern's)
};
}  // namespace ui

#endif
