#ifndef CLASSES_UI_UIDISPLAYINFO_H
#define CLASSES_UI_UIDISPLAYINFO_H

namespace ui {
// table 0x7100B75638
class UIDisplayInfo {
public:
    virtual ~UIDisplayInfo();  // slot 0
    unsigned char pad_8[0x40];  // UIObjectBase constructs one at +0x50 and its next field at +0x98
};
}  // namespace ui

#endif
