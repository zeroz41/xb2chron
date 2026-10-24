#ifndef CLASSES_GMK_TIMECOND_H
#define CLASSES_GMK_TIMECOND_H

namespace gmk {
// table 0x7100B524A8; GfFieldMapGimmick::BdatInfo holds one (its row's OP_Time)
class TimeCond {
public:
    TimeCond() : m_time(0xffff) {}
    bool isMatch() const;
    virtual ~TimeCond() {}  // slot 0
    int m_time;  // the row's OP_Time, 0xFFFF for none (the name is not the original's)
};
}  // namespace gmk

#endif
