#ifndef CLASSES_EVENT_CHARAWINKPLAYER_H
#define CLASSES_EVENT_CHARAWINKPLAYER_H

namespace event { class CharaWeightPlayer; }

namespace event {
// table 0x7100B3CD10
class CharaWinkPlayer {
public:
    CharaWinkPlayer() : m_flags(0), m_weightPlayer(nullptr), m_state(nullptr), m_stateName("") {}
    virtual ~CharaWinkPlayer() {}  // slot 0
    // the blink states (1.0.0 names them; 3.0.1 keeps them out of line)
    void idle_start();
    void idle_waiting();
    void idle_wink();
    // the names below are not the original's
    unsigned int m_flags;  // 0x8; bit 0: idle_waiting does nothing
    CharaWeightPlayer* m_weightPlayer;  // 0x10; plays the eye close/open eases
    void (CharaWinkPlayer::*m_state)();  // 0x18; the running idle_* state
    int m_count;  // 0x28; frames until the next step
    const char* m_stateName;  // 0x30; "close", ...
};
}  // namespace event

#endif
