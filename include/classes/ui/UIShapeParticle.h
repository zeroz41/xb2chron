#ifndef CLASSES_UI_UISHAPEPARTICLE_H
#define CLASSES_UI_UISHAPEPARTICLE_H

namespace ui {
// table 0x7100B753D0
class UIShapeParticle {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~UIShapeParticle();  // slot 1
    virtual void update(unsigned int);  // slot 3
};
}  // namespace ui

#endif
