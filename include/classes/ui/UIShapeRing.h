#ifndef CLASSES_UI_UISHAPERING_H
#define CLASSES_UI_UISHAPERING_H

namespace ui {
// table 0x7100B75400
class UIShapeRing {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~UIShapeRing();  // slot 1
    virtual void update(unsigned int);  // slot 3
};
}  // namespace ui

#endif
