#ifndef CLASSES_UI_UIFONTMANAGER_H
#define CLASSES_UI_UIFONTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/Vector.h"

namespace ui { class UIFontManager; }
namespace ui { class UIResource; }
namespace layer { class LayerBase; }
namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B74A90
class UIFontManager : public ::mm::mtl::PtrSingleton< ::ui::UIFontManager> {
public:
    // a loaded font object (the names are not the original's)
    struct FontRes {
        unsigned short m_id;  // its row in the font table (the font set table's "resource")
        unsigned int m_hash;  // mm::mtl::hashStrCrc of its file name; getFontResFromStyle looks it up by it
        layer::LayerBase* m_font;  // its font resource object (UITextObject::applyText draws with it)
    };
    // a face pattern: a name's colour-map image (the names are not the original's)
    struct FacePattern {
        FacePattern(unsigned int hash, unsigned int imageNo) : m_hash(hash), m_imageNo(imageNo) {}
        unsigned int m_hash;  // mm::mtl::hashStrCrc of its "name"
        unsigned int m_imageNo;  // its "image_no": what findFacePattern hands out
    };
    // a font style's values (getFontStyleInfo copies two of them from the style object; the names are not the
    // original's)
    struct StyleInfo {
        float m_offsetX;  // the value beside m_offsetY (inferred from that pairing)
        float m_offsetY;  // UITextObject::getTransformPosOffs moves its text up by four times it
    };
    UIFontManager();
    virtual ~UIFontManager();  // slot 0
    void update(const fw::UpdateInfo& info);
    void importMSBP(const void* data, unsigned int size);  // the MessageStudio project's colours and icons
    void loadFontSet(const char* name, mm::mtl::IAllocator* allocator);
    bool isLoading() const;
    FontRes* getFontResFromStyle(unsigned short style);  // null when no loaded font is the style's
    bool getFontStyleInfo(unsigned short style, StyleInfo& info);  // false for no such style
    bool findFacePattern(const char* name, unsigned int& index);  // false when no pattern has that name
    UIResource* m_resource;  // loadFontSet's, counted
    mm::mtl::FixedVector<FontRes, 4> m_fontRes;  // the font set's fonts (update's)
    FontRes m_style;  // the font style object (its m_font) and its row
    bool m_loaded;  // update sets it once it has read the font set, loadFontSet clears it (the name is inferred)
    mm::mtl::Vector<FacePattern> m_facePatterns;
    layer::LayerBase* m_colorMap;  // the face patterns' colour map object (UITextObject::setTextFacePattern's)
    layer::LayerBase* m_icon;  // the font icon object (the name is inferred: LayerAccManager::createFontIconObj's)
};
}  // namespace ui

#endif
