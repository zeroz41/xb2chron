#ifndef CLASSES_UI_UIDISPLAYINFO_H
#define CLASSES_UI_UIDISPLAYINFO_H

#include "mm/Col3.h"
#include "mm/Col4.h"

namespace ui {
// table 0x7100B75638
class UIDisplayInfo {
public:
    // the colours saveDefColor keeps for loadDefColor (the name is not the original's)
    struct DefColor {
        mm::Col3 m_mulColor;
        mm::Col3 m_addColor;
    };

    UIDisplayInfo();
    virtual ~UIDisplayInfo();  // slot 0
    void operator=(const UIDisplayInfo& other);  // returns nothing: the original leaves x0 alone
    void saveDefColor();
    void syncParent();
    void setDisp(bool disp);
    void loadDefColor();
    void linkColor(const UIDisplayInfo* info);
    void setPixelWidth(unsigned short width);
    void setPixelHeight(unsigned short height);
    // the info whose colours this one shows: the end of the linkColor chain (the name is not the original's)
    const UIDisplayInfo* getColorInfo() const {
        if (m_linkColor != nullptr) {
            return m_linkColor->getColorInfo();
        }
        return this;
    }

    bool m_disp;                     // setDisp's
    unsigned char m_center;          // 1: the object is placed by its center (UIObject::importDisplayInfo, from the
                                     //   layer's center type 2; 0 for type 0)
    unsigned char pad_0A;
    unsigned short m_priority;       // UIObjectAcc::getDispPriority and UIObject::setPriority
    mm::Col4 m_mulColor;             // UIObject::importDisplayInfo's: the layer's multiply colour
    mm::Col3 m_addColor;             // UIObject::setAddColor's
    unsigned short m_pixelWidth;     // setPixelWidth's
    unsigned short m_pixelHeight;    // setPixelHeight's
    bool m_changed;                  // the setters set it when a value changes (the name is not the original's)
    DefColor* m_defColor;            // saveDefColor's, allocated on first use
    const UIDisplayInfo* m_linkColor;  // linkColor's: the info whose colours this one shows
};
}  // namespace ui

#endif
