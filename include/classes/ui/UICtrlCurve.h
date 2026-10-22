#ifndef CLASSES_UI_UICTRLCURVE_H
#define CLASSES_UI_UICTRLCURVE_H

namespace ui {
// what UIUtil::getCurve hands out: one object per curve (UICtrlCurveLinear, UICtrlCurveSin90, ...), each a table
// with calc alone (no destructor, no RTTI); the name of this base is not the original's (no symbol names it)
class UICtrlCurve {
public:
    // the curve's value at time of duration, between from and to: UICtrlSimpleUpdater passes (time, 0, 1,
    // duration); UICtrlCurveLinear returns time / duration
    virtual float calc(float time, float from, float to, float duration) const = 0;  // slot 0
};
}  // namespace ui

#endif
