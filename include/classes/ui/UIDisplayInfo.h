#ifndef CLASSES_UI_UIDISPLAYINFO_H
#define CLASSES_UI_UIDISPLAYINFO_H

namespace ui {
// table 0x7100B75638
class UIDisplayInfo {
public:
    virtual ~UIDisplayInfo();  // slot 0
    unsigned char pad_08[0x1];
    unsigned char m_center;          // 1: the object is placed by its center (UIObject::importDisplayInfo, from the
                                     //   layer's center type 2; 0 for type 0)
    unsigned char pad_0A[0x22];
    unsigned short m_pixelWidth;     // setPixelWidth's
    unsigned short m_pixelHeight;    // setPixelHeight's
    unsigned char pad_30[0x18];      // UIObjectBase constructs one at +0x50 and its next field at +0x98
};
}  // namespace ui

#endif
