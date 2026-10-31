#ifndef CLASSES_EVENT_FRAMEINFO_H
#define CLASSES_EVENT_FRAMEINFO_H

namespace event {
// what the event objects' update(FrameInfo const&) slots get each frame. No table. Only the float at 0xc is known:
// CamMotion::update, CamHands::update and CharaObj::update read it and pass it on as the step of their players'
// update(float) (the name is not the original's)
class FrameInfo {
public:
    unsigned char pad_0[0xc];
    float m_step;  // 0xc
};
}  // namespace event

#endif
