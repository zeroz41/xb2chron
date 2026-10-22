#include "classes/ui/UITimer.h"
#include "ui/UIUtil.h"

namespace ui {

UITimer::UITimer() : m_time(0), m_end(0), m_speedFactor(1.0f) {}

UITimer::~UITimer() {
    ;  // stores the table (a statement the build compiles away)
}

void UITimer::update(float step) {
    m_time += UIUtil::timeSecToUITime(m_speedFactor * step);
}

void UITimer::start(unsigned long end) {
    m_time = 0;
    m_end = end;
    m_speedFactor = 1.0f;
}

void UITimer::restart() {
    if (m_end != 0) {
        m_time = 0;
    }
}

void UITimer::stop() {
    m_end = 0;
}

bool UITimer::isOver() const {
    if (m_end == 0) {
        return false;
    }
    return m_time >= m_end;
}

}  // namespace ui
