#ifndef CLASSES_EVENT_FRAMEINFO_H
#define CLASSES_EVENT_FRAMEINFO_H

namespace event {
// what the event objects' update(FrameInfo const&) slots get each frame. No table. The float at 0xc:
// CamMotion::update, CamHands::update and CharaObj::update read it and pass it on as the step of their players'
// update(float) (the name is not the original's). CharaObj::update copies all 0x14 bytes into CharaObj (0x3030).
class FrameInfo {
public:
    unsigned char pad_0[0x8];
    // CharaPlayTalkAuto/CharaPlayActionAuto::update count their time down by it (through CharaObj's copy); the
    // name is not the original's
    float m_cmdStep;  // 0x8
    float m_step;  // 0xc
    unsigned char pad_10[0x4];
};
}  // namespace event

#endif
