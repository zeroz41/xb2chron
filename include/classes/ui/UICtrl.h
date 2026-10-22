#ifndef CLASSES_UI_UICTRL_H
#define CLASSES_UI_UICTRL_H

#include "mm/mtl/FixedVector.h"

namespace ui { class UIObject; }
namespace ui { class UICtrlMethod; }
namespace ui { class UICtrlCurve; }

namespace ui {
// table 0x7100B74400; a run of up to 5 methods on an object over a time (UICtrlManager holds one per control slot
// and updates it while the object is valid). The field names are not the original's.
class UICtrl {
public:
    // a method and the curve its rate follows (none: linear)
    struct Method {
        UICtrlMethod* m_method;
        const UICtrlCurve* m_curve;
    };
    UICtrl();
    virtual ~UICtrl();  // slot 0
    void update(float step);
    void stop();
    void start(UIObject* object, float duration, const mm::mtl::FixedVector<Method, 5>& methods, bool loop);

    UIObject* m_object;  // a reference held while it runs
    float m_time;        // advances by the step times m_speed up to m_duration
    float m_unused;      // zeroed by the constructor, start and stop; nothing in 3.0.1 reads it
    float m_duration;
    bool m_loop;         // at m_duration, m_time wraps instead of stopping
    int m_loopCount;     // counts the wraps
    mm::mtl::FixedVector<Method, 5> m_methods;
    float m_speed;
};
}  // namespace ui

#endif
