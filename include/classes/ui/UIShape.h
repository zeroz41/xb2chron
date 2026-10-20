#ifndef CLASSES_UI_UISHAPE_H
#define CLASSES_UI_UISHAPE_H

namespace ui {
// table 0x7100B753A0
class UIShape {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~UIShape();  // slot 1
    virtual void update(unsigned int);  // slot 3
};
}  // namespace ui

#endif
