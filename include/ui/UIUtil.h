#ifndef UI_UIUTIL_H
#define UI_UIUTIL_H

#include "fw/LangUtil.h"

namespace mm { namespace mtl { class IAllocator; } }

namespace fw { struct PadData; }
namespace ui { class UIObject; }
namespace ui { class UICtrlCurve; }
namespace ui { class UILayoutObject; }
namespace mm { template <typename> class Rect; }

namespace ui {
// which curve UIUtil::getCurve hands out; the enumerators' names are not the original's, they follow the curve
// classes (1.0.0's names) getCurve returns for each value
enum CURVE_TYPE {
    CURVE_LINEAR,
    CURVE_SIN90,
    CURVE_SIN90_REV,
    CURVE_LINEAR_LOOP,
    CURVE_SIN180,
    CURVE_SIN180_REV,
};
}  // namespace ui

namespace ui { namespace UIUtil {
const UICtrlCurve* getCurve(CURVE_TYPE type);  // null for an unknown type
// true when text is a format for count numbers (UIObjectNumberPlugin and UIObjectTimePlugin take the text's own)
bool checkNumberTextFormat(const char* text, unsigned int count);
char getMoneySeparetor(fw::LangType lang);  // the thousands separator of lang's money, 0 for none
mm::mtl::IAllocator* getProgAllocator();
UIObject* getObject(unsigned int handle);
bool isValid(unsigned int handle);
bool isTerm(unsigned int handle);
UILayoutObject* getLayoutObject(unsigned int handle);  // null when the handle is no layout object's
unsigned long timeSecToUITime(float sec);  // seconds in UI time units
bool adjustScreen(mm::Rect<short>& rect);  // true when it had to move the rectangle onto the screen
// true when it had to move rect into area (UIObjectDockPlugin's execute keeps its object inside its area)
bool adjustRect(mm::Rect<short>& rect, mm::Rect<short>& area);
unsigned int registObject(UIObject* object);  // the handle its object map gives it
// puts the object handle against a side of the object target (0: on its center, 1: left, 2: right, 3: above,
// 4: below), target's rectangle taken by getRect mode 3 when outer, 2 otherwise (the parameter names are not the
// original's)
void setDockPos(unsigned int handle, unsigned int target, unsigned char side, bool outer);
const fw::PadData* getPadData();  // the pad the UI reads this frame (UIManager's, else the control pad's)
unsigned int convUIPadToFWPad(int pad, bool);  // a UI pad button's fw::PadData bits
}}  // namespace ui::UIUtil

#endif
