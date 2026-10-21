#ifndef CLASSES_BTL_SHAKECAMERAELEMENT_H
#define CLASSES_BTL_SHAKECAMERAELEMENT_H

namespace btl {
// table none (its derived classes')
class ShakeCameraElement {
public:
    virtual ~ShakeCameraElement();  // slot 0
    virtual void StopEternalShake() {}  // slot 2
};
}  // namespace btl

#endif
