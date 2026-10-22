#ifndef CLASSES_UI_UITEXTOBJECT_H
#define CLASSES_UI_UITEXTOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObject.h"
#include "ui/UIStr.h"

namespace mm { class Vec2; }
namespace mm { template <typename> class Pnt; }
namespace mm { namespace mtl { class IAllocator; } }
namespace layer { class LayerBase; }
namespace ui { class UILayoutObject; }

namespace ui {
// table 0x7100B74F58; a text: a font layer object showing a UI text after its tags are parsed
class UITextObject : public ::ui::UIObject {
public:
    // 1.0.0's is out of line (0x71006E1E20); 3.0.1's create inlines it
    UITextObject(layer::LayerBase* layer, const mm::mtl::FixStr<32>& name);
    virtual ~UITextObject();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 5
    virtual void apply();  // slot 6
    virtual void getDisplayOffset(unsigned short, mm::Pnt<short>&) const;  // slot 7
    virtual void getTransformPosOffs(mm::Vec2&);  // slot 8
    virtual unsigned int duplicateImpl(unsigned int);  // slot 9
    // a text object under the parent
    static UITextObject* create(UILayoutObject* parent, const mm::mtl::FixStr<32>& name,
                                mm::mtl::IAllocator* allocator);
    void applyText(const char* text);  // shows the text, in its style's font when it has one
    void setText(const UIStr& text);  // its base text, shown with its tags parsed
    // 1.0.0's getBaseText, getTextAlignH/V, getBorderWeight and getSlopeRot are out of line; 3.0.1 keeps no copy
    // (setText, reloadText and duplicateImpl inline them)
    const char* getBaseText();
    void setTextAlignH(unsigned char align);  // 0-2: left, center, right (anything else: fills its area)
    void setTextAlignV(unsigned char align);
    unsigned char getTextAlignH();
    unsigned char getTextAlignV();
    void setBorderWeight(float weight);  // over the font object's default (0.5)
    float getBorderWeight();
    void setSlopeRot(float rot);  // over the font object's default slope (12 degrees)
    float getSlopeRot();
    void setTextFacePattern(unsigned int pattern);
    void reloadText();  // parses its base text again (a message table's) and shows it
    static mm::mtl::RTTI m_rtti;
    UIStr m_baseText;  // setText's
    UIStr m_text;  // the base text with its tags parsed: what it shows
    unsigned short m_style;  // its font style (0xFFFF: none; setText takes its text's when it has none)
    unsigned char pad_13A[0x2];
    int m_facePattern;  // setTextFacePattern's (-1: none)
};
}  // namespace ui

#endif
