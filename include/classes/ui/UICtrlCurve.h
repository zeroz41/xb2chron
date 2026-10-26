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

// UIUtil::getCurve's curves, each a table with calc alone (1.0.0's names; the tables are ui/UIUtil's, calc their key
// function)
class UICtrlCurveLinear : public UICtrlCurve {
public:
    virtual float calc(float time, float from, float to, float duration) const;  // slot 0: time / duration
};
class UICtrlCurveLinearLoop : public UICtrlCurve {
public:
    // slot 0: up to 1 by half the duration, back to 0 by its end
    virtual float calc(float time, float from, float to, float duration) const;
};
class UICtrlCurveSin90 : public UICtrlCurve {
public:
    virtual float calc(float time, float from, float to, float duration) const;  // slot 0
};
class UICtrlCurveSin180 : public UICtrlCurve {
public:
    virtual float calc(float time, float from, float to, float duration) const;  // slot 0
};
class UICtrlCurveSin90Rev : public UICtrlCurve {
public:
    virtual float calc(float time, float from, float to, float duration) const;  // slot 0
};
class UICtrlCurveSin180Rev : public UICtrlCurve {
public:
    virtual float calc(float time, float from, float to, float duration) const;  // slot 0
};
}  // namespace ui

#endif
