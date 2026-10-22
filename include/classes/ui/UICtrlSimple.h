#ifndef CLASSES_UI_UICTRLSIMPLE_H
#define CLASSES_UI_UICTRLSIMPLE_H

#include "ui/UIUtil.h"
#include <string.h>

#include "classes/ui/UICtrlCurve.h"

namespace ui {
// N floats, each moving between its range's ends over m_duration along a curve (1.0.0 has UICtrlSimple<4>::update
// and UICtrlSimple<9>::update, which read each value's two ends side by side and the values after them);
// UIObjectDispPlugin fades its alpha with a UICtrlSimple<1>. The names are not the original's:
// UICtrlSimpleUpdater<UICtrlSimple<1>>::updateCtrl shows what each field does
template <int N>
class UICtrlSimple {
public:
    class Range {
    public:
        float m_start;
        float m_end;
    };
    // the ranges and values are zeroed as one block, the values again one by one (1.0.0's
    // mm::mtl::Array<UICtrlSimple<4>>::reserve, UICtrlCursorSelect's and UICtrlRevolveSelect's constructors)
    UICtrlSimple()
        : m_range(), m_value(), m_curve(nullptr), m_time(0.0f), m_duration(0.0f), m_speed(1.0f), m_loop(false), m_pause(false) {
        for (int i = 0; i < N; i++) {
            m_value[i] = 0.0f;
        }
    }
    // starts each value at its range's start, moving to its end over duration along the curve of type (the name
    // is not the original's; UIObjectDispPlugin::setDisp holds it)
    void start(const Range* range, float duration, CURVE_TYPE type) {
        m_time = 0.0f;
        m_duration = duration;
        m_speed = 1.0f;
        m_curve = UIUtil::getCurve(type);
        // the ranges are copied as one block: UICtrlCursorSelect::setSelIndex stores each end from its own register
        memcpy(m_range, range, sizeof(m_range));
        for (int i = 0; i < N; i++) {
            m_value[i] = m_range[i].m_start;
        }
        m_loop = false;
    }
    // moves m_time on by step times m_speed and the values with it (1.0.0 has UICtrlSimple<4>::update and
    // UICtrlSimple<9>::update out of line)
    void update(float step) {
        if (step != 0.0f && m_time != m_duration && !m_pause) {
            m_time = m_time + step * m_speed;
            if (m_time >= m_duration) {
                if (m_loop) {
                    m_time -= m_duration;
                } else {
                    m_time = m_duration;
                }
            }
            float rate = m_curve != nullptr ? m_curve->calc(m_time, 0.0f, 1.0f, m_duration) : m_time / m_duration;
            for (int i = 0; i < N; i++) {
                m_value[i] = m_range[i].m_start + rate * (m_range[i].m_end - m_range[i].m_start);
            }
        }
    }
    bool isBusy() const { return m_time != m_duration; }

    Range m_range[N];
    float m_value[N];            // m_start + curve(m_time) * (m_end - m_start)
    const UICtrlCurve* m_curve;  // m_time / m_duration when there is none
    float m_time;                // advances by the frame's time step times m_speed up to m_duration
    float m_duration;
    float m_speed;
    bool m_loop;   // at m_duration, m_time wraps instead of stopping
    bool m_pause;  // m_time does not advance
};
}  // namespace ui

#endif
