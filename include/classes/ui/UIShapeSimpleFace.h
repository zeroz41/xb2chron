#ifndef CLASSES_UI_UISHAPESIMPLEFACE_H
#define CLASSES_UI_UISHAPESIMPLEFACE_H

namespace ui {
// table 0x7100B75430
class UIShapeSimpleFace {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~UIShapeSimpleFace();  // slot 1
    virtual void update(unsigned int);  // slot 3
};
}  // namespace ui

#endif
