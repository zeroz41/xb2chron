#ifndef UI_UISTR_H
#define UI_UISTR_H

namespace ui {

// a UI text (0x18 bytes: UIObjectTextPlugin keeps one at 0x80 of its 0x98)
class UIStr {
public:
    UIStr();
    ~UIStr();
    bool isValid() const;
    bool compare(const UIStr& other);  // true when they are the same text
    void copy(const UIStr& other);
    unsigned char pad_00[0x18];
};

}  // namespace ui

#endif
