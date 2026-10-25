#ifndef CLASSES_GF_TGFTWEEN_H
#define CLASSES_GF_TGFTWEEN_H

namespace gf {
// a template: 1 instances in the module. Eases from one value to another over a duration
// (GfFieldMoveSpeed's speed); the member names are not the original's
template <typename T0>
class TGfTween {
public:
    TGfTween() : m_duration(0.5f), m_time(0.0f) {}
    virtual ~TGfTween() {}  // slot 0

    T0 m_from;
    T0 m_to;
    float m_duration;
    float m_time;
};
}  // namespace gf

#endif
