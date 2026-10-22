#ifndef CLASSES_UI_UITIMER_H
#define CLASSES_UI_UITIMER_H

namespace ui {
// table 0x7100B75598; a time UITimerManager counts in UI time units until its end
class UITimer {
public:
    UITimer();
    virtual ~UITimer();  // slot 0
    void update(float step);  // the step in seconds, times m_speedFactor
    void start(unsigned long end);
    void restart();
    void stop();
    bool isOver() const;
    unsigned long m_time;  // the time counted since start
    unsigned long m_end;   // start's; 0 once stopped
    float m_speedFactor;   // UITimerManager::setTimerSpeedFactor
};
}  // namespace ui

#endif
