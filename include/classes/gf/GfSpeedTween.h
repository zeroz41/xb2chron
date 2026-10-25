#ifndef CLASSES_GF_GFSPEEDTWEEN_H
#define CLASSES_GF_GFSPEEDTWEEN_H

namespace gf {
// table 0x7100B566A0. Moves a value towards a target at a fixed rate per second (GfEnemyFieldMoveSpeed's
// speed); the member names are not the original's
class GfSpeedTween {
public:
    GfSpeedTween() : m_from(0.0f), m_to(1.0f), m_value(0.0f), m_rate(0.5f) {}
    virtual ~GfSpeedTween() {}  // slot 0

    float m_from;
    float m_to;
    float m_value;
    float m_rate;  // per second
};
}  // namespace gf

#endif
